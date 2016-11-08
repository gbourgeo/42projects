	;; int tolower(int c);

	segment .text
	global 	_ft_tolower

_ft_tolower:
	cmp 	rdi, "A"
	jl 		do_end
	cmp 	rdi, "Z"
	jg 		do_end
	add 	rdi, 32

do_end:
	mov 	rax, rdi
	ret
