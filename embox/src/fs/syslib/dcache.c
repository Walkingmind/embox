/**
 * @file
 *
 * @date 29.04.14
 * @author Vita Loginova
 */
#include <util/hashtable.h>
#include <util/dlist.h>
#include <errno.h>
#include <embox/unit.h>
#include <string.h>

#include <mem/misc/pool.h>

#include <dirent.h>

#include <fs/dcache.h>

#define DCACHE_TABLE_SIZE OPTION_GET(NUMBER, dcache_table_size)
#define DCACHE_MAX_NAME_SIZE 20

EMBOX_UNIT_INIT(dcache_init);

struct dkey {
	char fullpath[DCACHE_MAX_NAME_SIZE + 1];
};

struct dvalue {
	struct dkey key;
	struct path path;
	struct dlist_head link;
};

POOL_DEF(dcache_path_pool, struct dvalue, DCACHE_TABLE_SIZE);

static struct hashtable *dcache_table = NULL;
static struct dlist_head values;

static void dvalue_delete(struct dvalue *dvalue) {
	hashtable_del(dcache_table, &dvalue->key);
	dlist_del(&dvalue->link);
	pool_free(&dcache_path_pool, dvalue);
}

static void compound_path(char *source, const char *prefix, const char *rest) {
	strcpy(source, prefix);

	if (rest[0] != '/' && (0 != strcmp("/", prefix))) {
		strcat(source, "/");
	}

	strcat(source, rest);
}

static void dvalue_init(struct dvalue *dvalue, struct path *path,
		const char *prefix, const char *rest) {
	compound_path(dvalue->key.fullpath, prefix, rest);
	dvalue->path = *path;
	dlist_head_init(&dvalue->link);
}

static void dvalue_add(struct dvalue *dvalue) {
	dlist_add_next(&dvalue->link, &values);
	hashtable_put(dcache_table, &dvalue->key, dvalue);
}

int dcache_delete(const char *prefix, const char *rest) {
	struct dkey dkey;
	struct dvalue *dvalue;

	if (strlen(rest) == 0) {
		return -EINVAL;
	}

	if (strlen(prefix) + strlen(rest) + 1 > DCACHE_MAX_NAME_SIZE) {
		return -EINVAL;
	}

	compound_path(dkey.fullpath, prefix, rest);
	if (NULL != (dvalue = hashtable_get(dcache_table, &dkey))) {
		dvalue_delete(dvalue);
	}

	return 0;
}

int dcache_add(const char *prefix, const char *rest, struct path *path) {
	struct dvalue *dvalue;

	if (!path) {
		return -EINVAL;
	}

	if (strlen(rest) == 0) {
		return -EINVAL;
	}

	if (strlen(prefix) + strlen(rest) + 1 > DCACHE_MAX_NAME_SIZE) {
		return -EINVAL;
	}

	if (NULL == (dvalue = pool_alloc(&dcache_path_pool))) {
		struct dvalue *last;

		last = dlist_entry(values.prev, struct dvalue, link);
		dvalue_delete(last);
		dvalue = pool_alloc(&dcache_path_pool);

		assert(NULL != dvalue);
	}

	dvalue_init(dvalue, path, prefix, rest);
	dvalue_add(dvalue);

	return 0;
}

struct path *dcache_get(const char *prefix, const char *rest) {
	struct dkey dkey;
	struct dvalue *dvalue;
	int prefix_len, rest_len;
	const char *pref_tmp;

	prefix_len = 0;

	if (rest == NULL || 0 == (rest_len = strlen(rest))) {
		return NULL;
	}

	if (prefix == NULL) {
		prefix_len = 0;
		pref_tmp = "";
	} else {
		prefix_len = strlen(prefix);
		pref_tmp = prefix;

	}
	if ((prefix_len + rest_len + 1) > DCACHE_MAX_NAME_SIZE) {
		return NULL;
	}

	compound_path(dkey.fullpath, pref_tmp, rest);
	dvalue = hashtable_get(dcache_table, &dkey);

	return dvalue ? &dvalue->path : NULL;
}

static size_t dcache_hash(void *key) {
	struct dkey *dkey = key;
	size_t hash;
	char *path = dkey->fullpath;

	hash = 0;
	while (*path != '\0') {
		hash ^= *path++;
	}

	return hash;
}

static int dcache_cmp(void *key1, void *key2) {
	struct dkey *dkey1 = key1, *dkey2 = key2;
	return strcmp(dkey1->fullpath, dkey2->fullpath);
}

static int dcache_init(void) {
	dcache_table = hashtable_create(DCACHE_TABLE_SIZE,
			&dcache_hash, &dcache_cmp);

	if (dcache_table == NULL) {
		return -ENOMEM;
	}

	dlist_init(&values);

	return 0;
}

