	.file	"example.c"
	.text
.Ltext0:
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"compress"
.LC1:
	.string	"%s error: %d\n"
.LC2:
	.string	"uncompress"
.LC3:
	.string	"bad uncompress\n"
.LC4:
	.string	"uncompress(): %s\n"
	.text
	.p2align 2,,3
	.globl	test_compress
	.type	test_compress, @function
test_compress:
.LFB27:
	.file 1 "test/example.c"
	.loc 1 91 0
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
	subl	$16, %esp
.LCFI3:
	.cfi_def_cfa_offset 32
	movl	32(%esp), %esi
	movl	40(%esp), %ebx
	.loc 1 93 0
	movl	$hello, %edi
	xorl	%eax, %eax
	movl	$-1, %ecx
	repnz scasb
	notl	%ecx
	.loc 1 95 0
	movl	%ecx, 12(%esp)
	movl	$hello, 8(%esp)
	leal	36(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	compress
.LVL1:
	.loc 1 96 0
	testl	%eax, %eax
	jne	.L7
	.loc 1 98 0
	movl	$1651663207, (%ebx)
	movl	$6645601, 4(%ebx)
	.loc 1 100 0
	movl	36(%esp), %eax
.LVL2:
	movl	%eax, 12(%esp)
	movl	%esi, 8(%esp)
	leal	44(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	uncompress
.LVL3:
	.loc 1 101 0
	testl	%eax, %eax
	jne	.L8
	.loc 1 103 0
	movl	$hello, 4(%esp)
	movl	%ebx, (%esp)
	call	strcmp
.LVL4:
	testl	%eax, %eax
	jne	.L9
	.loc 1 107 0
	movl	%ebx, 4(%esp)
	movl	$.LC4, (%esp)
	call	printf
	.loc 1 109 0
	addl	$16, %esp
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
.LVL5:
.L7:
.LCFI8:
	.cfi_restore_state
	.loc 1 96 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC0, 8(%esp)
.L5:
	.loc 1 101 0 discriminator 1
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL6:
	movl	%eax, (%esp)
	call	fprintf
.LVL7:
	movl	$1, (%esp)
	call	exit
.L9:
	.loc 1 104 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$15, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC3, (%esp)
	call	fwrite
	.loc 1 105 0
	movl	$1, (%esp)
	call	exit
.LVL8:
.L8:
	.loc 1 101 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC2, 8(%esp)
	jmp	.L5
	.cfi_endproc
.LFE27:
	.size	test_compress, .-test_compress
	.section	.rodata.str1.1
.LC5:
	.string	"wb"
.LC6:
	.string	"gzopen error\n"
.LC7:
	.string	"ello"
.LC8:
	.string	"gzputs err: %s\n"
.LC9:
	.string	"hello"
.LC10:
	.string	", %s!"
.LC11:
	.string	"gzprintf err: %s\n"
.LC12:
	.string	"rb"
.LC13:
	.string	"gzread err: %s\n"
.LC14:
	.string	"bad gzread: %s\n"
.LC15:
	.string	"gzread(): %s\n"
	.section	.rodata.str1.4,"aMS",@progbits,1
	.align 4
.LC16:
	.string	"gzseek error, pos=%ld, gztell=%ld\n"
	.section	.rodata.str1.1
.LC17:
	.string	"gzgetc error\n"
.LC18:
	.string	"gzungetc error\n"
.LC19:
	.string	"gzgets err after gzseek: %s\n"
.LC20:
	.string	"bad gzgets after gzseek\n"
.LC21:
	.string	"gzgets() after gzseek: %s\n"
	.text
	.p2align 2,,3
	.globl	test_gzio
	.type	test_gzio, @function
test_gzio:
.LFB28:
	.loc 1 118 0
	.cfi_startproc
.LVL9:
	pushl	%ebp
.LCFI9:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI10:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI11:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI12:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$60, %esp
.LCFI13:
	.cfi_def_cfa_offset 80
	movl	80(%esp), %ebx
	movl	84(%esp), %esi
	.loc 1 123 0
	movl	$hello, %edi
	xorl	%eax, %eax
	movl	$-1, %ecx
	repnz scasb
	movl	%ecx, %ebp
	notl	%ebp
	.loc 1 127 0
	movl	$.LC5, 4(%esp)
	movl	%ebx, (%esp)
	call	gzopen
	movl	%eax, %edi
.LVL10:
	.loc 1 128 0
	testl	%eax, %eax
	je	.L25
	.loc 1 132 0
	movl	$104, 4(%esp)
	movl	%eax, (%esp)
	call	gzputc
.LVL11:
	.loc 1 133 0
	movl	$.LC7, 4(%esp)
	movl	%edi, (%esp)
	call	gzputs
	cmpl	$4, %eax
	jne	.L27
	.loc 1 137 0
	movl	$.LC9, 8(%esp)
	movl	$.LC10, 4(%esp)
	movl	%edi, (%esp)
	call	gzprintf
	cmpl	$8, %eax
	jne	.L28
	.loc 1 141 0
	movl	$1, 8(%esp)
	movl	$1, 4(%esp)
	movl	%edi, (%esp)
	call	gzseek
	.loc 1 142 0
	movl	%edi, (%esp)
	call	gzclose
	.loc 1 144 0
	movl	$.LC12, 4(%esp)
	movl	%ebx, (%esp)
	call	gzopen
	movl	%eax, %ebx
.LVL12:
	.loc 1 145 0
	testl	%eax, %eax
	je	.L25
	.loc 1 149 0
	movl	$1651663207, (%esi)
	movl	$6645601, 4(%esi)
	.loc 1 151 0
	movl	88(%esp), %eax
.LVL13:
	movl	%eax, 8(%esp)
	movl	%esi, 4(%esp)
	movl	%ebx, (%esp)
	call	gzread
	cmpl	%ebp, %eax
	jne	.L29
	.loc 1 155 0
	movl	$hello, 4(%esp)
	movl	%esi, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L30
	.loc 1 159 0
	movl	%esi, 4(%esp)
	movl	$.LC15, (%esp)
	call	printf
	.loc 1 162 0
	movl	$1, 8(%esp)
	movl	$-8, 4(%esp)
	movl	%ebx, (%esp)
	call	gzseek
	movl	%eax, %edi
.LVL14:
	.loc 1 163 0
	cmpl	$6, %eax
	jne	.L17
	.loc 1 163 0 is_stmt 0 discriminator 1
	movl	%ebx, (%esp)
	call	gztell
.LVL15:
	cmpl	$6, %eax
	jne	.L17
	.loc 1 169 0 is_stmt 1
	movl	(%ebx), %eax
	testl	%eax, %eax
	je	.L19
	.loc 1 169 0 is_stmt 0 discriminator 1
	decl	%eax
	movl	%eax, (%ebx)
	incl	8(%ebx)
	movl	4(%ebx), %eax
	cmpb	$32, (%eax)
	setne	31(%esp)
	incl	%eax
	movl	%eax, 4(%ebx)
.L20:
	.loc 1 169 0 discriminator 3
	cmpb	$0, 31(%esp)
	jne	.L31
	.loc 1 174 0 is_stmt 1
	movl	%ebx, 4(%esp)
	movl	$32, (%esp)
	call	gzungetc
	cmpl	$32, %eax
	jne	.L32
	.loc 1 179 0
	movl	88(%esp), %eax
	movl	%eax, 8(%esp)
	movl	%esi, 4(%esp)
	movl	%ebx, (%esp)
	call	gzgets
	.loc 1 180 0
	movl	$-1, %ecx
	movl	%esi, %edi
.LVL16:
	movb	31(%esp), %al
	repnz scasb
.LVL17:
	cmpl	$-9, %ecx
	jne	.L33
	.loc 1 184 0
	movl	$hello+6, 4(%esp)
	movl	%esi, (%esp)
	call	strcmp
	testl	%eax, %eax
	jne	.L34
	.loc 1 188 0
	movl	%esi, 4(%esp)
	movl	$.LC21, (%esp)
	call	printf
	.loc 1 191 0
	movl	%ebx, (%esp)
	call	gzclose
	.loc 1 193 0
	addl	$60, %esp
	.cfi_remember_state
.LCFI14:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI15:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
.LVL18:
	popl	%esi
.LCFI16:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI17:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI18:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL19:
	.p2align 2,,3
.L19:
.LCFI19:
	.cfi_restore_state
	.loc 1 169 0 discriminator 2
	movl	%ebx, (%esp)
	call	gzgetc
	cmpl	$32, %eax
	setne	31(%esp)
	jmp	.L20
.L17:
	.loc 1 165 0
	movl	%ebx, (%esp)
	call	gztell
	.loc 1 164 0
	movl	%eax, 12(%esp)
	movl	%edi, 8(%esp)
	movl	$.LC16, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	.loc 1 166 0
	movl	$1, (%esp)
	call	exit
.LVL20:
.L25:
	.loc 1 146 0
	movl	stderr, %eax
.LVL21:
	movl	%eax, 12(%esp)
	movl	$13, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC6, (%esp)
	call	fwrite
	.loc 1 147 0
	movl	$1, (%esp)
	call	exit
.LVL22:
.L28:
	.loc 1 138 0
	leal	44(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	gzerror
	movl	%eax, 8(%esp)
	movl	$.LC11, 4(%esp)
.LVL23:
.L26:
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	.loc 1 139 0
	movl	$1, (%esp)
	call	exit
.LVL24:
.L31:
	.loc 1 170 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$13, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC17, (%esp)
	call	fwrite
	.loc 1 171 0
	movl	$1, (%esp)
	call	exit
.LVL25:
.L29:
	.loc 1 152 0
	leal	44(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	gzerror
	movl	%eax, 8(%esp)
	movl	$.LC13, 4(%esp)
	jmp	.L26
.L30:
	.loc 1 156 0
	movl	%esi, 8(%esp)
	movl	$.LC14, 4(%esp)
	jmp	.L26
.LVL26:
.L34:
	.loc 1 185 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$24, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC20, (%esp)
	call	fwrite
	.loc 1 186 0
	movl	$1, (%esp)
	call	exit
.L33:
	.loc 1 181 0
	leal	44(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%ebx, (%esp)
	call	gzerror
	movl	%eax, 8(%esp)
	movl	$.LC19, 4(%esp)
	jmp	.L26
.LVL27:
.L32:
	.loc 1 175 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$15, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC18, (%esp)
	call	fwrite
	.loc 1 176 0
	movl	$1, (%esp)
	call	exit
.LVL28:
.L27:
	.loc 1 134 0
	leal	44(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%edi, (%esp)
	call	gzerror
	movl	%eax, 8(%esp)
	movl	$.LC8, 4(%esp)
	jmp	.L26
	.cfi_endproc
.LFE28:
	.size	test_gzio, .-test_gzio
	.section	.rodata.str1.1
.LC22:
	.string	"1.2.8"
.LC23:
	.string	"deflateInit"
.LC24:
	.string	"deflate"
.LC25:
	.string	"deflateEnd"
	.text
	.p2align 2,,3
	.globl	test_deflate
	.type	test_deflate, @function
test_deflate:
.LFB29:
	.loc 1 203 0
	.cfi_startproc
.LVL29:
	pushl	%edi
.LCFI20:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
.LCFI21:
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
.LCFI22:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subl	$80, %esp
.LCFI23:
	.cfi_def_cfa_offset 96
	movl	100(%esp), %ebx
	.loc 1 206 0
	movl	$hello, %edi
	xorl	%eax, %eax
	movl	$-1, %ecx
	repnz scasb
	movl	%ecx, %esi
	notl	%esi
.LVL30:
	.loc 1 208 0
	movl	$0, 56(%esp)
	.loc 1 209 0
	movl	$0, 60(%esp)
	.loc 1 210 0
	movl	$0, 64(%esp)
	.loc 1 212 0
	movl	$56, 12(%esp)
	movl	$.LC22, 8(%esp)
	movl	$-1, 4(%esp)
	leal	24(%esp), %edi
	movl	%edi, (%esp)
	call	deflateInit_
.LVL31:
	.loc 1 213 0
	testl	%eax, %eax
	jne	.L47
	.loc 1 215 0
	movl	$hello, 24(%esp)
	.loc 1 216 0
	movl	96(%esp), %eax
.LVL32:
	movl	%eax, 36(%esp)
	.loc 1 218 0
	jmp	.L37
	.p2align 2,,3
.L48:
	.loc 1 218 0 is_stmt 0 discriminator 2
	cmpl	%ebx, 44(%esp)
	jae	.L42
	.loc 1 219 0 is_stmt 1
	movl	$1, 40(%esp)
	movl	$1, 28(%esp)
	.loc 1 220 0
	movl	$0, 4(%esp)
	movl	%edi, (%esp)
	call	deflate
.LVL33:
	.loc 1 221 0
	testl	%eax, %eax
	jne	.L46
.LVL34:
.L37:
	.loc 1 218 0 discriminator 1
	cmpl	%esi, 32(%esp)
	jne	.L48
	jmp	.L42
.LVL35:
	.p2align 2,,3
.L49:
	.loc 1 228 0
	testl	%eax, %eax
	jne	.L46
.LVL36:
.L42:
	.loc 1 225 0
	movl	$1, 40(%esp)
	.loc 1 226 0
	movl	$4, 4(%esp)
	movl	%edi, (%esp)
	call	deflate
.LVL37:
	.loc 1 227 0
	cmpl	$1, %eax
	jne	.L49
	.loc 1 231 0
	movl	%edi, (%esp)
	call	deflateEnd
.LVL38:
	.loc 1 232 0
	testl	%eax, %eax
	jne	.L50
	.loc 1 233 0
	addl	$80, %esp
	.cfi_remember_state
.LCFI24:
	.cfi_def_cfa_offset 16
	popl	%ebx
.LCFI25:
	.cfi_def_cfa_offset 12
	.cfi_restore 3
	popl	%esi
.LCFI26:
	.cfi_def_cfa_offset 8
	.cfi_restore 6
.LVL39:
	popl	%edi
.LCFI27:
	.cfi_def_cfa_offset 4
	.cfi_restore 7
	ret
.LVL40:
.L46:
.LCFI28:
	.cfi_restore_state
	.loc 1 221 0
	movl	%eax, 12(%esp)
	movl	$.LC24, 8(%esp)
.L45:
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL41:
	movl	%eax, (%esp)
	call	fprintf
.LVL42:
	movl	$1, (%esp)
	call	exit
.LVL43:
.L47:
	.loc 1 213 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC23, 8(%esp)
	jmp	.L45
.L50:
	.loc 1 232 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC25, 8(%esp)
	jmp	.L45
	.cfi_endproc
.LFE29:
	.size	test_deflate, .-test_deflate
	.section	.rodata.str1.1
.LC26:
	.string	"inflateInit"
.LC27:
	.string	"inflate"
.LC28:
	.string	"inflateEnd"
.LC29:
	.string	"bad inflate\n"
.LC30:
	.string	"inflate(): %s\n"
	.text
	.p2align 2,,3
	.globl	test_inflate
	.type	test_inflate, @function
test_inflate:
.LFB30:
	.loc 1 241 0
	.cfi_startproc
.LVL44:
	pushl	%ebp
.LCFI29:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI30:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI31:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI32:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$92, %esp
.LCFI33:
	.cfi_def_cfa_offset 112
	movl	116(%esp), %edi
	movl	120(%esp), %ebp
	movl	124(%esp), %esi
	.loc 1 245 0
	movl	$1651663207, 0(%ebp)
	movl	$6645601, 4(%ebp)
	.loc 1 247 0
	movl	$0, 56(%esp)
	.loc 1 248 0
	movl	$0, 60(%esp)
	.loc 1 249 0
	movl	$0, 64(%esp)
	.loc 1 251 0
	movl	112(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 252 0
	movl	$0, 28(%esp)
	.loc 1 253 0
	movl	%ebp, 36(%esp)
	.loc 1 255 0
	movl	$56, 8(%esp)
	movl	$.LC22, 4(%esp)
	leal	24(%esp), %ebx
	movl	%ebx, (%esp)
	call	inflateInit_
.LVL45:
	.loc 1 256 0
	testl	%eax, %eax
	je	.L57
	jmp	.L65
	.p2align 2,,3
.L62:
	.loc 1 258 0 discriminator 2
	cmpl	%edi, 32(%esp)
	jae	.L53
	.loc 1 259 0
	movl	$1, 40(%esp)
	movl	$1, 28(%esp)
	.loc 1 260 0
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	inflate
.LVL46:
	.loc 1 261 0
	cmpl	$1, %eax
	je	.L53
	.loc 1 262 0
	testl	%eax, %eax
	jne	.L61
.L57:
	.loc 1 258 0 discriminator 1
	cmpl	%esi, 44(%esp)
	jb	.L62
.L53:
	.loc 1 265 0
	movl	%ebx, (%esp)
	call	inflateEnd
.LVL47:
	.loc 1 266 0
	testl	%eax, %eax
	jne	.L63
	.loc 1 268 0
	movl	$hello, 4(%esp)
	movl	%ebp, (%esp)
	call	strcmp
.LVL48:
	testl	%eax, %eax
	jne	.L64
	.loc 1 272 0
	movl	%ebp, 4(%esp)
	movl	$.LC30, (%esp)
	call	printf
	.loc 1 274 0
	addl	$92, %esp
	.cfi_remember_state
.LCFI34:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI35:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
.LCFI36:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI37:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI38:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL49:
.L61:
.LCFI39:
	.cfi_restore_state
	.loc 1 262 0
	movl	%eax, 12(%esp)
	movl	$.LC27, 8(%esp)
.L59:
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL50:
	movl	%eax, (%esp)
	call	fprintf
.LVL51:
	movl	$1, (%esp)
	call	exit
.LVL52:
.L65:
	.loc 1 256 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC26, 8(%esp)
	jmp	.L59
.LVL53:
.L64:
	.loc 1 269 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$12, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC29, (%esp)
	call	fwrite
	.loc 1 270 0
	movl	$1, (%esp)
	call	exit
.LVL54:
.L63:
	.loc 1 266 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC28, 8(%esp)
	jmp	.L59
	.cfi_endproc
.LFE30:
	.size	test_inflate, .-test_inflate
	.section	.rodata.str1.1
.LC31:
	.string	"deflate not greedy\n"
	.section	.rodata.str1.4
	.align 4
.LC32:
	.string	"deflate should report Z_STREAM_END\n"
	.text
	.p2align 2,,3
	.globl	test_large_deflate
	.type	test_large_deflate, @function
test_large_deflate:
.LFB31:
	.loc 1 282 0
	.cfi_startproc
.LVL55:
	pushl	%ebp
.LCFI40:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI41:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI42:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI43:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$92, %esp
.LCFI44:
	.cfi_def_cfa_offset 112
	movl	116(%esp), %ebp
	movl	120(%esp), %edi
	movl	124(%esp), %esi
	.loc 1 286 0
	movl	$0, 56(%esp)
	.loc 1 287 0
	movl	$0, 60(%esp)
	.loc 1 288 0
	movl	$0, 64(%esp)
	.loc 1 290 0
	movl	$56, 12(%esp)
	movl	$.LC22, 8(%esp)
	movl	$1, 4(%esp)
	leal	24(%esp), %ebx
	movl	%ebx, (%esp)
	call	deflateInit_
.LVL56:
	.loc 1 291 0
	testl	%eax, %eax
	jne	.L76
	.loc 1 293 0
	movl	112(%esp), %eax
.LVL57:
	movl	%eax, 36(%esp)
	.loc 1 294 0
	movl	%ebp, 40(%esp)
	.loc 1 299 0
	movl	%edi, 24(%esp)
	.loc 1 300 0
	movl	%esi, 28(%esp)
	.loc 1 301 0
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	deflate
.LVL58:
	.loc 1 302 0
	testl	%eax, %eax
	jne	.L75
	.loc 1 303 0
	movl	28(%esp), %eax
.LVL59:
	testl	%eax, %eax
	jne	.L77
	.loc 1 309 0
	movl	$0, 8(%esp)
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	deflateParams
	.loc 1 310 0
	movl	112(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 311 0
	shrl	%ebp
	movl	%ebp, 28(%esp)
	.loc 1 312 0
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	deflate
.LVL60:
	.loc 1 313 0
	testl	%eax, %eax
	jne	.L75
	.loc 1 316 0
	movl	$1, 8(%esp)
	movl	$9, 4(%esp)
	movl	%ebx, (%esp)
	call	deflateParams
.LVL61:
	.loc 1 317 0
	movl	%edi, 24(%esp)
	.loc 1 318 0
	movl	%esi, 28(%esp)
	.loc 1 319 0
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	deflate
.LVL62:
	.loc 1 320 0
	testl	%eax, %eax
	jne	.L75
	.loc 1 322 0
	movl	$4, 4(%esp)
	movl	%ebx, (%esp)
	call	deflate
.LVL63:
	.loc 1 323 0
	decl	%eax
.LVL64:
	jne	.L78
	.loc 1 327 0
	movl	%ebx, (%esp)
	call	deflateEnd
.LVL65:
	.loc 1 328 0
	testl	%eax, %eax
	jne	.L79
	.loc 1 329 0
	addl	$92, %esp
	.cfi_remember_state
.LCFI45:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI46:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
.LCFI47:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI48:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI49:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.L75:
.LCFI50:
	.cfi_restore_state
	.loc 1 302 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC24, 8(%esp)
.L74:
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL66:
	movl	%eax, (%esp)
	call	fprintf
.LVL67:
	movl	$1, (%esp)
	call	exit
.LVL68:
.L76:
	.loc 1 291 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC23, 8(%esp)
	jmp	.L74
.L79:
	.loc 1 328 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC25, 8(%esp)
	jmp	.L74
.LVL69:
.L78:
	.loc 1 324 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$35, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC32, (%esp)
	call	fwrite
	.loc 1 325 0
	movl	$1, (%esp)
	call	exit
.L77:
	.loc 1 304 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$19, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC31, (%esp)
	call	fwrite
	.loc 1 305 0
	movl	$1, (%esp)
	call	exit
	.cfi_endproc
.LFE31:
	.size	test_large_deflate, .-test_large_deflate
	.section	.rodata.str1.1
.LC33:
	.string	"large inflate"
.LC34:
	.string	"bad large inflate: %ld\n"
.LC35:
	.string	"large_inflate(): OK"
	.text
	.p2align 2,,3
	.globl	test_large_inflate
	.type	test_large_inflate, @function
test_large_inflate:
.LFB32:
	.loc 1 337 0
	.cfi_startproc
.LVL70:
	pushl	%ebp
.LCFI51:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI52:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI53:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI54:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$92, %esp
.LCFI55:
	.cfi_def_cfa_offset 112
	movl	116(%esp), %ebp
	movl	120(%esp), %esi
	movl	124(%esp), %edi
	.loc 1 341 0
	movl	$1651663207, (%esi)
	movl	$6645601, 4(%esi)
	.loc 1 343 0
	movl	$0, 56(%esp)
	.loc 1 344 0
	movl	$0, 60(%esp)
	.loc 1 345 0
	movl	$0, 64(%esp)
	.loc 1 347 0
	movl	112(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 348 0
	movl	%ebp, 28(%esp)
	.loc 1 350 0
	movl	$56, 8(%esp)
	movl	$.LC22, 4(%esp)
	leal	24(%esp), %ebx
	movl	%ebx, (%esp)
	call	inflateInit_
.LVL71:
	.loc 1 351 0
	testl	%eax, %eax
	je	.L85
	jmp	.L93
	.p2align 2,,3
.L90:
	.loc 1 358 0
	testl	%eax, %eax
	jne	.L89
.L85:
	.loc 1 354 0
	movl	%esi, 36(%esp)
	.loc 1 355 0
	movl	%edi, 40(%esp)
	.loc 1 356 0
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	inflate
.LVL72:
	.loc 1 357 0
	cmpl	$1, %eax
	jne	.L90
	.loc 1 361 0
	movl	%ebx, (%esp)
	call	inflateEnd
.LVL73:
	.loc 1 362 0
	testl	%eax, %eax
	jne	.L91
	.loc 1 364 0
	movl	44(%esp), %eax
.LVL74:
	shrl	%ebp
	leal	0(%ebp,%edi,2), %edx
	cmpl	%edx, %eax
	jne	.L92
	.loc 1 368 0
	movl	$.LC35, (%esp)
	call	puts
	.loc 1 370 0
	addl	$92, %esp
	.cfi_remember_state
.LCFI56:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI57:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
.LCFI58:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI59:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI60:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL75:
.L89:
.LCFI61:
	.cfi_restore_state
	.loc 1 358 0
	movl	%eax, 12(%esp)
	movl	$.LC33, 8(%esp)
.L87:
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL76:
	movl	%eax, (%esp)
	call	fprintf
.LVL77:
	movl	$1, (%esp)
	call	exit
.LVL78:
.L93:
	.loc 1 351 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC26, 8(%esp)
	jmp	.L87
.LVL79:
.L92:
	.loc 1 365 0
	movl	%eax, 8(%esp)
	movl	$.LC34, 4(%esp)
	movl	stderr, %eax
	movl	%eax, (%esp)
	call	fprintf
	.loc 1 366 0
	movl	$1, (%esp)
	call	exit
.LVL80:
.L91:
	.loc 1 362 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC28, 8(%esp)
	jmp	.L87
	.cfi_endproc
.LFE32:
	.size	test_large_inflate, .-test_large_inflate
	.p2align 2,,3
	.globl	test_flush
	.type	test_flush, @function
test_flush:
.LFB33:
	.loc 1 378 0
	.cfi_startproc
.LVL81:
	pushl	%ebp
.LCFI62:
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	pushl	%edi
.LCFI63:
	.cfi_def_cfa_offset 12
	.cfi_offset 7, -12
	pushl	%esi
.LCFI64:
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushl	%ebx
.LCFI65:
	.cfi_def_cfa_offset 20
	.cfi_offset 3, -20
	subl	$92, %esp
.LCFI66:
	.cfi_def_cfa_offset 112
	movl	112(%esp), %ebx
	movl	116(%esp), %esi
	.loc 1 381 0
	movl	$hello, %edi
	xorl	%eax, %eax
	movl	$-1, %ecx
	repnz scasb
	movl	%ecx, %ebp
	notl	%ebp
	.loc 1 383 0
	movl	$0, 56(%esp)
	.loc 1 384 0
	movl	$0, 60(%esp)
	.loc 1 385 0
	movl	$0, 64(%esp)
	.loc 1 387 0
	movl	$56, 12(%esp)
	movl	$.LC22, 8(%esp)
	movl	$-1, 4(%esp)
	leal	24(%esp), %edi
	movl	%edi, (%esp)
	call	deflateInit_
.LVL82:
	.loc 1 388 0
	testl	%eax, %eax
	jne	.L101
	.loc 1 390 0
	movl	$hello, 24(%esp)
	.loc 1 391 0
	movl	%ebx, 36(%esp)
	.loc 1 392 0
	movl	$3, 28(%esp)
	.loc 1 393 0
	movl	(%esi), %eax
.LVL83:
	movl	%eax, 40(%esp)
	.loc 1 394 0
	movl	$3, 4(%esp)
	movl	%edi, (%esp)
	call	deflate
.LVL84:
	.loc 1 395 0
	testl	%eax, %eax
	jne	.L100
	.loc 1 397 0
	incb	3(%ebx)
	.loc 1 398 0
	subl	$3, %ebp
	movl	%ebp, 28(%esp)
	.loc 1 400 0
	movl	$4, 4(%esp)
	movl	%edi, (%esp)
	call	deflate
.LVL85:
	.loc 1 401 0
	cmpl	$1, %eax
	je	.L97
	.loc 1 402 0
	testl	%eax, %eax
	jne	.L100
.L97:
	.loc 1 404 0
	movl	%edi, (%esp)
	call	deflateEnd
.LVL86:
	.loc 1 405 0
	testl	%eax, %eax
	jne	.L102
	.loc 1 407 0
	movl	44(%esp), %eax
.LVL87:
	movl	%eax, (%esi)
	.loc 1 408 0
	addl	$92, %esp
	.cfi_remember_state
.LCFI67:
	.cfi_def_cfa_offset 20
	popl	%ebx
.LCFI68:
	.cfi_def_cfa_offset 16
	.cfi_restore 3
	popl	%esi
.LCFI69:
	.cfi_def_cfa_offset 12
	.cfi_restore 6
	popl	%edi
.LCFI70:
	.cfi_def_cfa_offset 8
	.cfi_restore 7
	popl	%ebp
.LCFI71:
	.cfi_def_cfa_offset 4
	.cfi_restore 5
	ret
.LVL88:
.L100:
.LCFI72:
	.cfi_restore_state
	.loc 1 395 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC24, 8(%esp)
.L99:
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL89:
	movl	%eax, (%esp)
	call	fprintf
.LVL90:
	movl	$1, (%esp)
	call	exit
.LVL91:
.L101:
	.loc 1 388 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC23, 8(%esp)
	jmp	.L99
.L102:
	.loc 1 405 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC25, 8(%esp)
	jmp	.L99
	.cfi_endproc
.LFE33:
	.size	test_flush, .-test_flush
	.section	.rodata.str1.1
.LC36:
	.string	"inflateSync"
	.section	.rodata.str1.4
	.align 4
.LC37:
	.string	"inflate should report DATA_ERROR\n"
	.section	.rodata.str1.1
.LC38:
	.string	"after inflateSync(): hel%s\n"
	.text
	.p2align 2,,3
	.globl	test_sync
	.type	test_sync, @function
test_sync:
.LFB34:
	.loc 1 416 0
	.cfi_startproc
.LVL92:
	pushl	%esi
.LCFI73:
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
.LCFI74:
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$84, %esp
.LCFI75:
	.cfi_def_cfa_offset 96
	movl	104(%esp), %esi
	.loc 1 420 0
	movl	$1651663207, (%esi)
	movl	$6645601, 4(%esi)
	.loc 1 422 0
	movl	$0, 56(%esp)
	.loc 1 423 0
	movl	$0, 60(%esp)
	.loc 1 424 0
	movl	$0, 64(%esp)
	.loc 1 426 0
	movl	96(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 427 0
	movl	$2, 28(%esp)
	.loc 1 429 0
	movl	$56, 8(%esp)
	movl	$.LC22, 4(%esp)
	leal	24(%esp), %ebx
	movl	%ebx, (%esp)
	call	inflateInit_
.LVL93:
	.loc 1 430 0
	testl	%eax, %eax
	jne	.L109
	.loc 1 432 0
	movl	%esi, 36(%esp)
	.loc 1 433 0
	movl	108(%esp), %eax
.LVL94:
	movl	%eax, 40(%esp)
	.loc 1 435 0
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	inflate
	.loc 1 438 0
	movl	100(%esp), %eax
	subl	$2, %eax
	movl	%eax, 28(%esp)
	.loc 1 439 0
	movl	%ebx, (%esp)
	call	inflateSync
.LVL95:
	.loc 1 440 0
	testl	%eax, %eax
	jne	.L110
	.loc 1 442 0
	movl	$4, 4(%esp)
	movl	%ebx, (%esp)
	call	inflate
.LVL96:
	.loc 1 443 0
	cmpl	$-3, %eax
	jne	.L111
	.loc 1 448 0
	movl	%ebx, (%esp)
	call	inflateEnd
.LVL97:
	.loc 1 449 0
	testl	%eax, %eax
	jne	.L112
	.loc 1 451 0
	movl	%esi, 4(%esp)
	movl	$.LC38, (%esp)
	call	printf
.LVL98:
	.loc 1 452 0
	addl	$84, %esp
	.cfi_remember_state
.LCFI76:
	.cfi_def_cfa_offset 12
	popl	%ebx
.LCFI77:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	popl	%esi
.LCFI78:
	.cfi_def_cfa_offset 4
	.cfi_restore 6
	ret
.LVL99:
.L109:
.LCFI79:
	.cfi_restore_state
	.loc 1 430 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC26, 8(%esp)
.L108:
	.loc 1 440 0 discriminator 1
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL100:
	movl	%eax, (%esp)
	call	fprintf
.LVL101:
	movl	$1, (%esp)
	call	exit
.LVL102:
.L112:
	.loc 1 449 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC28, 8(%esp)
	jmp	.L108
.L111:
	.loc 1 444 0
	movl	stderr, %eax
.LVL103:
	movl	%eax, 12(%esp)
	movl	$33, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC37, (%esp)
	call	fwrite
	.loc 1 446 0
	movl	$1, (%esp)
	call	exit
.LVL104:
.L110:
	.loc 1 440 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC36, 8(%esp)
	jmp	.L108
	.cfi_endproc
.LFE34:
	.size	test_sync, .-test_sync
	.section	.rodata.str1.1
.LC39:
	.string	"deflateSetDictionary"
	.text
	.p2align 2,,3
	.globl	test_dict_deflate
	.type	test_dict_deflate, @function
test_dict_deflate:
.LFB35:
	.loc 1 460 0
	.cfi_startproc
.LVL105:
	pushl	%edi
.LCFI80:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%ebx
.LCFI81:
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$84, %esp
.LCFI82:
	.cfi_def_cfa_offset 96
	.loc 1 464 0
	movl	$0, 56(%esp)
	.loc 1 465 0
	movl	$0, 60(%esp)
	.loc 1 466 0
	movl	$0, 64(%esp)
	.loc 1 468 0
	movl	$56, 12(%esp)
	movl	$.LC22, 8(%esp)
	movl	$9, 4(%esp)
	leal	24(%esp), %ebx
	movl	%ebx, (%esp)
	call	deflateInit_
.LVL106:
	.loc 1 469 0
	testl	%eax, %eax
	jne	.L119
	.loc 1 471 0
	movl	$6, 8(%esp)
	movl	$dictionary, 4(%esp)
	movl	%ebx, (%esp)
	call	deflateSetDictionary
.LVL107:
	.loc 1 473 0
	testl	%eax, %eax
	jne	.L120
	.loc 1 475 0
	movl	72(%esp), %eax
.LVL108:
	movl	%eax, dictId
	.loc 1 476 0
	movl	96(%esp), %eax
	movl	%eax, 36(%esp)
	.loc 1 477 0
	movl	100(%esp), %eax
	movl	%eax, 40(%esp)
	.loc 1 479 0
	movl	$hello, 24(%esp)
	.loc 1 480 0
	movl	$hello, %edi
	xorl	%eax, %eax
	movl	$-1, %ecx
	repnz scasb
	notl	%ecx
	movl	%ecx, 28(%esp)
	.loc 1 482 0
	movl	$4, 4(%esp)
	movl	%ebx, (%esp)
	call	deflate
.LVL109:
	.loc 1 483 0
	decl	%eax
.LVL110:
	jne	.L121
	.loc 1 487 0
	movl	%ebx, (%esp)
	call	deflateEnd
.LVL111:
	.loc 1 488 0
	testl	%eax, %eax
	jne	.L122
	.loc 1 489 0
	addl	$84, %esp
	.cfi_remember_state
.LCFI83:
	.cfi_def_cfa_offset 12
	popl	%ebx
.LCFI84:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	popl	%edi
.LCFI85:
	.cfi_def_cfa_offset 4
	.cfi_restore 7
	ret
.L119:
.LCFI86:
	.cfi_restore_state
	.loc 1 469 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC23, 8(%esp)
.L118:
	.loc 1 473 0 discriminator 1
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL112:
	movl	%eax, (%esp)
	call	fprintf
.LVL113:
	movl	$1, (%esp)
	call	exit
.LVL114:
.L122:
	.loc 1 488 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC25, 8(%esp)
	jmp	.L118
.LVL115:
.L121:
	.loc 1 484 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$35, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC32, (%esp)
	call	fwrite
	.loc 1 485 0
	movl	$1, (%esp)
	call	exit
.LVL116:
.L120:
	.loc 1 473 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC39, 8(%esp)
	jmp	.L118
	.cfi_endproc
.LFE35:
	.size	test_dict_deflate, .-test_dict_deflate
	.section	.rodata.str1.1
.LC40:
	.string	"unexpected dictionary"
.LC41:
	.string	"inflate with dict"
.LC42:
	.string	"bad inflate with dict\n"
.LC43:
	.string	"inflate with dictionary: %s\n"
	.text
	.p2align 2,,3
	.globl	test_dict_inflate
	.type	test_dict_inflate, @function
test_dict_inflate:
.LFB36:
	.loc 1 497 0
	.cfi_startproc
.LVL117:
	pushl	%esi
.LCFI87:
	.cfi_def_cfa_offset 8
	.cfi_offset 6, -8
	pushl	%ebx
.LCFI88:
	.cfi_def_cfa_offset 12
	.cfi_offset 3, -12
	subl	$84, %esp
.LCFI89:
	.cfi_def_cfa_offset 96
	movl	104(%esp), %esi
	.loc 1 501 0
	movl	$1651663207, (%esi)
	movl	$6645601, 4(%esi)
	.loc 1 503 0
	movl	$0, 56(%esp)
	.loc 1 504 0
	movl	$0, 60(%esp)
	.loc 1 505 0
	movl	$0, 64(%esp)
	.loc 1 507 0
	movl	96(%esp), %eax
	movl	%eax, 24(%esp)
	.loc 1 508 0
	movl	100(%esp), %eax
	movl	%eax, 28(%esp)
	.loc 1 510 0
	movl	$56, 8(%esp)
	movl	$.LC22, 4(%esp)
	leal	24(%esp), %ebx
	movl	%ebx, (%esp)
	call	inflateInit_
.LVL118:
	.loc 1 511 0
	testl	%eax, %eax
	jne	.L133
	.loc 1 513 0
	movl	%esi, 36(%esp)
	.loc 1 514 0
	movl	108(%esp), %eax
.LVL119:
	movl	%eax, 40(%esp)
	jmp	.L128
.LVL120:
	.p2align 2,,3
.L126:
	.loc 1 527 0
	testl	%eax, %eax
	jne	.L134
.LVL121:
.L128:
	.loc 1 517 0
	movl	$0, 4(%esp)
	movl	%ebx, (%esp)
	call	inflate
.LVL122:
	.loc 1 518 0
	cmpl	$1, %eax
	je	.L125
	.loc 1 519 0
	cmpl	$2, %eax
	jne	.L126
	.loc 1 520 0
	movl	dictId, %eax
.LVL123:
	cmpl	%eax, 72(%esp)
	jne	.L135
	.loc 1 524 0
	movl	$6, 8(%esp)
	movl	$dictionary, 4(%esp)
	movl	%ebx, (%esp)
	call	inflateSetDictionary
.LVL124:
	jmp	.L126
	.p2align 2,,3
.L125:
	.loc 1 530 0
	movl	%ebx, (%esp)
	call	inflateEnd
.LVL125:
	.loc 1 531 0
	testl	%eax, %eax
	jne	.L136
	.loc 1 533 0
	movl	$hello, 4(%esp)
	movl	%esi, (%esp)
	call	strcmp
.LVL126:
	testl	%eax, %eax
	jne	.L137
	.loc 1 537 0
	movl	%esi, 4(%esp)
	movl	$.LC43, (%esp)
	call	printf
	.loc 1 539 0
	addl	$84, %esp
	.cfi_remember_state
.LCFI90:
	.cfi_def_cfa_offset 12
	popl	%ebx
.LCFI91:
	.cfi_def_cfa_offset 8
	.cfi_restore 3
	popl	%esi
.LCFI92:
	.cfi_def_cfa_offset 4
	.cfi_restore 6
	ret
.LVL127:
.L134:
.LCFI93:
	.cfi_restore_state
	.loc 1 527 0
	movl	%eax, 12(%esp)
	movl	$.LC41, 8(%esp)
.L132:
	movl	$.LC1, 4(%esp)
	movl	stderr, %eax
.LVL128:
	movl	%eax, (%esp)
	call	fprintf
.LVL129:
	movl	$1, (%esp)
	call	exit
.L135:
	.loc 1 521 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$21, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC40, (%esp)
	call	fwrite
	.loc 1 522 0
	movl	$1, (%esp)
	call	exit
.LVL130:
.L136:
	.loc 1 531 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC28, 8(%esp)
	jmp	.L132
.L133:
	.loc 1 511 0 discriminator 1
	movl	%eax, 12(%esp)
	movl	$.LC26, 8(%esp)
	jmp	.L132
.LVL131:
.L137:
	.loc 1 534 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$22, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC42, (%esp)
	call	fwrite
	.loc 1 535 0
	movl	$1, (%esp)
	call	exit
	.cfi_endproc
.LFE36:
	.size	test_dict_inflate, .-test_dict_inflate
	.section	.rodata.str1.1
.LC44:
	.string	"foo.gz"
.LC45:
	.string	"incompatible zlib version\n"
	.section	.rodata.str1.4
	.align 4
.LC46:
	.string	"warning: different zlib version\n"
	.align 4
.LC47:
	.string	"zlib version %s = 0x%04x, compile flags = 0x%lx\n"
	.section	.rodata.str1.1
.LC48:
	.string	"out of memory"
	.text
	.p2align 2,,3
	.globl	main_example
	.type	main_example, @function
main_example:
.LFB37:
	.loc 1 548 0
	.cfi_startproc
.LVL132:
	pushl	%edi
.LCFI94:
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
.LCFI95:
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
.LCFI96:
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subl	$32, %esp
.LCFI97:
	.cfi_def_cfa_offset 48
	.loc 1 550 0
	movl	$40000, 28(%esp)
.LVL133:
	.loc 1 554 0
	call	zlibVersion
	cmpb	$49, (%eax)
	jne	.L145
	.loc 1 558 0
	call	zlibVersion
	movl	%eax, %esi
	movl	$.LC22, %edi
	movl	$6, %ecx
	repz cmpsb
	jne	.L146
.L140:
	.loc 1 562 0
	call	zlibCompileFlags
	movl	%eax, 12(%esp)
	movl	$4736, 8(%esp)
	movl	$.LC22, 4(%esp)
	movl	$.LC47, (%esp)
	call	printf
	.loc 1 565 0
	movl	28(%esp), %edi
	movl	$1, 4(%esp)
	movl	%edi, (%esp)
	call	calloc
	movl	%eax, %esi
.LVL134:
	.loc 1 566 0
	movl	$1, 4(%esp)
	movl	$40000, (%esp)
	call	calloc
.LVL135:
	movl	%eax, %ebx
.LVL136:
	.loc 1 570 0
	testl	%esi, %esi
	je	.L141
	.loc 1 570 0 is_stmt 0 discriminator 1
	testl	%eax, %eax
	je	.L141
	.loc 1 578 0 is_stmt 1
	movl	$40000, 12(%esp)
	movl	%eax, 8(%esp)
	movl	%edi, 4(%esp)
	movl	%esi, (%esp)
	call	test_compress
.LVL137:
	.loc 1 580 0
	cmpl	$1, 48(%esp)
	jle	.L144
	.loc 1 580 0 is_stmt 0 discriminator 1
	movl	52(%esp), %eax
	movl	4(%eax), %eax
.L143:
	.loc 1 580 0 discriminator 3
	movl	$40000, 8(%esp)
	movl	%ebx, 4(%esp)
	movl	%eax, (%esp)
	call	test_gzio
	.loc 1 584 0 is_stmt 1 discriminator 3
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	test_deflate
	.loc 1 585 0 discriminator 3
	movl	$40000, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	test_inflate
	.loc 1 587 0 discriminator 3
	movl	$40000, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	test_large_deflate
	.loc 1 588 0 discriminator 3
	movl	$40000, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	test_large_inflate
	.loc 1 590 0 discriminator 3
	leal	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	test_flush
	.loc 1 591 0 discriminator 3
	movl	$40000, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	test_sync
	.loc 1 592 0 discriminator 3
	movl	$40000, 28(%esp)
	.loc 1 594 0 discriminator 3
	movl	$40000, 4(%esp)
	movl	%esi, (%esp)
	call	test_dict_deflate
	.loc 1 595 0 discriminator 3
	movl	$40000, 12(%esp)
	movl	%ebx, 8(%esp)
	movl	28(%esp), %eax
	movl	%eax, 4(%esp)
	movl	%esi, (%esp)
	call	test_dict_inflate
	.loc 1 597 0 discriminator 3
	movl	%esi, (%esp)
	call	free
	.loc 1 598 0 discriminator 3
	movl	%ebx, (%esp)
	call	free
	.loc 1 601 0 discriminator 3
	xorl	%eax, %eax
	addl	$32, %esp
	.cfi_remember_state
.LCFI98:
	.cfi_def_cfa_offset 16
	popl	%ebx
.LCFI99:
	.cfi_def_cfa_offset 12
	.cfi_restore 3
.LVL138:
	popl	%esi
.LCFI100:
	.cfi_def_cfa_offset 8
	.cfi_restore 6
.LVL139:
	popl	%edi
.LCFI101:
	.cfi_def_cfa_offset 4
	.cfi_restore 7
	ret
	.p2align 2,,3
.L146:
.LCFI102:
	.cfi_restore_state
	.loc 1 559 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$32, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC46, (%esp)
	call	fwrite
	jmp	.L140
.LVL140:
	.p2align 2,,3
.L144:
	.loc 1 580 0
	movl	$.LC44, %eax
	jmp	.L143
.L141:
	.loc 1 571 0
	movl	$.LC48, (%esp)
	call	puts
	.loc 1 572 0
	movl	$1, (%esp)
	call	exit
.LVL141:
.L145:
	.loc 1 555 0
	movl	stderr, %eax
	movl	%eax, 12(%esp)
	movl	$26, 8(%esp)
	movl	$1, 4(%esp)
	movl	$.LC45, (%esp)
	call	fwrite
	.loc 1 556 0
	movl	$1, (%esp)
	call	exit
	.cfi_endproc
.LFE37:
	.size	main_example, .-main_example
	.globl	dictId
	.bss
	.align 4
	.type	dictId, @object
	.size	dictId, 4
dictId:
	.zero	4
	.globl	dictionary
	.section	.rodata
	.type	dictionary, @object
	.size	dictionary, 6
dictionary:
	.string	"hello"
	.globl	hello
	.data
	.type	hello, @object
	.size	hello, 14
hello:
	.string	"hello, hello!"
	.text
.Letext0:
	.file 2 "./zconf.h"
	.file 3 "/home/user/workspace/embox/./src/compat/posix/include/sys/types.h"
	.file 4 "./zlib.h"
	.file 5 "/home/user/workspace/embox/./src/include/stdio.h"
	.file 6 "/home/user/workspace/embox/./src/include/../util/dlist_debug.h"
	.section	.debug_info,"",@progbits
.Ldebug_info0:
	.long	0x848
	.value	0x2
	.long	.Ldebug_abbrev0
	.byte	0x4
	.uleb128 0x1
	.long	.LASF70
	.byte	0x1
	.long	.LASF71
	.long	.LASF72
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
	.value	0x182
	.long	0x84
	.uleb128 0x5
	.byte	0x4
	.uleb128 0x3
	.byte	0x1
	.byte	0x6
	.long	.LASF9
	.uleb128 0x3
	.byte	0x2
	.byte	0x5
	.long	.LASF10
	.uleb128 0x3
	.byte	0x2
	.byte	0x7
	.long	.LASF11
	.uleb128 0x3
	.byte	0x8
	.byte	0x5
	.long	.LASF12
	.uleb128 0x3
	.byte	0x8
	.byte	0x7
	.long	.LASF13
	.uleb128 0x3
	.byte	0x4
	.byte	0x5
	.long	.LASF14
	.uleb128 0x6
	.long	.LASF15
	.byte	0x3
	.byte	0x41
	.long	0x71
	.uleb128 0x7
	.byte	0x4
	.long	0xc1
	.uleb128 0x8
	.long	0x6a
	.uleb128 0x7
	.byte	0x4
	.long	0xcc
	.uleb128 0x7
	.byte	0x4
	.long	0x6a
	.uleb128 0x6
	.long	.LASF16
	.byte	0x4
	.byte	0x50
	.long	0xdd
	.uleb128 0x7
	.byte	0x4
	.long	0xe3
	.uleb128 0x9
	.byte	0x1
	.long	0x78
	.long	0xfd
	.uleb128 0xa
	.long	0x78
	.uleb128 0xa
	.long	0x38
	.uleb128 0xa
	.long	0x38
	.byte	0
	.uleb128 0x6
	.long	.LASF17
	.byte	0x4
	.byte	0x51
	.long	0x108
	.uleb128 0x7
	.byte	0x4
	.long	0x10e
	.uleb128 0xb
	.byte	0x1
	.long	0x11f
	.uleb128 0xa
	.long	0x78
	.uleb128 0xa
	.long	0x78
	.byte	0
	.uleb128 0xc
	.long	.LASF31
	.byte	0x38
	.byte	0x4
	.byte	0x55
	.long	0x1f0
	.uleb128 0xd
	.long	.LASF18
	.byte	0x4
	.byte	0x56
	.long	0x1f0
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xd
	.long	.LASF19
	.byte	0x4
	.byte	0x57
	.long	0x38
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xd
	.long	.LASF20
	.byte	0x4
	.byte	0x58
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.uleb128 0xd
	.long	.LASF21
	.byte	0x4
	.byte	0x5a
	.long	0x1f0
	.byte	0x2
	.byte	0x23
	.uleb128 0xc
	.uleb128 0xd
	.long	.LASF22
	.byte	0x4
	.byte	0x5b
	.long	0x38
	.byte	0x2
	.byte	0x23
	.uleb128 0x10
	.uleb128 0xd
	.long	.LASF23
	.byte	0x4
	.byte	0x5c
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x14
	.uleb128 0xe
	.string	"msg"
	.byte	0x4
	.byte	0x5e
	.long	0xcc
	.byte	0x2
	.byte	0x23
	.uleb128 0x18
	.uleb128 0xd
	.long	.LASF24
	.byte	0x4
	.byte	0x5f
	.long	0x213
	.byte	0x2
	.byte	0x23
	.uleb128 0x1c
	.uleb128 0xd
	.long	.LASF25
	.byte	0x4
	.byte	0x61
	.long	0xd2
	.byte	0x2
	.byte	0x23
	.uleb128 0x20
	.uleb128 0xd
	.long	.LASF26
	.byte	0x4
	.byte	0x62
	.long	0xfd
	.byte	0x2
	.byte	0x23
	.uleb128 0x24
	.uleb128 0xd
	.long	.LASF27
	.byte	0x4
	.byte	0x63
	.long	0x78
	.byte	0x2
	.byte	0x23
	.uleb128 0x28
	.uleb128 0xd
	.long	.LASF28
	.byte	0x4
	.byte	0x65
	.long	0x71
	.byte	0x2
	.byte	0x23
	.uleb128 0x2c
	.uleb128 0xd
	.long	.LASF29
	.byte	0x4
	.byte	0x66
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x30
	.uleb128 0xd
	.long	.LASF30
	.byte	0x4
	.byte	0x67
	.long	0x4b
	.byte	0x2
	.byte	0x23
	.uleb128 0x34
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x5e
	.uleb128 0xf
	.long	.LASF32
	.byte	0x4
	.byte	0x4
	.value	0x6ce
	.long	0x213
	.uleb128 0x10
	.long	.LASF33
	.byte	0x4
	.value	0x6ce
	.long	0x71
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x1f6
	.uleb128 0x6
	.long	.LASF34
	.byte	0x4
	.byte	0x68
	.long	0x11f
	.uleb128 0x7
	.byte	0x4
	.long	0x31
	.uleb128 0x2
	.long	.LASF35
	.byte	0x4
	.value	0x4c8
	.long	0x236
	.uleb128 0x7
	.byte	0x4
	.long	0x23c
	.uleb128 0xf
	.long	.LASF36
	.byte	0xc
	.byte	0x4
	.value	0x686
	.long	0x277
	.uleb128 0x10
	.long	.LASF37
	.byte	0x4
	.value	0x687
	.long	0x44
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0x10
	.long	.LASF38
	.byte	0x4
	.value	0x688
	.long	0x224
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0x11
	.string	"pos"
	.byte	0x4
	.value	0x689
	.long	0xb0
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0xc
	.long	.LASF39
	.byte	0xc
	.byte	0x5
	.byte	0x24
	.long	0x2ad
	.uleb128 0xe
	.string	"fd"
	.byte	0x5
	.byte	0x25
	.long	0x71
	.byte	0x2
	.byte	0x23
	.uleb128 0
	.uleb128 0xd
	.long	.LASF40
	.byte	0x5
	.byte	0x26
	.long	0x6a
	.byte	0x2
	.byte	0x23
	.uleb128 0x4
	.uleb128 0xd
	.long	.LASF41
	.byte	0x5
	.byte	0x27
	.long	0x71
	.byte	0x2
	.byte	0x23
	.uleb128 0x8
	.byte	0
	.uleb128 0x6
	.long	.LASF42
	.byte	0x5
	.byte	0x28
	.long	0x277
	.uleb128 0x12
	.byte	0x1
	.long	.LASF47
	.byte	0x1
	.byte	0x58
	.byte	0x1
	.long	.LFB27
	.long	.LFE27
	.long	.LLST0
	.long	0x324
	.uleb128 0x13
	.long	.LASF43
	.byte	0x1
	.byte	0x59
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF44
	.byte	0x1
	.byte	0x5a
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x13
	.long	.LASF45
	.byte	0x1
	.byte	0x59
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x13
	.long	.LASF46
	.byte	0x1
	.byte	0x5a
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x14
	.string	"err"
	.byte	0x1
	.byte	0x5c
	.long	0x71
	.long	.LLST1
	.uleb128 0x15
	.string	"len"
	.byte	0x1
	.byte	0x5d
	.long	0x4b
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x25
	.uleb128 0x12
	.byte	0x1
	.long	.LASF48
	.byte	0x1
	.byte	0x72
	.byte	0x1
	.long	.LFB28
	.long	.LFE28
	.long	.LLST2
	.long	0x3a6
	.uleb128 0x13
	.long	.LASF49
	.byte	0x1
	.byte	0x73
	.long	0xbb
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x16
	.long	.LASF45
	.byte	0x1
	.byte	0x74
	.long	0x324
	.long	.LLST3
	.uleb128 0x13
	.long	.LASF46
	.byte	0x1
	.byte	0x75
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x17
	.string	"err"
	.byte	0x1
	.byte	0x7a
	.long	0x71
	.byte	0x2
	.byte	0x91
	.sleb128 -36
	.uleb128 0x15
	.string	"len"
	.byte	0x1
	.byte	0x7b
	.long	0x71
	.uleb128 0x18
	.long	.LASF50
	.byte	0x1
	.byte	0x7c
	.long	0x22a
	.long	.LLST4
	.uleb128 0x14
	.string	"pos"
	.byte	0x1
	.byte	0x7d
	.long	0xb0
	.long	.LLST5
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF51
	.byte	0x1
	.byte	0xc8
	.byte	0x1
	.long	.LFB29
	.long	.LFE29
	.long	.LLST6
	.long	0x409
	.uleb128 0x13
	.long	.LASF43
	.byte	0x1
	.byte	0xc9
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF44
	.byte	0x1
	.byte	0xca
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x19
	.long	.LASF52
	.byte	0x1
	.byte	0xcc
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x14
	.string	"err"
	.byte	0x1
	.byte	0xcd
	.long	0x71
	.long	.LLST7
	.uleb128 0x14
	.string	"len"
	.byte	0x1
	.byte	0xce
	.long	0x4b
	.long	.LLST8
	.byte	0
	.uleb128 0x12
	.byte	0x1
	.long	.LASF53
	.byte	0x1
	.byte	0xee
	.byte	0x1
	.long	.LFB30
	.long	.LFE30
	.long	.LLST9
	.long	0x479
	.uleb128 0x13
	.long	.LASF43
	.byte	0x1
	.byte	0xef
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x13
	.long	.LASF44
	.byte	0x1
	.byte	0xf0
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x13
	.long	.LASF45
	.byte	0x1
	.byte	0xef
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x13
	.long	.LASF46
	.byte	0x1
	.byte	0xf0
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x14
	.string	"err"
	.byte	0x1
	.byte	0xf2
	.long	0x71
	.long	.LLST10
	.uleb128 0x19
	.long	.LASF54
	.byte	0x1
	.byte	0xf3
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF55
	.byte	0x1
	.value	0x117
	.byte	0x1
	.long	.LFB31
	.long	.LFE31
	.long	.LLST11
	.long	0x4f0
	.uleb128 0x1b
	.long	.LASF43
	.byte	0x1
	.value	0x118
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1b
	.long	.LASF44
	.byte	0x1
	.value	0x119
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1b
	.long	.LASF45
	.byte	0x1
	.value	0x118
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1b
	.long	.LASF46
	.byte	0x1
	.value	0x119
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x1c
	.long	.LASF52
	.byte	0x1
	.value	0x11b
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1d
	.string	"err"
	.byte	0x1
	.value	0x11c
	.long	0x71
	.long	.LLST12
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF56
	.byte	0x1
	.value	0x14e
	.byte	0x1
	.long	.LFB32
	.long	.LFE32
	.long	.LLST13
	.long	0x567
	.uleb128 0x1b
	.long	.LASF43
	.byte	0x1
	.value	0x14f
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1b
	.long	.LASF44
	.byte	0x1
	.value	0x150
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1b
	.long	.LASF45
	.byte	0x1
	.value	0x14f
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1b
	.long	.LASF46
	.byte	0x1
	.value	0x150
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x1d
	.string	"err"
	.byte	0x1
	.value	0x152
	.long	0x71
	.long	.LLST14
	.uleb128 0x1c
	.long	.LASF54
	.byte	0x1
	.value	0x153
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF57
	.byte	0x1
	.value	0x177
	.byte	0x1
	.long	.LFB33
	.long	.LFE33
	.long	.LLST15
	.long	0x5cc
	.uleb128 0x1b
	.long	.LASF43
	.byte	0x1
	.value	0x178
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1b
	.long	.LASF44
	.byte	0x1
	.value	0x179
	.long	0x5cc
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1c
	.long	.LASF52
	.byte	0x1
	.value	0x17b
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -88
	.uleb128 0x1d
	.string	"err"
	.byte	0x1
	.value	0x17c
	.long	0x71
	.long	.LLST16
	.uleb128 0x1e
	.string	"len"
	.byte	0x1
	.value	0x17d
	.long	0x38
	.byte	0
	.uleb128 0x7
	.byte	0x4
	.long	0x4b
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF58
	.byte	0x1
	.value	0x19d
	.byte	0x1
	.long	.LFB34
	.long	.LFE34
	.long	.LLST17
	.long	0x649
	.uleb128 0x1b
	.long	.LASF43
	.byte	0x1
	.value	0x19e
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1b
	.long	.LASF44
	.byte	0x1
	.value	0x19f
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1b
	.long	.LASF45
	.byte	0x1
	.value	0x19e
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1b
	.long	.LASF46
	.byte	0x1
	.value	0x19f
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x1d
	.string	"err"
	.byte	0x1
	.value	0x1a1
	.long	0x71
	.long	.LLST18
	.uleb128 0x1c
	.long	.LASF54
	.byte	0x1
	.value	0x1a2
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF59
	.byte	0x1
	.value	0x1c9
	.byte	0x1
	.long	.LFB35
	.long	.LFE35
	.long	.LLST19
	.long	0x6a2
	.uleb128 0x1b
	.long	.LASF43
	.byte	0x1
	.value	0x1ca
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1b
	.long	.LASF44
	.byte	0x1
	.value	0x1cb
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1c
	.long	.LASF52
	.byte	0x1
	.value	0x1cd
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.uleb128 0x1d
	.string	"err"
	.byte	0x1
	.value	0x1ce
	.long	0x71
	.long	.LLST20
	.byte	0
	.uleb128 0x1a
	.byte	0x1
	.long	.LASF60
	.byte	0x1
	.value	0x1ee
	.byte	0x1
	.long	.LFB36
	.long	.LFE36
	.long	.LLST21
	.long	0x719
	.uleb128 0x1b
	.long	.LASF43
	.byte	0x1
	.value	0x1ef
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1b
	.long	.LASF44
	.byte	0x1
	.value	0x1f0
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x1b
	.long	.LASF45
	.byte	0x1
	.value	0x1ef
	.long	0x324
	.byte	0x2
	.byte	0x91
	.sleb128 8
	.uleb128 0x1b
	.long	.LASF46
	.byte	0x1
	.value	0x1f0
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 12
	.uleb128 0x1d
	.string	"err"
	.byte	0x1
	.value	0x1f2
	.long	0x71
	.long	.LLST22
	.uleb128 0x1c
	.long	.LASF54
	.byte	0x1
	.value	0x1f3
	.long	0x219
	.byte	0x3
	.byte	0x91
	.sleb128 -72
	.byte	0
	.uleb128 0x1f
	.byte	0x1
	.long	.LASF61
	.byte	0x1
	.value	0x221
	.long	0x71
	.long	.LFB37
	.long	.LFE37
	.long	.LLST23
	.long	0x79e
	.uleb128 0x1b
	.long	.LASF62
	.byte	0x1
	.value	0x222
	.long	0x71
	.byte	0x2
	.byte	0x91
	.sleb128 0
	.uleb128 0x1b
	.long	.LASF63
	.byte	0x1
	.value	0x223
	.long	0xc6
	.byte	0x2
	.byte	0x91
	.sleb128 4
	.uleb128 0x20
	.long	.LASF43
	.byte	0x1
	.value	0x225
	.long	0x324
	.long	.LLST24
	.uleb128 0x20
	.long	.LASF45
	.byte	0x1
	.value	0x225
	.long	0x324
	.long	.LLST25
	.uleb128 0x1c
	.long	.LASF44
	.byte	0x1
	.value	0x226
	.long	0x4b
	.byte	0x2
	.byte	0x91
	.sleb128 -20
	.uleb128 0x21
	.long	.LASF46
	.byte	0x1
	.value	0x227
	.long	0x4b
	.value	0x9c40
	.uleb128 0x22
	.long	.LASF64
	.byte	0x1
	.value	0x228
	.long	0x79e
	.byte	0
	.uleb128 0x8
	.long	0xbb
	.uleb128 0x23
	.long	.LASF25
	.byte	0x1
	.byte	0x4d
	.long	0x7af
	.byte	0
	.uleb128 0x8
	.long	0xd2
	.uleb128 0x23
	.long	.LASF26
	.byte	0x1
	.byte	0x4e
	.long	0x7c0
	.byte	0
	.uleb128 0x8
	.long	0xfd
	.uleb128 0x24
	.long	0x6a
	.long	0x7d0
	.uleb128 0x25
	.byte	0
	.uleb128 0x26
	.long	.LASF65
	.byte	0x6
	.byte	0x92
	.long	0x7c5
	.byte	0x1
	.byte	0x1
	.uleb128 0x26
	.long	.LASF66
	.byte	0x5
	.byte	0xc6
	.long	0x7ea
	.byte	0x1
	.byte	0x1
	.uleb128 0x7
	.byte	0x4
	.long	0x2ad
	.uleb128 0x24
	.long	0x6a
	.long	0x800
	.uleb128 0x27
	.long	0x44
	.byte	0xd
	.byte	0
	.uleb128 0x28
	.long	.LASF67
	.byte	0x1
	.byte	0x1d
	.long	0x7f0
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	hello
	.uleb128 0x24
	.long	0x6a
	.long	0x822
	.uleb128 0x27
	.long	0x44
	.byte	0x5
	.byte	0
	.uleb128 0x28
	.long	.LASF68
	.byte	0x1
	.byte	0x22
	.long	0x834
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	dictionary
	.uleb128 0x8
	.long	0x812
	.uleb128 0x28
	.long	.LASF69
	.byte	0x1
	.byte	0x23
	.long	0x4b
	.byte	0x1
	.byte	0x5
	.byte	0x3
	.long	dictId
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
	.uleb128 0x26
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x9
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
	.uleb128 0xa
	.uleb128 0x5
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xb
	.uleb128 0x15
	.byte	0x1
	.uleb128 0x27
	.uleb128 0xc
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0xc
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
	.uleb128 0xd
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
	.uleb128 0x10
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
	.uleb128 0x11
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
	.uleb128 0x15
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
	.uleb128 0x16
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
	.uleb128 0x6
	.byte	0
	.byte	0
	.uleb128 0x17
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
	.uleb128 0xa
	.byte	0
	.byte	0
	.uleb128 0x18
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
	.uleb128 0x19
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
	.uleb128 0x1a
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
	.uleb128 0x1b
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
	.uleb128 0x1c
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
	.uleb128 0x1d
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
	.uleb128 0x1e
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
	.uleb128 0x1f
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
	.uleb128 0x20
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
	.uleb128 0x21
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
	.uleb128 0x1c
	.uleb128 0x5
	.byte	0
	.byte	0
	.uleb128 0x22
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1c
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x24
	.uleb128 0x1
	.byte	0x1
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x1
	.uleb128 0x13
	.byte	0
	.byte	0
	.uleb128 0x25
	.uleb128 0x21
	.byte	0
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
	.uleb128 0xb
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x3f
	.uleb128 0xc
	.uleb128 0x3c
	.uleb128 0xc
	.byte	0
	.byte	0
	.uleb128 0x27
	.uleb128 0x21
	.byte	0
	.uleb128 0x49
	.uleb128 0x13
	.uleb128 0x2f
	.uleb128 0xb
	.byte	0
	.byte	0
	.uleb128 0x28
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
	.section	.debug_loc,"",@progbits
.Ldebug_loc0:
.LLST0:
	.long	.LFB27-.Ltext0
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
	.value	0x2
	.byte	0x74
	.sleb128 32
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
	.long	.LFE27-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 32
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
	.long	.LVL5-.Ltext0
	.long	.LVL6-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL6-.Ltext0
	.long	.LVL7-1-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 -20
	.long	.LVL8-.Ltext0
	.long	.LFE27-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST2:
	.long	.LFB28-.Ltext0
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
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI13-.Ltext0
	.long	.LCFI14-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 80
	.long	.LCFI14-.Ltext0
	.long	.LCFI15-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI15-.Ltext0
	.long	.LCFI16-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI16-.Ltext0
	.long	.LCFI17-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI17-.Ltext0
	.long	.LCFI18-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI18-.Ltext0
	.long	.LCFI19-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI19-.Ltext0
	.long	.LFE28-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 80
	.long	0
	.long	0
.LLST3:
	.long	.LVL9-.Ltext0
	.long	.LVL17-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 4
	.long	.LVL19-.Ltext0
	.long	.LVL23-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 4
	.long	.LVL24-.Ltext0
	.long	.LVL26-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 4
	.long	.LVL27-.Ltext0
	.long	.LFE28-.Ltext0
	.value	0x2
	.byte	0x91
	.sleb128 4
	.long	0
	.long	0
.LLST4:
	.long	.LVL10-.Ltext0
	.long	.LVL11-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL11-1-.Ltext0
	.long	.LVL12-.Ltext0
	.value	0x1
	.byte	0x57
	.long	.LVL12-.Ltext0
	.long	.LVL13-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL13-.Ltext0
	.long	.LVL18-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL19-.Ltext0
	.long	.LVL20-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL20-.Ltext0
	.long	.LVL21-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL22-.Ltext0
	.long	.LVL23-.Ltext0
	.value	0x1
	.byte	0x57
	.long	.LVL24-.Ltext0
	.long	.LVL28-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL28-.Ltext0
	.long	.LFE28-.Ltext0
	.value	0x1
	.byte	0x57
	.long	0
	.long	0
.LLST5:
	.long	.LVL14-.Ltext0
	.long	.LVL15-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL15-1-.Ltext0
	.long	.LVL16-.Ltext0
	.value	0x1
	.byte	0x57
	.long	.LVL19-.Ltext0
	.long	.LVL20-.Ltext0
	.value	0x1
	.byte	0x57
	.long	.LVL24-.Ltext0
	.long	.LVL25-.Ltext0
	.value	0x1
	.byte	0x57
	.long	.LVL27-.Ltext0
	.long	.LVL28-.Ltext0
	.value	0x1
	.byte	0x57
	.long	0
	.long	0
.LLST6:
	.long	.LFB29-.Ltext0
	.long	.LCFI20-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI20-.Ltext0
	.long	.LCFI21-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI21-.Ltext0
	.long	.LCFI22-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI22-.Ltext0
	.long	.LCFI23-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI23-.Ltext0
	.long	.LCFI24-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	.LCFI24-.Ltext0
	.long	.LCFI25-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI25-.Ltext0
	.long	.LCFI26-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI26-.Ltext0
	.long	.LCFI27-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI27-.Ltext0
	.long	.LCFI28-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI28-.Ltext0
	.long	.LFE29-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	0
	.long	0
.LLST7:
	.long	.LVL31-.Ltext0
	.long	.LVL32-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL33-.Ltext0
	.long	.LVL34-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL35-.Ltext0
	.long	.LVL36-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL37-.Ltext0
	.long	.LVL38-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL38-.Ltext0
	.long	.LVL41-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL41-.Ltext0
	.long	.LVL42-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -84
	.long	.LVL43-.Ltext0
	.long	.LFE29-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST8:
	.long	.LVL30-.Ltext0
	.long	.LVL39-.Ltext0
	.value	0x1
	.byte	0x56
	.long	.LVL40-.Ltext0
	.long	.LFE29-.Ltext0
	.value	0x1
	.byte	0x56
	.long	0
	.long	0
.LLST9:
	.long	.LFB30-.Ltext0
	.long	.LCFI29-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI29-.Ltext0
	.long	.LCFI30-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI30-.Ltext0
	.long	.LCFI31-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI31-.Ltext0
	.long	.LCFI32-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI32-.Ltext0
	.long	.LCFI33-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI33-.Ltext0
	.long	.LCFI34-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	.LCFI34-.Ltext0
	.long	.LCFI35-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI35-.Ltext0
	.long	.LCFI36-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI36-.Ltext0
	.long	.LCFI37-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI37-.Ltext0
	.long	.LCFI38-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI38-.Ltext0
	.long	.LCFI39-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI39-.Ltext0
	.long	.LFE30-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	0
	.long	0
.LLST10:
	.long	.LVL45-.Ltext0
	.long	.LVL46-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL46-.Ltext0
	.long	.LVL47-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL47-.Ltext0
	.long	.LVL48-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL49-.Ltext0
	.long	.LVL50-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL50-.Ltext0
	.long	.LVL51-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -100
	.long	.LVL52-.Ltext0
	.long	.LVL53-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL54-.Ltext0
	.long	.LFE30-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST11:
	.long	.LFB31-.Ltext0
	.long	.LCFI40-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI40-.Ltext0
	.long	.LCFI41-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI41-.Ltext0
	.long	.LCFI42-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI42-.Ltext0
	.long	.LCFI43-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI43-.Ltext0
	.long	.LCFI44-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI44-.Ltext0
	.long	.LCFI45-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	.LCFI45-.Ltext0
	.long	.LCFI46-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI46-.Ltext0
	.long	.LCFI47-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI47-.Ltext0
	.long	.LCFI48-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI48-.Ltext0
	.long	.LCFI49-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI49-.Ltext0
	.long	.LCFI50-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI50-.Ltext0
	.long	.LFE31-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	0
	.long	0
.LLST12:
	.long	.LVL56-.Ltext0
	.long	.LVL57-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL58-.Ltext0
	.long	.LVL59-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL60-.Ltext0
	.long	.LVL61-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL62-.Ltext0
	.long	.LVL63-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL63-.Ltext0
	.long	.LVL64-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL65-.Ltext0
	.long	.LVL66-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL66-.Ltext0
	.long	.LVL67-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -100
	.long	.LVL68-.Ltext0
	.long	.LVL69-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST13:
	.long	.LFB32-.Ltext0
	.long	.LCFI51-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI51-.Ltext0
	.long	.LCFI52-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI52-.Ltext0
	.long	.LCFI53-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI53-.Ltext0
	.long	.LCFI54-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI54-.Ltext0
	.long	.LCFI55-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI55-.Ltext0
	.long	.LCFI56-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	.LCFI56-.Ltext0
	.long	.LCFI57-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI57-.Ltext0
	.long	.LCFI58-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI58-.Ltext0
	.long	.LCFI59-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI59-.Ltext0
	.long	.LCFI60-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI60-.Ltext0
	.long	.LCFI61-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI61-.Ltext0
	.long	.LFE32-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	0
	.long	0
.LLST14:
	.long	.LVL71-.Ltext0
	.long	.LVL72-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL72-.Ltext0
	.long	.LVL73-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL73-.Ltext0
	.long	.LVL74-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL75-.Ltext0
	.long	.LVL76-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL76-.Ltext0
	.long	.LVL77-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -100
	.long	.LVL78-.Ltext0
	.long	.LVL79-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL80-.Ltext0
	.long	.LFE32-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST15:
	.long	.LFB33-.Ltext0
	.long	.LCFI62-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI62-.Ltext0
	.long	.LCFI63-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI63-.Ltext0
	.long	.LCFI64-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI64-.Ltext0
	.long	.LCFI65-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI65-.Ltext0
	.long	.LCFI66-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI66-.Ltext0
	.long	.LCFI67-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	.LCFI67-.Ltext0
	.long	.LCFI68-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 20
	.long	.LCFI68-.Ltext0
	.long	.LCFI69-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI69-.Ltext0
	.long	.LCFI70-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI70-.Ltext0
	.long	.LCFI71-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI71-.Ltext0
	.long	.LCFI72-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI72-.Ltext0
	.long	.LFE33-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 112
	.long	0
	.long	0
.LLST16:
	.long	.LVL82-.Ltext0
	.long	.LVL83-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL84-.Ltext0
	.long	.LVL85-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL85-.Ltext0
	.long	.LVL86-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL86-.Ltext0
	.long	.LVL87-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL88-.Ltext0
	.long	.LVL89-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL89-.Ltext0
	.long	.LVL90-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -100
	.long	.LVL91-.Ltext0
	.long	.LFE33-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST17:
	.long	.LFB34-.Ltext0
	.long	.LCFI73-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI73-.Ltext0
	.long	.LCFI74-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI74-.Ltext0
	.long	.LCFI75-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI75-.Ltext0
	.long	.LCFI76-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	.LCFI76-.Ltext0
	.long	.LCFI77-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI77-.Ltext0
	.long	.LCFI78-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI78-.Ltext0
	.long	.LCFI79-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI79-.Ltext0
	.long	.LFE34-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	0
	.long	0
.LLST18:
	.long	.LVL93-.Ltext0
	.long	.LVL94-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL95-.Ltext0
	.long	.LVL96-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL96-.Ltext0
	.long	.LVL97-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL97-.Ltext0
	.long	.LVL98-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL99-.Ltext0
	.long	.LVL100-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL100-.Ltext0
	.long	.LVL101-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -84
	.long	.LVL102-.Ltext0
	.long	.LVL103-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL104-.Ltext0
	.long	.LFE34-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST19:
	.long	.LFB35-.Ltext0
	.long	.LCFI80-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI80-.Ltext0
	.long	.LCFI81-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI81-.Ltext0
	.long	.LCFI82-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI82-.Ltext0
	.long	.LCFI83-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	.LCFI83-.Ltext0
	.long	.LCFI84-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI84-.Ltext0
	.long	.LCFI85-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI85-.Ltext0
	.long	.LCFI86-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI86-.Ltext0
	.long	.LFE35-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	0
	.long	0
.LLST20:
	.long	.LVL106-.Ltext0
	.long	.LVL107-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL107-.Ltext0
	.long	.LVL108-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL109-.Ltext0
	.long	.LVL110-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL111-.Ltext0
	.long	.LVL112-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL112-.Ltext0
	.long	.LVL113-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -84
	.long	.LVL114-.Ltext0
	.long	.LVL115-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL116-.Ltext0
	.long	.LFE35-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST21:
	.long	.LFB36-.Ltext0
	.long	.LCFI87-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI87-.Ltext0
	.long	.LCFI88-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI88-.Ltext0
	.long	.LCFI89-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI89-.Ltext0
	.long	.LCFI90-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	.LCFI90-.Ltext0
	.long	.LCFI91-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI91-.Ltext0
	.long	.LCFI92-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI92-.Ltext0
	.long	.LCFI93-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI93-.Ltext0
	.long	.LFE36-.Ltext0
	.value	0x3
	.byte	0x74
	.sleb128 96
	.long	0
	.long	0
.LLST22:
	.long	.LVL118-.Ltext0
	.long	.LVL119-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL120-.Ltext0
	.long	.LVL121-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL122-.Ltext0
	.long	.LVL123-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL124-.Ltext0
	.long	.LVL125-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL125-.Ltext0
	.long	.LVL126-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL127-.Ltext0
	.long	.LVL128-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL128-.Ltext0
	.long	.LVL129-1-.Ltext0
	.value	0x3
	.byte	0x91
	.sleb128 -84
	.long	.LVL130-.Ltext0
	.long	.LVL131-.Ltext0
	.value	0x1
	.byte	0x50
	.long	0
	.long	0
.LLST23:
	.long	.LFB37-.Ltext0
	.long	.LCFI94-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI94-.Ltext0
	.long	.LCFI95-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI95-.Ltext0
	.long	.LCFI96-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI96-.Ltext0
	.long	.LCFI97-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI97-.Ltext0
	.long	.LCFI98-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 48
	.long	.LCFI98-.Ltext0
	.long	.LCFI99-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 16
	.long	.LCFI99-.Ltext0
	.long	.LCFI100-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 12
	.long	.LCFI100-.Ltext0
	.long	.LCFI101-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 8
	.long	.LCFI101-.Ltext0
	.long	.LCFI102-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 4
	.long	.LCFI102-.Ltext0
	.long	.LFE37-.Ltext0
	.value	0x2
	.byte	0x74
	.sleb128 48
	.long	0
	.long	0
.LLST24:
	.long	.LVL134-.Ltext0
	.long	.LVL135-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL135-1-.Ltext0
	.long	.LVL139-.Ltext0
	.value	0x1
	.byte	0x56
	.long	.LVL140-.Ltext0
	.long	.LVL141-.Ltext0
	.value	0x1
	.byte	0x56
	.long	0
	.long	0
.LLST25:
	.long	.LVL136-.Ltext0
	.long	.LVL137-1-.Ltext0
	.value	0x1
	.byte	0x50
	.long	.LVL137-1-.Ltext0
	.long	.LVL138-.Ltext0
	.value	0x1
	.byte	0x53
	.long	.LVL140-.Ltext0
	.long	.LVL141-.Ltext0
	.value	0x1
	.byte	0x53
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
.LASF65:
	.string	"__assertion_message_buff"
.LASF18:
	.string	"next_in"
.LASF19:
	.string	"avail_in"
.LASF26:
	.string	"zfree"
.LASF34:
	.string	"z_stream"
.LASF27:
	.string	"opaque"
.LASF13:
	.string	"long long unsigned int"
.LASF38:
	.string	"next"
.LASF6:
	.string	"Bytef"
.LASF28:
	.string	"data_type"
.LASF52:
	.string	"c_stream"
.LASF12:
	.string	"long long int"
.LASF9:
	.string	"signed char"
.LASF24:
	.string	"state"
.LASF14:
	.string	"long int"
.LASF36:
	.string	"gzFile_s"
.LASF37:
	.string	"have"
.LASF40:
	.string	"has_ungetc"
.LASF48:
	.string	"test_gzio"
.LASF15:
	.string	"off_t"
.LASF72:
	.string	"/home/user/workspace/embox/third-party/lib/zlib-1.2.8"
.LASF33:
	.string	"dummy"
.LASF30:
	.string	"reserved"
.LASF57:
	.string	"test_flush"
.LASF53:
	.string	"test_inflate"
.LASF3:
	.string	"unsigned int"
.LASF5:
	.string	"long unsigned int"
.LASF61:
	.string	"main_example"
.LASF11:
	.string	"short unsigned int"
.LASF29:
	.string	"adler"
.LASF1:
	.string	"uInt"
.LASF45:
	.string	"uncompr"
.LASF60:
	.string	"test_dict_inflate"
.LASF20:
	.string	"total_in"
.LASF46:
	.string	"uncomprLen"
.LASF56:
	.string	"test_large_inflate"
.LASF49:
	.string	"fname"
.LASF16:
	.string	"alloc_func"
.LASF4:
	.string	"uLong"
.LASF41:
	.string	"ungetc"
.LASF23:
	.string	"total_out"
.LASF69:
	.string	"dictId"
.LASF67:
	.string	"hello"
.LASF39:
	.string	"file_struct"
.LASF2:
	.string	"unsigned char"
.LASF21:
	.string	"next_out"
.LASF17:
	.string	"free_func"
.LASF32:
	.string	"internal_state"
.LASF10:
	.string	"short int"
.LASF50:
	.string	"file"
.LASF31:
	.string	"z_stream_s"
.LASF71:
	.string	"test/example.c"
.LASF64:
	.string	"myVersion"
.LASF42:
	.string	"FILE"
.LASF43:
	.string	"compr"
.LASF22:
	.string	"avail_out"
.LASF35:
	.string	"gzFile"
.LASF8:
	.string	"voidpf"
.LASF51:
	.string	"test_deflate"
.LASF70:
	.string	"GNU C 4.6.3"
.LASF7:
	.string	"char"
.LASF68:
	.string	"dictionary"
.LASF58:
	.string	"test_sync"
.LASF0:
	.string	"Byte"
.LASF25:
	.string	"zalloc"
.LASF59:
	.string	"test_dict_deflate"
.LASF54:
	.string	"d_stream"
.LASF66:
	.string	"stderr"
.LASF55:
	.string	"test_large_deflate"
.LASF44:
	.string	"comprLen"
.LASF62:
	.string	"argc"
.LASF63:
	.string	"argv"
.LASF47:
	.string	"test_compress"
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
