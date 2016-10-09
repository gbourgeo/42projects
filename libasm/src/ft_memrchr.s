	;; void *memrchr(const void *s, int c, size_t n);
	;; rdi = s, c = rsi, n = rdx
	segment .text
	global 	_ft_memrchr

_ft_memrchr:
	cmp 	rdi, 0
	je 		_return_false

_while:
	cmp 	rdx, 0
	jbe 	_return_false
	dec		rdx
	cmp		sil, [rdi + rdx]
	je 		_return_true
	jmp 	_while

_return_false:
	lea rax, [0]
	ret

_return_true:
	lea rax, [rdi + rdx]
	ret
