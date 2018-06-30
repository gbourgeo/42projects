	[BITS 32]

	section .text
	global	woody32_encrypt:function

woody32_encrypt:
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
	xor ebx, ebx
	mov DWORD [esp+4], eax
	.L2:
	mov eax, edx
	sub ebx, 1640531527
	sal eax, 4
	lea ebp, [eax+edi]
	mov eax, edx
	shr eax, 5
	add eax, esi
	xor eax, ebp
	lea ebp, [ebx+edx]
	xor eax, ebp
	mov ebp, DWORD [esp]
	add ecx, eax
	mov eax, ecx
	sal eax, 4
	add ebp, eax
	mov eax, ecx
	shr eax, 5
	add eax, DWORD [esp+4]
	xor eax, ebp
	lea ebp, [ebx+ecx]
	xor eax, ebp
	add edx, eax
	cmp ebx, -957401312
	jne .L2
	mov eax, DWORD [esp+28]
	mov DWORD [eax], ecx
	mov DWORD [eax+4], edx
	add esp, 8
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
