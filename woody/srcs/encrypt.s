	[BITS 64]

	section .text
	global	woody_encrypt:function
	
woody_encrypt:
	push	r13
	push	r12
	mov	r12d, 8
	sub	r12, rdi
	cmp	rsi, 8
	push	rbp
	push	rbx
	jbe	end
	mov	rbp, rdi
encrypt:
	movzx	r8d, BYTE [rbp]
	movzx	eax, BYTE [rbp+1]
	xor	r9d, r9d
	movzx	ecx, BYTE [rbp+4]
	mov	ebx, DWORD [rdx]
	mov	edi, DWORD [rdx+4]
	mov	r11d, DWORD [rdx+8]
	mov	r10d, DWORD [rdx+12]
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
encrypt_loop:
	mov	eax, ecx
	mov	r13d, ecx
	sub	r9d, 1640531527
	sal	eax, 4
	shr	r13d, 5
	add	r13d, edi
	add	eax, ebx
	xor	eax, r13d
	lea	r13d, [r9+rcx]
	xor	eax, r13d
	add	r8d, eax
	mov	eax, r8d
	mov	r13d, r8d
	sal	eax, 4
	shr	r13d, 5
	add	r13d, r10d
	add	eax, r11d
	xor	eax, r13d
	lea	r13d, [r9+r8]
	xor	eax, r13d
	add	ecx, eax
	cmp	r9d, -957401312
	jne	encrypt_loop
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
	ja	encrypt
end:
	pop	rbx
	pop	rbp
	pop	r12
	pop	r13
	ret
