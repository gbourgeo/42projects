	;;  int memcmp(const void *s1, const void *s2, size_t n);
	;; rdi = s1, rsi = s2, n = rdx
	segment .text
	global	_ft_memcmp

_ft_memcmp:
	mov 	rax, 0
	mov 	rcx, rdx
	cld
	repe	cmpsb
	je		_same
	mov 	al, byte [rdi - 1]
	sub 	al, byte [rsi - 1]
	movsx	rax, al

_same:
	ret
