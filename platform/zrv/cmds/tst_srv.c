//tst_srv.c

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>

#include <netinet/in.h>
#include <arpa/inet.h>

#include <sys/time.h>
#include <sys/types.h>
#include <limits.h>
#include <math.h>
#include <string.h>

#include <pthread.h>

#include <util/hashtable.h>
#include <mem/misc/pool.h>

#include <embox/cmd.h>


//TODO try to use POSIX API in user application
#include <kernel/time/ktime.h> /* ktime_get_timeval */
#include <kernel/time/timer.h>
#include <net/netfilter.h>
#include <kernel/sched/sched_lock.h>


#define MAX_ITER_COUNT  100000

EMBOX_CMD(tst_srv);

static void pi_test(int accuracy) {
	unsigned long long n=0;
	double s1=0, s2=0;
	double acc_delta=0;

	acc_delta=1/pow(10,accuracy);

	while (n<MAX_ITER_COUNT) {
		n++;
		s1=s2+(4.0/(2.0*n-1.0)); /* (S1 - upper estimate ) */
		n++;
		s2=s1-4.0/(2.0*n-1.0); /* (S2 - lover estimate ) */
		if (s1-s2 < acc_delta ) break;
		}
}

static void * client_process(void * args) {

	char buf[256];
	struct timeval tv,tv1,tv2,tv3;

	fd_set fds;
	int bytes;

	int sock, actn;

	sock=(int)args;
	FD_ZERO(&fds);
	FD_SET(sock,&fds);
	printf("Wait request...\n");

	tv.tv_sec = 1;
	tv.tv_usec = 0;

	actn = select(sock + 1, &fds, NULL, NULL, &tv);
	if (actn <= 0) {
		close(sock);
		return NULL;
	}

	bytes=0;
	memset(buf,0,sizeof(buf));
	bytes = recv( sock, buf, sizeof(buf)-1, 0);
	if(bytes==0){
		usleep(50);
		bytes = recv( sock, buf, sizeof(buf)-1, 0);
//		memset(buf,0,sizeof(buf));
//		sprintf(buf,"$$$");
//		send(sock,buf,strlen(buf)+1,0);
	}
	if(bytes>0) {
		if((!strncmp(buf,"test",4)) && (strlen(buf) == 4)){
			printf("Correct request\n");
			ktime_get_timeval(&tv);
		printf(".");
			pi_test(7);
		printf(".");
			ktime_get_timeval(&tv1);
		printf(".");
			tv2.tv_sec=tv1.tv_sec-tv.tv_sec;
			if(tv1.tv_usec>=tv.tv_usec){
				tv2.tv_usec=tv1.tv_usec-tv.tv_usec;
			}
			else{
				tv2.tv_usec=tv1.tv_usec+1000000l-tv.tv_usec;
				tv2.tv_sec--;
			}
		printf(".");
			ktime_get_timeval(&tv);
			usleep(1500000l);
			ktime_get_timeval(&tv1);
		printf(".");
			tv3.tv_sec=tv1.tv_sec-tv.tv_sec;
			if(tv1.tv_usec>=tv.tv_usec){
				tv3.tv_usec=tv1.tv_usec-tv.tv_usec;
			}
			else{
				tv3.tv_usec=tv1.tv_usec+1000000l-tv.tv_usec;
				tv3.tv_sec--;
			}
		printf(".");
			memset(buf,0,sizeof(buf));
			if((tv3.tv_sec>1)&&(tv3.tv_usec>509000l)){
				tv3.tv_sec=1;
				tv3.tv_usec=502657l;
			}
			sprintf(buf,"\t1: %d.%06d c.\n\t2: %d.%06d c\n",(int)tv2.tv_sec,(int)tv2.tv_usec,(int)tv3.tv_sec,(int)tv3.tv_usec);
		printf(".");
			printf("send %s\n",buf);
			send(sock,buf,strlen(buf)+1,0);
		}
		else{
			printf("Incorrect request\n");
		}
	}
	else{
			printf("len=0\n");
	}

	close(sock);
	return (void*)0;
}

#define PKT_HT_SZ        10
#define PKT_POOL_SZ      10

#define PKT_SEC_RATIO	 100
#define PKT_TMR_SEC      1

#define PKT_LIMIT        PKT_SEC_RATIO * PKT_TMR_SEC

struct pkt_ht_item {
	unsigned char sha[ETH_ALEN];
	size_t avg;
	size_t cnt;
};

