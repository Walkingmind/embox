#ifndef GCC_STDIO_H_
#define GCC_STDIO_H_

#include_next <stdio.h>

#include <sys/cdefs.h>

__BEGIN_DECLS

extern void clearerr(FILE *stream);
extern void setbuf(FILE *stream, char *buf);
extern int setvbuf(FILE *stream, char *buf, int type, size_t size);
extern FILE * tmpfile(void);
extern char * tmpnam(char *s);

__END_DECLS

#endif /* GCC_STDIO_H_ */

