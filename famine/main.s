	.file	"main.c"
	.intel_syntax noprefix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s : %d\n"
	.text
	.p2align 4,,15
	.globl	get_dat_elf
	.type	get_dat_elf, @function
get_dat_elf:
.LFB37:
	.cfi_startproc
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
	sub	rsp, 1032
	.cfi_def_cfa_offset 1072
	movzx	edx, BYTE PTR [rdi]
	test	dl, dl
	je	.L10
	lea	r8, -1[rsp]
	mov	eax, 1
	.p2align 4,,10
	.p2align 3
.L3:
	mov	BYTE PTR [r8+rax], dl
	mov	ecx, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rdi+rax]
	test	dl, dl
	jne	.L3
.L2:
	movzx	edx, BYTE PTR [rsi]
	test	dl, dl
	je	.L19
	movsx	rdi, ecx
	mov	eax, 1
	mov	rbx, rsp
	add	rdi, rsp
	.p2align 4,,10
	.p2align 3
.L5:
	mov	BYTE PTR -1[rdi+rax], dl
	mov	r8d, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rsi+rax]
	test	dl, dl
	jne	.L5
	add	ecx, r8d
.L4:
	movsx	rcx, ecx
	xor	edx, edx
	xor	eax, eax
	mov	BYTE PTR [rsp+rcx], 0
	mov	rsi, rbx
	xor	ecx, ecx
	mov	edi, 2
	call	syscall@PLT
	cmp	eax, -1
	mov	rbp, rax
	je	.L1
	mov	esi, eax
	mov	ecx, 2
	xor	eax, eax
	mov	edx, 1
	mov	edi, 8
	call	syscall@PLT
	cmp	eax, -1
	mov	r12, rax
	je	.L17
	sub	rsp, 8
	.cfi_def_cfa_offset 1080
	mov	edx, eax
	xor	esi, esi
	push	0
	.cfi_def_cfa_offset 1088
	xor	eax, eax
	mov	r9d, ebp
	mov	r8d, 2
	mov	ecx, 3
	mov	edi, 9
	call	syscall@PLT
	mov	r13, rax
	cmp	r13, -1
	pop	rax
	.cfi_def_cfa_offset 1080
	pop	rdx
	.cfi_def_cfa_offset 1072
	je	.L17
	lea	rdi, .LC0[rip]
	mov	edx, ebp
	mov	rsi, rbx
	xor	eax, eax
	call	printf@PLT
	mov	edi, ebp
	call	close@PLT
	mov	edx, r12d
	mov	rsi, r13
	mov	edi, 11
	xor	eax, eax
	call	syscall@PLT
.L1:
	add	rsp, 1032
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	pop	rbx
	.cfi_def_cfa_offset 32
	pop	rbp
	.cfi_def_cfa_offset 24
	pop	r12
	.cfi_def_cfa_offset 16
	pop	r13
	.cfi_def_cfa_offset 8
	ret
.L17:
	.cfi_restore_state
	mov	edi, ebp
	call	close@PLT
	add	rsp, 1032
	.cfi_remember_state
	.cfi_def_cfa_offset 40
	pop	rbx
	.cfi_def_cfa_offset 32
	pop	rbp
	.cfi_def_cfa_offset 24
	pop	r12
	.cfi_def_cfa_offset 16
	pop	r13
	.cfi_def_cfa_offset 8
	ret
.L19:
	.cfi_restore_state
	mov	rbx, rsp
	jmp	.L4
.L10:
	xor	ecx, ecx
	jmp	.L2
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
	je	.L20
	.p2align 4,,10
	.p2align 3
.L22:
	xor	eax, eax
	mov	ecx, 1024
	mov	rdx, r12
	mov	esi, r14d
	mov	edi, 217
	call	syscall@PLT
	test	eax, eax
	mov	r15d, eax
	jle	.L29
	xor	ebx, ebx
	jmp	.L24
	.p2align 4,,10
	.p2align 3
.L23:
	movsx	eax, BYTE PTR 32[rsp+rbp]
	add	ebx, eax
	cmp	r15d, ebx
	jle	.L22
.L24:
	movsx	rbp, ebx
	cmp	BYTE PTR 34[rsp+rbp], 8
	jne	.L23
	lea	rsi, 19[r12+rbp]
	mov	rdi, r13
	call	get_dat_elf
	jmp	.L23
.L29:
	mov	edi, DWORD PTR 8[rsp]
	call	close@PLT
.L20:
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
	.globl	direct
	.section	.rodata.str1.1
.LC1:
	.string	"/tmp/test/"
.LC2:
	.string	"/tmp/test2/"
	.section	.data.rel.local,"aw",@progbits
	.align 16
	.type	direct, @object
	.size	direct, 24
direct:
	.quad	.LC1
	.quad	.LC2
	.quad	0
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
