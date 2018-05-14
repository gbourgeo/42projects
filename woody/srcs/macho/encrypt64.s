	[BITS 64]

	section	.text
	global	_woody64_encrypt

_woody64_encrypt:
	push	rbp
	mov		rbp, rsp

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
	mov	r12d, dword [rsi]
	mov	ebx, dword [rsi + 4]
	mov	eax, dword [rsi + 8]
	mov	r9d, dword [rsi + 12]
	mov	r10d, 32
	mov	r8d, -1640531527
LBB0_3:
	mov	r11d, edx
	shl	edx, 4
	add	edx, r12d
	lea	r14d, [r11 + r8]
	mov	r15d, r11d
	shr	r15d, 5
	add	r15d, ebx
	xor	r15d, edx
	xor	r15d, r14d
	add	ecx, r15d
	mov	edx, ecx
	shl	edx, 4
	add	edx, eax
	lea	esi, [r8 + rcx]
	xor	esi, edx
	mov	edx, ecx
	shr	edx, 5
	add	edx, r9d
	xor	edx, esi
	add	edx, r11d
	add	r8d, -1640531527
	dec	r10d
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
