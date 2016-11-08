	;; int puts(const char *s);

	%define SYS_WRITE	0x2000004
	%define STDOUT		1

	segment	.data
	new_line db 10
	
	segment .text
	global 	_ft_puts
	extern 	_ft_strlen

_ft_puts:
	call 	_ft_strlen
	push 	rax
	cmp 	rax, 0
	jg 		do_print
	cmp 	rax, 0
	jz 		do_end
	jmp 	do_error

do_print:
	mov 	rsi, rdi
	mov 	rdi, STDOUT
	mov 	rdx, rax
	mov 	rax, SYS_WRITE
	syscall

	test 	rax, rax
	jle 	do_error
	jmp 	do_end

do_end:
	lea		rsi, [rel new_line]
	mov 	rdi, STDOUT
	mov 	rdx, 1
	mov 	rax, SYS_WRITE
	syscall

	test 	rax, rax
	jle 	do_error
	pop 	rax
	inc 	rax
	mov		rax, 10
	ret

do_error:
	pop 	rax
	mov 	rax, -1
	ret
