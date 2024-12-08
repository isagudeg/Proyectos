	.file	"main2.c"
	.text
	.section	.rodata
.LC8:
	.string	"Resultado final double: %lf\n"
.LC9:
	.string	"Resultado final float: %f\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$64, %rsp
	movsd	.LC0(%rip), %xmm0
	movsd	%xmm0, -32(%rbp)
	movsd	.LC1(%rip), %xmm0
	movsd	%xmm0, -24(%rbp)
	pxor	%xmm0, %xmm0
	movsd	%xmm0, -16(%rbp)
	movss	.LC3(%rip), %xmm0
	movss	%xmm0, -44(%rbp)
	movss	.LC4(%rip), %xmm0
	movss	%xmm0, -40(%rbp)
	pxor	%xmm0, %xmm0
	movss	%xmm0, -36(%rbp)
	movq	$0, -8(%rbp)
	jmp	.L2
.L3:
	movq	-32(%rbp), %rax
	movq	%rax, %xmm0
	call	sin@PLT
	movsd	%xmm0, -56(%rbp)
	movq	-24(%rbp), %rax
	movq	%rax, %xmm0
	call	cos@PLT
	movapd	%xmm0, %xmm2
	mulsd	-56(%rbp), %xmm2
	movsd	%xmm2, -56(%rbp)
	movsd	-32(%rbp), %xmm0
	mulsd	-24(%rbp), %xmm0
	movq	%xmm0, %rax
	movq	%rax, %xmm0
	call	sqrt@PLT
	addsd	-56(%rbp), %xmm0
	movsd	-16(%rbp), %xmm1
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -16(%rbp)
	movss	-44(%rbp), %xmm0
	movaps	%xmm0, %xmm1
	mulss	%xmm0, %xmm1
	movss	-40(%rbp), %xmm0
	mulss	%xmm0, %xmm0
	subss	%xmm0, %xmm1
	movss	-44(%rbp), %xmm0
	divss	-40(%rbp), %xmm0
	addss	%xmm1, %xmm0
	movss	-36(%rbp), %xmm1
	addss	%xmm1, %xmm0
	movss	%xmm0, -36(%rbp)
	movsd	-32(%rbp), %xmm1
	movsd	.LC6(%rip), %xmm0
	addsd	%xmm1, %xmm0
	movsd	%xmm0, -32(%rbp)
	movsd	-24(%rbp), %xmm0
	movsd	.LC6(%rip), %xmm1
	subsd	%xmm1, %xmm0
	movsd	%xmm0, -24(%rbp)
	movss	-44(%rbp), %xmm1
	movss	.LC7(%rip), %xmm0
	addss	%xmm1, %xmm0
	movss	%xmm0, -44(%rbp)
	movss	-40(%rbp), %xmm0
	movss	.LC7(%rip), %xmm1
	subss	%xmm1, %xmm0
	movss	%xmm0, -40(%rbp)
	addq	$1, -8(%rbp)
.L2:
	cmpq	$999999999, -8(%rbp)
	jle	.L3
	movq	-16(%rbp), %rax
	movq	%rax, %xmm0
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	pxor	%xmm4, %xmm4
	cvtss2sd	-36(%rbp), %xmm4
	movq	%xmm4, %rax
	movq	%rax, %xmm0
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	movl	$1, %eax
	call	printf@PLT
	movl	$0, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.align 8
.LC0:
	.long	0
	.long	1071644672
	.align 8
.LC1:
	.long	1717986918
	.long	1073899110
	.align 4
.LC3:
	.long	1066192077
	.align 4
.LC4:
	.long	1080872141
	.align 8
.LC6:
	.long	-1598689907
	.long	1051772663
	.align 4
.LC7:
	.long	925353388
	.ident	"GCC: (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
