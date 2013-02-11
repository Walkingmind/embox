/**
 * @file
 * @brief Keyboard driver
 *
 * @date 12.12.10
 * @author Anton Bondarev
 */

#include <types.h>

#include <asm/io.h>

#include <drivers/keyboard.h>
#include <drivers/input/input_dev.h>

#define KEYBOARD_SCAN_CODE_EXT    0xE0

#define KEYBOARD_SCAN_CODE_CTRL   0x1D
#define KEYBOARD_SCAN_CODE_ALT    0x38
#define KEYBOARD_SCAN_CODE_SHIFT  0x2A
#define KEYBOARD_SCAN_CODE_CAPS   0x3A


#define  I8042_CMD_READ_MODE   0x20
#define  I8042_CMD_WRITE_MODE  0x60
#define  I8042_CMD_PORT_DIS    0xAD
#define  I8042_CMD_PORT_EN     0xAE

#define  I8042_MODE_XLATE      0x40
#define  I8042_MODE_DISABLE    0x10



#define  CMD_PORT              0x64
#define  STATUS_PORT           0x64
#define  DATA_PORT             0x60


#define keyboard_wait_read()  do {} while (0 == (inb(STATUS_PORT) & 0x01))
#define keyboard_wait_write() do {} while (0 != (inb(STATUS_PORT) & 0x02))

extern const unsigned int keymap[][4];

static int keyboard_havechar(void) {
	unsigned char c = inb(STATUS_PORT);
	return (c == 0xFF) ? 0 : c & 1;
}

static void keyboard_send_cmd(uint8_t cmd) {
	keyboard_wait_write();
	outb(cmd, CMD_PORT);
}

static unsigned char keyboard_get_mode(void) {
	keyboard_send_cmd(I8042_CMD_READ_MODE);
	keyboard_wait_read();
	return inb(DATA_PORT);
}

static void keyboard_set_mode(unsigned char mode) {
	keyboard_send_cmd(I8042_CMD_WRITE_MODE);
	keyboard_wait_write();
	outb(mode, DATA_PORT);
}

int keyboard_has_symbol(void) {
	return keyboard_havechar();
}

#include <kernel/printk.h>



static int kbd_state;

int key_is_pressed(struct input_event *event) {
	return event->type & KEY_PRESSED;
}

static void kbd_key_serv_press(int state, int flag) {
	if(state & KEY_PRESSED) {
		kbd_state |= flag;
	} else {
		kbd_state &= ~flag;
	}
}


#define KMC_PORTB 0x61
int keyboard_get_input_event(struct input_event *event) {
	uint8_t scan_code;
	int flag = 0;
	keyboard_wait_read();

	scan_code = inb(DATA_PORT);

//	printk("s 0x%X\n", scan_code);
	if(scan_code == KEYBOARD_SCAN_CODE_EXT) {
		keyboard_wait_read();
		scan_code = inb(DATA_PORT);
	}
	if(scan_code & 0x80) {
		/* key unpressed */
		event->type &= ~KEY_PRESSED;
	} else {
		/* key pressed */
		event->type |= KEY_PRESSED;
	}
	scan_code &= 0x7F;

	switch(scan_code) {
	case KEYBOARD_SCAN_CODE_CTRL:
		flag = CTRL_PRESSED;
		break;

	case KEYBOARD_SCAN_CODE_ALT:
		flag = ALT_PRESSED;
		break;
	case KEYBOARD_SCAN_CODE_SHIFT:
		flag = SHIFT_PRESSED;
		break;
	case KEYBOARD_SCAN_CODE_CAPS:
		flag = CAPS_PRESSED;
		break;
	}
	kbd_key_serv_press(event->type, flag);

	event->value = kbd_state | scan_code;

	return 0;
}

extern int keymap_to_ascii(struct input_event *event, unsigned char ascii_buff[4]);

int keyboard_getc(void) {
	static unsigned char ascii_buff[4];
	static int ascii_len;
	static int seq_cnt = 0;
	struct input_event event;

	if(ascii_len > seq_cnt) {
		return ascii_buff[seq_cnt++];
	}
	ascii_len = 0;

	do {
		keyboard_get_input_event(&event);
		if(key_is_pressed(&event)) {
			ascii_len = keymap_to_ascii(&event, ascii_buff);
		}
	} while(ascii_len == 0);

	seq_cnt = 0;

	return ascii_buff[seq_cnt++];
}



static struct input_dev kbd_dev = {
		.name = "keyboard",
		.irq = 1,
		.getc = keyboard_getc
};


void keyboard_init(void) {
	uint8_t mode;

	/* If 0x64 returns 0xff, then we have no keyboard
	 * controller */
	if (inb(0x64) == 0xFF) {
		return;
	}

	keyboard_send_cmd(I8042_CMD_PORT_DIS);

	/* Empty keyboard buffer */
	while (keyboard_havechar()) inb(DATA_PORT);

	/* Read the current mode */
	mode = keyboard_get_mode();
	/* Turn on scancode translate mode so that we can
	 use the scancode set 1 tables */
	mode |= I8042_MODE_XLATE;
	/* Enable keyboard. */
	mode &= ~I8042_MODE_DISABLE;
	/* Write the new mode */
	keyboard_set_mode(mode);

	keyboard_send_cmd(I8042_CMD_PORT_EN);

	input_dev_register(&kbd_dev);
	kbd_state = 0;
}
