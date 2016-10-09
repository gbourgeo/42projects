	;; void *memchr(const void *s, int c, size_t n);
	;; rdi = s, c = rsi, n = rdx
	segment .text
	global 	_ft_memchr

_ft_memchr:
	push 	rcx
	mov 	rcx, 0
	cmp 	rdi, 0
	je 		_return_false

_while:
	cmp 	rcx, rdx
	jae 	_return_false
	cmp		sil, [rdi + rcx]
	je 		_return_true
	inc		rcx
	jmp 	_while

_return_false:
	pop		rcx
	lea 	rax, [0]
	ret

_return_true:
	lea 	rax, [rdi + rcx]
	pop		rcx
	ret
