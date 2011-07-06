/**
 * @file
 * @brief Implementation of the socket for Transmission Control Protocol(TCP).
 *
 * @date 06.07.11
 * @author Dmitry Zubarevich
 */

#include <net/net.h>
#include <net/in.h>
#include <embox/net_sock.h>

extern struct proto tcp_prot;

extern const struct proto_ops inet_stream_ops;

EMBOX_NET_SOCK(SOCK_STREAM, IPPROTO_TCP, tcp_prot, inet_stream_ops, 0);
