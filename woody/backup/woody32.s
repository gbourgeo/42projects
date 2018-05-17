	[BITS 64]

	global woody32_func:function
	global woody32_decrypt:function
	global woody32_size:data
	global woody32_args:data
	global woody32_keys:data

	segment .text
	woody32_size dd end - woody32_func
	woody32_args dd end - args
	
woody32_func:					; ELF version
	push rdi
	push rsi
	push rdx
	push rax
	push rbx
	
	push DWORD banner_size
	push banner
	push 1
	syscall

	jmp woody32_end

woody32_decrypt:
	push	r15
	push	r14
	and	rsi, -8
	push	r13
	push	r12
	push	rbp
	push	rbx
	mov	QWORD [rsp-8], rsi
	je	.L1
	mov	r12, rdi
	xor	ebx, ebx
	xor	ebp, ebp
	mov	r15, rdx
.L6:
	lea	eax, [rbp+3]
	add	rbx, r12
	lea	r14d, [rbp+1]
	movzx	esi, BYTE [rbx]
	lea	r13d, [rbp+2]
	mov	r11d, DWORD [r15+8]
	add	rax, r12
	add	r14, r12
	mov	r10d, DWORD [r15+12]
	mov	QWORD [rsp-48], rax
	movzx	eax, BYTE [rax]
	add	r13, r12
	sal	esi, 24
	or	esi, eax
	movzx	eax, BYTE [r14]
	sal	eax, 16
	or	esi, eax
	movzx	eax, BYTE [r13+0]
	sal	eax, 8
	or	esi, eax
	lea	eax, [rbp+4]
	add	rax, r12
	mov	rdi, rax
	mov	QWORD [rsp-40], rax
	lea	eax, [rbp+5]
	movzx	ecx, BYTE [rdi]
	mov	edi, -957401312
	add	rax, r12
	mov	rdx, rax
	mov	QWORD [rsp-32], rax
	lea	eax, [rbp+6]
	add	rax, r12
	sal	ecx, 24
	mov	r8, rax
	mov	QWORD [rsp-24], rax
	lea	eax, [rbp+7]
	add	rax, r12
	mov	r9, rax
	mov	QWORD [rsp-16], rax
	movzx	eax, BYTE [rdx]
	sal	eax, 16
	or	ecx, eax
	movzx	eax, BYTE [r9]
	mov	r9d, DWORD [r15]
	or	ecx, eax
	movzx	eax, BYTE [r8]
	mov	r8d, DWORD [r15+4]
	sal	eax, 8
	or	ecx, eax
.L3:
	mov	eax, esi
	mov	edx, esi
	sal	eax, 4
	shr	edx, 5
	add	edx, r10d
	add	eax, r11d
	xor	eax, edx
	lea	edx, [rsi+rdi]
	xor	eax, edx
	sub	ecx, eax
	mov	eax, ecx
	mov	edx, ecx
	sal	eax, 4
	shr	edx, 5
	add	edx, r8d
	add	eax, r9d
	xor	eax, edx
	lea	edx, [rcx+rdi]
	xor	eax, edx
	sub	esi, eax
	add	edi, 1640531527
	jne	.L3
	mov	eax, esi
	shr	eax, 24
	mov	BYTE [rbx], al
	mov	eax, esi
	mov	rbx, QWORD [rsp-40]
	shr	eax, 16
	mov	BYTE [r14], al
	mov	eax, esi
	shr	eax, 8
	mov	BYTE [r13+0], al
	mov	rax, QWORD [rsp-48]
	mov	BYTE [rax], sil
	mov	eax, ecx
	shr	eax, 24
	mov	BYTE [rbx], al
	mov	rbx, QWORD [rsp-32]
	mov	eax, ecx
	shr	eax, 16
	mov	BYTE [rbx], al
	mov	rbx, QWORD [rsp-24]
	mov	eax, ecx
	shr	eax, 8
	mov	BYTE [rbx], al
	lea	ebx, [rbp+8]
	cmp	QWORD [rsp-8], rbx
	mov	rax, QWORD [rsp-16]
	mov	rbp, rbx
	mov	BYTE [rax], cl
	ja	.L6
.L1:
	pop	rbx
	pop	rbp
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	ret
	
woody32_end:
	mov rsi, DWORD text_size
	mov rdx, DWORD woody32_keys
	mov rdi, text_vaddr
	call woody32_decrypt

	pop rbx
	pop rax
	pop rdx
	pop rsi
	pop rdi

	push text_vaddr
	ret

args:
	woody32_keys dd 0x0, 0x0, 0x0, 0x0
	text_vaddr dd 0x0
	text_size dd 0x0
	banner_size dd 0x0
	banner db ""
end:

