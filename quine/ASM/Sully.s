	global _main
	extern _dprintf
	extern _open
	extern _close
	extern _stat
	extern _system

	section .rodata
	integer dd 5
	sully db "Sully_", 0
	sully_len equ $-sully
	string db "	global _main%1$c	extern _dprintf%1$c	extern _open%1$c	extern _close%1$c	extern _stat%1$c	extern _system%1$c%1$c	section .rodata%1$c	integer dd %d%1$c	sully db %3$cSully_%3$c, 0%1$c	sully_len equ $-sully%1$c	string db %3$c%s%3$c, 0%1$c	compil_1 db %3$c~/Downloads/nasm-2.11.02/nasm -f macho64 %3$c, 0%1$c	compil_1len equ $-compil_1%1$c	compil_2 db %3$cgcc -Wall -Werror -Wextra -o %3$c, 0%1$c	compil_2len equ $-compil_2%1$c%1$c	section .text%1$c_main:%1$c	push rbp%1$c	mov rbp, rsp%1$c	sub rsp, 128%1$c	cmp DWORD [rel integer], 0%1$c	jle end%1$c	lea rdi, [rsp]%1$c	lea rsi, [rel compil_1]%1$c	mov edx, compil_1len%1$c	call strncpy%1$c	mov DWORD [rsp + 124], compil_1len - 1%1$c	lea rdi, [rsp + compil_1len - 1] ; 'nasm -f elf64 '%1$c	lea rsi, [rel sully]%1$c	mov edx, sully_len%1$c	call strncpy%1$c	add DWORD [rsp + 124], sully_len - 1%1$c	lea rdi, [rsp + compil_1len + sully_len - 2] ; 'nasm -f elf64 Sully_'%1$c	mov esi, DWORD [rel integer]%1$c	add esi, -1%1$c	call my_itoa%1$c	add DWORD [rsp + 124], eax%1$c	mov eax, DWORD [rsp + 124]%1$c	mov BYTE [rsp + rax], '.'%1$c	mov BYTE [rsp + rax + 1], 's'%1$c	mov BYTE [rsp + rax + 2], ' '%1$c	mov BYTE [rsp + rax + 3], '&'%1$c	mov BYTE [rsp + rax + 4], '&'%1$c	mov BYTE [rsp + rax + 5], ' '%1$c	add DWORD [rsp + 124], 5%1$c	lea rdi, [rsp + rax + 6] ; 'nasm -f elf64 Sully_W.s && '%1$c	lea rsi, [rel compil_2]%1$c	mov edx, compil_2len%1$c	call strncpy%1$c	add DWORD [rsp + 124], compil_2len%1$c	mov eax, DWORD [rsp + 124]%1$c	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o '%1$c	lea rsi, [rel sully]%1$c	mov edx, sully_len%1$c	call strncpy%1$c	add DWORD [rsp + 124], sully_len - 1%1$c	mov eax, DWORD [rsp + 124]%1$c	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_'%1$c	mov esi, DWORD [rel integer]%1$c	add esi, -1%1$c	call my_itoa%1$c	add DWORD [rsp + 124], eax%1$c	mov eax, DWORD [rsp + 124]%1$c	mov BYTE [rsp + rax], ' '%1$c	lea rdi, [rsp + rax + 1] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W '%1$c	lea rsi, [rel sully]%1$c	mov edx, sully_len%1$c	call strncpy%1$c	add DWORD [rsp + 124], sully_len%1$c	mov eax, DWORD [rsp + 124]%1$c	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_'%1$c	mov esi, DWORD [rel integer]%1$c	add esi, -1%1$c	call my_itoa%1$c	add DWORD [rsp + 124], eax%1$c	mov eax, DWORD [rsp + 124]%1$c	mov BYTE [rsp + rax], '.'%1$c	mov BYTE [rsp + rax + 1], 's'%1$c	mov BYTE [rsp + rax + 2], 0%1$c	add DWORD [rsp + 124], 2%1$c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.s'%1$c	lea rdi, [rsp + rax - sully_len] ;Sully_W.s%1$c	call create_file%1$c	cmp eax, 0%1$c	jne end%1$c	mov eax, DWORD [rsp + 124]%1$c	mov BYTE [rsp + rax - 1], 'o'%1$c	mov BYTE [rsp + rax], ' '%1$c	mov BYTE [rsp + rax + 1], '&'%1$c	mov BYTE [rsp + rax + 2], '&'%1$c	mov BYTE [rsp + rax + 3], ' '%1$c	mov BYTE [rsp + rax + 4], '.'%1$c	mov BYTE [rsp + rax + 5], '/'%1$c	add DWORD [rsp + 124], 5%1$c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./'%1$c	lea rdi, [rsp + rax + 6]%1$c	lea rsi, [rel sully]%1$c	mov edx, sully_len%1$c	call strncpy%1$c	add DWORD [rsp + 124], sully_len%1$c	mov eax, DWORD [rsp + 124]%1$c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_'%1$c	lea rdi, [rsp + rax]%1$c	mov esi, DWORD [rel integer]%1$c	add esi, -1%1$c	call my_itoa%1$c	add DWORD [rsp + 124], eax%1$c	mov eax, DWORD [rsp + 124]%1$c	mov BYTE [rsp + rax], 0%1$c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_W'%1$c	lea rdi, [rsp]%1$c	call _system%1$cend:%1$c	add rsp, 128%1$c	xor rax, rax%1$c	leave%1$c	ret%1$cstrncpy:%1$c	push rdi%1$c	mov rdi, rsi%1$c	mov rcx, rdx%1$c	xor al, al%1$c	cld%1$c	repne scasb%1$c	mov rcx, rdi%1$c	pop rdi%1$c	sub rcx, rsi%1$c	push rdi%1$c	cld%1$c	rep movsb%1$c	mov BYTE [rdi], 0%1$c	pop rdi%1$c	mov rax, rdi%1$c	ret%1$c	;; int my_itoa(char *buff, int i)%1$cmy_itoa:%1$c	push rbp%1$c	mov rbp, rsp%1$c	sub rsp, 12%1$c%1$c	mov rsp, rdi%1$c	mov eax, esi%1$c	mov DWORD [rsp + 8], eax	;i%1$c	mov ecx, 1					;len%1$c%1$c	xor edx, edx%1$c	mov ebx, 10%1$c	jmp my_itoa_nblen_loop%1$cmy_itoa_nblen:%1$c	inc ecx%1$cmy_itoa_nblen_loop:%1$c	cmp eax, 10%1$c	div ebx%1$c	jge my_itoa_nblen%1$c%1$c	mov eax, DWORD [rsp + 8]%1$c	mov DWORD [rsp + 8], ecx%1$c	mov ebx, 10%1$cmy_itoa_write:%1$c	cmp ecx, 0%1$c	jle my_itoa_end%1$c	dec ecx%1$c	xor dx, dx%1$c	div ebx%1$c	add dx, 48%1$c	mov BYTE [rsp + rcx], dl%1$cmy_itoa_end:%1$c	mov eax, DWORD [rsp + 8]%1$c	add rsp, 12%1$c	leave%1$c	ret%1$c	;; int create_file(char *file, int nb)%1$ccreate_file:%1$c	push rbp%1$c	mov rbp, rsp%1$c	sub rsp, 16%1$c%1$c	mov rsi, 2561%1$c	mov rdx, 420%1$c	call _open%1$c	cmp eax, 0%1$c	jl create_file_end%1$c	mov DWORD [rsp], eax%1$c	mov edi, eax%1$c	lea rsi, [rel string]%1$c	mov edx, 10%1$c	mov rcx, [rel integer]%1$c	add rcx, -1%1$c	mov r8, 34%1$c	lea r9, [rel string]%1$c	call _dprintf%1$c	mov edi, DWORD [rsp]%1$c	call _close%1$c	xor eax, eax%1$ccreate_file_end:%1$c	add rsp, 16%1$c	leave%1$c	ret%1$c", 0
	compil_1 db "~/Downloads/nasm-2.11.02/nasm -f macho64 ", 0
	compil_1len equ $-compil_1
	compil_2 db "gcc -Wall -Werror -Wextra -o ", 0
	compil_2len equ $-compil_2

	section .text
