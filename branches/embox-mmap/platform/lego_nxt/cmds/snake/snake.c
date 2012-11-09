/**
 * @file
 *
 * @date 01.04.10
 * @author Anton Kozlov
 */

#include <embox/cmd.h>
#include <unistd.h>
#include <time.h>
#include <drivers/nxt_buttons.h>
#include <drivers/lcd.h>
extern __u8 display_buffer[NXT_LCD_DEPTH+1][NXT_LCD_WIDTH];

#define SPEED_INC 5
#define SIZE_X 25
#define SIZE_Y 16
#define SNAKE_LEN 4
#define SNK '*'
#define FRU 'o'
EMBOX_CMD(exec);

static int rand_seed = 0;
static int sleep_time = 1200;
static int speed_count = SPEED_INC;

static char field[SIZE_X * SIZE_Y];
static char dir[SIZE_X * SIZE_Y];

typedef struct {
	int x;
	int y;
} point;

static point head, tail, diff;
static char diff_char = 'l';

static point dxp = {1,0};
static point dxm = {-1,0};
static point dyp = {0,1};
static point dym = {0,-1};

static point nil = {0,0};

static int score = 0;

static void draw_nxt_white(point p) {
	int i, x = p.x * 4, y = p.y / 2;
	char fill = 0xf0;
	if (p.y & 1)
		fill = 0x0f;
	for (i = 0; i < 4; i++) {
		display_buffer[y][x++] &= fill;
	}
}

static void draw_nxt_bitmap(point p, uint8_t *bitmap) {
	int i, x = p.x * 4, y = p.y / 2;
	for (i = 0; i < 4; i++) {
		display_buffer[y][x++] |= bitmap[i] << (4 * (p.y & 1));
	}
}

static uint8_t i_head[] = {0x0f, 0x09, 0x09, 0xf};
static uint8_t i_middle[4] = {0x0, 0x06, 0x06, 0x0};
static uint8_t i_die[] = {0x09, 0x06, 0x06, 0x09};
static uint8_t i_fruit[] = {0x0f, 0x0b, 0x09, 0x0f};
#if 1

static void draw_nxt_middle(point p) {
	draw_nxt_bitmap(p, i_middle);
}

static void draw_nxt_connect(point p, point diff) {
}

static void draw_nxt_head(point p) {
	draw_nxt_bitmap(p, i_head);
}

static void draw_nxt_die(point p) {
	draw_nxt_bitmap(p, i_die);
}

static void draw_nxt_fruit(point p) {
	draw_nxt_bitmap(p, i_fruit);
}
#endif
static int f2d(int x, int y) {
	return y + x * SIZE_Y;
}

static point d2f(unsigned int offset) {
	point p = {offset % SIZE_Y, offset / SIZE_Y};
	return p;
}

static void snake_init(void) {
	int i, j = SIZE_Y / 2;
	int si = (SIZE_X - SNAKE_LEN) /2;
	head.y = tail.y = j;
	tail.x = si;
	for (i=0;i<SNAKE_LEN;i++) {
		field[f2d(si + i,j)] = SNK;
		dir  [f2d(si + i,j)] = 'l';
	}
	head.x = si + i - 1;
}

static void draw(point p, char c) {
	field[f2d(p.x,p.y)] = c;
}

static int space(char c) {
	return (c == '.' || c == ' ');
}

static int random(void) {
	rand_seed += clock();
	return rand_seed;
}

static void fruit_draw(void) {
	point p = nil;
	while (!space(field[f2d(p.x, p.y)])) {
		unsigned int t = random() % ((SIZE_X - 3) * (SIZE_Y - 3));
		p = d2f(t);
		p.x++;
		p.y++;
	}
	draw(p, FRU);
	draw_nxt_fruit(p);
}

static void refresh(void) {
	int i, j;
	display_clear_screen();
	for (i = 0; i < SIZE_Y; i++) {
		for (j = 0; j < SIZE_X; j++) {
			if (!space(field[f2d(j,i)])) {
				point p = {j, i};
				draw_nxt_middle(p);
			}
		}
	}
}

