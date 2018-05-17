	[BITS 32]

	global woody32_func:function
	global woody32_decrypt:function
	global woody32_size:data
	global woody32_args:data
	global woody32_keys:data

	section .text
	woody32_size dd end - woody32_func
	woody32_args dd end - args
	
woody32_func:					; ELF version
	push ebp
	mov	ebp, esp
	push edi
	push esi
	push edx
	push eax
	push ebx
	
	mov edi, 1
	mov esi, banner
	mov edx, [banner_size]
	syscall

	jmp woody32_end

woody32_decrypt:
	ret
woody32_end:
	call woody32_decrypt

	pop ebx
	pop eax
	pop edx
	pop esi
	pop edi
	mov esp, ebp
	pop ebp
	;push text_vaddr
	ret

args:
	woody32_keys dd 0x0, 0x0, 0x0, 0x0
	text_vaddr dd 0x0
	text_size dd 0x0
	banner_size dd 0xe
	banner db "....WOODY....", 10
end:
