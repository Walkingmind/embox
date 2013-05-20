/**
 * @file
 * @brief TODO
 *
 * @date 16.05.2013
 * @author Alexander Kalmuk
 */

#ifndef PROFILER_SAMPLING_H_
#define PROFILER_SAMPLING_H_

#define SYMBOL_NAME_LEN        0x10
#define SYMBOL_CNT_UPPERBOUND  0x80

struct sample {
	char name[SYMBOL_NAME_LEN];
	unsigned int cnt;
};

extern void sampling_routine(void);

extern size_t sampling_copy_sample(void *buf, size_t len);

extern void sampling_diff_samples(void *diff, void *old_sample, void *new_sample, size_t len);

#endif /* PROFILER_SAMPLING_H_ */
