	.file	"minigzip.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s: %s\n"
	.text
	.p2align 2,,3
	.globl	error
	.type	error, @function
error:
.LFB28:
	.file 1 "test/minigzip.c"
	.loc 1 353 0
	.cfi_startproc
.LVL0:
	subl	$28, %esp
.LCFI0:
	.cfi_def_cfa_offset 32
	.loc 1 354 0
	movl	32(%esp), %eax
	movl	%eax, 12(%esp)
	movl	prog, %eax
	movl	%eax, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	.loc 1 355 0
	movl	$1, (%esp)
	call	exit
	.cfi_endproc
.LFE28:
	.size	error, .-error
	.section	.rodata.str1.1
.LC1:
	.string	"fread"
.LC2:
	.string	"failed gzclose"
	.text
	.p2align 2,,3
	.globl	gz_compress
	.type	gz_compress, @function
gz_compress:
.LFB29:
	.loc 1 365 0
	.cfi_startproc
.LVL1:
	pushl	%ebp
.LCFI1:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI2:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI3:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI4:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$16428, %esp
.LCFI5:
	.cfi_def_cfa_offset 16448
	movl	16448(%esp), %esi
	movl	16452(%esp), %ebp
	leal	28(%esp), %edi
	jmp	.L5
.LVL2:
	.p2align 2,,3
.L11:
	.loc 1 384 0
	movl	%ebx, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%ebp, (%esp)
	call	gzwrite
	cmpl	%ebx, %eax
	jne	.L9
.LVL3:
.L5:
	.loc 1 377 0
	movl	%esi, 12(%esp)
	movl	$16384, 8(%esp)
	movl	$1, 4(%esp)
	movl	%edi, (%esp)
	call	fread
	movl	%eax, %ebx
.LVL4:
	.loc 1 378 0
	movl	%esi, (%esp)
	call	ferror
.LVL5:
	testl	%eax, %eax
	jne	.L10
	.loc 1 382 0
	testl	%ebx, %ebx
	jne	.L11
	.loc 1 386 0
	movl	%esi, (%esp)
	call	fclose
	.loc 1 387 0
	movl	%ebp, (%esp)
	call	gzclose
	testl	%eax, %eax
	jne	.L12
	.loc 1 388 0
	addl	$16428, %esp
	.cfi_remember_state
.LCFI6:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI7:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
.LVL6:
	popl	%esi
.LCFI8:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI9:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI10:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL7:
.L10:
.LCFI11:
	.cfi_restore_state
	.loc 1 379 0
	movl	$.LC1, (%esp)
	call	perror
	.loc 1 380 0
	movl	$1, (%esp)
	call	exit
