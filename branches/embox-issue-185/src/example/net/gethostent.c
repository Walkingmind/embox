/**
 * @file
 * @brief Example of using gethostent function
 *
 * @date 20.08.12
 * @author Ilia Vaprol
 */

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <framework/example/self.h>

EMBOX_EXAMPLE(exec);

static void print_info(struct hostent *he) {
	char **ptr;

	printf("\nname: %s\n", he->h_name);
	for (ptr = he->h_aliases; *ptr != NULL; ptr++) {
		printf("alternate name: %s\n", *ptr);
	}

	printf("address type: %s\n",
			(he->h_addrtype == AF_INET ? "AF_INET" : "unknown"));

	if (he->h_length != sizeof(struct in_addr)) {
		printf("Invalid length: %d\n", he->h_length);
		return;
	}

	for (ptr = he->h_addr_list; *ptr != NULL; ++ptr) {
		printf("%s address: %s\n",
				(ptr == he->h_addr_list ? "primary" : "alternate"),
				inet_ntoa((*(struct in_addr *)*ptr)));
	}
}

static int exec(int argc, char *argv[]) {
	struct hostent *he;

	sethostent(1);

	while ((he = gethostent()) != NULL) {
		print_info(he);
	}

	endhostent();

	return 0;
}
