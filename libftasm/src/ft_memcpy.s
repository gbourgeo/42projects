	;; void *memcpy(void *dest, const void *src, size_t n);

	segment .text
	global 	_ft_memcpy

_ft_memcpy:
	mov		r10, rdi
	cmp		rdi, byte 0
	je		return
	cmp		rsi, byte 0
	je		return
	cld							; auto rcx++ rsi++
	mov		rcx, rdx			; len of apply
	rep		movsb				; while [rdi] = [rsi]
	jmp		return

return:
	mov		rax, r10
	ret
