	global _main
	extern _dprintf
	extern _open
	extern _close
	extern _stat
	extern _system
	extern _remove
	extern _malloc
	extern _free
	extern _strcpy
	extern _strcat
	extern _strlen

	section .rodata
	string db "	global _main%1$c	extern _dprintf%1$c	extern _open%1$c	extern _close%1$c	extern _stat%1$c	extern _system%1$c	extern _remove%1$c	extern _malloc%1$c	extern _free%1$c	extern _strcpy%1$c	extern _strcat%1$c	extern _strlen%1$c%1$c	section .rodata%1$c	string db %2$c%3s%2$c, 0%1$c	sully db %2$c%4$s%2$c, 0%1$c	sully_len equ $-sully%1$c	compil_1 db %2$c%5$s%2$c, 0%1$c	compil_1len equ $-compil_1%1$c	compil_2 db %2$c%6$s%2$c, 0%1$c	compil_2len equ $-compil_2%1$c	extension db %2$c.s%2$c, 0%1$c	object db %2$c.o%2$c, 0%1$c	space db %2$c %2$c, 0%1$c	and_exec db %2$c && ./%2$c, 0%1$c	integer dd %7$d%1$c%1$c	section .text%1$c_main:%1$c	push rbp%1$c	mov rbp, rsp%1$c	sub rsp, 32%1$c%1$c	mov eax, DWORD [rel integer]%1$c	mov DWORD [rsp + 16], eax%1$c	mov eax, 1%1$c	jmp my_prog%1$cmy_loop_err:%1$c	cmp QWORD [rsp + 24], 0%1$c	je my_prog_err%1$c	mov rdi, QWORD [rsp + 24]%1$c	call _free%1$c	jmp my_prog_err%1$cmy_prog:%1$c	cmp DWORD [rsp + 16], 0%1$c	jl end%1$c	lea rdi, [rsp]%1$c	mov esi, DWORD [rsp + 16]%1$c	call my_itoa%1$c	add eax, sully_len - 1%1$c	mov ebx, 4%1$c	imul ebx%1$c	mov DWORD [rsp + 20], eax%1$c	add DWORD [rsp + 20], compil_1len%1$c	add DWORD [rsp + 20], compil_2len%1$c	add DWORD [rsp + 20], 7%1$c	mov edi, DWORD [rsp + 20]%1$c	call _malloc%1$c	mov QWORD [rsp + 24], rax%1$c	cmp QWORD [rsp + 24], 0%1$c	je end%1$c	mov rdi, QWORD [rsp + 24]%1$c	lea rsi, [rel sully]%1$c	lea rdx, [rsp]%1$c	lea rcx, [rel compil_1]%1$c	lea r8, [rel compil_2]%1$c	mov r9d, DWORD [rsp + 16]%1$c	mov r10d, 0%1$c	call my_exec%1$c	cmp eax, 0%1$c	jne my_prog_err%1$c	cmp DWORD [rsp + 16], 0%1$c	jle my_prog_end%1$c	lea rdi, [rsp]%1$c	mov esi, DWORD [rsp + 16]%1$c	dec esi%1$c	call my_itoa%1$c	mov rdi, QWORD [rsp + 24]%1$c	lea rsi, [rel sully]%1$c	lea rdx, [rsp]%1$c	lea rcx, [rel compil_1]%1$c	lea r8, [rel compil_2]%1$c	mov r9d, DWORD [rsp + 16]%1$c	dec r9d%1$c	mov r10d, 1%1$c	call my_exec%1$c	cmp eax, 0%1$c	jne my_prog_err%1$c%1$cmy_prog_end:%1$c	mov rdi, QWORD [rsp + 24]%1$c	call _free%1$c	xor rax, rax%1$c	jmp end%1$cmy_prog_err:%1$c	mov eax, 1%1$cend:%1$c	add rsp, 32%1$c	leave%1$c	ret%1$c	;; int my_exec(char *cmd, char *sully, char *itoa, char *compil1, char *compil2, int integer, int exec)%1$cmy_exec:%1$c	push rbp%1$c	mov rbp, rsp%1$c	sub rsp, 64%1$c%1$c	mov QWORD [rsp + 0], rdi	; cmd%1$c	mov QWORD [rsp + 8], rsi	; sully%1$c	mov QWORD [rsp + 16], rdx	; itoa%1$c	mov QWORD [rsp + 24], rcx	; compil1%1$c	mov QWORD [rsp + 32], r8	; compil2%1$c	mov DWORD [rsp + 40], r9d	; integer%1$c	mov DWORD [rsp + 44], r10d	; exec%1$c%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 8]%1$c	mov rdx, -1%1$c	call _strcpy%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 16]%1$c	mov rdx, -1%1$c	call _strcat%1$c	mov rdi, QWORD [rsp + 0]%1$c	lea rsi, [rel extension]%1$c	mov rdx, -1%1$c	call _strcat%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 8]%1$c	mov rdx, QWORD [rsp + 24]%1$c	mov rcx, QWORD [rsp + 32]%1$c	mov r8d, DWORD [rsp + 40]%1$c	call create_file%1$c	cmp eax, 0%1$c	jne my_exec_end%1$c%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 24]%1$c	mov rdx, -1%1$c	call _strcpy					; 'PATH=~/.brew/bin nasm -f macho64 '%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 8]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_'%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 16]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5'%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 32]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o '%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 8]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_'%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 16]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5'%1$c	mov rdi, QWORD [rsp + 0]%1$c	lea rsi, [rel space]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 '%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 8]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_'%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 16]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5'%1$c	mov rdi, QWORD [rsp + 0]%1$c	lea rsi, [rel object]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o'%1$c	cmp DWORD [rsp + 44], 0%1$c	je my_exec_system%1$c	mov rdi, QWORD [rsp + 0]%1$c	lea rsi, [rel and_exec]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o && ./'%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 8]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o && ./Sully_'%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 16]%1$c	mov rdx, -1%1$c	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o && ./Sully_5'%1$c%1$cmy_exec_system:%1$c	mov rdi, QWORD [rsp + 0]%1$c	call _system%1$c	mov DWORD [rsp + 48], eax%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 8]%1$c	mov rdx, -1%1$c	call _strcpy					; 'Sully_'%1$c	mov rdi, QWORD [rsp + 0]%1$c	mov rsi, QWORD [rsp + 16]%1$c	mov rdx, -1%1$c	call _strcat					; 'Sully_5'%1$c	mov rdi, QWORD [rsp + 0]%1$c	lea rsi, [rel object]%1$c	mov rdx, -1%1$c	call _strcat					; 'Sully_5.o'%1$c	mov rdi, QWORD [rsp + 0]%1$c	call _remove%1$cmy_exec_end:%1$c	add rsp, 64%1$c	pop rbp%1$c	ret%1$c	;; int my_itoa(char *buff, int i)%1$cmy_itoa:%1$c	push rbp%1$c	mov rbp, rsp%1$c	sub rsp, 12%1$c%1$c	mov rsp, rdi%1$c	mov eax, esi%1$c	mov DWORD [rsp + 8], eax ;i%1$c	mov ecx, 1 ;len%1$c%1$c	xor edx, edx%1$c	mov ebx, 10%1$c	jmp my_itoa_nblen_loop%1$cmy_itoa_nblen:%1$c	inc ecx%1$cmy_itoa_nblen_loop:%1$c	cmp eax, 10%1$c	div ebx%1$c	jge my_itoa_nblen%1$c%1$c	mov eax, DWORD [rsp + 8]%1$c	mov DWORD [rsp + 8], ecx%1$c	mov ebx, 10%1$cmy_itoa_write:%1$c	cmp ecx, 0%1$c	jle my_itoa_end%1$c	dec ecx%1$c	xor dx, dx%1$c	div ebx%1$c	add dx, 48%1$c	mov BYTE [rsp + rcx], dl%1$cmy_itoa_end:%1$c	mov eax, DWORD [rsp + 8]%1$c	add rsp, 12%1$c	leave%1$c	ret%1$c	;; int create_file(char *file, char *sully, char *compil1, char *compil2, int nb)%1$ccreate_file:%1$c	push rbp%1$c	mov rbp, rsp%1$c	sub rsp, 64%1$c%1$c	mov QWORD [rsp + 24], rsi%1$c	mov QWORD [rsp + 32], rdx%1$c	mov QWORD [rsp + 40], rcx%1$c	mov DWORD [rsp + 48], r8d%1$c%1$c	mov rsi, 1537%1$c	mov rdx, 420%1$c	mov al, 0%1$c	call _open%1$c	mov DWORD [rsp + 52], eax%1$c	cmp DWORD [rsp + 52], 0%1$c	jl create_file_end%1$c	mov edi, eax%1$c	lea rsi, [rel string]%1$c	mov edx, 10%1$c	mov ecx, 34%1$c	lea r8, [rel string]%1$c	mov r9, QWORD [rsp + 24]%1$c	mov rax, QWORD [rsp + 32]%1$c	mov QWORD [rsp], rax%1$c	mov rax, QWORD [rsp + 40]%1$c	mov QWORD [rsp + 8], rax%1$c	mov eax, DWORD [rsp + 48]%1$c	mov DWORD [rsp + 16], eax%1$c	mov al, 0%1$c	call _dprintf%1$c	mov edi, DWORD [rsp + 28]%1$c	call _close%1$c	xor eax, eax%1$ccreate_file_end:%1$c	add rsp, 64%1$c	leave%1$c	ret%1$c", 0
	sully db "Sully_", 0
	sully_len equ $-sully
	compil_1 db "PATH=~/.brew/bin nasm -f macho64 ", 0
	compil_1len equ $-compil_1
	compil_2 db ".s && gcc -o ", 0
	compil_2len equ $-compil_2
	extension db ".s", 0
	object db ".o", 0
	space db " ", 0
	and_exec db " && ./", 0
	integer dd 5

	section .text
