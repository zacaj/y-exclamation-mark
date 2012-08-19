	.file	"testb.c"
	.text
	.p2align 2,,3
	.globl	_string_equal_string
	.def	_string_equal_string;	.scl	2;	.type	32;	.endef
_string_equal_string:
LFB0:
	.cfi_startproc
	pushl	%edi
	.cfi_def_cfa_offset 8
	.cfi_offset 7, -8
	pushl	%esi
	.cfi_def_cfa_offset 12
	.cfi_offset 6, -12
	pushl	%ebx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subl	$16, %esp
	.cfi_def_cfa_offset 32
	movl	32(%esp), %esi
	movl	36(%esp), %ebx
	movl	%ebx, %edi
	xorl	%eax, %eax
	movl	$-1, %ecx
	repne scasb
	notl	%ecx
	decl	%ecx
	movl	%ecx, (%esp)
	call	_malloc
	movl	%eax, (%esi)
	movl	%ebx, 36(%esp)
	movl	%eax, 32(%esp)
	addl	$16, %esp
	.cfi_def_cfa_offset 16
	popl	%ebx
	.cfi_def_cfa_offset 12
	.cfi_restore 3
	popl	%esi
	.cfi_def_cfa_offset 8
	.cfi_restore 6
	popl	%edi
	.cfi_def_cfa_offset 4
	.cfi_restore 7
	jmp	_strcpy
	.cfi_endproc
LFE0:
	.section .rdata,"dr"
LC0:
	.ascii "c:/model.s3d\12\0"
	.text
	.p2align 2,,3
	.globl	_pathToModel
	.def	_pathToModel;	.scl	2;	.type	32;	.endef
_pathToModel:
LFB1:
	.cfi_startproc
	subl	$44, %esp
	.cfi_def_cfa_offset 48
	movl	$LC0, 4(%esp)
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	_string_equal_string
	movl	28(%esp), %eax
	addl	$44, %esp
	.cfi_def_cfa_offset 4
	ret
	.cfi_endproc
LFE1:
	.p2align 2,,3
	.globl	_int_equal_int
	.def	_int_equal_int;	.scl	2;	.type	32;	.endef
_int_equal_int:
LFB2:
	.cfi_startproc
	movl	8(%esp), %eax
	movl	4(%esp), %edx
	movl	%eax, (%edx)
	ret
	.cfi_endproc
LFE2:
	.p2align 2,,3
	.globl	_loadModelFrom
	.def	_loadModelFrom;	.scl	2;	.type	32;	.endef
_loadModelFrom:
LFB3:
	.cfi_startproc
	movl	$1, %eax
	ret
	.cfi_endproc
LFE3:
	.def	___main;	.scl	2;	.type	32;	.endef
	.section	.text.startup,"x"
	.p2align 2,,3
	.globl	_main
	.def	_main;	.scl	2;	.type	32;	.endef
_main:
LFB4:
	.cfi_startproc
	pushl	%ebp
	.cfi_def_cfa_offset 8
	.cfi_offset 5, -8
	movl	%esp, %ebp
	.cfi_def_cfa_register 5
	andl	$-16, %esp
	subl	$32, %esp
	call	___main
	movl	$LC0, 4(%esp)
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	_string_equal_string
	leave
	.cfi_restore 5
	.cfi_def_cfa 4, 4
	ret
	.cfi_endproc
LFE4:
	.def	_malloc;	.scl	2;	.type	32;	.endef
	.def	_strcpy;	.scl	2;	.type	32;	.endef
