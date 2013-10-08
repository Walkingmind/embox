/**
 * @file
 * @brief Print network statistic
 *
 * @date 30.12.11
 * @author Alexander Kalmuk
 * @author Alexandr Chernakov
 */

#include <embox/cmd.h>
#include <stdio.h>
#include <net/sock.h>
#include <net/l4/udp.h>
#include <net/l4/tcp.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>

EMBOX_CMD(exec);

static const char * sock_state_str(enum sock_state st) {
	switch (st) {
	case SS_UNKNOWN:       return "UNKNOWN";
	case SS_UNCONNECTED:   return "UNCONNECTED";
	case SS_BOUND:         return "BOUND";
	case SS_LISTENING:     return "LISTENING";
	case SS_CONNECTING:    return "CONNECTING";
	case SS_CONNECTED:     return "CONNECTED";
	case SS_ESTABLISHED:   return "ESTABLISHED";
	case SS_DISCONNECTING: return "DISCONNECTING";
	case SS_CLOSED:        return "CLOSED";
	}

	assert(0, "illegal socket state %d", st);
	return NULL;
}

static const char * tcp_sock_state_str(enum tcp_sock_state st) {
	switch (st) {
	case TCP_MAX_STATE:    break;
	case TCP_SYN_RECV_PRE: return "SYN_RECV_PRE";
	case TCP_CLOSED:       return "CLOSED";
	case TCP_LISTEN:       return "LISTEN";
	case TCP_SYN_SENT:     return "SYN_SENT";
	case TCP_SYN_RECV:     return "SYN_RECV";
	case TCP_ESTABIL:      return "ESTABLISHED";
	case TCP_FINWAIT_1:    return "FIN_WAIT1";
	case TCP_FINWAIT_2:    return "FIN_WAIT2";
	case TCP_CLOSEWAIT:    return "CLOSE_WAIT";
	case TCP_CLOSING:      return "CLOSING";
	case TCP_LASTACK:      return "LAST_ACK";
	case TCP_TIMEWAIT:     return "TIME_WAIT";
	}

	assert(0, "illegal tcp socket state %d", st);
	return NULL;
}

void print_inet_sock_info(const struct sock *sk) {
	const struct inet_sock *in_sk;

	in_sk = (const struct inet_sock *)sk;
	assert(in_sk != NULL);
	assert(in_sk->sk.opt.so_domain == AF_INET);

	printf("%-5s ", in_sk->sk.opt.so_protocol == IPPROTO_TCP ? "tcp"
			: in_sk->sk.opt.so_protocol == IPPROTO_UDP ? "udp"
			: "unknown");

	if (in_sk->src_in.sin_family == AF_INET) {
		printf("%*s:%-5hu ", INET_ADDRSTRLEN,
				inet_ntoa(in_sk->src_in.sin_addr),
				ntohs(in_sk->src_in.sin_port));
	}
	else {
		/* FIXME */
		assert(in_sk->src_in.sin_family == AF_UNSPEC);
		printf("%*s:%-5c ", INET_ADDRSTRLEN, "0.0.0.0", '*');
	}


	if (in_sk->dst_in.sin_family == AF_INET) {
		printf("%s:%hu ", inet_ntoa(in_sk->dst_in.sin_addr),
				ntohs(in_sk->dst_in.sin_port));
	}
	else {
		/* FIXME */
		assert(in_sk->src_in.sin_family == AF_UNSPEC);
		printf("%*s:%-5c ", INET_ADDRSTRLEN, "0.0.0.0", '*');
	}

	printf("%s", in_sk->sk.opt.so_protocol == IPPROTO_TCP
			? tcp_sock_state_str(((const struct tcp_sock *)&in_sk->sk)->state)
			: sock_state_str(sock_get_state(&in_sk->sk)));

	printf("\n");
}

void print_info(const char *title, const struct sock_ops *ops,
		void (*print_sock_info)(const struct sock *)) {
	const struct sock *sk;

	if (title != NULL) {
		printf("%s\n", title);
	}

	if (ops != NULL) {
		sock_foreach(sk, ops) {
			(*print_sock_info)(sk);
		}
	}
}

static int exec(int argc, char **argv) {
	print_info(
			"Active Internet connections\n"
			"Proto   Local Address   Foreign Address   State\n",
			tcp_sock_ops, &print_inet_sock_info);
	print_info(NULL, udp_sock_ops, &print_inet_sock_info);

	return 0;
}
