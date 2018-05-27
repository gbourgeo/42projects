	.file	"main.c"
	.intel_syntax noprefix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s %d %d\n"
.LC1:
	.string	"not en elf file"
	.text
	.p2align 4,,15
	.globl	pack_dat_elf
	.type	pack_dat_elf, @function
pack_dat_elf:
.LFB38:
	.cfi_startproc
	cmp	BYTE PTR [rdx], 127
	mov	rax, rdx
	je	.L4
.L2:
	lea	rdi, .LC1[rip]
	jmp	puts@PLT
	.p2align 4,,10
	.p2align 3
.L4:
	cmp	BYTE PTR 1[rdx], 69
	jne	.L2
	cmp	BYTE PTR 2[rdx], 76
	jne	.L2
	cmp	BYTE PTR 3[rdx], 70
	jne	.L2
	cmp	BYTE PTR 4[rdx], 2
	jne	.L2
	cmp	BYTE PTR 5[rdx], 0
	je	.L2
	cmp	BYTE PTR 6[rdx], 1
	jne	.L2
	movzx	ecx, BYTE PTR 16[rdx]
	lea	edx, -2[rcx]
	cmp	dl, 1
	ja	.L2
	mov	edx, edi
	lea	rdi, .LC0[rip]
	mov	ecx, esi
	mov	rsi, rax
	xor	eax, eax
	jmp	printf@PLT
	.cfi_endproc
.LFE38:
	.size	pack_dat_elf, .-pack_dat_elf
	.section	.rodata.str1.1
.LC2:
	.string	"%s "
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
	je	.L14
	lea	r8, -1[rsp]
	mov	eax, 1
	.p2align 4,,10
	.p2align 3
.L7:
	mov	BYTE PTR [r8+rax], dl
	mov	ecx, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rdi+rax]
	test	dl, dl
	jne	.L7
.L6:
	movzx	edx, BYTE PTR [rsi]
	test	dl, dl
	je	.L22
	movsx	rdi, ecx
	mov	eax, 1
	mov	rbx, rsp
	add	rdi, rsp
	.p2align 4,,10
	.p2align 3
.L9:
	mov	BYTE PTR -1[rdi+rax], dl
	mov	r8d, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rsi+rax]
	test	dl, dl
	jne	.L9
	add	ecx, r8d
.L8:
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
	je	.L5
	mov	esi, eax
	mov	ecx, 2
	xor	eax, eax
	mov	edx, 1
	mov	edi, 8
	call	syscall@PLT
	cmp	eax, -1
	mov	r12, rax
	je	.L21
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
	je	.L21
	lea	rdi, .LC2[rip]
	mov	rsi, rbx
	xor	eax, eax
	call	printf@PLT
	mov	rdx, r13
	mov	esi, r12d
	mov	edi, ebp
	call	pack_dat_elf
	mov	edi, ebp
	call	close@PLT
	mov	edx, r12d
	mov	rsi, r13
	mov	edi, 11
	xor	eax, eax
	call	syscall@PLT
.L5:
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
.L21:
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
.L22:
	.cfi_restore_state
	mov	rbx, rsp
	jmp	.L8
.L14:
	xor	ecx, ecx
	jmp	.L6
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
	je	.L23
	.p2align 4,,10
	.p2align 3
.L25:
	xor	eax, eax
	mov	ecx, 1024
	mov	rdx, r12
	mov	esi, r14d
	mov	edi, 217
	call	syscall@PLT
	test	eax, eax
	mov	r15d, eax
	jle	.L32
	xor	ebx, ebx
	jmp	.L27
	.p2align 4,,10
	.p2align 3
.L26:
	movsx	eax, BYTE PTR 32[rsp+rbp]
	add	ebx, eax
	cmp	r15d, ebx
	jle	.L25
.L27:
	movsx	rbp, ebx
	cmp	BYTE PTR 34[rsp+rbp], 8
	jne	.L26
	lea	rsi, 19[r12+rbp]
	mov	rdi, r13
	call	get_dat_elf
	jmp	.L26
.L32:
	mov	edi, DWORD PTR 8[rsp]
	call	close@PLT
.L23:
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
.LC3:
	.string	"/tmp/test/"
.LC4:
	.string	"/tmp/test2/"
	.section	.data.rel.local,"aw",@progbits
	.align 16
	.type	direct, @object
	.size	direct, 24
direct:
	.quad	.LC3
	.quad	.LC4
	.quad	0
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
