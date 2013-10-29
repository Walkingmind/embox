/**
 * @file
 * @brief wide-character classification and mapping utilities
 * @details TODO: Now wchar set is a char set only (see ctype.h). Any wchar greater than 255
 * does not belong to any charclass and will be recognized as invalid.
 * @date 21.10.13
 * @author Alexander Kalmuk
 */

#ifndef WCTYPE_H_
#define WCTYPE_H_

#include <wchar.h>
#include <ctype.h>

typedef int wctrans_t;

/* Wrapper of ctype function to make it wctype function */
#define WCFUNC(class) \
	static inline int isw ## class(wint_t wc) { \
		return ((wc < (wint_t)0x100 ? is ## class(wc) : 0)); \
	}

WCFUNC(alnum);
WCFUNC(alpha);
WCFUNC(blank);
WCFUNC(cntrl);
WCFUNC(digit);
WCFUNC(graph);
WCFUNC(lower);
WCFUNC(print);
WCFUNC(punct);
WCFUNC(space);
WCFUNC(upper);
WCFUNC(xdigit);

#undef WCFUNC

static inline wint_t towlower(wint_t wc) {
	if (wc == WEOF)
		return WEOF;
	return (wc < (wint_t)0x100 ? tolower(wc) : wc);
}

static inline wint_t towupper(wint_t wc) {
	if (wc == WEOF)
		return WEOF;
	return (wc < (wint_t)0x100 ? toupper(wc) : wc);
}

#include <sys/cdefs.h>

__BEGIN_DECLS

extern int iswctype(wint_t, wctype_t);
extern wint_t towctrans(wint_t, wctrans_t);

extern wctype_t wctype(const char *property);
extern wctrans_t wctrans(const char *charclass);

__END_DECLS

#endif /* WCTYPE_H_ */
