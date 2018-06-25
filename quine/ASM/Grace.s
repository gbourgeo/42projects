	%define BEGIN main
	%define LOOPME loop
	%define ENDIT return
	global BEGIN
	extern dprintf
	extern open
	extern close
	%macro GRACE 0
BEGIN:
	push rbp
	mov rbp, rsp
	;; Open file ([file], O_CREAT | O_TRUNC | O_WRONLY, 0644)
	lea rdi, [rel file]
	mov rsi, 577
	mov rdx, 420
	call open WRT ..plt
	cmp rax, 0
	jl ENDIT
	mov DWORD [rsp], eax

	mov edi, eax
	lea rsi, [rel string]
	mov edx, 10
	mov ecx, 10
	mov r8d, 10
	mov r9d, 10
	push 10
	push 10
	push 10
	push 34
	push 34
	push 10
	push 34
	push rsi
	push 34
	mov r10, 47
LOOPME:
	push 10
	dec r10
	cmp r10, 0
	jg LOOPME
	call dprintf WRT ..plt

	mov edi, DWORD [rbp]
	call close WRT ..plt
ENDIT:
	xor rax, rax
	leave
	ret
	%endmacro
	section .rodata
	string db "	%%define BEGIN main%c	%%define LOOPME loop%c	%%define ENDIT return%c	global BEGIN%c	extern dprintf%c	extern open%c	extern close%c	%%macro GRACE 0%cBEGIN:%c	push rbp%c	mov rbp, rsp%c	;; Open file ([file], O_CREAT | O_TRUNC | O_WRONLY, 0644)%c	lea rdi, [rel file]%c	mov rsi, 577%c	mov rdx, 420%c	call open WRT ..plt%c	cmp rax, 0%c	jl ENDIT%c	mov DWORD [rsp], eax%c%c	mov edi, eax%c	lea rsi, [rel string]%c	mov edx, 10%c	mov ecx, 10%c	mov r8d, 10%c	mov r9d, 10%c	push 10%c	push 10%c	push 10%c	push 34%c	push 34%c	push 10%c	push 34%c	push rsi%c	push 34%c	mov r10, 47%cLOOPME:%c	push 10%c	dec r10%c	cmp r10, 0%c	jg LOOPME%c	call dprintf WRT ..plt%c%c	mov edi, DWORD [rbp]%c	call close WRT ..plt%cENDIT:%c	xor rax, rax%c	leave%c	ret%c	%%endmacro%c	section .rodata%c	string db %c%s%c, 0%c	file db %cGrace_kid.s%c, 0%c	section .text%cGRACE%c", 0
	file db "Grace_kid.s", 0
	section .text
GRACE
