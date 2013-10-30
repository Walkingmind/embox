/**
 * @file 
 * @brief 
 *
 * @author  Anton Kozlov 
 * @date    30.10.2013
 */

#include <stdio.h>
#include <unistd.h>
#include <drivers/input/input_dev.h>
#include <embox/cmd.h>

EMBOX_CMD(input_test_main);

static void usage(char *argv0) {
	printf("Usage: %s -i INPUT_DEV\n", argv0);
}

static char *dev_type_map(enum input_dev_type type) {
	switch (type) {
	case INPUT_DEV_KBD:
		return "KEYBOARD";
	case INPUT_DEV_MOUSE:
		return "MOUSE";
	case INPUT_DEV_APB:
		return "APB";
	}

	/* NOTREACHED */
	return "";
}

static int indev_cb(struct input_dev *indev) {
	struct input_event ev;

	while (0 == input_dev_event(indev, &ev)) {
		printf("input event: dev_type=%s, type=%08x, value=%08x\n",
			dev_type_map(ev.devtype), ev.type, ev.value);
	}

	return 0;
}

static int input_test_main(int argc, char **argv) {
	int opt;
	char *indev_name = NULL;
	struct input_dev *indev;

	getopt_init();
	while (-1 != (opt = getopt(argc, argv, "i:"))) {
		switch(opt) {
		case 'i':
			indev_name = optarg;
			break;
		default:
			usage(argv[0]);
			return 1;
		}
	}

	if (!indev_name) {
		usage(argv[0]);
		return 1;
	}

	indev = input_dev_lookup(indev_name);
	if (NULL == indev) {
		printf("Cannot find such input dev");
		return 1;
	}

	if (0 != input_dev_open(indev, indev_cb)) {
		return 1;
	}

	while (1) {
		sleep(1);
	}

	return 0;
}
