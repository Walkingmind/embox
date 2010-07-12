/** 
 * @file
 * @author Fedor Burdun
 * @data 08.07.2010
 * @description Interface for use in drivers.
 */

#ifndef __DRIVER_H_
#define __DRIVER_H_

//#include <kernel/mm/kmalloc.h>
#include <kernel/irq.h>
#include <sys/types.h>
#include <stddef.h>

typedef int device_cmd;
typedef int io_cmd;
typedef int device_desc;
typedef int device_flags;
typedef int driver_flags;

typedef device_desc FILE;
//#define FILE device_desc;

typedef struct device 		device_t;
typedef struct io_context 	io_context_t;
typedef struct driver 		driver_t;

/*
 * this interface for char device will not support fseek (call ioctl with some argument)
 * but it may be common interface for all devices
 */
typedef struct device_ops {
	int (*open)  ( device_t *dev , int mode );
	int (*close) ( device_t *dev );
	int (*read)  ( device_t *dev , char *buf    , size_t n  );
	int (*write) ( device_t *dev , char *buf    , size_t n  );
	int (*ioctl) ( device_t *dev , io_cmd c     , void *arg );
	int (*devctl)( device_t *dev , device_cmd c , void *arg );
} device_ops_t;

/* return code for -open(), -close(), -read(), -write(), ioctl() */
#define ERROR_IO_UNKNOWN 			0x0001
#define ERROR_IO_DONT_SUPPORT 		0x0002

/* return code for devctl(), device_create(), device_destroy() */
#define ERROR_DEV_UNKNOWN 			0x0001
#define ERROR_DEV_DONT_SUPPORT 		0x0002
#define ERROR_DEV_BUSY				0x0003

/*
 * Need it or NOT ?
 * io context, that show path to route flow of data
 */
struct io_context {
	device_desc in, out; /* FILE in, out; */
};

/*
 * device information, that accesiable for kernel
 */
struct device {
	const char 			*desc;		/* char description of device */
	device_flags		flags;		/* some flag, allows read/write or some operations? */
	io_context_t 		ioc;		/* in/out context */
	driver_t 			*driver;	/* driver, that controlled its device */
	size_t 				private_s; 	/* description of private data */
	void 				*private;
};

/*
 * description of device's drivers
 * generate by kernel on stage of registry driver in system. Macross EMBOX_DRIVER?
 */
struct driver {
	const char 		*name;		/* name of driver */
	device_ops_t 	ops;		/* interface of device, that controlled by this driver */
	driver_flags 	flags;		/* some flag of driver */
	size_t 			private_s;	/* size of private data */
	void 			*private;	/* private data */

	int (*load)  ( driver_t *this );			/* init of driver, allocate memory and other */
												/* return 0 or -ERR */

	int (*probe) ( driver_t *this , void *arg);	/* find more devices in system and registry they */
												/* arg need for send driver some information, for
													example about path to file for driver of file system
													in order that create device of specific file */
												/* return count of new devices or -ERR */

	int (*unload)( driver_t *this );			/* free devices and memory */
												/* return 0 or -ERR */
};

/* function for use in driver */
/* control of devices from driver */

device_t 	*device_create( driver_t *this , const char *name , device_flags flags , size_t private_s );
			/* allocate memory for device, generate integer descriptor, set some default settings */
			/* io_context was set by kernel probably with /dev/null */

int 		device_destroy( device_t *dev );
			/* free memory */

device_desc device_select( const char *desc ); 
			/* select device by description string (devFS?) */
			/* if can't find device, return /dev/null */

#if 1
/* shared device's interface */
int device_open  ( device_desc dev , int mode );
int device_close ( device_desc dev );
int device_read  ( device_desc dev , char *buf    , size_t n  );
int device_write ( device_desc dev , char *buf    , size_t n  );
int device_ioctl ( device_desc dev , io_cmd c     , void *arg );
int device_devctl( device_desc dev , device_cmd c , void *arg );
#endif

#endif /* __DRIVER_H_ */

