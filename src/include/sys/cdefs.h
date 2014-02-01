/*
 * @file
 *
 * @date Jan 2, 2013
 * @author: Anton Bondarev
 */

#ifndef SYS_CDEFS_H_
#define SYS_CDEFS_H_

/* __BEGIN_DECLS should be used at the beginning of your declarations,
   so that C++ compilers don't mangle their names.  Use __END_DECLS at
   the end of C declarations. */
#undef __BEGIN_DECLS
#undef __END_DECLS
#ifdef __cplusplus
# define __BEGIN_DECLS extern "C" {
# define __END_DECLS }
#else
# define __BEGIN_DECLS /* empty */
# define __END_DECLS /* empty */
#endif

#endif /* SYS_CDEFS_H_ */
