/**
 * @file
 *
 * @brief An implementation of 'hashtable' interface
 *
 * @date 30.09.11
 *
 * @author Dmitry Zubarevich
 * @author Avdyukhin Dmitry
 * @author Anton Bondarev
 */

#include <errno.h>
#include <string.h>

#include <util/hashtable.h>
#include <util/dlist.h>


#include <mem/objalloc.h>


#include <framework/mod/options.h>

#define CONFIG_HASHTABLE_ELEM_QUNTITY  OPTION_GET(NUMBER,item_quntity)

OBJALLOC_DEF(ht_elem_pool, struct hashtable_element,
		CONFIG_HASHTABLE_ELEM_QUNTITY * 16);


struct hashtable *hashtable_create(struct hashtable *ht, size_t table_size,
		ht_hash_ft get_hash, ht_cmp_ft cmp) {

	ht->table = (struct hashtable_entry *)(ht + 1);

	memset(ht->table, 0, table_size * sizeof(struct hashtable_entry));

	ht->get_hash_key = get_hash;
	ht->table_size = table_size;
	ht->cmp = cmp;
	dlist_init(&ht->all);

	return ht;
}

int hashtable_put(struct hashtable *ht, void *key, void *value) {
	size_t idx;
	struct hashtable_element *htel;

	assert(ht);

	if (NULL == (htel = objalloc(&ht_elem_pool))) {
		return -ENOMEM;
	}
	htel->key = key;
	htel->value = value;

	idx = ht->get_hash_key(key) % ht->table_size;
	if (0 == ht->table[idx].cnt) {
		dlist_init(&ht->table[idx].list);
	}

	ht->table[idx].cnt ++;
	dlist_add_next(dlist_head_init(&htel->lnk), &ht->table[idx].list);

	dlist_add_prev(dlist_head_init(&htel->general_lnk), &ht->all);

	return ENOERR;
}

void *hashtable_get(struct hashtable *ht, void* key) {
	size_t idx;
	struct hashtable_element *htel;

	assert(ht);

	idx = ht->get_hash_key(key) % ht->table_size;
	if (!ht->table[idx].cnt) {
		return NULL;
	}
	dlist_foreach_entry(htel, &ht->table[idx].list, lnk) {
		if(0 == ht->cmp(key, htel->key)) {
			return htel->value;
		}
	}

	return NULL;
}

int hashtable_del(struct hashtable *ht, void *key) {
	size_t idx;
	struct hashtable_element *htel;

	assert(ht);

	idx = ht->get_hash_key(key) % ht->table_size;
	dlist_foreach_entry(htel, &ht->table[idx].list, lnk) {
		if(0 == ht->cmp(key, htel->key)) {
			dlist_del_init(&htel->lnk);
			dlist_del_init(&htel->general_lnk);
			objfree(&ht_elem_pool, htel);

			ht->table[idx].cnt--;

			return ENOERR;
		}
	}

	return -ENOENT;
}

void hashtable_destroy(struct hashtable *ht) {
	int i;
	struct hashtable_element *htel;

	assert(ht);

	for(i = 0; i < ht->table_size; i ++) {
		if (0 == ht->table[i].cnt) {
			continue;
		}
		dlist_foreach_entry(htel, &ht->table[i].list, lnk) {
			objfree(&ht_elem_pool, htel);
		}

	}
}

void *hashtable_get_key_first(struct hashtable *ht) {
	struct hashtable_element *htel;

	assert(ht);

	if (dlist_empty(&ht->all)) {
		return NULL;
	}

	htel = dlist_first_entry(&ht->all, struct hashtable_element, general_lnk);
	return &htel->key;
}

void *hashtable_get_key_next(struct hashtable *ht, void *prev_key) {
	struct hashtable_element *htel;

	assert(ht);

	if (dlist_empty(&ht->all)) {
		return NULL;
	}

	htel = member_cast_out(prev_key, struct hashtable_element, key);
	if (dlist_last(&ht->all) == &htel->general_lnk) {
		return NULL;
	}

	htel = dlist_first_entry(&htel->general_lnk, struct hashtable_element, general_lnk);
	return &htel->key;
}
