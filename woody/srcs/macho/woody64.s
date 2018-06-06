	[BITS 64]
	
	global	_woody64_func
	global	_woody64_size
	
	section	.text
	_woody64_size dd _end - _woody64_func

_woody64_func:					; MACH-O version
	push rdi
	push rsi
	push rdx
	push rax
	push rbx
	
	mov rdi, 1
	lea rsi, [rel banner]
	mov edx, [rel banner_size]
	mov rax, 0x2000004
	syscall

	jmp woody64_end
	
;; void woody_decrypt(void *text_section, uint32_t text_size, int *key)
woody64_decrypt:
	push	rbp
	mov	rbp, rsp

	push	r15
	push	r14
	push	r13
	push	r12
	push	rbx

	mov	qword [rbp - 56], rdx
	and	rsi, -8
	mov	qword [rbp - 48], rsi
	je	LBB0_5
	xor	r13d, r13d
LBB0_2:
	movzx	eax, byte [rdi + r13]
	shl	eax, 24
	mov	ecx, r13d
	or	ecx, 1
	mov	qword [rbp - 112], rcx
	movzx	ecx, byte [rdi + rcx]
	shl	ecx, 16
	or	ecx, eax
	mov	eax, r13d
	or	eax, 2
	mov	qword [rbp - 104], rax
	movzx	eax, byte [rdi + rax]
	shl	eax, 8
	or	eax, ecx
	mov	ecx, r13d
	or	ecx, 3
	mov	qword [rbp - 96], rcx
	movzx	ecx, byte [rdi + rcx]
	or	ecx, eax
	mov	eax, r13d
	or	eax, 4
	mov	qword [rbp - 88], rax
	movzx	eax, byte [rdi + rax]
	shl	eax, 24
	mov	edx, r13d
	or	edx, 5
	mov	qword [rbp - 80], rdx
	movzx	edx, byte [rdi + rdx]
	shl	edx, 16
	or	edx, eax
	mov	eax, r13d
	or	eax, 6
	mov	qword [rbp - 72], rax
	movzx	eax, byte [rdi + rax]
	shl	eax, 8
	or	eax, edx
	mov	edx, r13d
	or	edx, 7
	mov	qword [rbp - 64], rdx
	movzx	edx, byte [rdi + rdx]
	or	edx, eax
	mov	rsi, qword [rbp - 56]
	mov	r15d, dword [rsi + 8]
	mov	r12d, dword [rsi + 12]
	mov	eax, dword [rsi]
	mov	r9d, dword [rsi + 4]
	mov	r10d, -957401312
	mov	r8d, 32
LBB0_3:
	mov	r11d, ecx
	shl	r11d, 4
	add	r11d, r15d
	lea	r14d, [rcx + r10]
	xor	r14d, r11d
	mov	esi, ecx
	shr	esi, 5
	add	esi, r12d
	xor	esi, r14d
	sub	edx, esi
	mov	esi, edx
	shl	esi, 4
	add	esi, eax
	lea	ebx, [r10 + rdx]
	xor	ebx, esi
	mov	esi, edx
	shr	esi, 5
	add	esi, r9d
	xor	esi, ebx
	sub	ecx, esi
	add	r10d, 1640531527
	dec	r8d
	jne	LBB0_3
	mov	eax, ecx
	shr	eax, 24
	mov	byte [rdi + r13], al
	mov	eax, ecx
	shr	eax, 16
	mov	rsi, qword [rbp - 112]
	mov	byte [rdi + rsi], al
	mov	rax, qword [rbp - 104]
	mov	byte [rdi + rax], ch
	mov	rax, qword [rbp - 96]
	mov	byte [rdi + rax], cl
	mov	eax, edx
	shr	eax, 24
	mov	rcx, qword [rbp - 88]
	mov	byte [rdi + rcx], al
	mov	eax, edx
	shr	eax, 16
	mov	rcx, qword [rbp - 80]
	mov	byte [rdi + rcx], al
	mov	rax, qword [rbp - 72]
	mov	byte [rdi + rax], dh
	mov	rax, qword [rbp - 64]
	mov	byte [rdi + rax], dl
	lea	r13d, [r13 + 8]
	cmp	r13, qword [rbp - 48]
	jb	LBB0_2
LBB0_5:
	pop	rbx
	pop	r12
	pop	r13
	pop	r14
	pop	r15
	pop	rbp
	ret

woody64_end:
	lea rdx, [rel woody64_keys]
	mov rsi, QWORD [rel text_size]
	lea rdi, [rel _woody64_func]
	add	rdi, QWORD [rel text_vaddr]
	call woody64_decrypt

	lea rax, [rel _woody64_func]
	add rax, QWORD [rel jump_offset]
	mov QWORD [rel jump_offset], rax
	
	pop rbx
	pop rax
	pop rdx
	pop rsi
	pop rdi

	jmp QWORD [rel jump_offset]
	
_end:	
	woody64_keys dd 0x0, 0x0, 0x0, 0x0
	text_vaddr dq 0x0
	text_size dq 0x0
	jump_offset dq 0x0
	banner_size dq 0x0
	banner db ''
