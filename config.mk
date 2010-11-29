ARCH           = microblaze
KERNEL_VERSION = 2.6.33
CROSS_COMPILE  = mb-linux-
KERNEL_SRC     = linux-$(KERNEL_VERSION).tar.bz2
KERNEL_PATCHES = linux-$(KERNEL_VERSION)-spartan3a.patch.gz
KERNEL_CONFIG  = config-$(KERNEL_VERSION)-spartan3a.default
KERNEL_URL     = http://www.kernel.org/pub/linux/kernel/v2.6/$(KERNEL_SRC)