_main:
	push rbp
	mov rbp, rsp
	sub rsp, 128
	cmp DWORD [rel integer], 0
	jle end
	lea rdi, [rsp]
	lea rsi, [rel compil_1]
	mov edx, compil_1len
	call strncpy
	mov DWORD [rsp + 124], compil_1len - 1
	lea rdi, [rsp + compil_1len - 1] ; 'nasm -f elf64 '
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy
	add DWORD [rsp + 124], sully_len - 1
	lea rdi, [rsp + compil_1len + sully_len - 2] ; 'nasm -f elf64 Sully_'
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add DWORD [rsp + 124], eax
	mov eax, DWORD [rsp + 124]
	mov BYTE [rsp + rax], '.'
	mov BYTE [rsp + rax + 1], 's'
	mov BYTE [rsp + rax + 2], ' '
	mov BYTE [rsp + rax + 3], '&'
	mov BYTE [rsp + rax + 4], '&'
	mov BYTE [rsp + rax + 5], ' '
	add DWORD [rsp + 124], 5
	lea rdi, [rsp + rax + 6] ; 'nasm -f elf64 Sully_W.s && '
	lea rsi, [rel compil_2]
	mov edx, compil_2len
	call strncpy
	add DWORD [rsp + 124], compil_2len
	mov eax, DWORD [rsp + 124]
	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o '
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy
	add DWORD [rsp + 124], sully_len - 1
	mov eax, DWORD [rsp + 124]
	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_'
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add DWORD [rsp + 124], eax
	mov eax, DWORD [rsp + 124]
	mov BYTE [rsp + rax], ' '
	lea rdi, [rsp + rax + 1] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W '
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy
	add DWORD [rsp + 124], sully_len
	mov eax, DWORD [rsp + 124]
	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_'
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add DWORD [rsp + 124], eax
	mov eax, DWORD [rsp + 124]
	mov BYTE [rsp + rax], '.'
	mov BYTE [rsp + rax + 1], 's'
	mov BYTE [rsp + rax + 2], 0
	add DWORD [rsp + 124], 2
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.s'
	lea rdi, [rsp + rax - sully_len] ;Sully_W.s
	call create_file
	cmp eax, 0
	jne end
	mov eax, DWORD [rsp + 124]
	mov BYTE [rsp + rax - 1], 'o'
	mov BYTE [rsp + rax], ' '
	mov BYTE [rsp + rax + 1], '&'
	mov BYTE [rsp + rax + 2], '&'
	mov BYTE [rsp + rax + 3], ' '
	mov BYTE [rsp + rax + 4], '.'
	mov BYTE [rsp + rax + 5], '/'
	add DWORD [rsp + 124], 5
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./'
	lea rdi, [rsp + rax + 6]
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy
	add DWORD [rsp + 124], sully_len
	mov eax, DWORD [rsp + 124]
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_'
	lea rdi, [rsp + rax]
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add DWORD [rsp + 124], eax
	mov eax, DWORD [rsp + 124]
	mov BYTE [rsp + rax], 0
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_W'
	lea rdi, [rsp]
	call _system
