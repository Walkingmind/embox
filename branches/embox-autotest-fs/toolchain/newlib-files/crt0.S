	.extern main
	.extern exit

	.global _start
_start:
	mov  (%esp), %eax
	mov  %esp, %ebx
	add  $4, %ebx
	push %ebx
	push %eax
	call main
	add  $8, %esp 
	push %eax
	call exit
.wait: 
	hlt
	jmp .wait
