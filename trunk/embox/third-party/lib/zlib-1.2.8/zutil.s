	.file	"zutil.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"1.2.8"
	.text
	.p2align 2,,3
	.globl	zlibVersion
	.type	zlibVersion, @function
zlibVersion:
.LFB27:
	.file 1 "zutil.c"
	.loc 1 31 0
	.cfi_startproc
	.loc 1 33 0
	movl	$.LC0, %eax
	ret
	.cfi_endproc
.LFE27:
	.size	zlibVersion, .-zlibVersion
	.p2align 2,,3
	.globl	zlibCompileFlags
	.type	zlibCompileFlags, @function
zlibCompileFlags:
.LFB28:
	.loc 1 36 0
	.cfi_startproc
.LVL0:
	.loc 1 116 0
	movl	$85, %eax
	ret
	.cfi_endproc
.LFE28:
	.size	zlibCompileFlags, .-zlibCompileFlags
	.p2align 2,,3
	.globl	zError
	.type	zError, @function
zError:
.LFB29:
	.loc 1 138 0
	.cfi_startproc
.LVL1:
	.loc 1 139 0
	movl	$2, %eax
	subl	4(%esp), %eax
	movl	z_errmsg(,%eax,4), %eax
	.loc 1 140 0
	ret
	.cfi_endproc
.LFE29:
	.size	zError, .-zError
	.p2align 2,,3
	.globl	zcalloc
	.hidden	zcalloc
	.type	zcalloc, @function
zcalloc:
.LFB30:
	.loc 1 308 0
	.cfi_startproc
.LVL2:
	movl	12(%esp), %eax
	.loc 1 310 0
	imull	8(%esp), %eax
	movl	%eax, 4(%esp)
	jmp	malloc
	.cfi_endproc
.LFE30:
	.size	zcalloc, .-zcalloc
	.p2align 2,,3
	.globl	zcfree
	.hidden	zcfree
	.type	zcfree, @function
zcfree:
.LFB31:
	.loc 1 317 0
	.cfi_startproc
.LVL3:
	.loc 1 318 0
	movl	8(%esp), %eax
	movl	%eax, 4(%esp)
	jmp	free
	.cfi_endproc
.LFE31:
	.size	zcfree, .-zcfree
	.globl	z_errmsg
	.section	.rodata.str1.1
.LC1:
	.string	"need dictionary"
.LC2:
	.string	"stream end"
.LC3:
	.string	""
.LC4:
	.string	"file error"
.LC5:
	.string	"stream error"
.LC6:
	.string	"data error"
.LC7:
	.string	"insufficient memory"
.LC8:
	.string	"buffer error"
.LC9:
	.string	"incompatible version"
	.section	.rodata
	.align 32
	.type	z_errmsg, @object
	.size	z_errmsg, 40
z_errmsg:
	.long	.LC1
	.long	.LC2
	.long	.LC3
	.long	.LC4
	.long	.LC5
	.long	.LC6
	.long	.LC7
	.long	.LC8
	.long	.LC9
	.long	.LC3
	.text
