/**
 * @file
 *
 * @date 07.12.10
 * @author Fedor Burdun
 */

#include <unistd.h> /* for debug. for use sleep */
#include <kernel/thread/api.h>
#include <types.h>
#include <ctype.h>
#include <string.h>
//#include <drivers/tty.h>
#include <drivers/tty_action.h>
#include <kernel/diag.h>

#ifdef CONFIG_TTY_CONSOLE_COUNT
#define CC tty->consoles[tty->console_cur]
#define BUFF tty->consoles[tty->console_cur]->cl_buff
#define BUFF_c tty->consoles[tty->console_cur]->cl_cur
#define BUFF_s tty->consoles[tty->console_cur]->cl_cnt
#else
#define CC tty->consoles[tty->console_cur]
#define BUFF tty->rx_buff
#define BUFF_c tty->rx_cur
#define BUFF_s tty->rx_cnt
#endif
/*
 * FIXME
 * 	buffers is used elements of different sizes. Check it and fix if need.
 */

struct vt_token char_token( char ch ) {
	struct vt_token tmp;
	tmp.action = VT_ACTION_PRINT;
	tmp.ch = ch;
	tmp.attrs_len = 0;
	tmp.params_len = 0;
	/* null to array */
	return tmp;
}

/* auxilary functions */

void tty_write_space(tty_device_t *tty, uint32_t cnt) {
	struct vt_token vt = char_token(' ');
	for (; cnt > 0; --cnt) {
		//tty->file_op->fwrite(" ", sizeof(char), 1, NULL);
		vtbuild((struct vtbuild *)tty->vtb, &vt);
	}
}

void tty_go_left(tty_device_t *tty, uint32_t cnt) {
#if 0
	tty->file_op->fwrite("\e[%dD",sizeof(char),4+((cnt>9)?(1):(0))+((cnt>99)?(1):(0)),NULL);
#else
	for (; cnt > 0; --cnt) {
		vtbuild((struct vtbuild *)tty->vtb, TOKEN_LEFT);
	}
#endif
}

void tty_go_right(tty_device_t *tty, uint32_t cnt) {
#if 0
	tty->file_op->fwrite("\e[%dC",sizeof(char),4+((cnt>9)?(1):(0))+((cnt>99)?(1):(0)),NULL);
#else
	for (; cnt > 0; --cnt) {
		vtbuild((struct vtbuild *)tty->vtb, TOKEN_RIGHT);
	}
#endif
}

void tty_go_cursor_position(tty_device_t *tty,
		uint32_t cur_before, uint32_t cur_after) {
	if (cur_before < cur_after) {
		tty_go_right(tty, cur_after - cur_before);
	} else {
		tty_go_left(tty, cur_before - cur_after);
	}
}

void tty_clean_line(tty_device_t *tty, uint32_t cur_before,
			uint32_t length, uint32_t cur_after) {
	tty_go_left(tty, cur_before);
	tty_write_space(tty, length);
	tty_go_left(tty, length - cur_after);
}

void tty_write_line(tty_device_t *tty, uint8_t *line,
			uint32_t size, uint32_t cur_after) {
	tty->file_op->fwrite(line, sizeof(uint8_t), size, NULL);
	tty_go_left(tty, size - cur_after);
}

void tty_rewrite_line(tty_device_t *tty, uint8_t *line, uint32_t size,
		uint32_t old_size, uint32_t cur_before, uint32_t cur_after) {
	tty_go_left(tty, cur_before);
	if (old_size > size) {
		tty_write_space(tty, old_size);
		tty_go_left(tty, old_size);
	}
	tty->file_op->fwrite(line, sizeof(uint8_t), size, NULL);
	#if 0
	int i;
	for (i = 0; i < size; ++i) {
		tty->file_op->fwrite(&line[i], sizeof(uint8_t), 1, NULL);
		printf("wtf?");
		printf(" s: %d ", size);
	}
	#endif
	tty_go_left(tty, size - cur_after);
}

void copy_forward(uint8_t *s, uint8_t *d, uint32_t size) {
	size_t i;
	for (i = 0; i < size; ++i) {
		d[i] = s[i];
	}
}

void copy_backward(uint8_t *s, uint8_t *d, uint32_t size) {
	for (; size > 0; --size) {
		d[size] = s[size];
	}
	d[0] = s[0];
}

/* actions in tty */

/* print char */
void tac_key_alpha(tty_device_t *tty, struct vt_token *token) { //TODO change rx_buff to tty->console[ current ]->cl_buf //
	if (tty->ins_mod) { /* INSERT MODE */
		if (BUFF_s < TTY_RXBUFF_SIZE) {
			++BUFF_s;
			copy_backward(
				(uint8_t *) &BUFF[BUFF_c],
				(uint8_t *) &BUFF[BUFF_c + 1],
				(BUFF_s - BUFF_c));
			BUFF[BUFF_c++] = token->ch;
			vtbuild((struct vtbuild *)tty->vtb, token);
			tty_write_line(tty, (uint8_t *) &BUFF[BUFF_c],
				BUFF_s - BUFF_c, 0);
		}
	} else { /* REPLACE MOD */
		if (BUFF_c < TTY_RXBUFF_SIZE) {
			BUFF[BUFF_c++] = token->ch;
			if (BUFF_c > BUFF_s) {
				BUFF_s = BUFF_c;
			}
			vtbuild((struct vtbuild *)tty->vtb, token);
		}
	}
}