static void field_init(void) {
	int i, j;
	for (i = 0; i < SIZE_X; i++)
		for (j = 0; j < SIZE_Y; j++)
			field[f2d(i,j)] = '.';
	for (i = 0; i < SIZE_X; i++) {
		field[f2d(i,0)] = field[f2d(i,SIZE_Y - 1)] = '-';
	}
	for (i = 0; i < SIZE_Y; i++) {
		field[f2d(0,i)] = field[f2d(SIZE_X - 1,i)] = '|';
	}
	snake_init();
	refresh();

	fruit_draw();
}

static point point_plus(point p1, point p2) {
	point p = {p1.x + p2.x, p1.y + p2.y};
	return p;
}

static char field_char(point p) {
	return field[f2d(p.x,p.y)];
}

static char dir_char(point p) {
	return dir[f2d(p.x,p.y)];
}

static char button_dispatch(uint32_t btns) {
	if ((btns & BT_DOWN) && (btns & BT_ENTER)) {
		return 'q';
	}
	if (btns & BT_DOWN) {
		return 'j';
	}
	if (btns & BT_LEFT) {
		return 'h';
	}
	if (btns & BT_RIGHT) {
		return 'l';
	}
	if (btns & BT_ENTER) {
		return 'k';
	}
	return ' ';
}

static point dispatch(char c) {
	switch (c) {
	case 'h':
		return dxm;
	case 'j':
		return dyp;
	case 'k':
		return dym;
	case 'l':
		return dxp;
	}
	return nil;

}

static int snake_update(void) {
	point p = point_plus(head, diff);
	char new_pos = field_char(p);

	dir[f2d(head.x, head.y)] = diff_char;

	switch (new_pos) {
	case FRU:
		if (!speed_count--) {
			if (sleep_time >= 50)
				sleep_time -= 20;
			speed_count = SPEED_INC;
		}
		draw_nxt_white(head);
		draw_nxt_middle(head);
		draw_nxt_connect(head, diff);
		draw_nxt_white(p);
		draw_nxt_head(p);
		head = p;
		score += 10;
		draw(p,SNK);
		fruit_draw();
		nxt_lcd_force_update();
		break;
	case ' ':
	case '.':
		draw(tail,' ');
		draw_nxt_white(tail);

		draw(p, SNK);
		draw_nxt_white(head);
		draw_nxt_middle(head);
		draw_nxt_connect(head, diff);
		draw_nxt_head(p);

		head = p;
		tail = point_plus(dispatch(dir_char(tail)), tail);
		nxt_lcd_force_update();
		break;
	default:
		draw(p,'X');
		draw_nxt_white(p);
		draw_nxt_die(p);
		draw_nxt_white(head);
		draw_nxt_middle(head);
		draw_nxt_connect(head, diff);
		nxt_lcd_force_update();

		return 0;
	}
	return 1;
}

static int valid(point p) {
	return !(p.x == 0 && p.y == 0);
}

static int begin_splash(void) {
	display_clear_screen();
	display_string("\nnxtSnake\n\nUp + Down = exit\nEat't up!");
	while (!nxt_buttons_was_pressed()) {
		usleep(100);
	}
	return 1;
}

static void end_splash(void) {
	display_clear_screen();
	display_string("Game over =(");
	while (!nxt_buttons_was_pressed()) {
		usleep(100);
	}
}

static int exec(int argc, char **argv) {
	if (!begin_splash()) {
		return 0;
	}

	display_clear_screen();
	field_init();
	diff = dxp;
	while (snake_update()) {
		char ch;
		point d = nil;
		point d2 = nil;

		usleep(sleep_time);
		ch = button_dispatch(nxt_buttons_was_pressed());
		if (ch == 'q') {
			break;
		}
		d = dispatch(ch);
		d2 = point_plus(d,diff);

		if (valid(d2) && valid(d)) {
			diff = d;
			diff_char = ch;
		}
	}
	end_splash();
	display_clear_screen();
	return 0;
}
