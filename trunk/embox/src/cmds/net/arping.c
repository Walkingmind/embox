/**
 * @file
 * @brief Ping hosts by ARP requests/replies.
 *
 * @date 23.12.09
 * @author Nikolay Korotky
 */

#include <embox/cmd.h>

#include <hal/ipl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <net/if_ether.h>
#include <net/inetdevice.h>
#include <string.h>

#include <net/util/macaddr.h>
#include <net/l3/arp.h>
#include <net/neighbour.h>
#include <kernel/time/time.h>



EMBOX_CMD(exec);

#define DEFAULT_INTERVAL (1000 * USEC_PER_MSEC)

static void print_usage(void) {
	printf("Usage: arping [-I if] [-c cnt] host\n");
}

static int exec(int argc, char **argv) {
	int opt;
	int cnt = 4, cnt_resp = 0, i;
	struct in_device *in_dev = inetdev_get_by_name("eth0");
	struct in_addr dst;
	char dst_b[] = "xxx.xxx.xxx.xxx";
	char from_b[] = "xxx.xxx.xxx.xxx";
	struct in_addr from;
	unsigned char mac[18], hw_addr[ETH_ALEN];
	static ipl_t ipl;

	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "I:c:h:ed"))) {
		switch (opt) {
		case 'e':
			ipl_restore(ipl);
			return 0;
		case 'd':
			ipl = ipl_save();
			return 0;
		case 'I': /* get interface */
			if (NULL == (in_dev = inetdev_get_by_name(optarg))) {
				printf("arping: unknown iface %s\n", optarg);
				return -EINVAL;
			}
			break;
		case 'c': /* get ping cnt */
			if (1 != sscanf(optarg, "%d", &cnt)) {
				printf("arping: bad number of packets to transmit.\n");
				return -EINVAL;
			}
			break;
		case '?':
			printf("Invalid option `-%c'\n", optopt);
			/* FALLTHROUGH */
		case 'h':
			print_usage();
			/* FALLTHROUGH */
		default:
			return 0;
		}
	};

	if (argc == 1) {
		print_usage();
		return 0;
	}

	/* Get destination address. */
	if (0 == inet_aton(argv[argc - 1], &dst)) {
		printf("arping: invalid IP address: %s\n", argv[argc - 1]);
		return -EINVAL;
	}

	strncpy(dst_b, inet_ntoa(dst), sizeof(dst_b));
	from.s_addr = in_dev->ifa_address;
	strncpy(from_b, inet_ntoa(from), sizeof(from_b));
	printf("ARPING %s from %s %s\n", dst_b, from_b, in_dev->dev->name);
	for (i = 1; i <= cnt; i++) {
#if 1
		(void)hw_addr;
		(void)mac;
		arp_send(ARP_OPER_REQUEST, ETH_P_IP, in_dev->dev->addr_len,
				sizeof in_dev->ifa_address, NULL, &in_dev->ifa_address,
				NULL, &dst.s_addr, NULL, in_dev->dev);
#else
		neighbour_del(ETH_P_IP, &dst, in_dev->dev);
		arp_send(ARP_OPER_REQUEST, ETH_P_IP, in_dev->dev->addr_len,
				sizeof in_dev->ifa_address, NULL, &in_dev->ifa_address,
				NULL, &dst.s_addr, NULL, in_dev->dev);
		usleep(DEFAULT_INTERVAL);
		if (0 == neighbour_get_haddr(ETH_P_IP, &dst, in_dev->dev,
					ARPG_HRD_ETHERNET, sizeof hw_addr, &hw_addr[0])) {
			macaddr_print(mac, hw_addr);
			printf("Unicast reply from %s [%s]  %dms\n", dst_b, mac, -1);
			cnt_resp++;
		}
#endif
	}
	printf("Sent %d probes (%d broadcast(s))\n", cnt, 1);
	printf("Received %d response(s)\n", cnt_resp);

	return 0;
}
