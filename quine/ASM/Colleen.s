	extern printf
	global main

	section .rodata
	string db "	extern printf%c	global main%c%c	section .rodata%c	string db %c%s%c, 0%c%c	section .text%c	;; Here begins the main function%cmain:%c	push rbp%c	mov rbp, rsp%c	lea rdi, [rel string]%c	mov rsi, 10%c	mov rdx, 10%c	mov rcx, 39%c	mov r8, 10%c	mov r9, 34%cloop:%c	push 10%c	call dec_rcx%c	cmp rcx, 10%c	jg loop%c	push 34%c	push rdi%c	xor rax, rax%c	call printf WRT ..plt%c	xor rax, rax%c	leave%c	ret%c%cdec_rcx:%c	dec rcx%c	ret%c", 0

	section .text
	;; Here begins the main function
main:
	push rbp
	mov rbp, rsp
	lea rdi, [rel string]
	mov rsi, 10
	mov rdx, 10
	mov rcx, 39
	mov r8, 10
	mov r9, 34
loop:
	push 10
	call dec_rcx
	cmp rcx, 10
	jg loop
	push 34
	push rdi
	xor rax, rax
	call printf WRT ..plt
	xor rax, rax
	leave
	ret

dec_rcx:
	dec rcx
	ret
