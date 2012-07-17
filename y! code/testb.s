	.file	"testb.c"
	.def	___main;	.scl	2;	.type	32;	.endef
	.text
.globl _main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	andl	$-16, %esp
	movl	$0, %eax
	addl	$15, %eax
	addl	$15, %eax
	shrl	$4, %eax
	sall	$4, %eax
	movl	%eax, -8(%ebp)
	movl	-8(%ebp), %eax
	call	__alloca
	call	___main
	movl	$64, (%esp)
	call	_malloc
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	addl	$56, %eax
	movl	$5, (%eax)
	movl	$0, %eax
	leave
	ret
	.def	_malloc;	.scl	2;	.type	32;	.endef
