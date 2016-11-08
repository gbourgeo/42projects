	;; int isdigit(int c);

	segment .text
	global 	_ft_isdigit

_ft_isdigit:
	cmp 	rdi, "0"
	jl 		ret_false
	cmp 	rdi, "9"
	jle 	ret_true

ret_false:
	mov 	rax, 0
	ret

ret_true:
	mov 	rax, 1
	ret
