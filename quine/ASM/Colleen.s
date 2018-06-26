	extern _printf
	global _main

	section .rodata
	string db "	extern _printf%c	global _main%c%c	section .rodata%c	string db %c%s%c, 0%c%c	section .text%c	;; Here begins the main function%c_main:%c	push rbp%c	mov rbp, rsp%c	lea rdi, [rel string]%c	mov rsi, 10%c	mov rdx, 10%c	mov rcx, 10%c	mov r8, 10%c	mov r9, 34%c	mov r15, 30%cloop:%c	push 10%c	call dec_r15%c	cmp r15, 0%c	jg loop%c	push 34%c	push rdi					; For %%s%c	xor rax, rax%c	call _printf%c	xor rax, rax%c	leave%c	ret%c%cdec_r15:%c	dec r15%c	ret%c", 0

	section .text
	;; Here begins the main function
_main:
	push rbp
	mov rbp, rsp
	lea rdi, [rel string]
	mov rsi, 10
	mov rdx, 10
	mov rcx, 10
	mov r8, 10
	mov r9, 34
	mov r15, 30
loop:
	push 10
	call dec_r15
	cmp r15, 0
	jg loop
	push 34
	push rdi					; For %s
	xor rax, rax
	call _printf
	xor rax, rax
	leave
	ret

dec_r15:
	dec r15
	ret
