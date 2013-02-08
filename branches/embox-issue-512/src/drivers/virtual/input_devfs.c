/**
 * @file
 *
 * @date 20.01.13
 * @author Alexander Kalmuk
 */

#include <types.h>
#include <stdlib.h>
#include <string.h>

#include <fs/file_desc.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <fs/file_operation.h>

#include <kernel/irq.h>
#include <mem/objalloc.h>
#include <util/ring_buff.h>

#include <kernel/thread/event.h>
#include <kernel/thread/sched_lock.h>
#include <kernel/thread/sched.h>

#include <embox/unit.h>

#include <drivers/input/input_dev.h>



EMBOX_UNIT_INIT(init);

#define MAX_OPEN_CNT      64
#define EVENT_SIZE        sizeof(struct input_event)
//#define BUF_SIZE          (32 * EVENT_SIZE)

OBJALLOC_DEF(__input_handlers, struct input_subscriber, MAX_OPEN_CNT);


static int input_devfs_open(struct node *node, struct file_desc *file_desc, int flags);
static int input_devfs_close(struct file_desc *desc);
static size_t input_devfs_read(struct file_desc *desc, void *buf, size_t size);

static kfile_operations_t input_dev_file_op = {
	.open = input_devfs_open,
	.close = input_devfs_close,
	.read = input_devfs_read
};


static DLIST_DEFINE(__input_devices);



static struct input_subscriber *input_dev_find_subscriber(struct input_dev *dev, unsigned int handler_id) {
	struct input_subscriber *cur, *nxt;

	assert(dev != NULL);

	dlist_foreach_entry(cur, nxt, &dev->subscribers, subscribers) {
		if (cur->id == handler_id) {
			return cur;
		}
	}

	return NULL;
}

void input_dev_register(struct input_dev *dev) {
	assert(dev != NULL);

	dlist_init(&dev->subscribers); /* clean subscribers list */

	dlist_add_prev(dlist_head_init(&dev->global_indev_list), &__input_devices);
}


static irq_return_t input_irq_handler(unsigned int irq_nr, void *data) {
	struct input_dev *dev;
	char symbol;
	struct input_subscriber *tmp;
	struct input_subscriber *subsc;


	dev = (struct input_dev *)data;
	assert(dev);
	symbol = (char) dev->getc();


	dlist_foreach_entry(subsc, tmp, &dev->subscribers, subscribers) {
		ring_buff_enqueue(&subsc->rbuff, &symbol, 1);
	}

	return IRQ_HANDLED;
}


static struct input_dev *input_devfs_lookup(char *name) {
	struct input_dev *dev, *nxt;

	dlist_foreach_entry(dev, nxt, &__input_devices, global_indev_list) {
		if (0 == strcmp(dev->name, name)) {
			return dev;
		}
	}

	return NULL;
}


static int input_devfs_open(struct node *node, struct file_desc *desc, int flags) {
	struct input_dev *dev;
	struct input_subscriber *hnd;

	if (NULL == (dev = input_devfs_lookup((char *)desc->node->name))) {
		return -1;
	}

	hnd = objalloc(&__input_handlers);
	if (NULL == hnd) {
		objfree(&__input_handlers, hnd);
		return -1;
	}

	/* if we not open before */
	if(dlist_empty(&dev->subscribers)) {
		irq_attach(dev->irq, input_irq_handler, 0, dev, dev->name);
	}


	ring_buff_init(&hnd->rbuff, EVENT_SIZE, sizeof(hnd->inbuff) / EVENT_SIZE, hnd);

	/* store desc as id to search handler in read/close functions */
	hnd->id = (unsigned int)desc;

	dlist_add_prev(dlist_head_init(&hnd->subscribers), &dev->subscribers);

	return 0;

}

static int input_devfs_close(struct file_desc *desc) {
	struct input_dev *dev;
	struct input_subscriber *hnd;

	if (NULL == (dev = input_devfs_lookup((char *)desc->node->name))) {
		return -1;
	}

	if (NULL == (hnd = input_dev_find_subscriber(dev, (unsigned int)desc))) {
		return -1;
	}

	dlist_del(&hnd->subscribers);
	objfree(&__input_handlers, hnd);

	if (dlist_empty(&dev->subscribers)) {
		irq_detach(dev->irq, dev);
	}

	if (dlist_empty(&dev->subscribers) && dev->close) {
		dev->close(dev);
	}

	return 0;
}

static size_t input_devfs_read(struct file_desc *desc, void *buff, size_t size) {
	struct input_dev *dev;
	size_t cnt = size;
	struct input_subscriber *hnd;

	if (NULL == (dev = input_devfs_lookup((char *)desc->node->name))) {
		return -1;
	}

	if (NULL == (hnd = input_dev_find_subscriber(dev, (unsigned int)desc))) {
		return -1;
	}


	if(0 == ring_buff_get_cnt(&hnd->rbuff)) {
		sched_lock();
			irq_lock();
				event_init(&hnd->rx_happend, "event_rx_happend");
			irq_unlock();

			event_wait_ms(&hnd->rx_happend, SCHED_TIMEOUT_INFINITE);
		sched_unlock();
	}

	for(;0 < cnt;--cnt) {
		int tmp;
		char *tmp_char = buff;

		ring_buff_dequeue(&hnd->rbuff, &tmp, 1);
		*tmp_char = (char)tmp;


		buff = (void *)(((uint32_t)buff) + 1);
	}

	return size - cnt;

}


static int input_devfs_register(struct input_dev *dev) {
	struct node *node, *devnode;
	struct nas *dev_nas;

	assert(dev);

	/* register char device */
	if (NULL == (node = vfs_find_node("/dev/input", NULL))) {
		return -1;
	}
	if (NULL == (devnode = vfs_add_path(dev->name, node))) {
		return -1;
	}

	dev_nas = devnode->nas;
	if(NULL == (dev_nas->fs = alloc_filesystem("empty"))) {
		return -1;
	}

	dev_nas->fs->file_op = &input_dev_file_op;

	return 0;
}

static int init(void) {
	struct node *node;
	struct input_dev *dev, *nxt;

	if (NULL == (node = vfs_find_node("/dev", NULL))) {
		return -1;
	}

	if (NULL == (node = vfs_add_path("input", node))) {
		return -1;
	}
	node->type = NODE_TYPE_DIRECTORY;

	dlist_foreach_entry(dev, nxt, &__input_devices, global_indev_list) {
		if (input_devfs_register(dev) < 0) {
			return -1;
		}
	}

	return 0;
}
