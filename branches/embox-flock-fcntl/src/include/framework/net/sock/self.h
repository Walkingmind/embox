/**
 * @file
 * @brief
 *
 * @date 04.07.11
 * @author Dmitry Zubarevich
 * @author Ilia Vaprol
 */

#ifndef FRAMEWORK_NET_SOCK_SELF_H_
#define FRAMEWORK_NET_SOCK_SELF_H_

#include __impl_x(framework/net/sock/self_impl.h)

#include <stddef.h>

#define EMBOX_NET_SOCK(_family, _type, _protocol, _is_default,  \
		_ops)                                                   \
	static const struct sock_ops _ops;                          \
	__EMBOX_NET_SOCK(_family##_type##_protocol, _family, _type, \
			_protocol, _is_default, _ops, NULL, NULL)

#define EMBOX_NET_SOCK_INIT(_family, _type, _protocol,          \
		_is_default, _ops, _init)                               \
	static const struct sock_ops _ops;                          \
	static int _init(void);                                     \
	__EMBOX_NET_SOCK(_family##_type##_protocol, _family, _type, \
			_protocol, _is_default, _ops, _init, NULL)

#define EMBOX_NET_SOCK_INIT_FINI(_family, _type, _protocol,     \
		_is_default, _ops, _init, _fini)                        \
	static const struct sock_ops _ops;                          \
	static int _init(void);                                     \
	static int _fini(void);                                     \
	__EMBOX_NET_SOCK(_family##_type##_protocol, _family, _type, \
			_protocol, _is_default, _ops, _init, _fini)

#endif /* FRAMEWORK_NET_SOCK_SELF_H_ */