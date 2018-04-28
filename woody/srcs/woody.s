	[BITS 64]

	global woody_func:function
	global woody_size:data
	global woody_offset:data

	segment .text

	woody_size dd end - woody_func
	woody_offset dd woody_run - woody_func

woody_func:

	banner db "....WOODY....", 10

woody_run:
	;; 	push rbp
	;; 	mov rbp, rsp

	;; save all the registers
	push rdi
	push rsi
	push rdx
	push rax
	push rbx
	
	;; write(1, msg, 14);
	mov rdi, 1
	lea rsi, [rel banner]
	mov rdx, 14
	mov rax, 1
	syscall

	;; restore the registers
	pop rbx
	pop rax
	pop rdx
	pop rsi
	pop rdi

	;; 	mov rsp, rbp
	;; 	pop rbp
	jmp 0xFFFFFFFF				; jump to the original address
end:
