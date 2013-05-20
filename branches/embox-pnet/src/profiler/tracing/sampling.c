/**
 * @file
 * @brief
 *
 * @author  Alexander Kalmuk
 * @date    16.05.2013
 */

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <debug/symbol.h>
#include <util/math.h>
#include <kernel/printk.h>
#include <profiler/sampling.h>
#include <module/embox/arch/stackframe.h>
#include <util/hashtable.h>
#include <embox/unit.h>

EMBOX_UNIT(sampling_init, sampling_fini);

#define STACK_DEPTH_FROM_FUNC  5 /* depth of stack in interrupt handler */
#define HASHTABLE_SIZE         0x10

static struct hashtable *symbols_ht;
static struct sample sample_array[SYMBOL_CNT_UPPERBOUND];
static int symbols_cnt;
static int inited;
static void inc_symbols(void *symbol, const char *name);

extern void stack_iter_current(stack_iter_t *);
extern int stack_iter_next(stack_iter_t *);
extern void *stack_iter_get_retpc(stack_iter_t *);

void sampling_routine(void) {
	stack_iter_t f;
	const struct symbol *s;
	int depth = STACK_DEPTH_FROM_FUNC;

	if (!inited) {
		return;
	}

	stack_iter_current(&f);
	do {
		stack_iter_next(&f);
	} while (--depth > 0);

	s = symbol_lookup(stack_iter_get_retpc(&f));

	if (s) {
		inc_symbols((void*)s, s->name);
	}
}

size_t sampling_copy_sample(void *buf, size_t len) {
	memcpy(buf, sample_array, len * sizeof(struct sample));
	return min(len, symbols_cnt);
}

void sampling_diff_samples(void *diff, void *old_sample, void *new_sample, size_t len) {
	int i;
	struct sample *_diff = diff;
	struct sample *_old_sample = old_sample;
	struct sample *_new_sample = new_sample;

	for (i = 0; i < len; i++) {
		memcpy(_diff[i].name, _old_sample[i].name, SYMBOL_NAME_LEN);
		_diff[i].name[SYMBOL_NAME_LEN - 1] = '\0';
		_diff[i].cnt = _new_sample[i].cnt - _old_sample[i].cnt;
	}
}

static void inc_symbols(void *symbol, const char *name) {
	struct sample *sample;

	sample = hashtable_get(symbols_ht, symbol);

	if (NULL == sample) {
		memcpy(sample_array[symbols_cnt].name, name, SYMBOL_NAME_LEN);
		sample_array[symbols_cnt].name[SYMBOL_NAME_LEN - 1] = '\0';
		sample_array[symbols_cnt].cnt = 1;
		hashtable_put(symbols_ht, symbol, &sample_array[symbols_cnt]);
		symbols_cnt++;
	} else {
		sample->cnt++;
	}
}

static size_t get_hash(void *key) {
	return (size_t)key;
}

static int cmp_key(void *key1, void *key2) {
	unsigned int k1 = (unsigned int)key1;
	unsigned int k2 = (unsigned int)key2;

	return (k1 < k2 ? -1 : k1 > k2);
}

static int sampling_init(void) {
	symbols_ht = hashtable_create(HASHTABLE_SIZE, get_hash, cmp_key);
	assert(symbols_ht);
	inited = 1;
	return 0;
}

static int sampling_fini(void) {
	hashtable_destroy(symbols_ht);
	return 0;
}
