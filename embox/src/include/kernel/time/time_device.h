/*
 * @brief Abstraction layer for time device.
 *
 * @date 13.06.2012
 * @author Alexander Kalmuk
 */

#ifndef KERNEL_TIME_DEVICE_H_
#define KERNEL_TIME_DEVICE_H_

enum device_config {
	EVENT_ONESHOT = 1,
	EVENT_PERIODIC = 0
};

enum counter_type {
	COUNTER_MONOTONIC = 0,
	COUNTER_PERIODIC = 1
};

/**
 * Time device, that generate interrupts.
 *
 * @param init - init function. Return 0 on success.
 * @param event_handler - handler called on each event occur.
 * @param set_mode - set mode function.
 * @resolution - number of events per second.
 * @name - name of device
 */
struct time_event_device {
	int (*init)(void);
	void (*event_handler)(void);
	int (*config)(enum device_config conf, void *param);
	uint32_t resolution;
	const char *name;
};

/**
 * Time device, that don't generate interrupts. Such device change own state
 * with fixed frequency and we need make request for it state.
 *
 * @param init - init function.
 * @param resolution - number of cycles per second.
 * @param read - return current number of cycles.
 * @param type - periodic or monotonic
 */
struct time_counter_device {
	int (*init)(void);
	uint32_t resolution;
	cycle_t (*read)(void);
	enum counter_type type;
};

#endif /* KERNEL_TIME_DEVICE_H_ */
