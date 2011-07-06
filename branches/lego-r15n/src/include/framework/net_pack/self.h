/**
 * @file
 * @brief
 *
 * @date 01.07.11
 * @author Dmitry Zubarevich
 */

#ifndef FRAMEWORK_NET_PACK_SELF_H_
#define FRAMEWORK_NET_PACK_SELF_H_

#include __impl_x(framework/net_pack/self_impl.h)

#define EMBOX_NET_PACK(_type, _func, _init)  	\
	static packet_type_t _##_type = { 			\
			.type = _type,						\
			.func = _func,						\
			.init = _init						\
		};										\
		__EMBOX_NET_PACK(_##_type)

#endif /* FRAMEWORK_NET_PACK_SELF_H_ */
