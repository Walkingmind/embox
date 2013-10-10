	.file	"gzclose.c"
	.text
.Ltext0:
	.p2align 2,,3
	.globl	gzclose
	.type	gzclose, @function
gzclose:
.LFB28:
	.file 1 "gzclose.c"
	.loc 1 13 0
	.cfi_startproc
.LVL0:
	movl	4(%esp), %eax
	.loc 1 17 0
	testl	%eax, %eax
	je	.L2
.LVL1:
	.loc 1 21 0
	cmpl	$7247, 12(%eax)
	je	.L5
	.loc 1 21 0 is_stmt 0 discriminator 2
	movl	%eax, 4(%esp)
	jmp	gzclose_w
	.p2align 2,,3
.L5:
	.loc 1 21 0 discriminator 1
	jmp	gzclose_r
.LVL2:
.L2:
	.loc 1 25 0 is_stmt 1
	movl	$-2, %eax
	ret
	.cfi_endproc
.LFE28:
	.size	gzclose, .-gzclose
.Letext0:
	.file 2 "zconf.h"
	.file 3 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h"
	.file 4 "zlib.h"
	.file 5 "gzguts.h"
	.file 6 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x3ee
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF53
	.byte	0x1
	.long	.LASF54
	.long	.LASF55
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF1
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF2
	.uleb128 0x4
	.long	.LASF4
	.byte	0x2
	.value	0x170
	.long	0x4d
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF3
	.uleb128 0x4
	.long	.LASF5
	.byte	0x2
	.value	0x172
	.long	0x2c
	.uleb128 0x4
	.long	.LASF6
	.byte	0x2
	.value	0x173
	.long	0x6c
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF7
	.uleb128 0x4
	.long	.LASF8
	.byte	0x2
	.value	0x179
	.long	0x41
	.uleb128 0x4
	.long	.LASF9
	.byte	0x2
	.value	0x182
	.long	0x8b
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF11
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF12
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF13
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF14
	.uleb128 0x6
	.long	.LASF15
	.byte	0x3
	.byte	0x43
	.long	0x33
	.uleb128 0x6
	.long	.LASF16
	.byte	0x4
	.byte	0x50
	.long	0xc6
	.uleb128 0x7
	.byte	0x4
	.long	0xcc
	.uleb128 0x8
	.byte	0x1
	.long	0x7f
	.long	0xe6
	.uleb128 0x9
	.long	0x7f
	.uleb128 0x9
	.long	0x54
	.uleb128 0x9
	.long	0x54
	.byte	0
	.uleb128 0x6
	.long	.LASF17
	.byte	0x4
	.byte	0x51
	.long	0xf1
	.uleb128 0x7
	.byte	0x4
	.long	0xf7
	.uleb128 0xa
	.byte	0x1
	.long	0x108
	.uleb128 0x9
	.long	0x7f
	.uleb128 0x9
	.long	0x7f
	.byte	0
	.uleb128 0xb
	.long	.LASF31
	.byte	0x38
	.byte	0x4
	.byte	0x55
	.long	0x1d9
	.uleb128 0xc
	.long	.LASF18
	.byte	0x4
	.byte	0x56
	.long	0x1d9
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.long	.LASF19
	.byte	0x4
	.byte	0x57
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.long	.LASF20
	.byte	0x4
	.byte	0x58
	.long	0x60
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.long	.LASF21
	.byte	0x4
	.byte	0x5a
	.long	0x1d9
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xc
	.long	.LASF22
	.byte	0x4
	.byte	0x5b
	.long	0x54
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xc
	.long	.LASF23
	.byte	0x4
	.byte	0x5c
	.long	0x60
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xd
	.string	"msg"
	.byte	0x4
	.byte	0x5e
	.long	0x1df
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.long	.LASF24
	.byte	0x4
	.byte	0x5f
	.long	0x202
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xc
	.long	.LASF25
	.byte	0x4
	.byte	0x61
	.long	0xbb
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.long	.LASF26
	.byte	0x4
	.byte	0x62
	.long	0xe6
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xc
	.long	.LASF27
	.byte	0x4
	.byte	0x63
	.long	0x7f
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.long	.LASF28
	.byte	0x4
	.byte	0x65
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xc
	.long	.LASF29
	.byte	0x4
	.byte	0x66
	.long	0x60
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xc
	.long	.LASF30
	.byte	0x4
	.byte	0x67
	.long	0x60
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x73
	.uleb128 0x7
	.byte	0x4
	.long	0x25
	.uleb128 0xe
	.long	.LASF32
	.byte	0x4
	.byte	0x4
	.value	0x6ce
	.long	0x202
	.uleb128 0xf
	.long	.LASF33
	.byte	0x4
	.value	0x6ce
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x1e5
	.uleb128 0x6
	.long	.LASF34
	.byte	0x4
	.byte	0x68
	.long	0x108
	.uleb128 0x7
	.byte	0x4
	.long	0x4d
	.uleb128 0x4
	.long	.LASF35
	.byte	0x4
	.value	0x4c8
	.long	0x225
	.uleb128 0x7
	.byte	0x4
	.long	0x22b
	.uleb128 0xe
	.long	.LASF36
	.byte	0xc
	.byte	0x4
	.value	0x686
	.long	0x266
	.uleb128 0xf
	.long	.LASF37
	.byte	0x4
	.value	0x687
	.long	0x2c
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xf
	.long	.LASF38
	.byte	0x4
	.value	0x688
	.long	0x213
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x10
	.string	"pos"
	.byte	0x4
	.value	0x689
	.long	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x11
	.byte	0x8c
	.byte	0x5
	.byte	0xa2
	.long	0x383
	.uleb128 0xd
	.string	"x"
	.byte	0x5
	.byte	0xa4
	.long	0x22b
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.long	.LASF39
	.byte	0x5
	.byte	0xa9
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xd
	.string	"fd"
	.byte	0x5
	.byte	0xaa
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xc
	.long	.LASF40
	.byte	0x5
	.byte	0xab
	.long	0x1df
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xc
	.long	.LASF41
	.byte	0x5
	.byte	0xac
	.long	0x2c
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.long	.LASF42
	.byte	0x5
	.byte	0xad
	.long	0x2c
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xd
	.string	"in"
	.byte	0x5
	.byte	0xae
	.long	0x213
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xd
	.string	"out"
	.byte	0x5
	.byte	0xaf
	.long	0x213
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xc
	.long	.LASF43
	.byte	0x5
	.byte	0xb0
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xd
	.string	"how"
	.byte	0x5
	.byte	0xb2
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xc
	.long	.LASF44
	.byte	0x5
	.byte	0xb3
	.long	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xd
	.string	"eof"
	.byte	0x5
	.byte	0xb4
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.uleb128 0xc
	.long	.LASF45
	.byte	0x5
	.byte	0xb5
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x38
	.uleb128 0xc
	.long	.LASF46
	.byte	0x5
	.byte	0xb7
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x3c
	.uleb128 0xc
	.long	.LASF47
	.byte	0x5
	.byte	0xb8
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x40
	.uleb128 0xc
	.long	.LASF48
	.byte	0x5
	.byte	0xba
	.long	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x44
	.uleb128 0xc
	.long	.LASF49
	.byte	0x5
	.byte	0xbb
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x48
	.uleb128 0xd
	.string	"err"
	.byte	0x5
	.byte	0xbd
	.long	0x33
	.byte	0x2
	.byte	0x23
	.uleb128 0x4c
	.uleb128 0xd
	.string	"msg"
	.byte	0x5
	.byte	0xbe
	.long	0x1df
	.byte	0x2
	.byte	0x23
	.uleb128 0x50
	.uleb128 0xc
	.long	.LASF50
	.byte	0x5
	.byte	0xc0
	.long	0x208
	.byte	0x2
	.byte	0x23
	.uleb128 0x54
	.byte	0
	.uleb128 0x6
	.long	.LASF51
	.byte	0x5
	.byte	0xc1
	.long	0x266
	.uleb128 0x6
	.long	.LASF52
	.byte	0x5
	.byte	0xc2
	.long	0x399
	.uleb128 0x7
	.byte	0x4
	.long	0x383
	.uleb128 0x12
	.byte	0x1
	.long	.LASF56
	.byte	0x1
	.byte	0xb
	.byte	0x1
	.long	0x33
	.long	.LFB28
	.long	.LFE28
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.long	0x3d9
	.uleb128 0x13
	.long	.LASF57
	.byte	0x1
	.byte	0xc
	.long	0x219
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x14
	.long	.LASF24
	.byte	0x1
	.byte	0xf
	.long	0x38e
	.long	.LLST0
	.byte	0
	.uleb128 0x15
	.long	0x25
	.long	0x3e4
	.uleb128 0x16
	.byte	0
	.uleb128 0x17
	.long	.LASF58
	.byte	0x6
	.byte	0x92
	.long	0x3d9
	.byte	0x1
	.byte	0x1
	.byte	0
	.section	.debug_abbrev,"",@progbits
