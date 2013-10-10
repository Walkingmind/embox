	.file	"compress.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"1.2.8"
	.text
	.p2align 2,,3
	.globl	compress2
	.type	compress2, @function
compress2:
.LFB21:
	.file 1 "compress.c"
	.loc 1 28 0
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
	.loc 1 32 0
	movl	104(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 33 0
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
	.loc 1 44 0
	movl	$0, 64(%esp)
	.loc 1 46 0
	movl	$56, 12(%esp)
	movl	$.LC0, 8(%esp)
	movl	112(%esp), %eax
	movl	%eax, 4(%esp)
	leal	24(%esp), %esi
	movl	%esi, (%esp)
	call	deflateInit_
	movl	%eax, %ebx
.LVL1:
	.loc 1 47 0
	testl	%eax, %eax
	je	.L5
.LVL2:
.L2:
	.loc 1 58 0
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
.L5:
.LCFI8:
	.cfi_restore_state
	.loc 1 49 0
	movl	$4, 4(%esp)
	movl	%esi, (%esp)
	call	deflate
.LVL4:
	movl	%eax, %ebx
.LVL5:
	.loc 1 50 0
	cmpl	$1, %eax
	je	.L3
	.loc 1 51 0
	movl	%esi, (%esp)
	call	deflateEnd
.LVL6:
	.loc 1 52 0
	testl	%ebx, %ebx
	jne	.L2
	movl	$-5, %ebx
.LVL7:
	jmp	.L2
.LVL8:
	.p2align 2,,3
.L3:
	.loc 1 54 0
	movl	44(%esp), %eax
.LVL9:
	movl	%eax, (%edi)
	.loc 1 56 0
	movl	%esi, (%esp)
	call	deflateEnd
	movl	%eax, %ebx
.LVL10:
	.loc 1 57 0
	jmp	.L2
	.cfi_endproc
.LFE21:
	.size	compress2, .-compress2
	.p2align 2,,3
	.globl	compress
	.type	compress, @function
compress:
.LFB22:
	.loc 1 67 0
	.cfi_startproc
.LVL11:
	pushl	%edi
.LCFI9:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
.LCFI10:
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
.LCFI11:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subl	$80, %esp
.LCFI12:
	.cfi_def_cfa_offset 96
	movl	100(%esp), %edi
.LVL12:
.LBB4:
.LBB5:
	.loc 1 32 0
	movl	104(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 33 0
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
	.loc 1 44 0
	movl	$0, 64(%esp)
	.loc 1 46 0
	movl	$56, 12(%esp)
	movl	$.LC0, 8(%esp)
	movl	$-1, 4(%esp)
	leal	24(%esp), %esi
	movl	%esi, (%esp)
	call	deflateInit_
	movl	%eax, %ebx
.LVL13:
	.loc 1 47 0
	testl	%eax, %eax
	je	.L9
.LVL14:
.L7:
.LBE5:
.LBE4:
	.loc 1 69 0
	movl	%ebx, %eax
	addl	$80, %esp
	.cfi_remember_state
.LCFI13:
	.cfi_def_cfa_offset 16
	popl	%ebx
.LCFI14:
	.cfi_def_cfa_offset 12
	.cfi_restore 3
	popl	%esi
.LCFI15:
	.cfi_def_cfa_offset 8
	.cfi_restore 6
	popl	%edi
.LCFI16:
	.cfi_def_cfa_offset 4
	.cfi_restore 7
	ret
.LVL15:
	.p2align 2,,3
.L9:
.LCFI17:
	.cfi_restore_state
.LBB7:
.LBB6:
	.loc 1 49 0
	movl	$4, 4(%esp)
	movl	%esi, (%esp)
	call	deflate
.LVL16:
	movl	%eax, %ebx
.LVL17:
	.loc 1 50 0
	cmpl	$1, %eax
	je	.L8
	.loc 1 51 0
	movl	%esi, (%esp)
	call	deflateEnd
.LVL18:
	.loc 1 52 0
	testl	%ebx, %ebx
	jne	.L7
	movl	$-5, %ebx
.LVL19:
	jmp	.L7
.LVL20:
	.p2align 2,,3
.L8:
	.loc 1 54 0
	movl	44(%esp), %eax
.LVL21:
	movl	%eax, (%edi)
	.loc 1 56 0
	movl	%esi, (%esp)
	call	deflateEnd
	movl	%eax, %ebx
.LVL22:
	jmp	.L7
.LBE6:
.LBE7:
	.cfi_endproc
.LFE22:
	.size	compress, .-compress
	.p2align 2,,3
	.globl	compressBound
	.type	compressBound, @function
compressBound:
.LFB23:
	.loc 1 77 0
	.cfi_startproc
.LVL23:
	movl	4(%esp), %edx
	.loc 1 78 0
	movl	%edx, %eax
	shrl	$12, %eax
	leal	13(%edx,%eax), %ecx
	movl	%edx, %eax
	shrl	$14, %eax
	addl	%ecx, %eax
	.loc 1 79 0
	shrl	$25, %edx
	.loc 1 78 0
	addl	%edx, %eax
	.loc 1 80 0
	ret
	.cfi_endproc
.LFE23:
	.size	compressBound, .-compressBound
.Letext0:
	.file 2 "zconf.h"
	.file 3 "zlib.h"
	.file 4 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x3b9
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF43
	.byte	0x1
	.long	.LASF44
	.long	.LASF45
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
	.long	.LASF46
	.byte	0x1
	.byte	0x16
	.byte	0x1
	.long	0x71
	.byte	0x1
	.long	0x274
	.uleb128 0x11
	.long	.LASF35
	.byte	0x1
	.byte	0x17
	.long	0x1da
	.uleb128 0x11
	.long	.LASF36
	.byte	0x1
	.byte	0x18
	.long	0x274
	.uleb128 0x11
	.long	.LASF37
	.byte	0x1
	.byte	0x19
	.long	0x27a
	.uleb128 0x11
	.long	.LASF38
	.byte	0x1
	.byte	0x1a
	.long	0x4b
	.uleb128 0x11
	.long	.LASF39
	.byte	0x1
	.byte	0x1b
	.long	0x71
	.uleb128 0x12
	.long	.LASF40
	.byte	0x1
	.byte	0x1d
	.long	0x209
	.uleb128 0x13
	.string	"err"
	.byte	0x1
	.byte	0x1e
	.long	0x71
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x78
	.uleb128 0x7
	.byte	0x4
	.long	0x280
	.uleb128 0x14
	.long	0x5e
	.uleb128 0x15
	.long	0x214
	.long	.LFB21
	.long	.LFE21
	.long	.LLST0
	.long	0x2d5
	.uleb128 0x16
	.long	0x226
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x16
	.long	0x231
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x16
	.long	0x23c
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x16
	.long	0x247
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x16
	.long	0x252
	.byte	0x2
	.byte	0x91
	.sleb128 16
	.uleb128 0x17
	.long	0x25d
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x18
	.long	0x268
	.long	.LLST1
	.byte	0
	.uleb128 0x19
	.byte	0x1
	.long	.LASF41
	.byte	0x1
	.byte	0x3e
	.byte	0x1
	.long	0x71
	.long	.LFB22
	.long	.LFE22
	.long	.LLST2
	.long	0x379
	.uleb128 0x1a
	.long	.LASF35
	.byte	0x1
	.byte	0x3f
	.long	0x1da
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1a
	.long	.LASF36
	.byte	0x1
	.byte	0x40
	.long	0x274
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1a
	.long	.LASF37
	.byte	0x1
	.byte	0x41
	.long	0x27a
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1a
	.long	.LASF38
	.byte	0x1
	.byte	0x42
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x1b
	.long	0x214
	.long	.LBB4
	.long	.Ldebug_ranges0+0
	.byte	0x1
	.byte	0x44
	.uleb128 0x16
	.long	0x247
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x16
	.long	0x23c
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x16
	.long	0x231
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x16
	.long	0x226
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1c
	.long	.Ldebug_ranges0+0x18
	.uleb128 0x17
	.long	0x25d
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x18
	.long	0x268
	.long	.LLST3
	.uleb128 0x1d
	.long	0x252
	.sleb128 -1
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x1e
	.byte	0x1
	.long	.LASF42
	.byte	0x1
	.byte	0x4b
	.byte	0x1
	.long	0x4b
	.long	.LFB23
	.long	.LFE23
	.byte	0x2
	.byte	0x74
	.sleb128 4
	.long	0x3a4
	.uleb128 0x1a
	.long	.LASF38
	.byte	0x1
	.byte	0x4c
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x1f
	.long	0x6a
	.long	0x3af
	.uleb128 0x20
	.byte	0
	.uleb128 0x21
	.long	.LASF47
	.byte	0x4
	.byte	0x92
	.long	0x3a4
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
	.uleb128 0x20
	.uleb128 0xb
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
	.uleb128 0x2e
	.byte	0x1
	.uleb128 0x31
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
	.uleb128 0x16
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x17
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x18
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x52
	.uleb128 0x1
	.uleb128 0x55
	.uleb128 0x6
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xd
	.byte	0
	.byte	0
	.uleb128 0x1e
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
	.uleb128 0x1f
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x21
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
.LLST2:
	.long	.LFB22-.Ltext0
	.long	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI9-.Ltext0
	.long	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI10-.Ltext0
	.long	.LCFI11-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI11-.Ltext0
	.long	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI12-.Ltext0
	.long	.LCFI13-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	.LCFI13-.Ltext0
	.long	.LCFI14-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI14-.Ltext0
	.long	.LCFI15-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI15-.Ltext0
	.long	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI16-.Ltext0
	.long	.LCFI17-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI17-.Ltext0
	.long	.LFE22-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	0
	.long	0
.LLST3:
	.long	.LVL13-.Ltext0
	.long	.LVL14-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL15-.Ltext0
	.long	.LVL16-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL16-1-.Ltext0
	.long	.LVL17-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL17-.Ltext0
	.long	.LVL18-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL18-1-.Ltext0
	.long	.LVL19-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL20-.Ltext0
	.long	.LVL21-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL21-.Ltext0
	.long	.LVL22-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL22-.Ltext0
	.long	.LFE22-.Ltext0
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
	.section	.debug_ranges,"",@progbits
.Ldebug_ranges0:
	.long	.LBB4-.Ltext0
	.long	.LBE4-.Ltext0
	.long	.LBB7-.Ltext0
	.long	.LBE7-.Ltext0
	.long	0
	.long	0
	.long	.LBB5-.Ltext0
	.long	.LBE5-.Ltext0
	.long	.LBB6-.Ltext0
	.long	.LBE6-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF20:
	.string	"total_in"
.LASF40:
	.string	"stream"
.LASF24:
	.string	"state"
.LASF39:
	.string	"level"
.LASF36:
	.string	"destLen"
.LASF30:
	.string	"reserved"
.LASF1:
	.string	"uInt"
.LASF12:
	.string	"short unsigned int"
.LASF41:
	.string	"compress"
.LASF16:
	.string	"alloc_func"
.LASF23:
	.string	"total_out"
.LASF8:
	.string	"uLongf"
.LASF35:
	.string	"dest"
.LASF42:
	.string	"compressBound"
.LASF46:
	.string	"compress2"
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
.LASF45:
	.string	"/home/anton/workspace/embox-trunk/third-party/lib/zlib-1.2.8"
.LASF43:
	.string	"GNU C 4.6.3"
.LASF3:
	.string	"unsigned int"
.LASF21:
	.string	"next_out"
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
.LASF44:
	.string	"compress.c"
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
.LASF47:
	.string	"__assertion_message_buff"
.LASF10:
	.string	"signed char"
.LASF31:
	.string	"z_stream_s"
.LASF37:
	.string	"source"
.LASF25:
	.string	"zalloc"
.LASF19:
	.string	"avail_in"
.LASF6:
	.string	"Bytef"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
