	[BITS 64]

	global woody_func:function
	global woody_size:data
	global woody_offset:data

	section .data
	msg db '....WOODY....', 10

	section .text

	woody_size dd end - woody_func
	woody_offset dd end - woody_func

woody_func:
	mov rdi, 1
	mov rsi, msg
	mov rdx, 14
	mov rax, 1
	syscall
	mov rdi, 0
	mov rax, 60
	syscall
end:	
