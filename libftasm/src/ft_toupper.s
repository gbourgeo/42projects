	;; int toupper(int c);

	segment .text
	global 	_ft_toupper

_ft_toupper:
	mov 	rax, rdi
	cmp 	rax, "a"
	jl 		do_end
	cmp 	rax, "z"
	jg 		do_end
	sub 	rax, 32

do_end:
	ret
