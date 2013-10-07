/**
 * @file
 * @brief NTP client
 *
 * @date 13.07.12
 * @author Alexander Kalmuk
 * @author Ilia Vaprol
 */

#include <arpa/inet.h>
#include <assert.h>
#include <embox/cmd.h>
#include <errno.h>
#include <framework/mod/options.h>
#include <kernel/time/time.h>
#include <net/lib/ntp.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/socket.h>
#include <time.h>

#define MODOPS_TIMEOUT OPTION_GET(NUMBER, timeout)

EMBOX_CMD(exec);

static int make_socket(const struct timeval *timeout, int *out_sock) {
	int ret, sock;

	assert(timeout != NULL);
	assert(out_sock != NULL);

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock == -1) {
		ret = -errno;
		assert(ret != 0);
		return ret;
	}

	if (-1 == setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO,
				timeout, sizeof *timeout)) {
		ret = -errno;
		close(sock);
		assert(ret != 0);
		return ret;
	}

	*out_sock = sock;

	return 0;
}

static int ntpdate_exec(struct ntphdr *req, in_addr_t server_addr,
		const struct timeval *timeout, struct ntphdr *out_rep) {
	int ret, sock;
	struct sockaddr_in addr;
	socklen_t addrlen;

	assert(req != NULL);
	assert(timeout != NULL);
	assert(out_rep != NULL);

	ret = make_socket(timeout, &sock);
	if (ret != 0) {
		return ret;
	}

	/* TODO connect */
	addr.sin_family = AF_INET;
	addr.sin_port = htons(NTP_PORT);
	addr.sin_addr.s_addr = server_addr;

	if (-1 == sendto(sock, req, sizeof *req, 0,
			(struct sockaddr *)&addr, sizeof addr)) {
		ret = -errno;
		goto error;
	}

	do {
		addrlen = sizeof addr;
		ret = recvfrom(sock, out_rep, sizeof *out_rep, 0,
					(struct sockaddr *)&addr, &addrlen);
		if (ret == -1) {
			ret = -errno;
			goto error;
		}
	} while ((addr.sin_addr.s_addr != server_addr)
			|| (addr.sin_port != htons(NTP_PORT))
			|| (ret < sizeof *out_rep)
			|| ntp_mode_client(out_rep));

	ret = 0;
error:
	close(sock);
	return ret;
}

static int ntpdate_process(const struct ntphdr *rep, int only_query) {
	int ret;
	struct timespec ts;

	assert(rep != NULL);

	if (!ntp_valid_stratum(rep)) {
		printf("ntpdate_process: error: invalid stratum (%s)\n",
				ntp_stratum_error(rep));
		return 0; /* error: incorrect packet */
	}

	if (only_query) {
		/* show result */
		ret = ntp_delay(rep, &ts);
		if (ret != 0) {
			return ret;
		}
		printf("stratum %hhd, delay %ld:%ld (s:ms)\n",
				rep->stratum, ts.tv_sec,
				ts.tv_nsec / NSEC_PER_MSEC);
	}
	else {
		/* setup new time */
		ret = ntp_time(rep, &ts);
		if (ret != 0) {
			return ret;
		}
		settimeofday(&ts, NULL);
	}

	return 0;
}

static int ntpdate(in_addr_t addr, const struct timeval *timeout,
		int only_query) {
	int ret;
	struct timespec ts;
	struct ntphdr req, rep;
	struct ntp_data_l xmit_time;

	getnsofday(&ts, NULL);
	ret = ntp_timespec_to_data_l(&ts, &xmit_time);
	if (ret != 0) {
		return ret;
	}
	ret = ntp_build(&req, NTP_LI_NO_WARNING, NTP_MOD_CLIENT, 0, 0,
			0, NULL, NULL, NULL, &xmit_time);
	if (ret != 0) {
		return ret;
	}

	ret = ntpdate_exec(&req, addr, timeout, &rep);
	if (ret != 0) {
		return ret;
	}

	return ntpdate_process(&rep, only_query);
}

static int exec(int argc, char **argv) {
	int opt, only_query, timeout;
	struct timeval timeout_tv;
	in_addr_t addr;

	only_query = 0;
	timeout = MODOPS_TIMEOUT;
	getopt_init();

	while (-1 != (opt = getopt(argc, argv, "hqt:"))) {
		switch (opt) {
		default:
			return -EINVAL;
		case 'h':
			printf("Usage: %s [-q] server", argv[0]);
			return 0;
		case 'q': /* Query only - don't set the clock */
			only_query = 1;
			break;
		case 't': /* Maximum time waiting for a server response */
			if (1 != sscanf(optarg, "%d", &timeout)) {
				printf("%s: error: wrong -t argument %s\n",
						argv[0], optarg);
				return -EINVAL;
			}
			break;
		}
	}

	if (optind >= argc) {
		printf("%s: error: no server specified\n", argv[0]);
		return -EINVAL;
	}
	else if (!inet_aton(argv[optind], (struct in_addr *)&addr)) {
		printf("%s: error: invalid address %s\n", argv[0],
				argv[optind]);
		return -EINVAL;
	}

	timeout_tv.tv_sec = timeout / MSEC_PER_SEC;
	timeout_tv.tv_usec = (timeout % MSEC_PER_SEC) * USEC_PER_MSEC;

	return ntpdate(addr, &timeout_tv, only_query);
}