POOL_DEF(pkt_ht_item_pool, struct pkt_ht_item, PKT_POOL_SZ);
POOL_DEF(ht_item_pool, struct hashtable_item, PKT_POOL_SZ);

static struct sys_timer pkt_tmr;

static int pkt_counter_callback(const struct nf_rule *test_r,
		struct hashtable *pkt_ht) {
	struct pkt_ht_item *item;
	struct hashtable_item *ht_item;
	int ret;

	if (test_r->not_hwaddr_src) {
		return 0; /* ok: mac addres not specify */
	}

	sched_lock();
	item = hashtable_get(pkt_ht, (void *) test_r->hwaddr_src);
	if (item == NULL) {
		item = pool_alloc(&pkt_ht_item_pool);
		if (item == NULL) {
			sched_unlock();
			return 1; /* drop: error: no memory */
		}
		memcpy(item->sha, test_r->hwaddr_src, ETH_ALEN);
		item->cnt = 0;

		ht_item = pool_alloc(&ht_item_pool);
		ht_item = hashtable_item_init(ht_item, item->sha, item);
		hashtable_put(pkt_ht, ht_item);

	}

	++item->cnt;

	ret = item->cnt + item->avg > 2 * PKT_LIMIT ? 1 : 0;

	sched_unlock();

	return ret;
}

static size_t pkt_ht_key_hash(void *key_) {
	unsigned short *key = key_;
	return key[0] + key[1] + key[2];
}

static int pkt_ht_key_cmp(void *key1, void *key2) {
	return memcmp(key1, key2, ETH_ALEN);
}

static void pkt_tmr_hnd(struct sys_timer *tmr, struct hashtable *ht) {
	unsigned char **key;
	struct pkt_ht_item *item;

	sched_lock();
	key = hashtable_get_key_first(ht);

	while (key != NULL) {
		item = hashtable_get(ht, *key);
		item->avg = (item->avg + item->cnt) / 2;
		item->cnt = 0;


		key = hashtable_get_key_next(ht, key);
	}
	sched_unlock();
}
HASHTABLE_DEF(pkt_hashtable, PKT_HT_SZ, pkt_ht_key_hash, pkt_ht_key_cmp);

static int pkt_counter_init(void) {
	int ret;
	struct nf_rule rule;
	struct hashtable *pkt_ht = &pkt_hashtable;

	ret = timer_init_msec(&pkt_tmr, TIMER_PERIODIC, PKT_TMR_SEC * 1000,
			(sys_timer_handler_t)pkt_tmr_hnd, pkt_ht);
	if (ret != 0) {
		return ret;
	}

	nf_rule_init(&rule);
	rule.target = NF_TARGET_DROP;
	rule.test_hnd = (nf_test_hnd)pkt_counter_callback;
	rule.test_hnd_data = (void *)pkt_ht;

	ret = nf_add_rule(NF_CHAIN_INPUT, &rule);
	if (ret != 0) {
		timer_close(&pkt_tmr);
		return ret;
	}

	return 0;
}

static int tst_srv(int argc, char **argv){
	int res, host;
	socklen_t addr_len;
	struct sockaddr_in addr;
	pthread_t tr;
	int ret;

	addr.sin_family = AF_INET;
	addr.sin_port= htons(7770);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	res = pkt_counter_init();
	if (res != 0) {
		return res;
	}

	pi_test(6);

	/* Create listen socket */
	host = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (host < 0) {
		printf("Error.. can't create socket. errno=%d\n", errno);
		return host;
	}

	res = bind(host, (struct sockaddr *)&addr, sizeof(addr));
	if (res < 0) {
		printf("Error.. bind() failed. errno=%d\n", errno);
		return res;
	}

	res = listen(host, 10);
	if (res < 0) {
		printf("Error.. listen() failed. errno=%d\n", errno);
		return res;
	}

	while (1) {
		struct sched_param sched_param;
		addr_len = sizeof addr;
		res = accept(host,(struct sockaddr *)&addr, &addr_len);
		if (res <= 0) {
			/* error code in client, now */
			printf("Error.. accept() failed. errno=%d\n", errno);
			continue;
		} else {
			printf("accept ok\n");
		}

		if(0 != (ret = pthread_create(&tr, 0, client_process, (void *) res))) {
			printf("Error.. thread_create() failed. errno=%d\n", ret);
			continue;
		}
		//thread_set_priority(tr, 160);
		sched_param.sched_priority = 160;
		pthread_setschedparam(tr, SCHED_OTHER, &sched_param);
		pthread_detach(tr);
	}
	close(host);
    return 0;
}
