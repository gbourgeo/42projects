	global main
	extern dprintf
	extern open
	extern close
	extern strncpy
	extern stat
	extern system

	section .rodata
	integer dd 5
	sully db "Sully_", 0
	sully_len equ $-sully
	string db "	global main%c	extern dprintf%c	extern open%c	extern close%c	extern strncpy%c	extern stat%c	extern system%c%c	section .rodata%c	integer dd %d%c	sully db %cSully_%c, 0%c	sully_len equ $-sully%c	string db %c%s%c, 0%c	compil_1 db %c%s%c, 0%c	compil_1len equ $-compil_1%c	compil_2 db %c%s%c, 0%c	compil_2len equ $-compil_2%c%c	section .text%cmain:%c	push rbp%c	mov rbp, rsp%c	sub rsp, 100%c	cmp DWORD [rel integer], 0%c	jl end%c	lea rdi, [rsp]								;%c	lea rsi, [rel sully]%c	mov edx, sully_len%c	call strncpy WRT ..plt%c	lea rdi, [rsp + sully_len - 1] 				; 'Sully_'%c	mov esi, DWORD [rel integer]%c	call my_itoa%c	mov DWORD [rsp + 100], eax%c	mov BYTE [rsp + sully_len + rax - 1], '.'%c	mov BYTE [rsp + sully_len + rax + 0], 's'%c	mov BYTE [rsp + sully_len + rax + 1], 0%c	lea rdi, [rsp]								; 'Sully_X.s'%c	call create_file%c	cmp DWORD [rel integer], 0%c	je end%c	lea rdi, [rsp]								;%c	lea rsi, [rel compil_1]%c	mov edx, compil_1len%c	call strncpy WRT ..plt%c	lea rdi, [rsp + compil_1len - 1] ; 'nasm -f elf64 '%c	lea rsi, [rel sully]%c	mov edx, sully_len%c	call strncpy WRT ..plt%c	lea rdi, [rsp + compil_1len + sully_len - 2] ; 'nasm -f elf64 Sully_'%c	mov esi, DWORD [rel integer]%c	add esi, -1%c	call my_itoa%c	add eax, compil_1len%c	add eax, sully_len%c	sub eax, 2%c	mov DWORD [rsp + 100], eax%c	mov BYTE [rsp + rax], '.'%c	mov BYTE [rsp + rax + 1], 's'%c	mov BYTE [rsp + rax + 2], ' '%c	mov BYTE [rsp + rax + 3], '&'%c	mov BYTE [rsp + rax + 4], '&'%c	mov BYTE [rsp + rax + 5], ' '%c	add DWORD [rsp + 100], 5%c	lea rdi, [rsp + rax + 6] ; 'nasm -f elf64 Sully_W.s && '%c	lea rsi, [rel compil_2]%c	mov edx, compil_2len%c	call strncpy WRT ..plt%c	add DWORD [rsp + 100], compil_2len%c	mov eax, DWORD [rsp + 100]%c	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o '%c	lea rsi, [rel sully]%c	mov edx, sully_len%c	call strncpy WRT ..plt%c	add DWORD [rsp + 100], sully_len - 1%c	mov eax, DWORD [rsp + 100]%c	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_'%c	mov esi, DWORD [rel integer]%c	add esi, -1%c	call my_itoa%c	add DWORD [rsp + 100], eax%c	mov eax, DWORD [rsp + 100]%c	mov BYTE [rsp + rax], ' '%c	lea rdi, [rsp + rax + 1] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W '%c	lea rsi, [rel sully]%c	mov edx, sully_len%c	call strncpy WRT ..plt%c	add DWORD [rsp + 100], sully_len%c	mov eax, DWORD [rsp + 100]%c	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_'%c	mov esi, DWORD [rel integer]%c	add esi, -1%c	call my_itoa%c	add DWORD [rsp + 100], eax%c	mov eax, DWORD [rsp + 100]%c	mov BYTE [rsp + rax], '.'%c	mov BYTE [rsp + rax + 1], 's'%c	mov BYTE [rsp + rax + 2], 0%c	add DWORD [rsp + 100], 2%c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.s'%c	lea rdi, [rsp + rax - sully_len] ;Sully_W.s%c	call create_file%c	cmp eax, 0%c	jne end%c	mov eax, DWORD [rsp + 100]%c	mov BYTE [rsp + rax - 1], 'o'%c	mov BYTE [rsp + rax], ' '%c	mov BYTE [rsp + rax + 1], '&'%c	mov BYTE [rsp + rax + 2], '&'%c	mov BYTE [rsp + rax + 3], ' '%c	mov BYTE [rsp + rax + 4], '.'%c	mov BYTE [rsp + rax + 5], '/'%c	add DWORD [rsp + 100], 5%c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./'%c	lea rdi, [rsp + rax + 6]%c	lea rsi, [rel sully]%c	mov edx, sully_len%c	call strncpy WRT ..plt%c	add DWORD [rsp + 100], sully_len%c	mov eax, DWORD [rsp + 100]%c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_'%c	lea rdi, [rsp + rax]%c	mov esi, DWORD [rel integer]%c	add esi, -1%c	call my_itoa%c	add DWORD [rsp + 100], eax%c	mov eax, DWORD [rsp + 100]%c	mov BYTE [rsp + rax], 0%c	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_W'%c	lea rdi, [rsp]%c	call system WRT ..plt%cend:%c	add rsp, 100%c	xor rax, rax%c	leave%c	ret%c	;; int my_itoa(char *buff, int i)%cmy_itoa:%c	push rbp%c	mov rbp, rsp%c	sub rsp, 12%c%c	mov rsp, rdi%c	mov eax, esi%c	mov DWORD [rsp + 8], eax	;i%c	mov ecx, 1					;len%c%c	xor edx, edx%c	mov ebx, 10%c	jmp my_itoa_nblen_loop%cmy_itoa_nblen:%c	inc ecx%cmy_itoa_nblen_loop:%c	cmp eax, 10%c	div ebx%c	jge my_itoa_nblen%c%c	mov eax, DWORD [rsp + 8]%c	mov DWORD [rsp + 8], ecx%c	mov ebx, 10%cmy_itoa_write:%c	cmp ecx, 0%c	jle my_itoa_end%c	dec ecx%c	xor dx, dx%c	div ebx%c	add dx, 48%c	mov BYTE [rsp + rcx], dl%cmy_itoa_end:%c	mov eax, DWORD [rsp + 8]%c	add rsp, 12%c	leave%c	ret%c	;; int create_file(char *file, int nb)%ccreate_file:%c	push rbp%c	mov rbp, rsp%c	sub rsp, 4%c%c	mov r13, rsi%c	mov r14, compil_1%c	mov r12, compil_2%c	mov rsi, 193%c	mov rdx, 420%c	call open WRT ..plt%c	cmp eax, 0%c	jl create_file_end%c	mov DWORD [rsp], eax%c	mov edi, eax%c	lea rsi, [rel string]%c	mov edx, 10%c	mov ecx, 10%c	mov r8d, 10%c	mov r9d, 10%c	mov r15, 216%cloop:%c	push 10%c	cmp r15, 0%c	dec r15%c	jg loop%c	push 34%c	push r12%c	push 34%c	push 10%c	push 10%c	push 34%c	push r14%c	push 34%c	push 10%c	push 34%c	push rsi%c	push 34%c	push 10%c	push 10%c	push 34%c	push 34%c	push 10%c	push r13%c	push 10%c	push 10%c	push 10%c	push 10%c	push 10%c	call dprintf WRT ..plt%c	add rsp, 1912%c	mov edi, DWORD [rsp]%c	call close WRT ..plt%c	xor eax, eax%ccreate_file_end:%c	add rsp, 4%c	leave%c	ret%c", 0
	compil_1 db "nasm -f elf64 ", 0
	compil_1len equ $-compil_1
	compil_2 db "gcc -Wall -Werror -Wextra -o ", 0
	compil_2len equ $-compil_2

	section .text
