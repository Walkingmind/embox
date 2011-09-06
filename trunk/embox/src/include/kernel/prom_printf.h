/**
 * @file
 *
 * @brief
 *
 * @date 25.11.10
 * @author Anton Bondarev
 */

#ifndef PROM_PRINTF_H_
#define PROM_PRINTF_H_

//#include <stdio.h>

#include __module_headers(embox/prom/printf)
#if 0
#if defined(CONFIG_PROM_PRINTF)
extern int prom_printf(const char *format, ...) __attribute__ ((format
				(printf, 1, 2)));
#else
#define prom_printf(...)  do ; while (0)
#endif
#endif
#endif /* PROM_PRINTF_H_ */
