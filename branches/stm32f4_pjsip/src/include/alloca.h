/*
 * @file
 *
 * @date 12.12.12
 * @author Anton Bondarev
 */

#ifndef ALLOCA_H_
#define ALLOCA_H_

#include <stddef.h> /* size_t in standard library */

//extern void * alloca(size_t size);
#define alloca(size) __builtin_alloca(size)

#endif /* ALLOCA_H_ */