.L9:
.LVL8:
.LBB11:
.LBB12:
	.loc 1 384 0
	leal	16412(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%ebp, (%esp)
	call	gzerror
	movl	%eax, (%esp)
	call	error
.LVL9:
.L12:
.LBE12:
.LBE11:
	.loc 1 387 0 discriminator 1
	movl	$.LC2, (%esp)
	call	error
	.cfi_endproc
.LFE29:
	.size	gz_compress, .-gz_compress
	.section	.rodata.str1.1
.LC3:
	.string	"failed fwrite"
.LC4:
	.string	"failed fclose"
	.text
	.p2align 2,,3
	.globl	gz_uncompress
	.type	gz_uncompress, @function
gz_uncompress:
.LFB30:
	.loc 1 433 0
	.cfi_startproc
.LVL10:
	pushl	%ebp
.LCFI12:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI13:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI14:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI15:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$16428, %esp
.LCFI16:
	.cfi_def_cfa_offset 16448
	movl	16448(%esp), %edi
	movl	16452(%esp), %ebp
	leal	28(%esp), %esi
	jmp	.L16
.LVL11:
	.p2align 2,,3
.L22:
	.loc 1 443 0
	movl	%ebp, 12(%esp)
	movl	%eax, 8(%esp)
	movl	$1, 4(%esp)
	movl	%esi, (%esp)
	call	fwrite
.LVL12:
	cmpl	%ebx, %eax
	jne	.L20
.LVL13:
.L16:
	.loc 1 439 0
	movl	$16384, 8(%esp)
	movl	%esi, 4(%esp)
	movl	%edi, (%esp)
	call	gzread
	movl	%eax, %ebx
.LVL14:
	.loc 1 440 0
	cmpl	$0, %eax
	jl	.L21
	.loc 1 441 0
	jne	.L22
	.loc 1 447 0
	movl	%ebp, (%esp)
	call	fclose
.LVL15:
	testl	%eax, %eax
	jne	.L23
	.loc 1 449 0
	movl	%edi, (%esp)
	call	gzclose
	testl	%eax, %eax
	jne	.L24
	.loc 1 450 0
	addl	$16428, %esp
	.cfi_remember_state
.LCFI17:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI18:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
.LVL16:
	popl	%esi
.LCFI19:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI20:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI21:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL17:
.L21:
.LCFI22:
	.cfi_restore_state
.LBB15:
.LBB16:
	.loc 1 440 0
	leal	16412(%esp), %eax
.LVL18:
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	gzerror
	movl	%eax, (%esp)
	call	error
.LVL19:
.L20:
.LBE16:
.LBE15:
	.loc 1 444 0
	movl	$.LC3, (%esp)
	call	error
.L24:
	.loc 1 449 0 discriminator 1
	movl	$.LC2, (%esp)
	call	error
.L23:
	.loc 1 447 0 discriminator 1
	movl	$.LC4, (%esp)
	call	error
	.cfi_endproc
.LFE30:
	.size	gz_uncompress, .-gz_uncompress
	.section	.rodata.str1.1
.LC5:
	.string	"%s: filename too long\n"
.LC6:
	.string	".gz"
.LC7:
	.string	"%s%s"
.LC8:
	.string	"rb"
.LC9:
	.string	"%s: can't gzopen %s\n"
	.text
	.p2align 2,,3
	.globl	file_compress
	.type	file_compress, @function
file_compress:
.LFB31:
	.loc 1 460 0
	.cfi_startproc
.LVL20:
	pushl	%edi
.LCFI23:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
.LCFI24:
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
.LCFI25:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subl	$1056, %esp
.LCFI26:
	.cfi_def_cfa_offset 1072
	movl	1072(%esp), %ebx
	.loc 1 465 0
	xorl	%eax, %eax
	movl	$-1, %ecx
	movl	%ebx, %edi
	repnz scasb
.LVL21:
	notl	%ecx
	addl	$2, %ecx
	cmpl	$1023, %ecx
	ja	.L29
	.loc 1 471 0
	movl	$.LC6, 16(%esp)
	movl	%ebx, 12(%esp)
	movl	$.LC7, 8(%esp)
	movl	$1024, 4(%esp)
	leal	32(%esp), %esi
	movl	%esi, (%esp)
	call	snprintf
	.loc 1 477 0
	movl	$.LC8, 4(%esp)
	movl	%ebx, (%esp)
	call	fopen
	movl	%eax, %edi
.LVL22:
	.loc 1 478 0
	testl	%eax, %eax
	je	.L30
	.loc 1 482 0
	movl	1076(%esp), %eax
.LVL23:
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	gzopen
.LVL24:
	.loc 1 483 0
	testl	%eax, %eax
	je	.L31
	.loc 1 487 0
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	gz_compress
.LVL25:
	.loc 1 489 0
	movl	%ebx, (%esp)
	call	unlink
	.loc 1 490 0
	addl	$1056, %esp
	.cfi_remember_state
.LCFI27:
	.cfi_def_cfa_offset 16
	popl	%ebx
.LCFI28:
	.cfi_def_cfa_offset 12
	.cfi_restore 3
	popl	%esi
.LCFI29:
	.cfi_def_cfa_offset 8
	.cfi_restore 6
	popl	%edi
.LCFI30:
	.cfi_def_cfa_offset 4
	.cfi_restore 7
.LVL26:
	ret
.L29:
.LCFI31:
	.cfi_restore_state
	.loc 1 466 0
	movl	prog, %eax
	movl	%eax, 8(%esp)
	movl	$.LC5, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	.loc 1 467 0
	movl	$1, (%esp)
	call	exit
.LVL27:
.L31:
	.loc 1 484 0
	movl	%esi, 12(%esp)
	movl	prog, %eax
.LVL28:
	movl	%eax, 8(%esp)
	movl	$.LC9, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	.loc 1 485 0
	movl	$1, (%esp)
	call	exit
.L30:
	.loc 1 479 0
	movl	%ebx, (%esp)
	call	perror
	.loc 1 480 0
	movl	$1, (%esp)
	call	exit
	.cfi_endproc
.LFE31:
	.size	file_compress, .-file_compress
	.section	.rodata.str1.1
.LC10:
	.string	"%s"
.LC11:
	.string	"wb"
	.text
	.p2align 2,,3
	.globl	file_uncompress
	.type	file_uncompress, @function
file_uncompress:
.LFB32:
	.loc 1 498 0
	.cfi_startproc
.LVL29:
	pushl	%ebp
.LCFI32:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI33:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI34:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI35:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$1068, %esp
.LCFI36:
	.cfi_def_cfa_offset 1088
	movl	1088(%esp), %ebx
	.loc 1 503 0
	xorl	%eax, %eax
	movl	$-1, %ecx
	movl	%ebx, %edi
	repnz scasb
.LVL30:
	movl	%ecx, %esi
	notl	%esi
	leal	-1(%esi), %edx
.LVL31:
	.loc 1 505 0
	leal	2(%esi), %eax
	cmpl	$1023, %eax
	ja	.L38
	.loc 1 511 0
	movl	%ebx, 12(%esp)
	movl	$.LC10, 8(%esp)
	movl	$1024, 4(%esp)
	leal	32(%esp), %ebp
	movl	%ebp, (%esp)
	movl	%edx, 24(%esp)
	call	snprintf
.LVL32:
	.loc 1 516 0
	movl	24(%esp), %edx
	cmpl	$3, %edx
	jbe	.L34
	.loc 1 516 0 is_stmt 0 discriminator 1
	leal	-4(%esi), %eax
	leal	(%ebx,%eax), %esi
.LVL33:
	movl	$.LC6, %edi
	movl	$4, %ecx
	repz cmpsb
	seta	28(%esp)
	setb	%cl
	cmpb	%cl, 28(%esp)
	je	.L39
.LVL34:
.L34:
	.loc 1 524 0 is_stmt 1
	movl	$.LC6, 12(%esp)
	movl	$.LC10, 8(%esp)
	movl	$1024, %eax
	subl	%edx, %eax
	movl	%eax, 4(%esp)
	addl	%ebp, %edx
	movl	%edx, (%esp)
	call	snprintf
	.loc 1 521 0
	movl	%ebx, 28(%esp)
	.loc 1 522 0
	movl	%ebp, %esi
.LVL35:
.L35:
	.loc 1 529 0
	movl	$.LC8, 4(%esp)
	movl	%esi, (%esp)
	call	gzopen
	movl	%eax, %edi
.LVL36:
	.loc 1 530 0
	testl	%eax, %eax
	je	.L40
	.loc 1 534 0
	movl	$.LC11, 4(%esp)
	movl	28(%esp), %eax
.LVL37:
	movl	%eax, (%esp)
	call	fopen
.LVL38:
	.loc 1 535 0
	testl	%eax, %eax
	je	.L41
	.loc 1 540 0
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	gz_uncompress
.LVL39:
	.loc 1 542 0
	movl	%esi, (%esp)
	call	unlink
	.loc 1 543 0
	addl	$1068, %esp
	.cfi_remember_state
.LCFI37:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI38:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
.LCFI39:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
.LVL40:
	popl	%edi
.LCFI40:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
.LVL41:
	popl	%ebp
.LCFI41:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL42:
	.p2align 2,,3
.L39:
.LCFI42:
	.cfi_restore_state
	.loc 1 519 0
	movb	$0, 32(%esp,%eax)
	.loc 1 517 0
	movl	%ebx, %esi
	.loc 1 518 0
	movl	%ebp, 28(%esp)
	.loc 1 519 0
	jmp	.L35
.LVL43:
.L38:
	.loc 1 506 0
	movl	prog, %eax
	movl	%eax, 8(%esp)
	movl	$.LC5, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
.LVL44:
	.loc 1 507 0
	movl	$1, (%esp)
	call	exit
.LVL45:
.L41:
	.loc 1 536 0
	movl	%ebx, (%esp)
	call	perror
.LVL46:
	.loc 1 537 0
	movl	$1, (%esp)
	call	exit
.L40:
	.loc 1 531 0
	movl	%esi, 12(%esp)
	movl	prog, %eax
	movl	%eax, 8(%esp)
	movl	$.LC9, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	.loc 1 532 0
	movl	$1, (%esp)
	call	exit
	.cfi_endproc
.LFE32:
	.size	file_uncompress, .-file_uncompress
	.section	.rodata.str1.1
.LC12:
	.string	"wb6 "
.LC13:
	.string	"gunzip"
.LC14:
	.string	"zcat"
.LC15:
	.string	"-c"
.LC16:
	.string	"-d"
.LC17:
	.string	"-f"
.LC18:
	.string	"-h"
.LC19:
	.string	"-r"
.LC20:
	.string	"can't gzdopen stdin"
.LC21:
	.string	"can't gzdopen stdout"
	.text
	.p2align 2,,3
	.globl	main_minigzip
	.type	main_minigzip, @function
main_minigzip:
.LFB33:
	.loc 1 559 0
	.cfi_startproc
.LVL47:
	pushl	%ebp
.LCFI43:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI44:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI45:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI46:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$92, %esp
.LCFI47:
	.cfi_def_cfa_offset 112
	movl	116(%esp), %ebx
.LVL48:
	.loc 1 566 0
	movl	$.LC12, 12(%esp)
	movl	$.LC10, 8(%esp)
	movl	$20, 4(%esp)
	leal	60(%esp), %eax
	movl	%eax, (%esp)
	call	snprintf
	.loc 1 571 0
	movl	(%ebx), %eax
	movl	%eax, prog
	.loc 1 572 0
	movl	(%ebx), %ebp
	movl	$47, 4(%esp)
	movl	%ebp, (%esp)
	call	strrchr
.LVL49:
	.loc 1 573 0
	testl	%eax, %eax
	je	.L43
	.loc 1 574 0
	leal	1(%eax), %ebp
.LVL50:
.L43:
	.loc 1 577 0
	movl	112(%esp), %eax
	decl	%eax
	movl	%eax, 36(%esp)
.LVL51:
	addl	$4, %ebx
.LVL52:
	.loc 1 579 0
	movl	$.LC13, %edi
	movl	$7, %ecx
	movl	%ebp, %esi
	repz cmpsb
.LVL53:
	je	.L65
	.loc 1 581 0
	movl	$.LC14, %edi
	movl	$5, %ecx
	movl	%ebp, %esi
	repz cmpsb
	seta	%al
.LVL54:
	setb	%dl
	subb	%dl, %al
	movsbl	%al, %eax
	.loc 1 561 0
	cmpl	$1, %eax
	sbbl	%edx, %edx
	andl	$1, %edx
	movl	%edx, 44(%esp)
	movl	%edx, 40(%esp)
.L44:
.LVL55:
	.loc 1 584 0 discriminator 1
	movl	36(%esp), %ecx
	testl	%ecx, %ecx
	jle	.L45
	movl	$.LC15, %ebp
	.loc 1 585 0
	movl	$3, %edx
	jmp	.L50
	.p2align 2,,3
.L78:
	.loc 1 587 0
	movl	$.LC16, %edi
	movl	%eax, %esi
	movl	%edx, %ecx
	repz cmpsb
	seta	35(%esp)
	setb	%cl
	cmpb	%cl, 35(%esp)
	je	.L68
	.loc 1 589 0
	movl	$.LC17, %edi
	movl	%eax, %esi
	movl	%edx, %ecx
	repz cmpsb
	seta	35(%esp)
	setb	%cl
	cmpb	%cl, 35(%esp)
	jne	.L47
	.loc 1 590 0
	movb	$102, 63(%esp)
.L46:
.LVL56:
	.loc 1 600 0
	addl	$4, %ebx
.LVL57:
	.loc 1 584 0
	decl	36(%esp)
	je	.L45
.LVL58:
.L50:
	.loc 1 585 0
	movl	(%ebx), %eax
	movl	%eax, %esi
	movl	%ebp, %edi
	movl	%edx, %ecx
	repz cmpsb
	seta	35(%esp)
	setb	%cl
	cmpb	%cl, 35(%esp)
	jne	.L78
	.loc 1 586 0
	movl	$1, 40(%esp)
.LVL59:
	.loc 1 600 0
	addl	$4, %ebx
.LVL60:
	.loc 1 584 0
	decl	36(%esp)
	jne	.L50
.LVL61:
.L45:
	.loc 1 602 0
	cmpb	$32, 63(%esp)
	je	.L79
.L51:
	.loc 1 604 0
	movl	36(%esp), %edx
	testl	%edx, %edx
	jne	.L76
	.loc 1 607 0
	movl	44(%esp), %eax
	testl	%eax, %eax
	je	.L53
	.loc 1 608 0
	movl	$.LC8, 4(%esp)
	.loc 1 651 0
	movl	stdin, %eax
	.loc 1 608 0
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	gzdopen
.LVL62:
	.loc 1 609 0
	testl	%eax, %eax
	je	.L80
	.loc 1 610 0
	movl	stdout, %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	gz_uncompress
.LVL63:
.L55:
	.loc 1 651 0
	xorl	%eax, %eax
	addl	$92, %esp
	.cfi_remember_state
.LCFI48:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI49:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
.LVL64:
	popl	%esi
.LCFI50:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI51:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI52:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL65:
	.p2align 2,,3
.L68:
.LCFI53:
	.cfi_restore_state
	.loc 1 588 0
	movl	$1, 44(%esp)
	jmp	.L46
	.p2align 2,,3
.L47:
	.loc 1 591 0
	movl	$.LC18, %edi
	movl	%eax, %esi
	movl	%edx, %ecx
	repz cmpsb
	seta	35(%esp)
	setb	%cl
	cmpb	%cl, 35(%esp)
	jne	.L48
	.loc 1 592 0
	movb	$104, 63(%esp)
	jmp	.L46
	.p2align 2,,3
.L48:
	.loc 1 593 0
	movl	$.LC19, %edi
	movl	%eax, %esi
	movl	%edx, %ecx
	repz cmpsb
	seta	%cl
	setb	35(%esp)
	cmpb	35(%esp), %cl
	jne	.L49
	.loc 1 594 0
	movb	$82, 63(%esp)
	jmp	.L46
	.p2align 2,,3
.L49:
	.loc 1 595 0
	cmpb	$45, (%eax)
	jne	.L45
	.loc 1 595 0 is_stmt 0 discriminator 1
	movb	1(%eax), %cl
	cmpb	$48, %cl
	jle	.L45
	cmpb	$57, %cl
	jg	.L45
	cmpb	$0, 2(%eax)
	jne	.L45
	.loc 1 597 0 is_stmt 1
	movb	%cl, 62(%esp)
	jmp	.L46
.LVL66:
	.p2align 2,,3
.L65:
	.loc 1 580 0
	movl	$1, 44(%esp)
	.loc 1 560 0
	movl	$0, 40(%esp)
	jmp	.L44
.LVL67:
	.p2align 2,,3
.L76:
	movl	40(%esp), %ebp
	movl	44(%esp), %edi
	movl	36(%esp), %esi
	jmp	.L69
.LVL68:
	.p2align 2,,3
.L82:
	.loc 1 622 0
	testl	%ebp, %ebp
	je	.L58
	.loc 1 623 0
	movl	$.LC8, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	gzopen
.LVL69:
	.loc 1 624 0
	testl	%eax, %eax
	je	.L81
	.loc 1 627 0
	movl	stdout, %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	gz_uncompress
.LVL70:
.L60:
	.loc 1 648 0
	addl	$4, %ebx
.LVL71:
	decl	%esi
.LVL72:
	je	.L55
.LVL73:
.L69:
	.loc 1 621 0
	testl	%edi, %edi
	jne	.L82
	.loc 1 632 0
	testl	%ebp, %ebp
	je	.L61
.LBB17:
	.loc 1 633 0
	movl	$.LC8, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	fopen
	movl	%eax, %edx
.LVL74:
	.loc 1 635 0
	testl	%eax, %eax
	je	.L83
	.loc 1 638 0
	leal	60(%esp), %eax
.LVL75:
	movl	%eax, 4(%esp)
	.loc 1 651 0
	movl	stdout, %eax
	.loc 1 638 0
	movl	(%eax), %eax
	movl	%eax, (%esp)
	movl	%edx, 28(%esp)
	call	gzdopen
.LVL76:
	.loc 1 639 0
	testl	%eax, %eax
	movl	28(%esp), %edx
	je	.L77
	.loc 1 641 0
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	gz_compress
.LVL77:
	jmp	.L60
	.p2align 2,,3
.L58:
.LBE17:
	.loc 1 629 0
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	file_uncompress
	jmp	.L60
	.p2align 2,,3
.L61:
	.loc 1 645 0
	leal	60(%esp), %edx
	movl	%edx, 4(%esp)
	movl	(%ebx), %eax
	movl	%eax, (%esp)
	call	file_compress
	jmp	.L60
.LVL78:
.L53:
	.loc 1 612 0
	leal	60(%esp), %edx
	movl	%edx, 4(%esp)
	.loc 1 651 0
	movl	stdout, %eax
	.loc 1 612 0
	movl	(%eax), %eax
	movl	%eax, (%esp)
	call	gzdopen
.LVL79:
	.loc 1 613 0
	testl	%eax, %eax
	je	.L77
	.loc 1 614 0
	movl	%eax, 4(%esp)
	movl	stdin, %eax
.LVL80:
	movl	%eax, (%esp)
	call	gz_compress
.LVL81:
	.loc 1 651 0
	xorl	%eax, %eax
	addl	$92, %esp
	.cfi_remember_state
.LCFI54:
	.cfi_def_cfa_offset 20
	popl	%ebx
	.cfi_restore 3
.LCFI55:
	.cfi_def_cfa_offset 16
.LVL82:
	popl	%esi
	.cfi_restore 6
.LCFI56:
	.cfi_def_cfa_offset 12
	popl	%edi
	.cfi_restore 7
.LCFI57:
	.cfi_def_cfa_offset 8
	popl	%ebp
	.cfi_restore 5
.LCFI58:
	.cfi_def_cfa_offset 4
	ret
.LVL83:
.L79:
.LCFI59:
	.cfi_restore_state
	.loc 1 603 0
	movb	$0, 63(%esp)
	jmp	.L51
.LVL84:
.L83:
.LBB18:
	.loc 1 636 0
	movl	(%ebx), %eax
.LVL85:
	movl	%eax, (%esp)
	call	perror
.LVL86:
	jmp	.L60
.LVL87:
.L81:
.LBE18:
	.loc 1 625 0
	movl	(%ebx), %eax
.LVL88:
	movl	%eax, 12(%esp)
	movl	prog, %eax
	movl	%eax, 8(%esp)
	movl	$.LC9, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	jmp	.L60
.LVL89:
.L80:
	.loc 1 609 0 discriminator 1
	movl	$.LC20, (%esp)
	call	error
.LVL90:
.L77:
.LBB19:
	.loc 1 639 0 discriminator 1
	movl	$.LC21, (%esp)
	call	error
.LVL91:
.LBE19:
	.cfi_endproc
.LFE33:
	.size	main_minigzip, .-main_minigzip
	.globl	prog
	.bss
	.align 4
	.type	prog, @object
	.size	prog, 4
prog:
	.zero	4
	.text
.Letext0:
	.file 2 "/home/anton/workspace/embox-trunk/./src/include/defines/size_t.h"
	.file 3 "/home/anton/workspace/embox-trunk/./src/compat/posix/include/sys/types.h"
	.file 4 "./zlib.h"
	.file 5 "/home/anton/workspace/embox-trunk/./src/include/stdio.h"
	.file 6 "/home/anton/workspace/embox-trunk/./src/include/../util/dlist_debug.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x51e
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF42
	.byte	0x1
	.long	.LASF43
	.long	.LASF44
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
	.uleb128 0x2
	.byte	0x4
	.byte	0x7
	.long	.LASF2
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF3
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.string	"int"
	.uleb128 0x2
	.byte	0x1
	.byte	0x6
	.long	.LASF4
	.uleb128 0x2
	.byte	0x2
	.byte	0x5
	.long	.LASF5
	.uleb128 0x2
	.byte	0x2
	.byte	0x7
	.long	.LASF6
	.uleb128 0x2
	.byte	0x8
	.byte	0x5
	.long	.LASF7
	.uleb128 0x2
	.byte	0x8
	.byte	0x7
	.long	.LASF8
	.uleb128 0x2
	.byte	0x4
	.byte	0x5
	.long	.LASF9
	.uleb128 0x4
	.long	.LASF10
	.byte	0x2
	.byte	0xc
	.long	0x2c
	.uleb128 0x4
	.long	.LASF11
	.byte	0x3
	.byte	0x43
	.long	0x41
	.uleb128 0x5
	.byte	0x4
	.long	0x8e
	.uleb128 0x6
	.long	0x3a
	.uleb128 0x7
	.long	0x3a
	.long	0xa3
	.uleb128 0x8
	.long	0x2c
	.byte	0x13
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x3a
	.uleb128 0x5
	.byte	0x4
	.long	0x25
	.uleb128 0x9
	.long	.LASF12
	.byte	0x4
	.value	0x4c8
	.long	0xbb
	.uleb128 0x5
	.byte	0x4
	.long	0xc1
	.uleb128 0xa
	.long	.LASF15
	.byte	0xc
	.byte	0x4
	.value	0x686
	.long	0xfc
	.uleb128 0xb
	.long	.LASF13
	.byte	0x4
	.value	0x687
	.long	0x2c
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xb
	.long	.LASF14
	.byte	0x4
	.value	0x688
	.long	0xa9
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xc
	.string	"pos"
	.byte	0x4
	.value	0x689
	.long	0x7d
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0xd
	.long	.LASF16
	.byte	0xc
	.byte	0x5
	.byte	0x27
	.long	0x132
	.uleb128 0xe
	.string	"fd"
	.byte	0x5
	.byte	0x28
	.long	0x41
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xf
	.long	.LASF17
	.byte	0x5
	.byte	0x29
	.long	0x3a
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xf
	.long	.LASF18
	.byte	0x5
	.byte	0x2a
	.long	0x41
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x4
	.long	.LASF19
	.byte	0x5
	.byte	0x2b
	.long	0xfc
	.uleb128 0x10
	.long	.LASF45
	.byte	0x5
	.byte	0xd1
	.byte	0x1
	.long	0x41
	.byte	0x3
	.long	0x15a
	.uleb128 0x11
	.long	.LASF20
	.byte	0x5
	.byte	0xd1
	.long	0x15a
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0x132
	.uleb128 0x12
	.byte	0x1
	.long	.LASF21
	.byte	0x1
	.value	0x16a
	.byte	0x1
	.byte	0x1
	.long	0x1ab
	.uleb128 0x13
	.string	"in"
	.byte	0x1
	.value	0x16b
	.long	0x15a
	.uleb128 0x13
	.string	"out"
	.byte	0x1
	.value	0x16c
	.long	0xaf
	.uleb128 0x14
	.string	"buf"
	.byte	0x1
	.value	0x16e
	.long	0x1ab
	.uleb128 0x14
	.string	"len"
	.byte	0x1
	.value	0x16f
	.long	0x41
	.uleb128 0x14
	.string	"err"
	.byte	0x1
	.value	0x170
	.long	0x41
	.byte	0
	.uleb128 0x7
	.long	0x3a
	.long	0x1bc
	.uleb128 0x15
	.long	0x2c
	.value	0x3fff
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF22
	.byte	0x1
	.value	0x1ae
	.byte	0x1
	.byte	0x1
	.long	0x207
	.uleb128 0x13
	.string	"in"
	.byte	0x1
	.value	0x1af
	.long	0xaf
	.uleb128 0x13
	.string	"out"
	.byte	0x1
	.value	0x1b0
	.long	0x15a
	.uleb128 0x14
	.string	"buf"
	.byte	0x1
	.value	0x1b2
	.long	0x1ab
	.uleb128 0x14
	.string	"len"
	.byte	0x1
	.value	0x1b3
	.long	0x41
	.uleb128 0x14
	.string	"err"
	.byte	0x1
	.value	0x1b4
	.long	0x41
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.long	.LASF23
	.byte	0x1
	.value	0x15f
	.byte	0x1
	.long	.LFB28
	.long	.LFE28
	.long	.LLST0
	.long	0x231
	.uleb128 0x17
	.string	"msg"
	.byte	0x1
	.value	0x160
	.long	0x88
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.byte	0
	.uleb128 0x18
	.long	0x160
	.long	.LFB29
	.long	.LFE29
	.long	.LLST1
	.long	0x2aa
	.uleb128 0x19
	.long	0x16f
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x19
	.long	0x17a
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1a
	.long	0x186
	.byte	0x4
	.byte	0x91
	.sleb128 -16420
	.uleb128 0x1b
	.long	0x192
	.long	.LLST2
	.uleb128 0x1c
	.long	0x19e
	.uleb128 0x1d
	.long	0x160
	.long	.LBB11
	.long	.LBE11
	.byte	0x1
	.value	0x16a
	.uleb128 0x1e
	.long	0x17a
	.long	.LLST3
	.uleb128 0x1f
	.long	.LBB12
	.long	.LBE12
	.uleb128 0x1c
	.long	0x186
	.uleb128 0x1c
	.long	0x192
	.uleb128 0x1a
	.long	0x19e
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x20
	.long	0x16f
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x18
	.long	0x1bc
	.long	.LFB30
	.long	.LFE30
	.long	.LLST4
	.long	0x323
	.uleb128 0x19
	.long	0x1cb
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x19
	.long	0x1d6
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1a
	.long	0x1e2
	.byte	0x4
	.byte	0x91
	.sleb128 -16420
	.uleb128 0x1b
	.long	0x1ee
	.long	.LLST5
	.uleb128 0x1c
	.long	0x1fa
	.uleb128 0x1d
	.long	0x1bc
	.long	.LBB15
	.long	.LBE15
	.byte	0x1
	.value	0x1ae
	.uleb128 0x1e
	.long	0x1cb
	.long	.LLST6
	.uleb128 0x1f
	.long	.LBB16
	.long	.LBE16
	.uleb128 0x1c
	.long	0x1e2
	.uleb128 0x1c
	.long	0x1ee
	.uleb128 0x1a
	.long	0x1fa
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x20
	.long	0x1d6
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.long	.LASF24
	.byte	0x1
	.value	0x1c9
	.byte	0x1
	.long	.LFB31
	.long	.LFE31
	.long	.LLST7
	.long	0x38c
	.uleb128 0x21
	.long	.LASF25
	.byte	0x1
	.value	0x1ca
	.long	0xa3
	.long	.LLST8
	.uleb128 0x22
	.long	.LASF26
	.byte	0x1
	.value	0x1cb
	.long	0xa3
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x23
	.long	.LASF27
	.byte	0x1
	.value	0x1cd
	.long	0x38c
	.byte	0x3
	.byte	0x91
	.sleb128 -1040
	.uleb128 0x24
	.string	"in"
	.byte	0x1
	.value	0x1ce
	.long	0x15a
	.long	.LLST9
	.uleb128 0x24
	.string	"out"
	.byte	0x1
	.value	0x1cf
	.long	0xaf
	.long	.LLST10
	.byte	0
	.uleb128 0x7
	.long	0x3a
	.long	0x39d
	.uleb128 0x15
	.long	0x2c
	.value	0x3ff
	.byte	0
	.uleb128 0x16
	.byte	0x1
	.long	.LASF28
	.byte	0x1
	.value	0x1f0
	.byte	0x1
	.long	.LFB32
	.long	.LFE32
	.long	.LLST11
	.long	0x427
	.uleb128 0x21
	.long	.LASF25
	.byte	0x1
	.value	0x1f1
	.long	0xa3
	.long	.LLST12
	.uleb128 0x25
	.string	"buf"
	.byte	0x1
	.value	0x1f3
	.long	0x38c
	.byte	0x3
	.byte	0x91
	.sleb128 -1056
	.uleb128 0x26
	.long	.LASF29
	.byte	0x1
	.value	0x1f4
	.long	0xa3
	.long	.LLST13
	.uleb128 0x26
	.long	.LASF27
	.byte	0x1
	.value	0x1f4
	.long	0xa3
	.long	.LLST14
	.uleb128 0x24
	.string	"out"
	.byte	0x1
	.value	0x1f5
	.long	0x15a
	.long	.LLST15
	.uleb128 0x24
	.string	"in"
	.byte	0x1
	.value	0x1f6
	.long	0xaf
	.long	.LLST16
	.uleb128 0x24
	.string	"len"
	.byte	0x1
	.value	0x1f7
	.long	0x72
	.long	.LLST17
	.byte	0
	.uleb128 0x27
	.byte	0x1
	.long	.LASF30
	.byte	0x1
	.value	0x22c
	.long	0x41
	.long	.LFB33
	.long	.LFE33
	.long	.LLST18
	.long	0x4c9
	.uleb128 0x21
	.long	.LASF31
	.byte	0x1
	.value	0x22d
	.long	0x41
	.long	.LLST19
	.uleb128 0x21
	.long	.LASF32
	.byte	0x1
	.value	0x22e
	.long	0x4c9
	.long	.LLST20
	.uleb128 0x26
	.long	.LASF33
	.byte	0x1
	.value	0x230
	.long	0x41
	.long	.LLST21
	.uleb128 0x26
	.long	.LASF34
	.byte	0x1
	.value	0x231
	.long	0x41
	.long	.LLST22
	.uleb128 0x26
	.long	.LASF25
	.byte	0x1
	.value	0x232
	.long	0xaf
	.long	.LLST23
	.uleb128 0x26
	.long	.LASF35
	.byte	0x1
	.value	0x233
	.long	0xa3
	.long	.LLST24
	.uleb128 0x23
	.long	.LASF36
	.byte	0x1
	.value	0x233
	.long	0x93
	.byte	0x2
	.byte	0x91
	.sleb128 -52
	.uleb128 0x28
	.long	.Ldebug_ranges0+0
	.uleb128 0x24
	.string	"in"
	.byte	0x1
	.value	0x279
	.long	0x15a
	.long	.LLST25
	.byte	0
	.byte	0
	.uleb128 0x5
	.byte	0x4
	.long	0xa3
	.uleb128 0x7
	.long	0x3a
	.long	0x4da
	.uleb128 0x29
	.byte	0
	.uleb128 0x2a
	.long	.LASF37
	.byte	0x6
	.byte	0x92
	.long	0x4cf
	.byte	0x1
	.byte	0x1
	.uleb128 0x2a
	.long	.LASF38
	.byte	0x5
	.byte	0xc7
	.long	0x15a
	.byte	0x1
	.byte	0x1
	.uleb128 0x2a
	.long	.LASF39
	.byte	0x5
	.byte	0xc8
	.long	0x15a
	.byte	0x1
	.byte	0x1
	.uleb128 0x2a
	.long	.LASF40
	.byte	0x5
	.byte	0xc9
	.long	0x15a
	.byte	0x1
	.byte	0x1
	.uleb128 0x2b
	.long	.LASF41
	.byte	0x1
	.value	0x150
	.long	0xa3
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	prog
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x5
	.uleb128 0xf
	.byte	0
	.uleb128 0xb
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x6
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x7
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x8
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
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
	.uleb128 0xb
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
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0xe
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
	.uleb128 0xf
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
	.uleb128 0x10
	.uleb128 0x2e
	.byte	0x1
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
	.uleb128 0x20
	.uleb128 0xb
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x13
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
	.byte	0
	.byte	0
	.uleb128 0x14
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0x8
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x15
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x16
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
	.uleb128 0x6
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0x18
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
	.uleb128 0x19
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1a
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x1b
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1c
	.uleb128 0x34
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x1d
	.uleb128 0x1d
	.byte	0x1
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.uleb128 0x58
	.uleb128 0xb
	.uleb128 0x59
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x1e
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.uleb128 0x2
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x1f
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x11
	.uleb128 0x1
	.uleb128 0x12
	.uleb128 0x1
	.byte	0
	.byte	0
	.uleb128 0x20
	.uleb128 0x5
	.byte	0
	.uleb128 0x31
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x21
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0x23
	.uleb128 0x34
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
	.uleb128 0x24
	.uleb128 0x34
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x34
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
	.uleb128 0x26
	.uleb128 0x34
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x27
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
	.uleb128 0x28
	.uleb128 0xb
	.byte	0x1
	.uleb128 0x55
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x29
	.uleb128 0x21
	.byte	0
	.byte	0
	.byte	0
	.uleb128 0x2a
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
	.uleb128 0x2b
	.uleb128 0x34
	.byte	0
	.uleb128 0x3
	.uleb128 0xe
	.uleb128 0x3a
	.uleb128 0xb
	.uleb128 0x3b
	.uleb128 0x5
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x2
	.uleb128 0xa
	.byte	0
	.byte	0
	.byte	0
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB28-.Ltext0
	.long	.LCFI0-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI0-.Ltext0
	.long	.LFE28-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 32
	.long	0
	.long	0
.LLST1:
	.long	.LFB29-.Ltext0
	.long	.LCFI1-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI1-.Ltext0
	.long	.LCFI2-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI2-.Ltext0
	.long	.LCFI3-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI3-.Ltext0
	.long	.LCFI4-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI4-.Ltext0
	.long	.LCFI5-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI5-.Ltext0
	.long	.LCFI6-.Ltext0
	.value	0x4
	.byte	0x74
	.sleb128 16448
	.long	.LCFI6-.Ltext0
	.long	.LCFI7-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI7-.Ltext0
	.long	.LCFI8-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI8-.Ltext0
	.long	.LCFI9-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI9-.Ltext0
	.long	.LCFI10-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI10-.Ltext0
	.long	.LCFI11-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI11-.Ltext0
	.long	.LFE29-.Ltext0
	.value	0x4
	.byte	0x74
	.sleb128 16448
	.long	0
	.long	0
.LLST2:
	.long	.LVL2-.Ltext0
	.long	.LVL3-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL4-.Ltext0
	.long	.LVL5-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL5-1-.Ltext0
	.long	.LVL6-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL7-.Ltext0
	.long	.LFE29-.Ltext0
	.value	0x1
	.byte	0x53
	.long	0
	.long	0
.LLST3:
	.long	.LVL8-.Ltext0
	.long	.LVL9-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 4
	.long	0
	.long	0
.LLST4:
	.long	.LFB30-.Ltext0
	.long	.LCFI12-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI12-.Ltext0
	.long	.LCFI13-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI13-.Ltext0
	.long	.LCFI14-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI14-.Ltext0
	.long	.LCFI15-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI15-.Ltext0
	.long	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI16-.Ltext0
	.long	.LCFI17-.Ltext0
	.value	0x4
	.byte	0x74
	.sleb128 16448
	.long	.LCFI17-.Ltext0
	.long	.LCFI18-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI18-.Ltext0
	.long	.LCFI19-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI19-.Ltext0
	.long	.LCFI20-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI20-.Ltext0
	.long	.LCFI21-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI21-.Ltext0
	.long	.LCFI22-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI22-.Ltext0
	.long	.LFE30-.Ltext0
	.value	0x4
	.byte	0x74
	.sleb128 16448
	.long	0
	.long	0
.LLST5:
	.long	.LVL11-.Ltext0
	.long	.LVL12-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL12-1-.Ltext0
	.long	.LVL13-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL14-.Ltext0
	.long	.LVL15-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL15-1-.Ltext0
	.long	.LVL16-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL17-.Ltext0
	.long	.LVL18-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL18-.Ltext0
	.long	.LFE30-.Ltext0
	.value	0x1
	.byte	0x53
	.long	0
	.long	0
.LLST6:
	.long	.LVL17-.Ltext0
	.long	.LVL19-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 0
	.long	0
	.long	0
.LLST7:
	.long	.LFB31-.Ltext0
	.long	.LCFI23-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI23-.Ltext0
	.long	.LCFI24-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI24-.Ltext0
	.long	.LCFI25-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI25-.Ltext0
	.long	.LCFI26-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI26-.Ltext0
	.long	.LCFI27-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 1072
	.long	.LCFI27-.Ltext0
	.long	.LCFI28-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI28-.Ltext0
	.long	.LCFI29-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI29-.Ltext0
	.long	.LCFI30-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI30-.Ltext0
	.long	.LCFI31-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI31-.Ltext0
	.long	.LFE31-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 1072
	.long	0
	.long	0
.LLST8:
	.long	.LVL20-.Ltext0
	.long	.LVL21-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 0
	.long	0
	.long	0
.LLST9:
	.long	.LVL22-.Ltext0
	.long	.LVL23-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL23-.Ltext0
	.long	.LVL26-.Ltext0
	.value	0x1
	.byte	0x57
	.long	.LVL27-.Ltext0
	.long	.LFE31-.Ltext0
	.value	0x1
	.byte	0x57
	.long	0
	.long	0
.LLST10:
	.long	.LVL24-.Ltext0
	.long	.LVL25-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL27-.Ltext0
	.long	.LVL28-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST11:
	.long	.LFB32-.Ltext0
	.long	.LCFI32-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI32-.Ltext0
	.long	.LCFI33-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI33-.Ltext0
	.long	.LCFI34-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI34-.Ltext0
	.long	.LCFI35-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI35-.Ltext0
	.long	.LCFI36-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI36-.Ltext0
	.long	.LCFI37-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 1088
	.long	.LCFI37-.Ltext0
	.long	.LCFI38-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI38-.Ltext0
	.long	.LCFI39-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI39-.Ltext0
	.long	.LCFI40-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI40-.Ltext0
	.long	.LCFI41-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI41-.Ltext0
	.long	.LCFI42-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI42-.Ltext0
	.long	.LFE32-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 1088
	.long	0
	.long	0
.LLST12:
	.long	.LVL29-.Ltext0
	.long	.LVL30-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 0
	.long	0
	.long	0
.LLST13:
	.long	.LVL34-.Ltext0
	.long	.LVL35-.Ltext0
	.value	0x1
	.byte	0x55
	.long	.LVL35-.Ltext0
	.long	.LVL40-.Ltext0
	.value	0x1
	.byte	0x56
	.long	.LVL42-.Ltext0
	.long	.LVL43-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 0
	.long	.LVL45-.Ltext0
	.long	.LFE32-.Ltext0
	.value	0x1
	.byte	0x56
	.long	0
	.long	0
.LLST14:
	.long	.LVL34-.Ltext0
	.long	.LVL35-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 0
	.long	.LVL35-.Ltext0
	.long	.LVL42-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -1060
	.long	.LVL42-.Ltext0
	.long	.LVL43-.Ltext0
	.value	0x1
	.byte	0x55
	.long	.LVL45-.Ltext0
	.long	.LFE32-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -1060
	.long	0
	.long	0
.LLST15:
	.long	.LVL38-.Ltext0
	.long	.LVL39-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL45-.Ltext0
	.long	.LVL46-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST16:
	.long	.LVL36-.Ltext0
	.long	.LVL37-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL37-.Ltext0
	.long	.LVL41-.Ltext0
	.value	0x1
	.byte	0x57
	.long	.LVL45-.Ltext0
	.long	.LFE32-.Ltext0
	.value	0x1
	.byte	0x57
	.long	0
	.long	0
.LLST17:
	.long	.LVL31-.Ltext0
	.long	.LVL32-1-.Ltext0
	.value	0x1
	.byte	0x52
	.long	.LVL32-1-.Ltext0
	.long	.LVL33-.Ltext0
	.value	0x3
	.byte	0x76
	.sleb128 -1
	.byte	0x9f
	.long	.LVL33-.Ltext0
	.long	.LVL34-.Ltext0
	.value	0x3
	.byte	0x70
	.sleb128 3
	.byte	0x9f
	.long	.LVL42-.Ltext0
	.long	.LVL43-.Ltext0
	.value	0x3
	.byte	0x70
	.sleb128 3
	.byte	0x9f
	.long	.LVL43-.Ltext0
	.long	.LVL44-1-.Ltext0
	.value	0x1
	.byte	0x52
	.long	.LVL44-1-.Ltext0
	.long	.LVL45-.Ltext0
	.value	0x3
	.byte	0x76
	.sleb128 -1
	.byte	0x9f
	.long	0
	.long	0
.LLST18:
	.long	.LFB33-.Ltext0
	.long	.LCFI43-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI43-.Ltext0
	.long	.LCFI44-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI44-.Ltext0
	.long	.LCFI45-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI45-.Ltext0
	.long	.LCFI46-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI46-.Ltext0
	.long	.LCFI47-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI47-.Ltext0
	.long	.LCFI48-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	.LCFI48-.Ltext0
	.long	.LCFI49-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI49-.Ltext0
	.long	.LCFI50-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI50-.Ltext0
	.long	.LCFI51-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI51-.Ltext0
	.long	.LCFI52-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI52-.Ltext0
	.long	.LCFI53-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI53-.Ltext0
	.long	.LCFI54-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	.LCFI54-.Ltext0
	.long	.LCFI55-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI55-.Ltext0
	.long	.LCFI56-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI56-.Ltext0
	.long	.LCFI57-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI57-.Ltext0
	.long	.LCFI58-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI58-.Ltext0
	.long	.LCFI59-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI59-.Ltext0
	.long	.LFE33-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	0
	.long	0
.LLST19:
	.long	.LVL47-.Ltext0
	.long	.LVL51-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 0
	.long	.LVL51-.Ltext0
	.long	.LVL54-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL54-.Ltext0
	.long	.LVL56-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -76
	.long	.LVL56-.Ltext0
	.long	.LVL58-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -76
	.byte	0x6
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.long	.LVL58-.Ltext0
	.long	.LVL59-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -76
	.long	.LVL59-.Ltext0
	.long	.LVL61-.Ltext0
	.value	0x7
	.byte	0x91
	.sleb128 -76
	.byte	0x6
	.byte	0x31
	.byte	0x1c
	.byte	0x9f
	.long	.LVL61-.Ltext0
	.long	.LVL63-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -76
	.long	.LVL65-.Ltext0
	.long	.LVL68-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -76
	.long	.LVL68-.Ltext0
	.long	.LVL71-.Ltext0
	.value	0x1
	.byte	0x56
	.long	.LVL71-.Ltext0
	.long	.LVL72-.Ltext0
	.value	0x3
	.byte	0x76
	.sleb128 -1
	.byte	0x9f
	.long	.LVL72-.Ltext0
	.long	.LVL78-.Ltext0
	.value	0x1
	.byte	0x56
	.long	.LVL78-.Ltext0
	.long	.LVL84-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -76
	.long	.LVL84-.Ltext0
	.long	.LVL89-.Ltext0
	.value	0x1
	.byte	0x56
	.long	.LVL89-.Ltext0
	.long	.LVL90-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -76
	.long	0
	.long	0
.LLST20:
	.long	.LVL47-.Ltext0
	.long	.LVL52-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 4
	.long	.LVL52-.Ltext0
	.long	.LVL64-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL65-.Ltext0
	.long	.LVL82-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL83-.Ltext0
	.long	.LFE33-.Ltext0
	.value	0x1
	.byte	0x53
	.long	0
	.long	0
.LLST21:
	.long	.LVL48-.Ltext0
	.long	.LVL55-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL55-.Ltext0
	.long	.LVL66-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -72
	.long	.LVL66-.Ltext0
	.long	.LVL67-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL67-.Ltext0
	.long	.LFE33-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -72
	.long	0
	.long	0
.LLST22:
	.long	.LVL48-.Ltext0
	.long	.LVL55-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL55-.Ltext0
	.long	.LVL66-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -68
	.long	.LVL66-.Ltext0
	.long	.LVL67-.Ltext0
	.value	0x2
	.byte	0x30
	.byte	0x9f
	.long	.LVL67-.Ltext0
	.long	.LFE33-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -68
	.long	0
	.long	0
.LLST23:
	.long	.LVL62-.Ltext0
	.long	.LVL63-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL69-.Ltext0
	.long	.LVL70-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL76-.Ltext0
	.long	.LVL77-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL79-.Ltext0
	.long	.LVL80-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL80-.Ltext0
	.long	.LVL81-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -108
	.long	.LVL87-.Ltext0
	.long	.LVL88-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL89-.Ltext0
	.long	.LVL90-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL90-.Ltext0
	.long	.LVL91-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST24:
	.long	.LVL49-.Ltext0
	.long	.LVL50-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL50-.Ltext0
	.long	.LVL53-.Ltext0
	.value	0x1
	.byte	0x55
	.long	0
	.long	0
.LLST25:
	.long	.LVL74-.Ltext0
	.long	.LVL75-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL75-.Ltext0
	.long	.LVL76-1-.Ltext0
	.value	0x1
	.byte	0x52
	.long	.LVL84-.Ltext0
	.long	.LVL85-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL85-.Ltext0
	.long	.LVL86-1-.Ltext0
	.value	0x1
	.byte	0x52
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
	.long	.LBB17-.Ltext0
	.long	.LBE17-.Ltext0
	.long	.LBB18-.Ltext0
	.long	.LBE18-.Ltext0
	.long	.LBB19-.Ltext0
	.long	.LBE19-.Ltext0
	.long	0
	.long	0
	.section	.debug_line,"",@progbits
.Ldebug_line0:
	.section	.debug_str,"MS",@progbits,1
.LASF11:
	.string	"off_t"
.LASF20:
	.string	"stream"
.LASF14:
	.string	"next"
.LASF40:
	.string	"stderr"
.LASF43:
	.string	"test/minigzip.c"
.LASF35:
	.string	"bname"
.LASF29:
	.string	"infile"
.LASF33:
	.string	"copyout"
.LASF41:
	.string	"prog"
.LASF30:
	.string	"main_minigzip"
.LASF22:
	.string	"gz_uncompress"
.LASF13:
	.string	"have"
.LASF19:
	.string	"FILE"
.LASF25:
	.string	"file"
.LASF0:
	.string	"unsigned char"
.LASF36:
	.string	"outmode"
.LASF2:
	.string	"long unsigned int"
.LASF6:
	.string	"short unsigned int"
.LASF10:
	.string	"size_t"
.LASF17:
	.string	"has_ungetc"
.LASF44:
	.string	"/home/anton/workspace/embox-trunk/third-party/lib/zlib-1.2.8"
.LASF24:
	.string	"file_compress"
.LASF3:
	.string	"char"
.LASF38:
	.string	"stdin"
.LASF12:
	.string	"gzFile"
.LASF1:
	.string	"unsigned int"
.LASF15:
	.string	"gzFile_s"
.LASF8:
	.string	"long long unsigned int"
.LASF26:
	.string	"mode"
.LASF31:
	.string	"argc"
.LASF34:
	.string	"uncompr"
.LASF23:
	.string	"error"
.LASF7:
	.string	"long long int"
.LASF39:
	.string	"stdout"
.LASF32:
	.string	"argv"
.LASF18:
	.string	"ungetc"
.LASF42:
	.string	"GNU C 4.6.3"
.LASF5:
	.string	"short int"
.LASF45:
	.string	"fileno"
.LASF9:
	.string	"long int"
.LASF16:
	.string	"file_struct"
.LASF37:
	.string	"__assertion_message_buff"
.LASF4:
	.string	"signed char"
.LASF28:
	.string	"file_uncompress"
.LASF21:
	.string	"gz_compress"
.LASF27:
	.string	"outfile"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
