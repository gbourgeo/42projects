[bits 32]
	global woody32_func:function
	global woody32_decrypt:function
	global woody32_size:data
	global woody32_keys:data

	segment .text
	woody32_size dd woody32_data - woody32_func

woody32_func:					; ELF 32 bits version
	push 	edi
	push 	esi
	push 	edx
	push 	eax
	push 	ebx

;	push	DWORD [banner32_size]
;	nop
;	jmp		banner32			;good addr
;	mov		eax, woody32_data
;	push	banner32			;wrong addr
;	mov		eax, banner32		;wrong addr
;	mov		eax, [banner32]		;wrong addr
;	mov		eax, [abs banner32]		;wrong addr
;	mov		eax, [fs:banner32]		;wrong addr
;	mov		eax, [ds:banner32]		;wrong addr
;	mov		eax, [rel banner32]		;wrong addr
;	mov		eax, dword [banner32]		;wrong addr
;	mov		eax, dword [abs banner32]		;wrong addr
;	mov		eax, dword [fs:banner32]		;wrong addr
;	mov		eax, dword [ds:banner32]		;wrong addr
;	mov		eax, dword [rel banner32]		;wrong addr
;	nop

	mov 	edi, 1
	push	DWORD banner32
	push	DWORD [banner32_size]
	pop		edx
	pop		esi
;	lea		esi, DWORD [banner32]
;	mov 	edx, DWORD [banner32_size]
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
	mov 	esi, DWORD [text_size]
	lea 	edx, [woody32_keys]
	lea 	edi, [woody32_func]
	add 	edi, [text_vaddr]
	call 	woody32_decrypt

	lea 	ebx, [woody32_func]
	add 	ebx, [text_vaddr]
	mov 	[text_vaddr], ebx
	lea 	eax, [woody32_func]
	add 	eax, [jump_vaddr]
	mov 	[jump_vaddr], eax

	pop 	ebx
	pop 	eax
	pop 	edx
	pop 	esi
	pop 	edi
	push	DWORD [jump_vaddr]
	ret

woody32_data:
	woody32_keys dd 0x0, 0x0, 0x0, 0x0
	text_vaddr dw 0x0
	text_size dw 0x0
	jump_vaddr dw 0x0
	banner32_size dw 0x0
	banner32 db ""
