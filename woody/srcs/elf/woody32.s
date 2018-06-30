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
	lea 	esi, [rel banner]
	mov 	edx, [rel banner_size]
	mov 	eax, 1
	syscall

	jmp 	woody32_end

woody32_decrypt:
	push ebp
	push edi
	push esi
	push ebx
	sub esp, 8
	mov eax, DWORD [esp+32]
	mov esi, DWORD [esp+28]
	mov ebx, DWORD [eax+8]
	mov ecx, DWORD [esi]
	mov edx, DWORD [esi+4]
	mov edi, DWORD [eax]
	mov esi, DWORD [eax+4]
	mov eax, DWORD [eax+12]
	mov DWORD [esp], ebx
	mov ebx, -957401312
	mov DWORD [esp+4], eax
	.L7:
	mov eax, ecx
	mov ebp, DWORD [esp]
	sal eax, 4
	add ebp, eax
	mov eax, ecx
	shr eax, 5
	add eax, DWORD [esp+4]
	xor eax, ebp
	lea ebp, [ecx+ebx]
	xor eax, ebp
	sub edx, eax
	mov eax, edx
	sal eax, 4
	lea ebp, [eax+edi]
	mov eax, edx
	shr eax, 5
	add eax, esi
	xor eax, ebp
	lea ebp, [edx+ebx]
	xor eax, ebp
	sub ecx, eax
	add ebx, 1640531527
	jne .L7
	mov eax, DWORD [esp+28]
	mov DWORD [eax], ecx
	mov DWORD [eax+4], edx
	add esp, 8
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret

woody32_end:
	
	mov 	esi, DWORD [rel text_size]
	lea 	edx, [rel woody32_keys]
	lea 	edi, [rel woody32_func]
	add 	edi, [rel text_vaddr]
	call 	woody32_decrypt

	lea 	ebx, [rel woody32_func]
	add 	ebx, [rel text_vaddr]
	mov 	[rel text_vaddr], ebx
	lea 	eax, [rel woody32_func]
	add 	eax, [rel jump_vaddr]
	mov 	[rel jump_vaddr], eax
	
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
