	;; char *strdup(const char *s);

	segment .text
	global 	_ft_strdup
	extern 	_ft_strlen
	extern 	_malloc

_ft_strdup:
	mov		rbx, rdi
	call	_ft_strlen
	mov		r8, rdi
	add		eax, 1			; arg is in rbx
	mov		edi, eax
	mov		ecx, eax
	push	rcx
	call	_malloc
	pop		rcx
	test	rax, rax
	jz		return
	mov		rdi, rax
	mov		rdx, rax
	mov		rsi, rbx

	repnz	movsb			;copi rsi dans rdi
	mov		byte [rdi], 0
	mov		rax, rdx

return:
	ret