.Letext0:
	.file 2 "zconf.h"
	.file 3 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x1c8
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF20
	.byte	0x1
	.long	.LASF21
	.long	.LASF22
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.byte	0x1
	.byte	0x8
	.long	.LASF0
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF1
	.uleb128 0x3
	.long	.LASF4
	.byte	0x2
	.value	0x173
	.long	0x3f
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF3
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x3
	.long	.LASF5
	.byte	0x2
	.value	0x182
	.long	0x60
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF6
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF9
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF10
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF11
	.uleb128 0x6
	.byte	0x4
	.long	0x92
	.uleb128 0x7
	.long	0x46
	.uleb128 0x6
	.byte	0x4
	.long	0x46
	.uleb128 0x8
	.byte	0x1
	.long	.LASF23
	.byte	0x1
	.byte	0x1e
	.byte	0x1
	.long	0x8c
	.long	.LFB27
	.long	.LFE27
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.uleb128 0x9
	.byte	0x1
	.long	.LASF12
	.byte	0x1
	.byte	0x23
	.byte	0x1
	.long	0x33
	.long	.LFB28
	.long	.LFE28
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.long	0xde
	.uleb128 0xa
	.long	.LASF24
	.byte	0x1
	.byte	0x25
	.long	0x33
	.byte	0x55
	.byte	0
	.uleb128 0x9
	.byte	0x1
	.long	.LASF13
	.byte	0x1
	.byte	0x88
	.byte	0x1
	.long	0x8c
	.long	.LFB29
	.long	.LFE29
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.long	0x109
	.uleb128 0xb
	.string	"err"
	.byte	0x1
	.byte	0x89
	.long	0x4d
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0xc
	.byte	0x1
	.long	.LASF14
	.byte	0x1
	.value	0x130
	.byte	0x1
	.long	0x54
	.long	.LFB30
	.long	.LFE30
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.long	0x154
	.uleb128 0xd
	.long	.LASF15
	.byte	0x1
	.value	0x131
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xd
	.long	.LASF16
	.byte	0x1
	.value	0x132
	.long	0x2c
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0xd
	.long	.LASF17
	.byte	0x1
	.value	0x133
	.long	0x2c
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.byte	0
	.uleb128 0xe
	.byte	0x1
	.long	.LASF25
	.byte	0x1
	.value	0x13a
	.byte	0x1
	.long	.LFB31
	.long	.LFE31
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.long	0x18c
	.uleb128 0xd
	.long	.LASF15
	.byte	0x1
	.value	0x13b
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0xf
	.string	"ptr"
	.byte	0x1
	.value	0x13c
	.long	0x54
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.byte	0
	.uleb128 0x10
	.long	0x46
	.long	0x197
	.uleb128 0x11
	.byte	0
	.uleb128 0x12
	.long	.LASF18
	.byte	0x3
	.byte	0x92
	.long	0x18c
	.byte	0x1
	.byte	0x1
	.uleb128 0x10
	.long	0x97
	.long	0x1b4
	.uleb128 0x13
	.long	0x2c
	.byte	0x9
	.byte	0
	.uleb128 0x14
	.long	.LASF19
	.byte	0x1
	.byte	0x11
	.long	0x1c6
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	z_errmsg
	.uleb128 0x7
	.long	0x1a4
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
	.uleb128 0x4
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
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x2e
	.byte	0
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
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
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
	.uleb128 0xc
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
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
	.uleb128 0xd
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0xe
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x27
	.uleb128 0xc
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
	.uleb128 0xf
	.uleb128 0x5
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x10
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x12
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
	.uleb128 0x13
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
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
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.byte	0
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
.LASF9:
	.string	"long long int"
.LASF1:
	.string	"unsigned int"
.LASF5:
	.string	"voidpf"
.LASF20:
	.string	"GNU C 4.6.3"
.LASF19:
	.string	"z_errmsg"
.LASF14:
	.string	"zcalloc"
.LASF16:
	.string	"items"
.LASF23:
	.string	"zlibVersion"
.LASF25:
	.string	"zcfree"
.LASF22:
	.string	"/home/user/workspace/embox/third-party/lib/zlib-1.2.8"
.LASF15:
	.string	"opaque"
.LASF10:
	.string	"long long unsigned int"
.LASF4:
	.string	"uLong"
.LASF18:
	.string	"__assertion_message_buff"
.LASF24:
	.string	"flags"
.LASF0:
	.string	"unsigned char"
.LASF3:
	.string	"char"
.LASF13:
	.string	"zError"
.LASF2:
	.string	"long unsigned int"
.LASF11:
	.string	"long int"
.LASF21:
	.string	"zutil.c"
.LASF8:
	.string	"short unsigned int"
.LASF6:
	.string	"signed char"
.LASF17:
	.string	"size"
.LASF7:
	.string	"short int"
.LASF12:
	.string	"zlibCompileFlags"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
