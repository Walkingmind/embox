/**
 * @file
 *
 * @date 18.07.09
 * @author Anton Bondarev
 */

#ifndef NET_INETDEVICE_H_
#define NET_INETDEVICE_H_

#include <net/netdevice.h>
#include <netinet/in.h>
#include <types.h>

typedef void (*devinet_callback_t)(void *pack);

struct net_device;

/**
 * structute of inet(IP) device
 */
typedef struct in_device {
	struct net_device *dev;
	in_addr_t         ifa_address;
	in_addr_t         ifa_mask;
	in_addr_t         ifa_broadcast;
	in_addr_t         ifa_anycast;
	unsigned char     ipv4_addr_length;

		/* IP packets requires uniq id. It's a way to generate them. Bytes order isn't important */
	uint32_t          ip_id_generator;
} in_device_t;

/**
 * get pointer on in_device struct linked with pointed net_device
 * @param dev
 * @return pointer on in_device struct, NULL if error
 */
extern in_device_t *in_dev_get(net_device_t *dev);

/**
 * set callback function for all incoming packet throw interface
 * use it in sniffer program
 * not need set interface to PROMISC mode now
 */
extern int inet_dev_listen(in_device_t *in_dev, unsigned short type,
					    devinet_callback_t callback);

/**
 * find known netdev device has pointed ip address
 * @param ipaddr - ip devices address
 */
extern struct net_device *ip_dev_find(in_addr_t addr);

/**
 * perform check: does this ip should be processes by local ip stack
 * (This function is intended for external packets processing.
 * It DOESN'T support internal stack conventions.)
 * @param ipaddr - ip address
 * @param check_broadcast - should we check broadcast addresses
 * @param check_multicast - should we check multicast addresses
 */
extern bool ip_is_local(in_addr_t addr, bool check_broadcast, bool check_multicast);

/**
 * Get inet_devive by name
 * @param if_name - interface name
 */
extern in_device_t *inet_dev_find_by_name(const char *if_name);

/**
 * Get loopback device. Probably temporarily needed
 * @return pointer to the loopback device
 */
extern struct net_device *inet_get_loopback_dev(void);

/**
 * set all config value for pointed interface
 * @param name - interface name
 * @param ipaddr - ip devices address
 * @param macaddr - MAC devices address
 */
extern int inet_dev_set_interface(const char *name, const in_addr_t ipaddr,
			    const in_addr_t mask, const unsigned char *macaddr);

/**
 * Set IP address (sw)
 * @param ipaddr - ip devices address
 */
extern int inet_dev_set_ipaddr(in_device_t *in_dev, const in_addr_t ipaddr);

/**
 * Set IP mask
 * @param mask - ip mask
 */
extern int inet_dev_set_mask(in_device_t *in_dev, const in_addr_t mask);

/**
 * Set broadcast addres
 * @param bcast - broadcast protocol address
 */
extern int inet_dev_set_bcast(in_device_t *in_dev, const in_addr_t bcast);

/**
 * Set MAC address
 * @param macaddr - MAC devices address
 */
extern int inet_dev_set_macaddr(in_device_t *in_dev, const unsigned char *macaddr);

/**
 * Get interface's IP address
 * @param in_dev interface handler
 */
extern in_addr_t inet_dev_get_ipaddr(in_device_t *in_dev);

/* iterator functions */
extern in_device_t * inet_dev_get_first_used(void);
extern in_device_t * inet_dev_get_next_used(in_device_t *);

extern int inet_dev_add_dev(struct net_device *dev);

extern int inet_dev_remove_dev(struct in_device *in_dev);

/**
 * generate new id for requiered interface
 */
static inline uint32_t inet_dev_get_id(in_device_t *in_dev) {
	return ++in_dev->ip_id_generator;
}

/*TODO: deprecated*/
extern int ifdev_up(const char *iname);
extern int ifdev_down(const char *iname);


#endif /* NET_INETDEVICE_H_ */
