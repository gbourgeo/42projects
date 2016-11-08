	;; void ft_putnbr(int n)

	%define SYS_WRITE	0x2000004
	%define STDOUT		1

	segment	.data
	negat	db "-"
	result	db 10

	segment	.text
	global	_ft_putnbr

_ft_putnbr:
	mov		r8, 9
	cmp		edi, 0
	jl		_print_neg

_modulo:
	mov		eax, edi
	mov		ecx, 10
	cdq							; edx = 0
	idiv	ecx					; eax / ecx -> eax = division result, edx = modulo result
	cmp		eax, 0				; if eax = 0, then edi was < 9, so we can print.
	je		_print
	mov		edi, eax			; else
	lea		rsi, [rel result]	; we go to the right address or our 'result'
	add		rsi, r8				; adding r8
	mov		byte [rsi], "0"		; We write "0" to it then either we had either we sub
	cmp		eax, 0
	jl		_subvalue
	jmp		_addvalue
_subvalue:
	sub		byte [rsi], dl
	jmp		_continue
_addvalue:
	add		byte [rsi], dl
_continue:
	dec		r8
	jmp		_modulo

_print:
	mov 	rax, SYS_WRITE
	lea		rsi, [rel result]
	add 	rsi, r8
	mov		byte [rsi], "0"
	cmp		edx, 0
	jl		_sub
	jmp		_add
_sub:
	sub		byte [rsi], dl
	jmp		_finish
_add:
	add		byte [rsi], dl
_finish:
	mov 	rdi, STDOUT
	mov 	rdx, 10
	sub		rdx, r8
	syscall
	ret

_print_neg:
	mov		rbx, rdi
	mov 	rax, SYS_WRITE
	mov 	rdi, STDOUT
	lea 	rsi, [rel negat]
	mov 	rdx, 1
	syscall

	test	rax, rax
	jle		_end
	mov		rdi, rbx
	jmp		_modulo

_end:
	ret
