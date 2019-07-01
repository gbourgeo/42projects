	[BITS 32]

	global woody32_func:function
	global woody32_size:data
	global woody32_keys:data

	segment .text
	woody32_size dd woody32_data - woody32_func

woody32_func:						; ELF 32 bits version
	push	edi
	push	eax
	push	ebx
	push	ecx
	push	edx

	mov		ecx, DWORD [esp + 16]
	add		ecx, banner32 - woody32_func + 0x8
	mov		edx, DWORD [ecx - 4]	; Load banner32_size
	mov		ebx, 1					; Write on STDOUT (1)
	mov		eax, 4					; Syscall write (4)
	int		0x80
	jmp		.end

.decrypt:
	push    ebp
	push    edi
	push    esi
	push    ebx
	sub     esp, 20

	mov     eax, DWORD [esp + 44]
	and     eax, -8
	mov     DWORD [esp + 16], eax
	je      .decrypt_end
	mov     eax, DWORD [esp + 40]
	mov     DWORD [esp + 8], 0
	mov     DWORD [esp + 12], eax
.decrypt_loop:
	mov     edi, DWORD [esp + 12]
	mov     ebx, -957401312
	movzx   ecx, BYTE [edi]
	movzx   eax, BYTE [edi + 1]
	movzx   edx, BYTE [edi + 4]
	sal     eax, 16
	sal     ecx, 24
	or      ecx, eax
	movzx   eax, BYTE [edi + 3]
	sal     edx, 24
	or      ecx, eax
	movzx   eax, BYTE [edi + 2]
	sal     eax, 8
	or      ecx, eax
	movzx   eax, BYTE [edi + 5]
	sal     eax, 16
	or      edx, eax
	movzx   eax, BYTE [edi + 7]
	or      edx, eax
	movzx   eax, BYTE [edi + 6]
	sal     eax, 8
	or      edx, eax
	mov     eax, DWORD [esp + 48]
	mov     eax, DWORD [eax]
	mov     DWORD [esp], eax
	mov     eax, DWORD [esp + 48]
	mov     eax, DWORD [eax + 4]
	mov     DWORD [esp + 4], eax
	mov     eax, DWORD [esp + 48]
	mov     edi, DWORD [eax + 8]
	mov     esi, DWORD [eax + 12]
.decrypt_algorythm:
	mov     eax, ecx
	sal     eax, 4
	lea     ebp, [eax + edi]
	mov     eax, ecx
	shr     eax, 5
	add     eax, esi
	xor     eax, ebp
	lea     ebp, [ecx + ebx]
	xor     eax, ebp
	mov     ebp, DWORD [esp]
	sub     edx, eax
	mov     eax, edx
	sal     eax, 4
	add     ebp, eax
	mov     eax, edx
	shr     eax, 5
	add     eax, DWORD [esp + 4]
	xor     eax, ebp
	lea     ebp, [edx + ebx]
	xor     eax, ebp
	sub     ecx, eax
	add     ebx, 1640531527
	jne     .decrypt_algorythm
	mov     esi, DWORD [esp + 12]
	mov     eax, ecx
	add     DWORD [esp + 8], 8
	shr     eax, 24
	mov     BYTE [esi], al
	mov     eax, ecx
	shr     eax, 16
	mov     BYTE [esi + 2], ch
	mov     BYTE [esi + 1], al
	mov     eax, edx
	shr     eax, 24
	mov     BYTE [esi + 3], cl
	mov     BYTE [esi + 4], al
	mov     eax, edx
	shr     eax, 16
	mov     BYTE [esi + 6], dh
	mov     BYTE [esi + 5], al
	mov     eax, esi
	add     eax, 8
	mov     BYTE [esi + 7], dl
	mov     esi, DWORD [esp + 8]
	mov     DWORD [esp + 12], eax
	cmp     DWORD [esp + 16], esi
	ja      .decrypt_loop
.decrypt_end:
	add     esp, 20
	pop     ebx
	pop     esi
	pop     edi
	pop     ebp
	ret

.end:	; ECX contains the [banner32] address
	sub		ecx, 32					; Go to [woody32_keys] address
	push	ecx
	add		ecx, 20					; Go to [text_size] address
	push	DWORD [ecx]
	sub		ecx, 4					; Go to [text_vaddr] address
	mov		ebx, DWORD [esp + 24]	; Get [woody32_func] address
	add		ebx, [ecx]				; Get [.text] address
	push	ebx
	call	.decrypt
	pop		ebx						; Get [.text] address
	pop		ecx						; Get [text_vaddr] address
	pop		ecx						; Get [woody32_keys] address

	mov		ebx, DWORD [esp + 16]	; Get [woody32_func] address
	add		ecx, 24					; Go to [jump_vaddr] address
	add		ebx, [ecx]				; Get old entry point
	mov		edi, ebx

	pop		edx
	pop		ecx
	pop		ebx
	pop		eax
	mov		DWORD [esp], edi
	ret

woody32_data:
	woody32_keys dd 0x0, 0x0, 0x0, 0x0
	text_vaddr dw 0x0
	text_size dw 0x0
	jump_vaddr dw 0x0
	banner32_size dw 0x0
	banner32 db ""
