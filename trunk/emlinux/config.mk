ARCH           = sparc
KERNEL_VERSION = 2.6.33
KERNEL_SRC     = linux-$(KERNEL_VERSION).tar.bz2
KERNEL_PATCHES = linux-$(KERNEL_VERSION)-$(ARCH).patch.gz
KERNEL_CONFIG  = config-$(KERNEL_VERSION)-$(ARCH).default
KERNEL_URL     = http://www.kernel.org/pub/linux/kernel/v2.6/$(KERNEL_SRC)

