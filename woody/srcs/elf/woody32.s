	[BITS 32]

	global woody32_func:function
	global woody32_decrypt:function
	global woody32_size:data
	global woody32_keys:data

	segment .text
	woody32_size dd end - woody32_func

woody32_func:					; ELF 32 bits version
	push 	edi
	push 	esi
	push 	edx
	push 	eax
	push 	ebx

	mov 	edi, 1
	;lea 	esi, [rel banner]
	;mov 	edx, [rel banner_size]
	mov 	eax, 1
	syscall

	jmp 	woody32_end
woody32_decrypt:
	push ebp
	push edi
	push esi
	push ebx
	sub esp, 24

	mov eax, DWORD [esp+48]
	and eax, -8
	mov DWORD [esp+20], eax
	je .L8
	mov eax, DWORD [esp+44]
	mov DWORD [esp+12], eax
	mov DWORD [esp+8], 0
.L11:
	mov esi, DWORD [esp+12]
	mov DWORD [esp+16], esi
	movzx ecx, BYTE [esi]
	sal ecx, 24
	movzx eax, BYTE [esi+1]
	sal eax, 16
	or ecx, eax
	movzx eax, BYTE [esi+3]
	or ecx, eax
	movzx eax, BYTE [esi+2]
	sal eax, 8
	or ecx, eax
	movzx edx, BYTE [esi+4]
	mov eax, edx
	sal eax, 24
	movzx edx, BYTE [esi+5]
	sal edx, 16
	or edx, eax
	movzx eax, BYTE [esi+7]
	or edx, eax
	movzx eax, BYTE [esi+6]
	sal eax, 8
	or edx, eax
	mov eax, DWORD [esp+52]
	mov eax, DWORD [eax]
	mov DWORD [esp], eax
	mov eax, DWORD [esp+52]
	mov eax, DWORD [eax+4]
	mov DWORD [esp+4], eax
	mov eax, DWORD [esp+52]
	mov edi, DWORD [eax+8]
	mov esi, DWORD [eax+12]
	mov ebx, -957401312
.L10:
	mov eax, ecx
	sal eax, 4
	lea ebp, [eax+edi]
	mov eax, ecx
	shr eax, 5
	add eax, esi
	xor eax, ebp
	lea ebp, [ecx+ebx]
	xor eax, ebp
	sub edx, eax
	mov eax, edx
	sal eax, 4
	mov ebp, DWORD [esp]
	add ebp, eax
	mov eax, edx
	shr eax, 5
	add eax, DWORD [esp+4]
	xor eax, ebp
	lea ebp, [edx+ebx]
	xor eax, ebp
	sub ecx, eax
	add ebx, 1640531527
	jne .L10
	mov eax, ecx
	shr eax, 24
	mov edi, DWORD [esp+16]
	mov BYTE [edi], al
	mov eax, ecx
	shr eax, 16
	mov BYTE [edi+1], al
	mov BYTE [edi+2], ch
	mov BYTE [edi+3], cl
	mov eax, edx
	shr eax, 24
	mov BYTE [edi+4], al
	mov eax, edx
	shr eax, 16
	mov BYTE [edi+5], al
	mov BYTE [edi+6], dh
	mov BYTE [edi+7], dl
	add DWORD [esp+8], 8
	mov eax, DWORD [esp+8]
	add DWORD [esp+12], 8
	cmp DWORD [esp+20], eax
	ja .L11
.L8:
	add esp, 24
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret

woody32_end:	
	;mov 	esi, DWORD [rel text_size]
	;lea 	edx, [rel woody32_keys]
	;lea 	edi, [rel woody32_func]
	;add 	edi, [rel text_vaddr]
	call 	woody32_decrypt

	;lea 	ebx, [rel woody32_func]
	;add 	ebx, [rel text_vaddr]
	;mov 	[rel text_vaddr], ebx
	;lea 	eax, [rel woody32_func]
	;add 	eax, [rel jump_vaddr]
	;mov 	[rel jump_vaddr], eax

	pop 	ebx
	pop 	eax
	pop 	edx
	pop 	esi
	pop 	edi
	push	DWORD [rel jump_vaddr]
	ret
end:
	woody32_keys dd 0x0, 0x0, 0x0, 0x0
	text_vaddr dw 0x0
	text_size dw 0x0
	jump_vaddr dw 0x0
	banner_size dw 0x0
	banner db ""
