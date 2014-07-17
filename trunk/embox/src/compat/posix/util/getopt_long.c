/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    17.07.2014
 */

#include <errno.h>
#include <string.h>
#include <getopt.h>

static int getopt_try_long(int argl, char *const arg[], const struct option *longopts, 
		const struct option **out_lopt) {
	const struct option *lopt;


	if (strncmp(arg[0], "--", 2)) {
		return -EINVAL;
	}

	for (lopt = longopts; lopt->name; lopt++) {
		const char *opt = arg[0] + 2;
		char *optarg_sep = strchrnul(opt, '=');

		*out_lopt = lopt;

		if (0 == strncmp(opt, lopt->name, optarg_sep - opt)) {
			switch (lopt->has_arg) {
			case no_argument:
				if (!*optarg_sep) {
					optarg = NULL;
					return 1;
				}
				break;
			case required_argument:
				if (argl >= 1) {
					optarg = arg[1];
					return 2;
				}
				break;
			case optional_argument:
				optarg = *optarg_sep ? optarg_sep + 1 : NULL;
				return 1;
			}
		}
	}
	return -ENOENT;
}

int getopt_long(int argc, char * const argv[],
                  const char *optstring,
                  const struct option *longopts, int *longindex) {

	if (optind < argc) {
		int consumed;
		const struct option *lopt;

		consumed = getopt_try_long(argc - optind, argv + optind, longopts, &lopt);
		if (consumed >= 0) {

			optind += consumed;
			if (longindex) {
				*longindex = lopt - longopts;
			}
			if (lopt->flag) {
				*lopt->flag = lopt->val;
				return 0;
			} else {
				return lopt->val;
			}
		}
	}

	return -1;
}

