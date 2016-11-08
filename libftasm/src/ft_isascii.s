	;; int isascii(int c);

	segment .text
	global 	_ft_isascii

_ft_isascii:
	cmp 	rdi, 0
	jl 		ret_false
	cmp 	rdi, 127
	jg 		ret_false
	mov 	rax, 1
	ret

ret_false:
	mov 	rax, 0
	ret
