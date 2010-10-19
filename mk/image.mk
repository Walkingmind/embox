# $Id$
#
# Author: Eldar Abusalimov
#

include $(MK_DIR)/util.mk

IMAGE      = $(BIN_DIR)/$(TARGET)
IMAGE_DIS  = $(IMAGE).dis
IMAGE_BIN  = $(IMAGE).bin
IMAGE_SREC = $(IMAGE).srec
IMAGE_SIZE = $(IMAGE).size
IMAGE_PIGGY= $(IMAGE).piggy

.PHONY: image image_init image_fini
image: image_init
image: $(IMAGE) $(IMAGE_SREC) $(IMAGE_BIN) $(IMAGE_SIZE) $(IMAGE_PIGGY)
ifeq ($(DISASSEMBLE),y)
image: $(IMAGE_DIS)
endif
ifeq ($(CHECKSUM),y)
image: checksum
endif
image: image_fini

image_init image_fini:

.PHONY: image_prepare
prepare: image_prepare
image_prepare:
	@mkdir -p $(OBJ_SUBDIRS)

.PHONY: checksum
checksum:
# Not yet implemented

CC      = $(CROSS_COMPILE)gcc
CPP     = $(CC) -E
AR      = $(CROSS_COMPILE)ar
AS      = $(CROSS_COMPILE)as
LD      = $(CROSS_COMPILE)ld
OBJDUMP = $(CROSS_COMPILE)objdump
OBJCOPY = $(CROSS_COMPILE)objcopy
SIZE    = size

ifeq ($(C),1)
CHECK   = sparse
REAL_CC = $(CC)
CC     := cgcc
endif

# Expand user defined flags and append them after default ones.

# Preprocessor flags
cppflags:=$(CPPFLAGS)
override CPPFLAGS  = -D__EMBOX__
override CPPFLAGS += -imacros $(AUTOCONF_DIR)/config.h
override CPPFLAGS += -I$(SRC_DIR)/include -I$(SRC_DIR)/arch/$(ARCH)/include
override CPPFLAGS += -nostdinc
override CPPFLAGS += -MMD -MP# -MT $@ -MF $(@:.o=.d)
override CPPFLAGS += $(cppflags)

# Compiler flags
cflags:=$(CFLAGS)
override CFLAGS  = -pedantic
override CFLAGS += -fno-strict-aliasing -fno-common
override CFLAGS += -Wall
override CFLAGS += -Wstrict-prototypes -Wdeclaration-after-statement -Winline
override CFLAGS += -Wundef -Wno-trigraphs -Wno-char-subscripts
override CFLAGS += -pipe
override CFLAGS += $(cflags)

# Linker flags
ldflags:=$(LDFLAGS)
override LDFLAGS  = -static
override LDFLAGS += -nostdlib
override LDFLAGS += -T $(LDSCRIPT)
override LDFLAGS += $(SUBDIRS_LDFLAGS)
override LDFLAGS += $(ldflags)

override ARFLAGS = rcs

LDSCRIPT = $(OBJ_DIR)/$(TARGET).lds

SRC_TO_OBJ = $(patsubst $(ROOT_DIR)%,$(OBJ_DIR)%.o,$(basename $1))
LIB_FILE   = $(1:%=$(LIB_DIR)/%)

# It's time to scan subdirs and prepare mods info.
include $(MK_DIR)/embuild.mk
# ...and to build dependency injection model
include $(MK_DIR)/codegen-di.mk

OBJS_ALL := $(foreach unit,$(MODS) $(LIBS),$(OBJS-$(unit)))
-include $(OBJS_ALL:.o=.d)

OBJS_BUILD := $(foreach mod,$(MODS_BUILD),$(OBJS-$(mod)))
OBJ_SUBDIRS := \
  $(sort $(dir $(OBJS_BUILD) $(foreach lib,$(LIBS),$(OBJS-$(lib)))))

$(OBJS_ALL): $(AUTOCONF_DIR)/config.h $(AUTOCONF_DIR)/build.mk

$(OBJ_DIR)/%.o::$(ROOT_DIR)/%.c
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -std=gnu99 -c $<

$(OBJ_DIR)/%.o::$(ROOT_DIR)/%.S
	$(CC) -o $@ $(CFLAGS) $(CPPFLAGS) -c $<

$(IMAGE): $(DEPSINJECT_OBJ) $(OBJS_BUILD) $(call LIB_FILE,$(LIBS))
	$(LD) $(LDFLAGS) $(OBJS_BUILD:%=\$N		%) \
		$(DEPSINJECT_OBJ) \
	-L$(LIB_DIR) $(LIBS:lib%.a=\$N		-l%) \
	-o $@ -Map $@.map

$(IMAGE_DIS): $(IMAGE)
	@$(OBJDUMP) -S $< > $@

$(IMAGE_SREC): $(IMAGE)
	@$(OBJCOPY) -O srec $< $@

$(IMAGE_BIN): $(IMAGE)
	@$(OBJCOPY) -O binary $< $@

$(IMAGE_PIGGY): $(IMAGE)
	@$(OBJCOPY) -O binary -R .note -R .comment -S $< $@.tmp
	@$(LD) -r -b binary $@.tmp -o $@
	@$(RM) $@.tmp

image_size_sort = \
	echo "" >> $@;                    \
	echo "sort by $2 size" >> $@;     \
	cat $@.tmp | sort -g -k $1 >> $@;

$(IMAGE_SIZE): $(IMAGE) $(OBJS_BUILD) $(DEPSINJECT_OBJ)
	@if [ `which $(SIZE) 2> /dev/null` ];  \
	then                                   \
	    $(SIZE) $^ > $@.tmp;               \
		echo "size util generated output for $(TARGET)" > $@; \
		$(call image_size_sort,1,text)     \
		$(call image_size_sort,2,data)     \
		$(call image_size_sort,3,bss)      \
		$(call image_size_sort,4,total)    \
		$(RM) $@.tmp;                      \
	else                                   \
		echo "size util not found" > $@;   \
	fi;

