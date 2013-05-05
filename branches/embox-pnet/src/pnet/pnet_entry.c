/**
 * @file
 * @brief
 *
 * @date 02.11.11
 * @author Anton Kozlov
 */

#include <errno.h>
#include <assert.h>
#include <pnet/prior_path.h>
#include <profiler/tracing/trace.h>

#include <pnet/core.h>
#include <pnet/node.h>

int pnet_entry(struct pnet_pack *pack) {
	struct __trace_point *p;
	struct __trace_block *tb;

	if (!(pack && pack->node && pack->node->rx_dfault)) {
		return -EINVAL;
	}
	pack->node = pack->node->rx_dfault;

	ktime_get_timespec(&pack->stat.start_time);
	pack->stat.running_time.tv_sec = 0;
	pack->stat.running_time.tv_nsec = 0;

	tb = trace_block_get_by_name("irq_handler_tb");
	pack->stat.last_interrupts_time = ns_to_timespec(trace_block_get_total_time(tb));

	p = trace_point_get_by_name("interrupt");
	pack->stat.interrupt_count = trace_point_get_value(p);

	pnet_rx_thread_add(pack);
	return 0;
}
