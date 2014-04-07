# $Id$
#
#   Date: Jun 22, 2012
# Author: Eldar Abusalimov
#

.PHONY : all image
all : image
	@echo 'Build complete'

# Run external builders prior to anything else.
-include __extbld
.PHONY : __extbld
__extbld :

include mk/core/common.mk

include $(MKGEN_DIR)/build.mk

TARGET ?= app$(if $(value PLATFORM),-$(PLATFORM))
TARGET := $(TARGET)$(if $(value LOCALVERSION),-$(LOCALVERSION))

IMAGE       = $(BIN_DIR)/$(TARGET)
IMAGE_DIS   = $(IMAGE).dis
IMAGE_BIN   = $(IMAGE).bin
IMAGE_SREC  = $(IMAGE).srec
IMAGE_SIZE  = $(IMAGE).size
IMAGE_PIGGY = $(IMAGE).piggy

include mk/flags.mk # It must be included after a user-defined config.

.SECONDEXPANSION:
include $(MKGEN_DIR)/include.mk

.SECONDARY:
.DELETE_ON_ERROR:

image: $(IMAGE)
image: $(IMAGE_DIS) $(IMAGE_BIN) $(IMAGE_SREC) $(IMAGE_SIZE) $(IMAGE_PIGGY)

CROSS_COMPILE ?=

CC      := $(CROSS_COMPILE)gcc
CPP     := $(CC) -E
CXX     := $(CROSS_COMPILE)g++
AR      := $(CROSS_COMPILE)ar
AS      := $(CROSS_COMPILE)as
LD      := $(CROSS_COMPILE)ld
NM      := $(CROSS_COMPILE)nm
OBJDUMP := $(CROSS_COMPILE)objdump
OBJCOPY := $(CROSS_COMPILE)objcopy
SIZE    := $(CROSS_COMPILE)size

# This must be expanded in a secondary expansion context.
common_prereqs_nomk  = mk/image2.mk mk/flags.mk $(MKGEN_DIR)/build.mk
common_prereqs       = $(common_prereqs_nomk) $(mk_file)
extbld_prerequisites = $(common_prereqs)

VPATH := $(SRCGEN_DIR)

%/. :
	@$(MKDIR) $*

cc_prerequisites    = $(common_prereqs) $(extra_prereqs)

$(OBJ_DIR)/%.o : $(ROOT_DIR)/%.c | $$(@D)/.
	$(CC) $(CFLAGS) $(CPPFLAGS) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o : $(ROOT_DIR)/%.S | $$(@D)/.
	$(CC) $(ASFLAGS) $(CPPFLAGS) $(flags) -c -o $@ $<

$(OBJ_DIR)/%.o : $(ROOT_DIR)/%.cpp | $$(@D)/.
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $(flags) -c -o $@ $<
$(OBJ_DIR)/%.o : $(ROOT_DIR)/%.cxx | $$(@D)/.
	$(CC) $(CXXFLAGS) $(CPPFLAGS) $(flags) -c -o $@ $<

cpp_prerequisites   = $(common_prereqs) $(extra_prereqs)
$(OBJ_DIR)/%.lds : $(ROOT_DIR)/%.lds.S | $$(@D)/.
	$(CPP) -P -undef $(CPPFLAGS) $(flags) -imacros $(SRCGEN_DIR)/config.lds.h \
		-MMD -MT $@ -MF $@.d -o $@ $<

fmt_line = $(addprefix \$(\n)$(\t)$(\t),$1)

ar_prerequisites    = $(common_prereqs) $(ar_objs)
$(OBJ_DIR)/%.a : | $$(@D)/.
	$(AR) $(ARFLAGS) $@ $(call fmt_line,$(ar_objs))

# Here goes image creation rules...

# workaround to get VPATH and GPATH to work with an OBJ_DIR.
$(shell $(MKDIR) $(OBJ_DIR) 2> /dev/null)
GPATH := $(OBJ_DIR:$(ROOT_DIR)/%=%)
VPATH += $(GPATH)

__define_image_rules = $(eval $(value __image_rule))
$(call __define_image_rules,$(IMAGE))

image_prerequisites = $(mk_file) \
	$(ld_scripts) $(ld_objs) $(ld_libs)
ifndef LD_SINGLE_T_OPTION
$(IMAGE): ld_scripts_flag = $(ld_scripts:%=-T%)
else
$(IMAGE): ld_scripts_flag = -T $(ld_scripts)
endif
$(IMAGE): ldflags_all = $(LDFLAGS) $(call fmt_line,$(ld_scripts_flag))

$(IMAGE): | $$(@D)/.
	$(CC) $(ldflags_all) $(call fmt_line,$(ld_objs)) $(call fmt_line,$(ld_libs)) \
	-o $@

$(IMAGE_DIS): $(IMAGE)
	$(OBJDUMP) -S $< > $@

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

$(IMAGE_SIZE): $(IMAGE)
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
		echo "$(SIZE) util not found" > $@;   \
	fi;

