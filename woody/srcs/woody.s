	[BITS 64]

	global woody_func:function
	global woody_decrypt:function
	global woody_size:data
	global woody_offs:data
	global woody_keys:data

	segment .text
	woody_size dd end - woody_func
	woody_offs dd woody_main - woody_func
	woody_keys dd 0x95a8882c, 0x9d2cc113, 0x815aa0cd, 0xa1c489f7
	
woody_func:
	banner db "....WOODY....", 10

woody_decrypt:
	push	r13
	push	r12

	mov	r12d, 8
	sub	r12, rdi
	cmp	rsi, 8
	push	rbp
	push	rbx
	jbe	decrypt_end
	mov	rbp, rdi
decrypt:
	movzx	r8d, BYTE [rbp]
	movzx	eax, BYTE [rbp+1]
	mov	r9d, -957401312
	movzx	ecx, BYTE [rbp+4]
	mov	ebx, DWORD [rdx+8]
	mov	edi, DWORD [rdx+12]
	mov	r11d, DWORD [rdx]
	mov	r10d, DWORD [rdx+4]
	sal	eax, 16
	sal	r8d, 24
	or	r8d, eax
	movzx	eax, BYTE [rbp+3]
	sal	ecx, 24
	or	r8d, eax
	movzx	eax, BYTE [rbp+2]
	sal	eax, 8
	or	r8d, eax
	movzx	eax, BYTE [rbp+5]
	sal	eax, 16
	or	ecx, eax
	movzx	eax, BYTE [rbp+7]
	or	ecx, eax
	movzx	eax, BYTE [rbp+6]
	sal	eax, 8
	or	ecx, eax
decrypt_loop:
	mov	eax, r8d
	mov	r13d, r8d
	sal	eax, 4
	shr	r13d, 5
	add	r13d, edi
	add	eax, ebx
	xor	eax, r13d
	lea	r13d, [r8+r9]
	xor	eax, r13d
	sub	ecx, eax
	mov	eax, ecx
	mov	r13d, ecx
	sal	eax, 4
	shr	r13d, 5
	add	r13d, r10d
	add	eax, r11d
	xor	eax, r13d
	lea	r13d, [rcx+r9]
	xor	eax, r13d
	sub	r8d, eax
	add	r9d, 1640531527
	jne	decrypt_loop
	mov	eax, r8d
	mov	BYTE [rbp+3], r8b
	mov	BYTE [rbp+7], cl
	shr	eax, 24
	add	rbp, 8
	mov	BYTE [rbp-8], al
	mov	eax, r8d
	shr	eax, 16
	mov	BYTE [rbp-7], al
	mov	eax, r8d
	shr	eax, 8
	mov	BYTE [rbp-6], al
	mov	eax, ecx
	shr	eax, 24
	mov	BYTE [rbp-4], al
	mov	eax, ecx
	shr	eax, 16
	mov	BYTE [rbp-3], al
	mov	eax, ecx
	shr	eax, 8
	mov	BYTE [rbp-2], al
	lea	rax, [r12+rbp]
	cmp	rsi, rax
	ja	decrypt
decrypt_end:
	pop	rbx
	pop	rbp
	pop	r12
	pop	r13
	ret

woody_main:
	;; save registers
	push rdi
	push rsi
	push rdx
	push rax
	push rbx
	
	mov rdi, 1
	lea rsi, [rel banner]
	mov rdx, 14
	mov rax, 1
	syscall						; write(1, msg, 14);

	;mov edx, [rel woody_keys]
	;mov esi, 0x1a0
	;mov edi, [rel text_vaddr]
	;call woody_decrypt			; void decrypt(u_char *d, size_t s, const uint32_t *k)

	;; restore registers
	pop rbx
	pop rax
	pop rdx
	pop rsi
	pop rdi

	nop
	jmp 0x42424242
	text_vaddr dd 0				; .text vaddr
end:
