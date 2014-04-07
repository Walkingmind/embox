ifeq (0,1)

ARCH           = sparc
KERNEL_VERSION = 2.6.33
CROSS_COMPILE  = sparc-linux-
KERNEL_PATCHES = linux-$(KERNEL_VERSION)-leon3.patch.gz
KERNEL_CONFIG  = config-$(KERNEL_VERSION)-leon3.default

else

ARCH           = microblaze
KERNEL_VERSION = 2.6.33
CROSS_COMPILE  = mb-linux-
KERNEL_PATCHES = linux-$(KERNEL_VERSION)-spartan3a.patch.gz
KERNEL_CONFIG  = config-$(KERNEL_VERSION)-spartan3a.default

endif

KERNEL_SRC     = linux-$(KERNEL_VERSION).tar.bz2
KERNEL_URL     = http://www.kernel.org/pub/linux/kernel/v2.6/$(KERNEL_SRC)
