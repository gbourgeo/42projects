	[BITS 32]

	section .text
	global	woody32_encrypt:function

woody32_encrypt:
        push    ebp
        push    edi
        push    esi
        push    ebx
        sub     esp, 20
        mov     eax, DWORD [esp+40]
        mov     DWORD [esp+8], 0
        mov     DWORD [esp+12], eax
        mov     eax, DWORD [esp+44]
        and     eax, -8
        mov     DWORD [esp+16], eax
        je      .end
.loop:
        mov     edi, DWORD [esp+12]
        xor     esi, esi
        movzx   ebx, BYTE [edi]
        movzx   eax, BYTE [edi+1]
        movzx   ecx, BYTE [edi+4]
        sal     eax, 16
        sal     ebx, 24
        or      ebx, eax
        movzx   eax, BYTE [edi+3]
        sal     ecx, 24
        or      ebx, eax
        movzx   eax, BYTE [edi+2]
        sal     eax, 8
        or      ebx, eax
        movzx   eax, BYTE [edi+5]
        sal     eax, 16
        or      ecx, eax
        movzx   eax, BYTE [edi+7]
        or      ecx, eax
        movzx   eax, BYTE [edi+6]
        sal     eax, 8
        or      ecx, eax
        mov     eax, DWORD [esp+48]
        mov     eax, DWORD [eax]
        mov     DWORD [esp], eax
        mov     eax, DWORD [esp+48]
        mov     eax, DWORD [eax+4]
        mov     DWORD [esp+4], eax
        mov     eax, DWORD [esp+48]
        mov     ebp, DWORD [eax+8]
        mov     edi, DWORD [eax+12]
.encryption:
        mov     edx, DWORD [esp]
        mov     eax, ecx
        sub     esi, 1640531527
        sal     eax, 4
        add     edx, eax
        mov     eax, ecx
        shr     eax, 5
        add     eax, DWORD [esp+4]
        xor     eax, edx
        lea     edx, [esi+ecx]
        xor     eax, edx
        add     ebx, eax
        mov     eax, ebx
        sal     eax, 4
        lea     edx, [eax+ebp]
        mov     eax, ebx
        shr     eax, 5
        add     eax, edi
        xor     eax, edx
        lea     edx, [esi+ebx]
        xor     eax, edx
        add     ecx, eax
        cmp     esi, -957401312
        jne     .encryption
        mov     edi, DWORD [esp+12]
        mov     eax, ebx
        add     DWORD [esp+8], 8
        shr     eax, 24
        mov     BYTE [edi], al
        mov     eax, ebx
        add     edi, 8
        shr     eax, 16
        mov     BYTE [edi-5], bl
        mov     BYTE [edi-7], al
        mov     eax, ebx
        mov     BYTE [edi-1], cl
        shr     eax, 8
        mov     BYTE [edi-6], al
        mov     eax, ecx
        shr     eax, 24
        mov     BYTE [edi-4], al
        mov     eax, ecx
        shr     eax, 16
        mov     BYTE [edi-3], al
        mov     eax, ecx
        shr     eax, 8
        mov     BYTE [edi-2], al
        mov     eax, DWORD [esp+8]
        cmp     DWORD [esp+16], eax
        mov     DWORD [esp+12], edi
        ja      .loop
.end:
        add     esp, 20
        pop     ebx
        pop     esi
        pop     edi
        pop     ebp
        ret