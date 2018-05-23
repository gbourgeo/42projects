	.file	"main.c"
	.intel_syntax noprefix
	.globl	direct
	.section	.rodata
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
	.section	.rodata
.LC2:
	.string	"%s\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	push	rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	mov	rbp, rsp
	.cfi_def_cfa_register 6
	sub	rsp, 1040
	mov	DWORD PTR -4[rbp], 0
	jmp	.L2
.L7:
	lea	rax, -1040[rbp]
	mov	edx, 1024
	mov	esi, 0
	mov	rdi, rax
	call	memset@PLT
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*8]
	lea	rax, direct[rip]
	mov	rax, QWORD PTR [rdx+rax]
	mov	ecx, 0
	mov	edx, 0
	mov	rsi, rax
	mov	edi, 2
	mov	eax, 0
	call	syscall@PLT
	mov	DWORD PTR -12[rbp], eax
	jmp	.L3
.L6:
	mov	DWORD PTR -8[rbp], 0
	jmp	.L4
.L5:
	mov	eax, DWORD PTR -8[rbp]
	cdqe
	lea	rdx, 18[rax]
	lea	rax, -1040[rbp]
	add	rax, rdx
	mov	rsi, rax
	lea	rdi, .LC2[rip]
	mov	eax, 0
	call	ft_printf@PLT
	mov	eax, DWORD PTR -8[rbp]
	cdqe
	lea	rdx, 16[rax]
	lea	rax, -1040[rbp]
	add	rax, rdx
	movzx	eax, BYTE PTR [rax]
	movsx	eax, al
	add	DWORD PTR -8[rbp], eax
.L4:
	mov	eax, DWORD PTR -8[rbp]
	cmp	eax, DWORD PTR -16[rbp]
	jl	.L5
.L3:
	lea	rdx, -1040[rbp]
	mov	eax, DWORD PTR -12[rbp]
	mov	ecx, 1024
	mov	esi, eax
	mov	edi, 78
	mov	eax, 0
	call	syscall@PLT
	mov	DWORD PTR -16[rbp], eax
	cmp	DWORD PTR -16[rbp], 0
	jg	.L6
	mov	eax, DWORD PTR -12[rbp]
	mov	edi, eax
	call	close@PLT
	add	DWORD PTR -4[rbp], 1
.L2:
	mov	eax, DWORD PTR -4[rbp]
	cdqe
	lea	rdx, 0[0+rax*8]
	lea	rax, direct[rip]
	mov	rax, QWORD PTR [rdx+rax]
	test	rax, rax
	jne	.L7
	mov	eax, 0
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
