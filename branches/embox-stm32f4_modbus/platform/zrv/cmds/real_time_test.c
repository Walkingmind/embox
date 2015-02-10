//real_time_test.c

#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>

#include <embox/cmd.h>

#include <kernel/time/ktime.h> /* ktime_get_timeval */
#include <kernel/time/timer.h>

#include <drivers/spi.h>


EMBOX_CMD(realtimetst);


static void * realtime_process(void * args) {
	char out=0x0f, in;
	spi_poll_switch_master_mode();
	while(1){
		spi_poll_send(&out, (__u8*)&in,1);
		usleep(10000l);
	}
	return (void*)0;
}

static int realtimetst(int argc, char **argv){

	pthread_t tr;
	int ret,res=0;
	struct sched_param sched_param;

	if(0 != (ret = pthread_create(&tr, 0, realtime_process, (void *) res))) {
		printf("Error.. thread_create() failed. errno=%d\n", ret);
		return -1;
	}
	sched_param.sched_priority = 160;
	pthread_setschedparam(tr, SCHED_OTHER, &sched_param);
	pthread_detach(tr);



	return 0;
}