_main:
	push rbp
	mov rbp, rsp
	sub rsp, 32

	mov eax, DWORD [rel integer]
	mov DWORD [rsp + 16], eax
	mov eax, 1
	jmp my_prog
my_loop_err:
	cmp QWORD [rsp + 24], 0
	je my_prog_err
	mov rdi, QWORD [rsp + 24]
	call _free
	jmp my_prog_err
my_prog:
	cmp DWORD [rsp + 16], 0
	jl end
	lea rdi, [rsp]
	mov esi, DWORD [rsp + 16]
	call my_itoa
	add eax, sully_len - 1
	mov ebx, 4
	imul ebx
	mov DWORD [rsp + 20], eax
	add DWORD [rsp + 20], compil_1len
	add DWORD [rsp + 20], compil_2len
	add DWORD [rsp + 20], 7
	mov edi, DWORD [rsp + 20]
	call _malloc
	mov QWORD [rsp + 24], rax
	cmp QWORD [rsp + 24], 0
	je end
	mov rdi, QWORD [rsp + 24]
	lea rsi, [rel sully]
	lea rdx, [rsp]
	lea rcx, [rel compil_1]
	lea r8, [rel compil_2]
	mov r9d, DWORD [rsp + 16]
	mov r10d, 0
	call my_exec
	cmp eax, 0
	jne my_prog_err
	cmp DWORD [rsp + 16], 0
	jle my_prog_end
	lea rdi, [rsp]
	mov esi, DWORD [rsp + 16]
	dec esi
	call my_itoa
	mov rdi, QWORD [rsp + 24]
	lea rsi, [rel sully]
	lea rdx, [rsp]
	lea rcx, [rel compil_1]
	lea r8, [rel compil_2]
	mov r9d, DWORD [rsp + 16]
	dec r9d
	mov r10d, 1
	call my_exec
	cmp eax, 0
	jne my_prog_err

