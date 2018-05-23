	[BITS 64]

	%define SYS_OPEN 2
	%define SYS_EXIT 60
	%define SYS_GETDENTS64 78
	global famine64_func:function
	global famine64_size:data

	section .text
	famine64_size dd famine64_end - famine64_func

famine64_func:
	push rdi
	push rsi
	push rdx
	push rax
	push rbx

	;; sys_open("/tmp/test?/, 0, 0)
	mov rax, SYS_OPEN
	mov rdi, dir_one
	xor rsi, rsi
	xor rdx, rdx
	syscall

	cmp rax, 0
	jbe famine64_error

	;; sys_getdents64(fd, esp, 0x3210)
	mov rdi, rax
	xor rdx, rdx
	xor rax, rax
	mov rdx, 0x3210
	sub rsp, rdx
	mov rsi, rsp
	mov rax, SYS_GETDENTS64
	syscall
	mov r10, rax

	xchg rax, rdx
	xor rcx, rcx
	mov r8, rsp
print_files:
	;;	char *get_file(void *start_of_struct_dirent)
	mov rdi, r8
	call get_file

	mov rsi, rax
	mov rdi, rax
	call strlen
	mov rdx, rax
	;;  write(1, rsp, rdx)
	mov rax, 1
	mov rdi, 1
	syscall

	mov r9, r8
	add r9, 16
	mov r8, rsp
	add r8, r9
	cmp r9, BYTE 0
	jl print_files
	jmp next

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
	
get_file:
	mov rax, rdi
	add rax, 18
	ret
next:	
	mov rax, 1
	mov rdi, 1
	mov rsi, OK
	mov rdx, 3
	syscall

	mov rax, 60
	syscall
	
	pop rbx
	pop rax
	pop rdx
	pop rsi
	pop rdi

	push QWORD [rel jump_vaddr]
	ret

famine64_error:
	mov rax, 1
	mov rdi, 1
	mov rsi, ERR
	mov rdx, 6
	syscall
	mov rax, SYS_EXIT
	syscall
	
famine64_data:
	OK db "OK", 10
	ERR db "ERROR", 10
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx"
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	jump_vaddr dq 0x0

famine64_end:
