/**
 * @file
 * @author Fedor Burdun
 * @data 08.07.2010
 * @description realization of device manipulation
 */

#include <driver.h>
#include <string.h>

#define CONFIG_DEV_MAX_COUNT 0xff

int has_init = 0; 								/* flag of initialization */
device_t device_pool[ CONFIG_DEV_MAX_COUNT ]; 	/* pool of all devices in system */

const char *empty_dev = "empty device";

/* Initialize pool */
void pool_init() {
#if 1
	int i = 0;
	for ( int i=0 ; i < CONFIG_DEV_MAX_COUNT ; ++i ) {
		/* memset( &device_pool[i] , 0 , sizeof( device_t ) ); */
		device_pool[i].desc 	= empty_dev;
		device_pool[i].flags	= 0;
		device_pool[i].ioc.in	= 0;
		device_pool[i].ioc.out	= 0;
		device_pool[i].driver 	= NULL;
		device_pool[i].private_s= 0;
		device_pool[i].private	= NULL;
	}

	for ( int i=1 ; i< CONFIG_DEV_MAX_COUNT ; ++i ) {
		device_pool[i-1].private = i; /* WARINIG! In empty dev private ptr use as index of next
			empty device in pool */
	}
#endif
}

device_t 	*device_create( driver_t *this , const char *name , device_flags flags , size_t private_s )
			/* allocate memory for device, generate integer descriptor, set some default settings */
			/* io_context was set by kernel probably with /dev/null */ {

#if 1
	/* init pool */
	if (!has_init) {
		pool_init();
		has_init = 1;
	}
	/* if pool now is empty */
	if (device_pool[0].private == 0) {
		return NULL;
	}
	/* push from list of empty devices */
	device_t *fr;
	fr = &device_pool[ (device_desc) device_pool[0].private ];
	device_pool[0].private = fr->private;
	/* init some property */
	fr->driver = this;
	fr->desc = name;
	fr->flags = flags;
	fr->private_s = private_s;
	fr->private = kmalloc( private_s );
	/* return same device structure */
	return fr;
#endif
}

int 		device_destroy( device_t *dev ) {
			/* free memory */
#if 0
	/* free memory */
	kfree( dev->private );
	/* set default value */
	dev->desc 		= empty_dev;
	dev->flags		= 0;
	dev->ioc.in		= 0;
	dev->ioc.out	= 0;
	dev->driver 	= NULL;
	dev->private_s= 0;
	/* insert in list of empty */
	dev->private	= device_pool[0].private;
	device_pool[0].private = ((unsigned long long) device_pool - (unsigned long long) dev)/sizeof(device_t);
#endif
}

/* select device by description string (devFS?) */       
device_desc device_select( const char *desc ) {
	device_desc i;
	for ( i=0 ; (i<CONFIG_DEV_MAX_COUNT) && (strcmp(desc,device_pool[i].desc)) ; ++i );
	if (!strcmp(desc,device_pool[i].desc)) {
		return i;
	}
	return 0;
}

#if 1
/* shared device's interface */
int device_open  ( device_desc *dev , int mode ) { 
}

int device_close ( device_desc *dev ) { 
}

int device_read  ( device_desc *dev , char *buf    , size_t n  ) { 
}

int device_write ( device_desc *dev , char *buf    , size_t n  ) { 
}

int device_ioctl ( device_desc *dev , io_cmd c     , void *arg ) { 
}

int device_devctl( device_desc *dev , device_cmd c , void *arg ) { 
}
#endif

