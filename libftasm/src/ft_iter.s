	;; void		ft_striter(char *s, void (*f)(char *))
	
	segment .text
	global 	_ft_iter

	;; rdi = char *s
	;; rsi = fonction
	;; arg de la fonction === rdi++;
_ft_iter:
	mov		rdx, rdi
	
_while:
	cmp		byte [rdx], 0
	je		_end
	mov		rdi, rdx
	push	rsi
	push	rdx
	call	rsi
	pop		rdx
	pop		rsi
	add		rdx, 1
	jmp		_while

_end:
	ret	
