	;; void bzero(void *s, size_t n);

	section .text
	global 	_ft_bzero
	
_ft_bzero:
	push rsi
	push rdi

while:
	cmp esi, 0
	jle end_while
	mov byte [rdi], 0
	add rdi, 1
	sub esi, 1
	jmp while

end_while:
	pop rdi
	pop rsi
	ret
