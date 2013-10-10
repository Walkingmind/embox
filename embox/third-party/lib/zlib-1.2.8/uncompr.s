	.file	"uncompr.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"1.2.8"
	.text
	.p2align 2,,3
	.globl	uncompress
	.type	uncompress, @function
uncompress:
.LFB21:
	.file 1 "uncompr.c"
	.loc 1 29 0
	.cfi_startproc
.LVL0:
	pushl	%edi
.LCFI0:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
.LCFI1:
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
.LCFI2:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subl	$80, %esp
.LCFI3:
	.cfi_def_cfa_offset 96
	movl	100(%esp), %edi
	.loc 1 33 0
	movl	104(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 34 0
	movl	108(%esp), %eax
	movl	%eax, 28(%esp)
	.loc 1 38 0
	movl	96(%esp), %eax
	movl	%eax, 36(%esp)
	.loc 1 39 0
	movl	(%edi), %eax
	movl	%eax, 40(%esp)
	.loc 1 42 0
	movl	$0, 56(%esp)
	.loc 1 43 0
	movl	$0, 60(%esp)
	.loc 1 45 0
	movl	$56, 8(%esp)
	movl	$.LC0, 4(%esp)
	leal	24(%esp), %esi
	movl	%esi, (%esp)
	call	inflateInit_
	movl	%eax, %ebx
.LVL1:
	.loc 1 46 0
	testl	%eax, %eax
	je	.L7
.LVL2:
.L2:
	.loc 1 59 0
	movl	%ebx, %eax
	addl	$80, %esp
	.cfi_remember_state
.LCFI4:
	.cfi_def_cfa_offset 16
	popl	%ebx
.LCFI5:
	.cfi_def_cfa_offset 12
	.cfi_restore 3
	popl	%esi
.LCFI6:
	.cfi_def_cfa_offset 8
	.cfi_restore 6
	popl	%edi
.LCFI7:
	.cfi_def_cfa_offset 4
	.cfi_restore 7
	ret
.LVL3:
	.p2align 2,,3
.L7:
.LCFI8:
	.cfi_restore_state
	.loc 1 48 0
	movl	$4, 4(%esp)
	movl	%esi, (%esp)
	call	inflate
.LVL4:
	movl	%eax, %ebx
.LVL5:
	.loc 1 49 0
	cmpl	$1, %eax
	je	.L3
	.loc 1 50 0
	movl	%esi, (%esp)
	call	inflateEnd
.LVL6:
	.loc 1 51 0
	cmpl	$2, %ebx
	je	.L5
	.loc 1 51 0 is_stmt 0 discriminator 1
	cmpl	$-5, %ebx
	jne	.L2
	movl	28(%esp), %eax
	testl	%eax, %eax
	jne	.L2
.L5:
	.loc 1 52 0 is_stmt 1
	movl	$-3, %ebx
.LVL7:
	jmp	.L2
.LVL8:
	.p2align 2,,3
.L3:
	.loc 1 55 0
	movl	44(%esp), %eax
.LVL9:
	movl	%eax, (%edi)
	.loc 1 57 0
	movl	%esi, (%esp)
	call	inflateEnd
	movl	%eax, %ebx
.LVL10:
	.loc 1 58 0
	jmp	.L2
	.cfi_endproc
.LFE21:
	.size	uncompress, .-uncompress
.Letext0:
	.file 2 "zconf.h"
	.file 3 "zlib.h"
	.file 4 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x2ae
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF40
	.byte	0x1
	.long	.LASF41
	.long	.LASF42
	.long	.Ltext0
	.long	.Letext0
	.long	.Ldebug_line0
	.uleb128 0x2
	.long	.LASF0
	.byte	0x2
	.value	0x170
	.long	0x31
	.uleb128 0x3
	.byte	0x1
	.byte	0x8
	.long	.LASF2
	.uleb128 0x2
	.long	.LASF1
	.byte	0x2
	.value	0x172
	.long	0x44
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF3
	.uleb128 0x2
	.long	.LASF4
	.byte	0x2
	.value	0x173
	.long	0x57
	.uleb128 0x3
	.byte	0x4
	.byte	0x7
	.long	.LASF5
	.uleb128 0x2
	.long	.LASF6
	.byte	0x2
	.value	0x179
	.long	0x25
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF7
	.uleb128 0x4
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.long	.LASF8
	.byte	0x2
	.value	0x17e
	.long	0x4b
	.uleb128 0x2
	.long	.LASF9
	.byte	0x2
	.value	0x182
	.long	0x90
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF10
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF11
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF12
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF13
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF14
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.long	.LASF15
	.uleb128 0x6
	.long	.LASF16
	.byte	0x3
	.byte	0x50
	.long	0xc7
	.uleb128 0x7
	.byte	0x4
	.long	0xcd
	.uleb128 0x8
	.byte	0x1
	.long	0x84
	.long	0xe7
	.uleb128 0x9
	.long	0x84
	.uleb128 0x9
	.long	0x38
	.uleb128 0x9
	.long	0x38
	.byte	0
	.uleb128 0x6
	.long	.LASF17
	.byte	0x3
	.byte	0x51
	.long	0xf2
	.uleb128 0x7
	.byte	0x4
	.long	0xf8
	.uleb128 0xa
	.byte	0x1
	.long	0x109
	.uleb128 0x9
	.long	0x84
	.uleb128 0x9
	.long	0x84
	.byte	0
	.uleb128 0xb
	.long	.LASF31
	.byte	0x38
	.byte	0x3
	.byte	0x55
	.long	0x1da
	.uleb128 0xc
	.long	.LASF18
	.byte	0x3
	.byte	0x56
	.long	0x1da
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xc
	.long	.LASF19
	.byte	0x3
	.byte	0x57
	.long	0x38
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.long	.LASF20
	.byte	0x3
	.byte	0x58
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xc
	.long	.LASF21
	.byte	0x3
	.byte	0x5a
	.long	0x1da
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xc
	.long	.LASF22
	.byte	0x3
	.byte	0x5b
	.long	0x38
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xc
	.long	.LASF23
	.byte	0x3
	.byte	0x5c
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xd
	.string	"msg"
	.byte	0x3
	.byte	0x5e
	.long	0x1e0
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xc
	.long	.LASF24
	.byte	0x3
	.byte	0x5f
	.long	0x203
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xc
	.long	.LASF25
	.byte	0x3
	.byte	0x61
	.long	0xbc
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xc
	.long	.LASF26
	.byte	0x3
	.byte	0x62
	.long	0xe7
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xc
	.long	.LASF27
	.byte	0x3
	.byte	0x63
	.long	0x84
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xc
	.long	.LASF28
	.byte	0x3
	.byte	0x65
	.long	0x71
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xc
	.long	.LASF29
	.byte	0x3
	.byte	0x66
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xc
	.long	.LASF30
	.byte	0x3
	.byte	0x67
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x5e
	.uleb128 0x7
	.byte	0x4
	.long	0x6a
	.uleb128 0xe
	.long	.LASF32
	.byte	0x4
	.byte	0x3
	.value	0x6ce
	.long	0x203
	.uleb128 0xf
	.long	.LASF33
	.byte	0x3
	.value	0x6ce
	.long	0x71
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x1e6
	.uleb128 0x6
	.long	.LASF34
	.byte	0x3
	.byte	0x68
	.long	0x109
	.uleb128 0x10
	.byte	0x1
	.long	.LASF43
	.byte	0x1
	.byte	0x18
	.byte	0x1
	.long	0x71
	.long	.LFB21
	.long	.LFE21
	.long	.LLST0
	.long	0x288
	.uleb128 0x11
	.long	.LASF35
	.byte	0x1
	.byte	0x19
	.long	0x1da
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x11
	.long	.LASF36
	.byte	0x1
	.byte	0x1a
	.long	0x288
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x11
	.long	.LASF37
	.byte	0x1
	.byte	0x1b
	.long	0x28e
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x11
	.long	.LASF38
	.byte	0x1
	.byte	0x1c
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x12
	.long	.LASF39
	.byte	0x1
	.byte	0x1e
	.long	0x209
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x13
	.string	"err"
	.byte	0x1
	.byte	0x1f
	.long	0x71
	.long	.LLST1
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x78
	.uleb128 0x7
	.byte	0x4
	.long	0x294
	.uleb128 0x14
	.long	0x5e
	.uleb128 0x15
	.long	0x6a
	.long	0x2a4
	.uleb128 0x16
	.byte	0
	.uleb128 0x17
	.long	.LASF44
	.byte	0x4
	.byte	0x92
	.long	0x299
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
	.uleb128 0x3
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
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x11
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
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x13
	.uleb128 0x34
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
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
	.long	.LFB21-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI1-.Ltext0
	.long	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI2-.Ltext0
	.long	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI3-.Ltext0
	.long	.LCFI4-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	.LCFI4-.Ltext0
	.long	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI5-.Ltext0
	.long	.LCFI6-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI6-.Ltext0
	.long	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI7-.Ltext0
	.long	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI8-.Ltext0
	.long	.LFE21-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	0
	.long	0
.LLST1:
	.long	.LVL1-.Ltext0
	.long	.LVL2-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL3-.Ltext0
	.long	.LVL4-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL4-1-.Ltext0
	.long	.LVL5-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL5-.Ltext0
	.long	.LVL6-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL6-1-.Ltext0
	.long	.LVL7-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL8-.Ltext0
	.long	.LVL9-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL9-.Ltext0
	.long	.LVL10-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL10-.Ltext0
	.long	.LFE21-.Ltext0
	.value	0x1
	.byte	0x50
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
.LASF20:
	.string	"total_in"
.LASF39:
	.string	"stream"
.LASF24:
	.string	"state"
.LASF21:
	.string	"next_out"
.LASF36:
	.string	"destLen"
.LASF30:
	.string	"reserved"
.LASF1:
	.string	"uInt"
.LASF12:
	.string	"short unsigned int"
.LASF16:
	.string	"alloc_func"
.LASF23:
	.string	"total_out"
.LASF8:
	.string	"uLongf"
.LASF35:
	.string	"dest"
.LASF25:
	.string	"zalloc"
.LASF2:
	.string	"unsigned char"
.LASF17:
	.string	"free_func"
.LASF9:
	.string	"voidpf"
.LASF5:
	.string	"long unsigned int"
.LASF33:
	.string	"dummy"
.LASF22:
	.string	"avail_out"
.LASF32:
	.string	"internal_state"
.LASF29:
	.string	"adler"
.LASF42:
	.string	"/home/anton/workspace/embox-trunk/third-party/lib/zlib-1.2.8"
.LASF43:
	.string	"uncompress"
.LASF40:
	.string	"GNU C 4.6.3"
.LASF3:
	.string	"unsigned int"
.LASF14:
	.string	"long long unsigned int"
.LASF28:
	.string	"data_type"
.LASF0:
	.string	"Byte"
.LASF38:
	.string	"sourceLen"
.LASF13:
	.string	"long long int"
.LASF7:
	.string	"char"
.LASF4:
	.string	"uLong"
.LASF34:
	.string	"z_stream"
.LASF26:
	.string	"zfree"
.LASF27:
	.string	"opaque"
.LASF11:
	.string	"short int"
.LASF18:
	.string	"next_in"
.LASF15:
	.string	"long int"
.LASF44:
	.string	"__assertion_message_buff"
.LASF10:
	.string	"signed char"
.LASF31:
	.string	"z_stream_s"
.LASF37:
	.string	"source"
.LASF19:
	.string	"avail_in"
.LASF6:
	.string	"Bytef"
.LASF41:
	.string	"uncompr.c"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