my_prog_end:
	mov rdi, QWORD [rsp + 24]
	call _free
	xor rax, rax
	jmp end
my_prog_err:
	mov eax, 1
end:
	add rsp, 32
	leave
	ret
	;; int my_exec(char *cmd, char *sully, char *itoa, char *compil1, char *compil2, int integer, int exec)
my_exec:
	push rbp
	mov rbp, rsp
	sub rsp, 64

	mov QWORD [rsp + 0], rdi	; cmd
	mov QWORD [rsp + 8], rsi	; sully
	mov QWORD [rsp + 16], rdx	; itoa
	mov QWORD [rsp + 24], rcx	; compil1
	mov QWORD [rsp + 32], r8	; compil2
	mov DWORD [rsp + 40], r9d	; integer
	mov DWORD [rsp + 44], r10d	; exec

	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 8]
	mov rdx, -1
	call _strcpy
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 16]
	mov rdx, -1
	call _strcat
	mov rdi, QWORD [rsp + 0]
	lea rsi, [rel extension]
	mov rdx, -1
	call _strcat
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 8]
	mov rdx, QWORD [rsp + 24]
	mov rcx, QWORD [rsp + 32]
	mov r8d, DWORD [rsp + 40]
	call create_file
	cmp eax, 0
	jne my_exec_end

	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 24]
	mov rdx, -1
	call _strcpy					; 'PATH=~/.brew/bin nasm -f macho64 '
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 8]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_'
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 16]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5'
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 32]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o '
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 8]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_'
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 16]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5'
	mov rdi, QWORD [rsp + 0]
	lea rsi, [rel space]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 '
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 8]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_'
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 16]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5'
	mov rdi, QWORD [rsp + 0]
	lea rsi, [rel object]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o'
	cmp DWORD [rsp + 44], 0
	je my_exec_system
	mov rdi, QWORD [rsp + 0]
	lea rsi, [rel and_exec]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o && ./'
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 8]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o && ./Sully_'
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 16]
	mov rdx, -1
	call _strcat					; 'PATH=~/.brew/bin nasm -f macho64 Sully_5.s && gcc -o Sully_5 Sully_5.o && ./Sully_5'

