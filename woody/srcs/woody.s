	[BITS 64]

	global woody_func:function
	global woody_size:data

	segment .text
	woody_size dd end - woody_func

woody_func:

	banner db "....WOODY....", 10

	mov rdi, 0
	mov rdi, 1
	lea rsi, [rel banner]
	mov rdx, 14
	mov rax, 1
	syscall						; write(1, msg, 14);

	jmp 0xFFFFFFFF
end:
