	;; size_t strlen(const char *s);

	segment .text
	global 	_ft_strlen

_ft_strlen:
	mov 	rax, 0
	cmp 	rdi, byte 0
	je 		return_false
	sub		rcx, rcx			; mise a 0 du compteur
	sub		al, al				; mise a 0 du char de comparaison
	not		rcx					; inverse le binaire (surement protect overflow)
	cld							; auto increment le ptr rcx et rdi a chaque appel
	repne	scasb				; repeat while [rdi] != al
	not		rcx					; restaure le compteur
	dec		rcx					; retire 1
	mov		rax, rcx			; ret value
	ret

return_false:
	mov rax, -1
	ret
