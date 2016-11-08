	;; void cat(int fd);
	;; All registers, except rcx and r11, are preserved during the syscall.

	%define SYS_READ	0x2000003
	%define SYS_WRITE	0x2000004
	%define STDOUT		1
	%define BUFFER_SIZE 255

	segment .bss
	file_buffer resb BUFFER_SIZE

	segment	.text
	global 	_ft_cat

_ft_cat:
	test	edi, edi
	js		_return
	;; We stock rdi in rbx so we can reuse the fd in the _read_write loop if the buffer is too low
	mov 	rbx, rdi

_read_write:
	mov 	rax, SYS_READ
	mov 	rdi, rbx
	lea		rsi, [rel file_buffer]
	mov 	rdx, BUFFER_SIZE
	syscall
	cmp		rax, 0
	jle		_return

	mov 	rdx, rax
	mov 	rax, SYS_WRITE
	mov 	rdi, STDOUT
	lea		rsi, [rel file_buffer]
	syscall
	cmp		rax, 0
	jle		_return
	
	jmp		_read_write

_return:
	ret
