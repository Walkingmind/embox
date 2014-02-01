/**
 * @file
 *
 * @brief
 *
 * @date 06.07.2011
 * @author Anton Bondarev
 */

#ifndef FRAMEWORK_EXAMPLE_TYPES_H_
#define FRAMEWORK_EXAMPLE_TYPES_H_

typedef int (*example_exec_t)(int argc, char **argv);

struct example {
	const struct mod *mod;
	example_exec_t exec;
};


#endif /* FRAMEWORK_EXAMPLE_TYPES_H_ */
