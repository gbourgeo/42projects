	;; void cat(int fd);

	%define SYS_READ	0
	%define SYS_WRITE	1
	%define STDOUT		1
	%define BUFFER_SIZE 2048

	segment .bss
	file_buffer resb BUFFER_SIZE

	segment	.text
	global 	_ft_cat

_ft_cat:
	mov 	rbx, rdi
	cmp 	rbx, 0
	jb		_return

_read_write:
	mov 	rax, SYS_READ
	mov 	rdi, rbx
	mov 	rsi, file_buffer
	mov 	rdx, BUFFER_SIZE
	syscall

	cmp 	rax, 0
	jbe 	_return

	mov 	rdx, rax
	mov 	rax, SYS_WRITE
	mov 	rdi, STDOUT
	mov 	rsi, file_buffer
	syscall

	jp 		_read_write

_return:
	cmp 	rbx, 0
	je 		_read_write
	ret
