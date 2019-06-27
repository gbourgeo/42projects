	[BITS 32]

	section .text
	global	woody32_encrypt:function

woody32_encrypt:
        push    ebp
        push    edi
        push    esi
        push    ebx
        sub     esp, 20

        mov     eax, DWORD [esp + 44]
        and     eax, -8
        mov     DWORD [esp + 16], eax
        je      .end
        mov     eax, DWORD [esp + 40]
        mov     DWORD [esp + 8], 0
        mov     DWORD [esp + 12], eax
.loop:
        mov     edi, DWORD [esp + 12]
        xor     ebx, ebx
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
.algorithm:
        mov     eax, edx
        mov     ebp, DWORD [esp]
        sub     ebx, 1640531527
        sal     eax, 4
        add     ebp, eax
        mov     eax, edx
        shr     eax, 5
        add     eax, DWORD [esp + 4]
        xor     eax, ebp
        lea     ebp, [ebx + edx]
        xor     eax, ebp
        add     ecx, eax
        mov     eax, ecx
        sal     eax, 4
        lea     ebp, [eax + edi]
        mov     eax, ecx
        shr     eax, 5
        add     eax, esi
        xor     eax, ebp
        lea     ebp, [ebx + ecx]
        xor     eax, ebp
        add     edx, eax
        cmp     ebx, -957401312
        jne     .algorithm
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
        ja      .loop
.end:
        add     esp, 20
        pop     ebx
        pop     esi
        pop     edi
        pop     ebp
        ret
