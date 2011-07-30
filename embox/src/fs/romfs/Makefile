
# Auto-generated package declaration inherited from parent directory.
# TODO Suggested renaming package to fs.romfs
$_PACKAGE := embox.fs

$_MODS = romfs partition

$_SRCS-romfs += romfs.c
$_DEPS-romfs += core

$_SRCS-partition += partition.c
$_DEPS-partition += core
$_DEPS-partition += embox.driver.flash

#describe special section
ifdef CONFIG_ROMFS_CPIO

$_LDFLAGS += $($_lds)

$_lds := $(OBJ_DIR)/fs/romfs/romfs.lds
$(IMAGE): $($_lds)

$($_lds): $($_SELFDIR)/romfs.lds.S $(AUTOCONF_DIR)/config.lds.h
	mkdir -p $(@D) && $(CPP) -Wp, -P -undef $(CPPFLAGS) \
		-imacros $(AUTOCONF_DIR)/config.lds.h -MMD -MT $@ -MF $@.d -o $@ $<

-include $($_lds).d
endif
