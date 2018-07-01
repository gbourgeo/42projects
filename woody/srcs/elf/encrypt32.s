	[BITS 32]

	section .text
	global	woody32_encrypt:function

woody32_encrypt:
	push ebp
	push edi
	push esi
	push ebx
	sub esp, 24

	mov eax, DWORD [esp+48]
	and eax, -8
	mov DWORD [esp+20], eax
	je .L1
	mov eax, DWORD [esp+44]
	mov DWORD [esp+12], eax
	mov DWORD [esp+8], 0
.L4:
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
	mov ebx, 0
.L3:
	sub ebx, 1640531527
	mov eax, edx
	sal eax, 4
	mov ebp, DWORD [esp]
	add ebp, eax
	mov eax, edx
	shr eax, 5
	add eax, DWORD [esp+4]
	xor eax, ebp
	lea ebp, [ebx+edx]
	xor eax, ebp
	add ecx, eax
	mov eax, ecx
	sal eax, 4
	lea ebp, [eax+edi]
	mov eax, ecx
	shr eax, 5
	add eax, esi
	xor eax, ebp
	lea ebp, [ebx+ecx]
	xor eax, ebp
	add edx, eax
	cmp ebx, -957401312
	jne .L3
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
	ja .L4
.L1:
	add esp, 24
	pop ebx
	pop esi
	pop edi
	pop ebp
	ret