end:
	add rsp, 128
	xor rax, rax
	leave
	ret
strncpy:
	push rdi
	mov rdi, rsi
	mov rcx, rdx
	xor al, al
	cld
	repne scasb
	mov rcx, rdi
	pop rdi
	sub rcx, rsi
	push rdi
	cld
	rep movsb
	mov BYTE [rdi], 0
	pop rdi
	mov rax, rdi
	ret
	;; int my_itoa(char *buff, int i)
my_itoa:
	push rbp
	mov rbp, rsp
	sub rsp, 12

	mov rsp, rdi
	mov eax, esi
	mov DWORD [rsp + 8], eax	;i
	mov ecx, 1					;len

	xor edx, edx
	mov ebx, 10
	jmp my_itoa_nblen_loop
my_itoa_nblen:
	inc ecx
my_itoa_nblen_loop:
	cmp eax, 10
	div ebx
	jge my_itoa_nblen

	mov eax, DWORD [rsp + 8]
	mov DWORD [rsp + 8], ecx
	mov ebx, 10
my_itoa_write:
	cmp ecx, 0
	jle my_itoa_end
	dec ecx
	xor dx, dx
	div ebx
	add dx, 48
	mov BYTE [rsp + rcx], dl
my_itoa_end:
	mov eax, DWORD [rsp + 8]
	add rsp, 12
	leave
	ret
	;; int create_file(char *file, int nb)
create_file:
	push rbp
	mov rbp, rsp
	sub rsp, 16

	mov rsi, 2561
	mov rdx, 420
	call _open
	cmp eax, 0
	jl create_file_end
	mov DWORD [rsp], eax
	mov edi, eax
	lea rsi, [rel string]
	mov edx, 10
	mov rcx, [rel integer]
	add rcx, -1
	mov r8, 34
	lea r9, [rel string]
	call _dprintf
	mov edi, DWORD [rsp]
	call _close
	xor eax, eax
create_file_end:
	add rsp, 16
	leave
	ret
