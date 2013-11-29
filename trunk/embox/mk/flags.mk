# $Id$

CFLAGS ?=
CXXFLAGS ?=
CPPFLAGS ?=
ASFLAGS ?=
ARFLAGS ?=
LDFLAGS ?=

ifneq ($(patsubst N,0,$(patsubst n,0,$(or $(value NDEBUG),0))),0)
override CPPFLAGS += -DNDEBUG
override NDEBUG := 1
else
override NDEBUG :=
endif

ifdef OPTIMIZE

override OPTIMIZE := $(strip $(OPTIMIZE:-O%=%))
__optimize_valid_values := s 0 1 2 3 4 5 99
__optimize_invalid := $(filter-out $(__optimize_valid_values),$(OPTIMIZE))
ifneq ($(__optimize_invalid),)
$(error Invalid value for OPTIMIZE flag: $(__optimize_invalid). \
  Valid values are: $(__optimize_valid_values))
endif

ifneq ($(words $(OPTIMIZE)),1)
$(error Only single value for OPTIMIZE flag is permitted)
endif

override CFLAGS += -O$(OPTIMIZE)
override CXXFLAGS += -O$(OPTIMIZE)

endif

# Expand user defined flags and append them after default ones.

__srcgen_includes_fn = $(addprefix $1$(SRCGEN_DIR)/src/,include arch/$(ARCH)/include)
__srcgen_includes := $(call __srcgen_includes_fn,)
$(and $(shell $(MKDIR) $(__srcgen_includes)),)

cppflags_fn = \
	-U__linux__ \
	-D__EMBOX__ \
	-D__unix \
	-D"__impl_x(path)=<../path>"\
	-imacros $(AUTOCONF_DIR)/config.h\
	-I$1$(SRC_DIR)/include -I$1$(SRC_DIR)/arch/$(ARCH)/include\
	-I$1$(SRCGEN_DIR)/include -I$1$(SRCGEN_DIR)/src/include\
	$(call __srcgen_includes_fn,-I$1) \
	$(if $(value PLATFORM),-I$1$(PLATFORM_DIR)/$(PLATFORM)/include)\
	-I$1$(SRC_DIR)/compat/linux/include -I$1$(SRC_DIR)/compat/posix/include\
	-nostdinc\
	-MMD -MP# -MT $@ -MF $(@:.o=.d)

# Preprocessor flags
cppflags := $(CPPFLAGS)
override CPPFLAGS  = $(call cppflags_fn,) $(cppflags)
EMBOX_EXPORT_CPPFLAGS := $(call cppflags_fn,$(abspath $(ROOT_DIR))/)

override COMMON_FLAGS := -pipe
override COMMON_FLAGS += --debug-prefix-map=$$(pwd)=
override COMMON_FLAGS += --debug-prefix-map=./=

# Assembler flags
asflags := $(CFLAGS)
override ASFLAGS = $(COMMON_FLAGS)
override ASFLAGS += $(asflags)

override COMMON_CCFLAGS := $(COMMON_FLAGS)
override COMMON_CCFLAGS += -fno-strict-aliasing -fno-common
override COMMON_CCFLAGS += -Wall -Werror
override COMMON_CCFLAGS += -Wundef -Wno-trigraphs -Wno-char-subscripts
override COMMON_CCFLAGS += -Wformat -Wno-format-zero-length #-Wformat-nonliteral

cxxflags := $(CXXFLAGS)
override CXXFLAGS = $(COMMON_CCFLAGS)
#override CXXFLAGS += -fno-rtti
#override CXXFLAGS += -fno-exceptions
#override CXXFLAGS += -fno-threadsafe-statics
override CXXFLAGS += -I$(SRC_DIR)/include/c++
override CXXFLAGS += -I$(ROOT_DIR)/build/gcc/include
#	C++ has build-in type bool
override CXXFLAGS += -DSTDBOOL_H_
override CXXFLAGS += $(cxxflags)

# Compiler flags
cflags := $(CFLAGS)
override CFLAGS  = $(COMMON_CCFLAGS)
override CFLAGS += -std=gnu99
#override CFLAGS += -fexceptions
override CFLAGS += $(cflags)

# Linker flags
ldflags := $(LDFLAGS)
override LDFLAGS  = -static -nostdlib
override LDFLAGS += $(ldflags)

override ARFLAGS = rcs



CCFLAGS ?=

