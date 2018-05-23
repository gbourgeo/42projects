	.file	"main.c"
	.intel_syntax noprefix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%s\n"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB35:
	.cfi_startproc
	push	r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	push	r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	lea	rax, direct[rip]
	push	r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	push	r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	sub	rsp, 1048
	.cfi_def_cfa_offset 1104
	mov	rdx, QWORD PTR direct[rip]
	mov	QWORD PTR 8[rsp], rax
	test	rdx, rdx
	je	.L11
	lea	rbp, 16[rsp]
	lea	r13, .LC0[rip]
.L8:
	xor	eax, eax
	mov	ecx, 128
	mov	rdi, rbp
	rep stosq
	mov	esi, 591872
	mov	rdi, rdx
	call	open@PLT
	mov	r14d, eax
	.p2align 4,,10
	.p2align 3
.L3:
	xor	eax, eax
	mov	ecx, 1024
	mov	rdx, rbp
	mov	esi, r14d
	mov	edi, 78
	call	syscall@PLT
	test	eax, eax
	mov	r12d, eax
	jle	.L14
	xor	r15d, r15d
	mov	rbx, rbp
	.p2align 4,,10
	.p2align 3
.L4:
	lea	rsi, 18[rbx]
	xor	eax, eax
	mov	rdi, r13
	call	ft_printf@PLT
	movzx	eax, WORD PTR 16[rbx]
	add	r15d, eax
	movsx	rbx, r15d
	add	rbx, rbp
	cmp	r12d, r15d
	jg	.L4
	jmp	.L3
.L14:
	mov	edi, r14d
	call	close@PLT
	add	QWORD PTR 8[rsp], 8
	mov	rax, QWORD PTR 8[rsp]
	mov	rdx, QWORD PTR [rax]
	test	rdx, rdx
	jne	.L8
.L11:
	add	rsp, 1048
	.cfi_def_cfa_offset 56
	xor	eax, eax
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
