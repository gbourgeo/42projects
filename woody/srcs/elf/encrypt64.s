	[BITS 64]

	section .text
	global	woody64_encrypt:function

woody64_encrypt:
	push r15
	push r14
	push r13
	push r12
	push rbp
	push rcx
	push rbx
	push rax

	and esi, -8
	mov DWORD [rsp - 4], esi
	je .end
	mov r11, rdi
	mov r14d, 0
	mov r13, rdx
.loop:
	mov r12d, r14d
	add r12, r11
	lea ebp, [r14 + 1]
	add rbp, r11
	lea ebx, [r14 + 2]
	add rbx, r11
	lea eax, [r14 + 3]
	add rax, r11
	mov QWORD [rsp - 48], rax
	movzx ecx, BYTE [r12]
	sal ecx, 24
	movzx eax, BYTE [rax]
	or ecx, eax
	movzx eax, BYTE [rbp + 0]
	sal eax, 16
	or ecx, eax
	movzx eax, BYTE [rbx]
	sal eax, 8
	or ecx, eax
	lea eax, [r14 + 4]
	lea rdi, [r11 + rax]
	mov QWORD [rsp - 40], rdi
	lea eax, [r14 + 5]
	lea rsi, [r11 + rax]
	mov QWORD [rsp - 32], rsi
	lea eax, [r14 + 6]
	lea r8, [r11 + rax]
	mov QWORD [rsp - 24], r8
	lea eax, [r14 + 7]
	lea r9, [r11 + rax]
	mov QWORD [rsp - 16], r9
	movzx edx, BYTE [rdi]
	sal edx, 24
	movzx eax, BYTE [rsi]
	sal eax, 16
	or edx, eax
	movzx eax, BYTE [r9]
	or edx, eax
	movzx eax, BYTE [r8]
	sal eax, 8
	or edx, eax
	mov r10d, DWORD [r13 + 0]
	mov r9d, DWORD [r13 + 4]
	mov r8d, DWORD [r13 + 8]
	mov edi, DWORD [r13 + 12]
	mov esi, 0
.encryption:
	sub esi, 1640531527
	mov eax, edx
	sal eax, 4
	add eax, r10d
	mov r15d, edx
	shr r15d, 5
	add r15d, r9d
	xor eax, r15d
	lea r15d, [rsi + rdx]
	xor eax, r15d
	add ecx, eax
	mov eax, ecx
	sal eax, 4
	add eax, r8d
	mov r15d, ecx
	shr r15d, 5
	add r15d, edi
	xor eax, r15d
	lea r15d, [rsi + rcx]
	xor eax, r15d
	add edx, eax
	cmp esi, -957401312
	jne .encryption
	mov eax, ecx
	shr eax, 24
	mov BYTE [r12], al
	mov eax, ecx
	shr eax, 16
	mov BYTE [rbp + 0], al
	movzx eax, ch
	mov BYTE [rbx], al
	mov rax, QWORD [rsp - 48]
	mov BYTE [rax], cl
	mov eax, edx
	shr eax, 24
	mov rbx, QWORD [rsp - 40]
	mov BYTE [rbx], al
	mov eax, edx
	shr eax, 16
	mov rbx, QWORD [rsp - 32]
	mov BYTE [rbx], al
	mov rbx, QWORD [rsp - 24]
	movzx eax, dh
	mov BYTE [rbx], al
	mov rax, QWORD [rsp - 16]
	mov BYTE [rax], dl
	add r14d, 8
	cmp DWORD [rsp - 4], r14d
	ja .loop
.end:
	pop rax
	pop rbx
	pop rcx
	pop rbp
	pop r12
	pop r13
	pop r14
	pop r15
	ret
