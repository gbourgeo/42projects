	;; int isalnum(int c);

	segment .text
	global 	_ft_isalnum

_ft_isalnum:
	cmp rdi, "0"
	jl ret_false
	cmp rdi, "9"
	jle ret_true
	cmp rdi, "A"
	jl ret_false
	cmp rdi, "Z"
	jle ret_true
	cmp rdi, "a"
	jl ret_false
	cmp rdi, "z"
	jle ret_true

ret_false:
	mov rax, 0
	ret

ret_true:
	mov rax, 1
	ret
