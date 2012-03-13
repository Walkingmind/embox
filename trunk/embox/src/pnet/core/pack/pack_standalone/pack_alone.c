/**
 * @file
 * @brief Network packet 
 *
 * @date 20.10.2011
 * @author Anton Kozlov
 */

#include <string.h>

#include <mem/objalloc.h>

#include <pnet/core.h>

#include <pnet/pnet_pack.h>
#include <pnet/pack/pack_alone.h>

#define PACK_DATA_LEN 64 //TODO

OBJALLOC_DEF(net_packs, struct pnet_pack, CONFIG_PNET_PACKETS_QUANTITY);
OBJALLOC_DEF(net_packs_data, unsigned char[PACK_DATA_LEN], CONFIG_PNET_PACKETS_QUANTITY);

static struct pnet_pack *pnet_pack_alloc(void *data, size_t len) {
	struct pnet_pack *pack = data;
	struct pnet_pack_data *pack_data = pack->data;

	if (len > PACK_DATA_LEN) {
		return NULL;
	}

	pack = objalloc(&net_packs);

	//pack->node = node;
	pack->dir = PNET_PACK_DIRECTION_RX; //TODO varios packet types

	pack_data->buff = objalloc(&net_packs_data);

	pack_data->len = len;

	pack->type = PNET_PACK_TYPE_SINGLE;

	return pack;
}

static void pnet_pack_free(struct pnet_pack *pack) {
	struct pnet_pack_data *data = pack->data;

	objfree(&net_packs_data, data->buff);

	objfree(&net_packs, pack);
}

PNET_PACK(PNET_PACK_TYPE_SINGLE,pnet_pack_alloc,pnet_pack_free);
