# Generated by GNU Make 3.81. Do not edit.

source_file := third-party/lib/zlib-1.2.8/../../../../../../third-party/lib/zlib-1.2.8/minigzip.o

source_base := $(basename $(source_file))

$(OBJ_DIR)/$(source_base).o : $$(o_prerequisites)

$(OBJ_DIR)/$(source_base).o : mk_file := $(MKGEN_DIR)/$(source_file).rule.mk

$(OBJ_DIR)/$(source_base).o : flags := -include $(SRCGEN_DIR)/include/module/third_party/zlib/gzip.h -D__EMBUILD_MOD__=third_party__zlib__gzip

$(OBJ_DIR)/$(source_base).o : 
	true

-include $(OBJ_DIR)/$(source_base).d