main:
	push rbp
	mov rbp, rsp
	sub rsp, 100
	cmp DWORD [rel integer], 0
	jl end
	lea rdi, [rsp]								;
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy WRT ..plt
	lea rdi, [rsp + sully_len - 1] 				; 'Sully_'
	mov esi, DWORD [rel integer]
	call my_itoa
	mov DWORD [rsp + 100], eax
	mov BYTE [rsp + sully_len + rax - 1], '.'
	mov BYTE [rsp + sully_len + rax + 0], 's'
	mov BYTE [rsp + sully_len + rax + 1], 0
	lea rdi, [rsp]								; 'Sully_X.s'
	call create_file
	cmp DWORD [rel integer], 0
	je end
	lea rdi, [rsp]								;
	lea rsi, [rel compil_1]
	mov edx, compil_1len
	call strncpy WRT ..plt
	lea rdi, [rsp + compil_1len - 1] ; 'nasm -f elf64 '
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy WRT ..plt
	lea rdi, [rsp + compil_1len + sully_len - 2] ; 'nasm -f elf64 Sully_'
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add eax, compil_1len
	add eax, sully_len
	sub eax, 2
	mov DWORD [rsp + 100], eax
	mov BYTE [rsp + rax], '.'
	mov BYTE [rsp + rax + 1], 's'
	mov BYTE [rsp + rax + 2], ' '
	mov BYTE [rsp + rax + 3], '&'
	mov BYTE [rsp + rax + 4], '&'
	mov BYTE [rsp + rax + 5], ' '
	add DWORD [rsp + 100], 5
	lea rdi, [rsp + rax + 6] ; 'nasm -f elf64 Sully_W.s && '
	lea rsi, [rel compil_2]
	mov edx, compil_2len
	call strncpy WRT ..plt
	add DWORD [rsp + 100], compil_2len
	mov eax, DWORD [rsp + 100]
	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o '
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy WRT ..plt
	add DWORD [rsp + 100], sully_len - 1
	mov eax, DWORD [rsp + 100]
	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_'
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add DWORD [rsp + 100], eax
	mov eax, DWORD [rsp + 100]
	mov BYTE [rsp + rax], ' '
	lea rdi, [rsp + rax + 1] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W '
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy WRT ..plt
	add DWORD [rsp + 100], sully_len
	mov eax, DWORD [rsp + 100]
	lea rdi, [rsp + rax] ; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_'
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add DWORD [rsp + 100], eax
	mov eax, DWORD [rsp + 100]
	mov BYTE [rsp + rax], '.'
	mov BYTE [rsp + rax + 1], 's'
	mov BYTE [rsp + rax + 2], 0
	add DWORD [rsp + 100], 2
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.s'
	lea rdi, [rsp + rax - sully_len] ;Sully_W.s
	call create_file
	cmp eax, 0
	jne end
	mov eax, DWORD [rsp + 100]
	mov BYTE [rsp + rax - 1], 'o'
	mov BYTE [rsp + rax], ' '
	mov BYTE [rsp + rax + 1], '&'
	mov BYTE [rsp + rax + 2], '&'
	mov BYTE [rsp + rax + 3], ' '
	mov BYTE [rsp + rax + 4], '.'
	mov BYTE [rsp + rax + 5], '/'
	add DWORD [rsp + 100], 5
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./'
	lea rdi, [rsp + rax + 6]
	lea rsi, [rel sully]
	mov edx, sully_len
	call strncpy WRT ..plt
	add DWORD [rsp + 100], sully_len
	mov eax, DWORD [rsp + 100]
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_'
	lea rdi, [rsp + rax]
	mov esi, DWORD [rel integer]
	add esi, -1
	call my_itoa
	add DWORD [rsp + 100], eax
	mov eax, DWORD [rsp + 100]
	mov BYTE [rsp + rax], 0
	;; 'nasm -f elf64 Sully_W.s && gcc -Wall -Werror -Wextra -o Sully_W Sully_W.o && ./Sully_W'
	lea rdi, [rsp]
	call system WRT ..plt
end:
	add rsp, 100
	xor rax, rax
	leave
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
	sub rsp, 4

	mov r13, rsi
	mov r14, compil_1
	mov r12, compil_2
	mov rsi, 193
	mov rdx, 420
	call open WRT ..plt
	cmp eax, 0
	jl create_file_end
	mov DWORD [rsp], eax
	mov edi, eax
	lea rsi, [rel string]
	mov edx, 10
	mov ecx, 10
	mov r8d, 10
	mov r9d, 10
	mov r15, 216
loop:
	push 10
	cmp r15, 0
	dec r15
	jg loop
	push 34
	push r12
	push 34
	push 10
	push 10
	push 34
	push r14
	push 34
	push 10
	push 34
	push rsi
	push 34
	push 10
	push 10
	push 34
	push 34
	push 10
	push r13
	push 10
	push 10
	push 10
	push 10
	push 10
	call dprintf WRT ..plt
	add rsp, 1912
	mov edi, DWORD [rsp]
	call close WRT ..plt
	xor eax, eax
create_file_end:
	add rsp, 4
	leave
	ret