/* remove one char */
void tac_key_del(tty_device_t *tty) {
	if (BUFF_c < BUFF_s) {
		copy_forward(
			(uint8_t *) &BUFF[BUFF_c+1],
			(uint8_t *) &BUFF[BUFF_c],
			--BUFF_s - BUFF_c);
		tty_rewrite_line(tty,
			(uint8_t *) &BUFF[BUFF_c],
			BUFF_s - BUFF_c,
			BUFF_s - BUFF_c + 1, 0, 0);
	}
}

/* remove one char */
void tac_key_backspace(tty_device_t *tty) {
	uint32_t i;
	if (BUFF_c > 0) {
		--BUFF_c;
		vtbuild((struct vtbuild *)tty->vtb, TOKEN_LEFT);
		for (i = BUFF_c; i < BUFF_s - 1; ++i) {
			BUFF[i] = BUFF[i + 1];
			tty->file_op->fwrite((uint8_t *) &BUFF[i], sizeof(char), 1, NULL);
		}
		tty->file_op->fwrite(" ", sizeof(char), 1, NULL);
		for (i = BUFF_c; i < BUFF_s; ++i) {
			vtbuild((struct vtbuild *)tty->vtb, TOKEN_LEFT);
		}
		--BUFF_s;
	}
}

/* move cursor left one char */
void tac_key_left(tty_device_t *tty) {
	if (BUFF_c > 0) {
		--BUFF_c;
		/* vtbuild((struct vtbuild *)tty->vtb, token); */
		tty_go_left(tty, 1);
	}
}

/* move cursor right one char */
void tac_key_right(tty_device_t *tty) {
	if (BUFF_c < BUFF_s) {
		++BUFF_c;
		/* vtbuild((struct vtbuild *)tty->vtb, token); */
		tty_go_right(tty, 1);
	}
}

/* move cursor to begin of the line */
void tac_key_home(tty_device_t *tty) {
	tty_go_cursor_position(tty, BUFF_c, 0);
	BUFF_c = 0;
}

/* move cursor to end of the line */
void tac_key_end(tty_device_t *tty) {
	tty_go_cursor_position(tty, BUFF_c, BUFF_s);
	BUFF_c = BUFF_s;
}

/* switch insert-replace mode */
void tac_key_ins(tty_device_t *tty) {
	tty->ins_mod = !tty->ins_mod;
}

/* execute command line */
void tac_key_enter(tty_device_t *tty, struct vt_token *token) {
	uint32_t i;
	#if 1
	if (CC->out_busy) return; /* don't wait */
	#else
	while (CC->out_busy);  /* wait resault if busy */
	#endif
	/* add string to output buffer */
	memcpy((void*) CC->out_buff, (const void*)
		BUFF, BUFF_s);
	CC->out_buff[BUFF_s] = '\0';
	///* TIMER context (that handle tty actions) != thread console that use tty!!!! *///printf(">>>%s",CC->out_buff); /* print echo to tty->console_cur */

	/* silent print to console */
	for (i=0;i<BUFF_s;++i) {
		CC->scr_buff[CC->scr_line*CC->width+CC->scr_column+i] = CC->out_buff[i];//BUFF[i];
	}

	BUFF_s = 0;
	BUFF_c = 0;

	CC->out_busy = true;
	vtbuild((struct vtbuild *)tty->vtb, token);
	++CC->scr_line; /* TODO make function of normalize */
	CC->scr_column = 0;
}

/* remove last word in command line */
void tac_remove_word(tty_device_t *tty) {
	/* find end of prev word */
	uint32_t tps; /* tps - to position space */
	tps = BUFF_c>0 ? BUFF_c-1 : 0;
	for (; tps>0 && isalpha(BUFF[tps]); --tps);
	for (; tps>0 && isspace(BUFF[tps]); --tps);
	if (tps > 0) {
		++tps;
	}

	copy_forward(
		(uint8_t *) &BUFF[BUFF_c],
		(uint8_t *) &BUFF[tps],
		BUFF_s - BUFF_c + tps);

	tty_rewrite_line(tty,
		(uint8_t *) &BUFF[tps],
		BUFF_s - BUFF_c,
		BUFF_s - tps,
		BUFF_c - tps, 0);

	BUFF_s -= BUFF_c - tps;
	BUFF_c = tps;
}

/* remove the line */
void tac_remove_line(tty_device_t *tty) {
	copy_forward(
		(uint8_t *) &BUFF[BUFF_c],
		(uint8_t *) &BUFF[0],
		BUFF_s - BUFF_c);
	tty_rewrite_line(tty,
		(uint8_t *) &BUFF[0],
		BUFF_s - BUFF_c,
		BUFF_s, BUFF_c, 0);
	BUFF_s -= BUFF_c;
	BUFF_c = 0;
}

void tac_goto00(tty_device_t *tty ) {
#if 1
	tty->file_op->fwrite("\x1b[H",sizeof(char),3,NULL);
#else
	/* other methods */
#endif
}

void tac_clear(tty_device_t *tty ) {
	tac_goto00( tty );
	tty->file_op->fwrite("\x1b[2J",sizeof(char),4,NULL);
}

#undef CC
#undef BUFF 
#undef BUFF_c
#undef BUFF_s
