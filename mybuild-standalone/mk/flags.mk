# $Id$

CFLAGS ?=
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

# Preprocessor flags
cppflags := $(CPPFLAGS)
override CPPFLAGS += -I$(SRC_DIR)/include
override CPPFLAGS += -I$(SRCGEN_DIR)/include

__srcgen_includes := $(SRCGEN_DIR)/src/include
$(and $(shell $(MKDIR) $(__srcgen_includes)),)
override CPPFLAGS += $(__srcgen_includes:%=-I%)

override CPPFLAGS += -MMD -MP
override CPPFLAGS += $(cppflags)

# Assembler flags
asflags := $(CFLAGS)
override ASFLAGS  = -pipe
override ASFLAGS += $(asflags)


cxxflags := $(CFLAGS)
override CXXFLAGS = -pipe
override CXXFLAGS += -fno-strict-aliasing -fno-common
override CXXFLAGS += -Wall -Werror
override CXXFLAGS += -Wundef -Wno-trigraphs -Wno-char-subscripts
override CXXFLAGS += -Wformat -Wformat-nonliteral
#override CXXFLAGS += -I$(SRC_DIR)/include/c++
override CXXFLAGS += -D"__BEGIN_DECLS=extern \"C\" {"
override CXXFLAGS += -D"__END_DECLS=}"
#	C++ has build-in type bool
override CXXFLAGS += -DSTDBOOL_H_
override CXXFLAGS += $(cxxflags)

# Compiler flags
cflags := $(CFLAGS)
override CFLAGS  = -std=gnu99
override CFLAGS += -fno-strict-aliasing -fno-common
override CFLAGS += -Wall -Werror
override CFLAGS += -Wstrict-prototypes -Wdeclaration-after-statement
override CFLAGS += -Wundef -Wno-trigraphs -Wno-char-subscripts
override CFLAGS += -Wformat -Wformat-nonliteral -Wno-format-zero-length
override CFLAGS += -pipe
override CFLAGS += -D"__BEGIN_DECLS="
override CFLAGS += -D"__END_DECLS="
override CFLAGS += $(cflags)

# Linker flags
ldflags := $(LDFLAGS)
override LDFLAGS =
#override LDFLAGS  = -static -nostdlib
override LDFLAGS += $(ldflags)

override ARFLAGS = rcs



CCFLAGS ?=

