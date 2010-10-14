/**
 * @file
 *
 * @date 23.11.2009
 * @author Alexey Fomin
 */
#ifndef INIT_H_
#define INIT_H_

#define PRE_INIT_LEVEL       -1
#define INIT_SYSTEM_LEVEL     0
#define INIT_MODULE_LEVEL     1
#define INIT_SYNCHRONIZE      2
#define INIT_NET_LEVEL        3
#define INIT_FS_LEVEL         3

#define INIT_MAX_LEVEL        3

typedef struct init_descriptor {
	const char *name;
	int (*init)(void);
	int level;
} init_descriptor_t;

#define DECLARE_INIT(name, init, level) \
	static int init(void); \
	static const init_descriptor_t _descriptor##init = { name, init, level }; \
	static const init_descriptor_t *_pdescriptor##init \
		__attribute__ ((used, section(".init_handlers"))) \
		= &_descriptor##init

int init(void);

#endif /* INIT_H_ */
