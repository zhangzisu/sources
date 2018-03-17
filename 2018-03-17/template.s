	.file	"template.cpp"
	.def	___main;	.scl	2;	.type	32;	.endef
	.section .rdata,"dr"
LC0:
	.ascii "r\0"
LC1:
	.ascii ".in\0"
LC2:
	.ascii "w\0"
LC3:
	.ascii ".out\0"
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	call	___main
	movl	__imp___iob, %eax
	movl	%eax, 8(%esp)
	movl	$LC0, 4(%esp)
	movl	$LC1, (%esp)
	call	_freopen
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, 8(%esp)
	movl	$LC2, 4(%esp)
	movl	$LC3, (%esp)
	call	_freopen
	movl	__imp___iob, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	__imp___iob, %eax
	addl	$32, %eax
	movl	%eax, (%esp)
	call	_fclose
	movl	$0, %eax
	leave
	ret
	.def	_freopen;	.scl	2;	.type	32;	.endef
	.def	_fclose;	.scl	2;	.type	32;	.endef
