	;; void cat(int fd);
	;; All registers, except rcx and r11, are preserved during the syscall.

	%define SYS_READ	0
	%define SYS_WRITE	1
	%define STDOUT		1
	%define BUFFER_SIZE 255

	segment .bss
	file_buffer resb BUFFER_SIZE

	segment	.text
	global 	_ft_cat

_ft_cat:
	mov 	rbx, rdi

_read_write:
	mov 	rax, SYS_READ
	mov 	rdi, rbx
	mov 	rsi, file_buffer
	mov 	rdx, BUFFER_SIZE
	syscall
	cmp		rax, 0
	jle		_return

	mov 	rdx, rax
	mov 	rax, SYS_WRITE
	mov 	rdi, STDOUT
	mov 	rsi, file_buffer
	syscall
	cmp		rax, 0
	jle		_return
	
	jmp		_read_write

_return:
	ret