.Ldebug_abbrev0:
	.uleb128 0x1
	.uleb128 0x11
	.byte	0x1
	.uleb128 0x25
	.uleb128 0xe
	.uleb128 0x13
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x1b
	.uleb128 0xe
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x10
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x2
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0xe
	.byte	0
	.byte	0
	.uleb128 0x3
	.uleb128 0x24
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3e
	.uleb128 0xb
	.uleb128 0x3
	.uleb128 0x8
	.byte	0
	.byte	0
	.uleb128 0x4
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x16
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xa
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xd
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x13
	.byte	0x1
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xf
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0xd
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x38
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x13
	.byte	0x1
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x12
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x40
	.uleb128 0xa
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x16
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LVL1-.Ltext0
	.long	.LVL2-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 0
	.long	0
	.long	0
	.section	.debug_aranges,"",@progbits
	.long	0x1c
	.value	0x2
	.long	.Ldebug_info0
	.byte	0x4
	.byte	0
	.value	0
	.value	0
	.long	.Ltext0
	.long	.Letext0-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF58:
	.string	"__assertion_message_buff"
.LASF18:
	.string	"next_in"
.LASF19:
	.string	"avail_in"
.LASF40:
	.string	"path"
.LASF26:
	.string	"zfree"
.LASF34:
	.string	"z_stream"
