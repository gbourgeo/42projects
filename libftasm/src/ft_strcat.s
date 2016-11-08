	;; char *strcat(char *dest, const char *src);

	section .text
	global 	_ft_strcat

_ft_strcat:
	push 	rbx
	mov 	rbx, rsi
	mov 	rax, rdi
	mov 	rcx, 0

while:
	cmp 	byte [rdi], 0
	je 		do_len
	inc		rdi
	jmp 	while

do_len:
	cmp 	byte [rbx], 0
	je 		do_copy
	inc 	rcx
	inc 	rbx
	jmp 	do_len

do_copy:
	inc 	rcx
	rep 	movsb
	pop 	rbx
	ret