my_exec_system:
	mov rdi, QWORD [rsp + 0]
	call _system
	mov DWORD [rsp + 48], eax
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 8]
	mov rdx, -1
	call _strcpy					; 'Sully_'
	mov rdi, QWORD [rsp + 0]
	mov rsi, QWORD [rsp + 16]
	mov rdx, -1
	call _strcat					; 'Sully_5'
	mov rdi, QWORD [rsp + 0]
	lea rsi, [rel object]
	mov rdx, -1
	call _strcat					; 'Sully_5.o'
	mov rdi, QWORD [rsp + 0]
	call _remove
my_exec_end:
	add rsp, 64
	pop rbp
	ret
	;; int my_itoa(char *buff, int i)
my_itoa:
	push rbp
	mov rbp, rsp
	sub rsp, 12

	mov rsp, rdi
	mov eax, esi
	mov DWORD [rsp + 8], eax ;i
	mov ecx, 1 ;len

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
	;; int create_file(char *file, char *sully, char *compil1, char *compil2, int nb)
create_file:
	push rbp
	mov rbp, rsp
	sub rsp, 64

	mov QWORD [rsp + 24], rsi
	mov QWORD [rsp + 32], rdx
	mov QWORD [rsp + 40], rcx
	mov DWORD [rsp + 48], r8d

	mov rsi, 1537
	mov rdx, 420
	mov al, 0
	call _open
	mov DWORD [rsp + 52], eax
	cmp DWORD [rsp + 52], 0
	jl create_file_end
	mov edi, eax
	lea rsi, [rel string]
	mov edx, 10
	mov ecx, 34
	lea r8, [rel string]
	mov r9, QWORD [rsp + 24]
	mov rax, QWORD [rsp + 32]
	mov QWORD [rsp], rax
	mov rax, QWORD [rsp + 40]
	mov QWORD [rsp + 8], rax
	mov eax, DWORD [rsp + 48]
	mov DWORD [rsp + 16], eax
	mov al, 0
	call _dprintf
	mov edi, DWORD [rsp + 28]
	call _close
	xor eax, eax
create_file_end:
	add rsp, 64
	leave
	ret