.LASF27:
	.string	"opaque"
.LASF14:
	.string	"long long unsigned int"
.LASF43:
	.string	"direct"
.LASF38:
	.string	"next"
.LASF8:
	.string	"Bytef"
.LASF28:
	.string	"data_type"
.LASF13:
	.string	"long long int"
.LASF10:
	.string	"signed char"
.LASF24:
	.string	"state"
.LASF2:
	.string	"long int"
.LASF36:
	.string	"gzFile_s"
.LASF54:
	.string	"gzclose.c"
.LASF37:
	.string	"have"
.LASF15:
	.string	"off_t"
.LASF52:
	.string	"gz_statep"
.LASF33:
	.string	"dummy"
.LASF30:
	.string	"reserved"
.LASF1:
	.string	"unsigned int"
.LASF7:
	.string	"long unsigned int"
.LASF49:
	.string	"seek"
.LASF50:
	.string	"strm"
.LASF55:
	.string	"/home/anton/workspace/embox-trunk/third-party/lib/zlib-1.2.8"
.LASF46:
	.string	"level"
.LASF41:
	.string	"size"
.LASF12:
	.string	"short unsigned int"
.LASF29:
	.string	"adler"
.LASF5:
	.string	"uInt"
.LASF20:
	.string	"total_in"
.LASF16:
	.string	"alloc_func"
.LASF6:
	.string	"uLong"
.LASF51:
	.string	"gz_state"
.LASF47:
	.string	"strategy"
.LASF23:
	.string	"total_out"
.LASF3:
	.string	"unsigned char"
.LASF21:
	.string	"next_out"
.LASF17:
	.string	"free_func"
.LASF32:
	.string	"internal_state"
.LASF11:
	.string	"short int"
.LASF57:
	.string	"file"
.LASF31:
	.string	"z_stream_s"
.LASF22:
	.string	"avail_out"
.LASF35:
	.string	"gzFile"
.LASF9:
	.string	"voidpf"
.LASF53:
	.string	"GNU C 4.6.3"
.LASF0:
	.string	"char"
.LASF39:
	.string	"mode"
.LASF4:
	.string	"Byte"
.LASF25:
	.string	"zalloc"
.LASF48:
	.string	"skip"
.LASF42:
	.string	"want"
.LASF56:
	.string	"gzclose"
.LASF44:
	.string	"start"
.LASF45:
	.string	"past"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
