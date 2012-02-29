/**
 * @file
 * @brief Pending packet resolution.
 * @date 13.12.11
 * @author Alexander Kalmuk
 */

#ifndef NET_ARP_QUEUE_H_
#define NET_ARP_QUEUE_H_

#include <net/skbuff.h>

/**
 * Try to send all pending packets with appropriate IP address
 * containing in ARP pack.
 * @param arp_pack - ARP pack received on ARP resolution request
 */
extern void arp_queue_process(sk_buff_t *arp_pack);

/**
 * Add pending packet pack in specific queue to wait for further
 * transmitting. It called only if there are no hw address of destination host
 * in ARP cache.
 * @param - pack - pending pack waiting for transmitting.
 */
extern int arp_queue_add(struct sk_buff *pack);

#define is_ready(sock) (sock->sk->arp_queue_info & 0x000000FF)
#define was_transmited(sock) ((sock->sk->arp_queue_info & 0x0000FF00) >> 8)
#define get_answer(sock) ((sock->sk->arp_queue_info & 0x00FF0000) >> 16)

#endif /* NET_ARP_QUEUE_H_ */
