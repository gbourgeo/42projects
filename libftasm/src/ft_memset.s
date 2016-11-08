	;; void *memset(void *s, int c, size_t n);

	segment .text
	global 	_ft_memset

_ft_memset:
	mov 	r10, rdi
	cmp 	rdi, byte 0
	je 		return
	cld
	mov		al, sil
	mov		rcx, rdx
	rep		stosb

return:
	mov 	rax, r10
	ret
