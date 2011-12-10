/**
 * @file
 *
 * @date 27.05.09
 * @author Nikolay Korotky
 */

#ifndef NETUTILS_H_
#define NETUTILS_H_

unsigned char *ipaddr_scan(const unsigned char *addr, unsigned char *res);
unsigned char *macaddr_scan(const unsigned char *addr, unsigned char *res);
void macaddr_print(unsigned char *buf, const unsigned char *addr);
int is_addr_from_net(const unsigned char *uip,
		    const unsigned char *nip, unsigned char msk);

#endif /* NETUTILS_H_ */
