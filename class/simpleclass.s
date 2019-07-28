	.file	"simpleclass.cpp"
	.text
	.section	.text._ZN5HelloC2Ev,"axG",@progbits,_ZN5HelloC5Ev,comdat
	.align 2
	.weak	_ZN5HelloC2Ev
	.type	_ZN5HelloC2Ev, @function
_ZN5HelloC2Ev:
.LFB1:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %eax
	movl	$7, (%eax)
	nop
	popl	%ebp
.LCFI2:
	ret
.LFE1:
	.size	_ZN5HelloC2Ev, .-_ZN5HelloC2Ev
	.weak	_ZN5HelloC1Ev
	.set	_ZN5HelloC1Ev,_ZN5HelloC2Ev
	.section	.text._ZN5Hello9print_varEv,"axG",@progbits,_ZN5Hello9print_varEv,comdat
	.align 2
	.weak	_ZN5Hello9print_varEv
	.type	_ZN5Hello9print_varEv, @function
_ZN5Hello9print_varEv:
.LFB3:
	pushl	%ebp
.LCFI3:
	movl	%esp, %ebp
.LCFI4:
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	99(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
	nop
	popl	%ebp
.LCFI5:
	ret
.LFE3:
	.size	_ZN5Hello9print_varEv, .-_ZN5Hello9print_varEv
	.text
	.globl	main
	.type	main, @function
main:
.LFB4:
	leal	4(%esp), %ecx
.LCFI6:
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
.LCFI7:
	movl	%esp, %ebp
	pushl	%ecx
.LCFI8:
	subl	$20, %esp
	call	__x86.get_pc_thunk.ax
	addl	$_GLOBAL_OFFSET_TABLE_, %eax
	subl	$12, %esp
	leal	-12(%ebp), %eax
	pushl	%eax
	call	_ZN5HelloC1Ev
	addl	$16, %esp
	subl	$12, %esp
	leal	-12(%ebp), %eax
	pushl	%eax
	call	_ZN5Hello9print_varEv
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
.LCFI9:
	leave
.LCFI10:
	leal	-4(%ecx), %esp
.LCFI11:
	ret
.LFE4:
	.size	main, .-main
	.section	.text.__x86.get_pc_thunk.ax,"axG",@progbits,__x86.get_pc_thunk.ax,comdat
	.globl	__x86.get_pc_thunk.ax
	.hidden	__x86.get_pc_thunk.ax
	.type	__x86.get_pc_thunk.ax, @function
__x86.get_pc_thunk.ax:
.LFB5:
	movl	(%esp), %eax
	ret
.LFE5:
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0
	.byte	0x3
	.string	"zR"
	.uleb128 0x1
	.sleb128 -4
	.uleb128 0x8
	.uleb128 0x1
	.byte	0x1b
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0x88
	.uleb128 0x1
	.align 4
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB1-.
	.long	.LFE1-.LFB1
	.uleb128 0
	.byte	0x4
	.long	.LCFI0-.LFB1
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0xc5
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.align 4
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB3-.
	.long	.LFE3-.LFB3
	.uleb128 0
	.byte	0x4
	.long	.LCFI3-.LFB3
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI5-.LCFI4
	.byte	0xc5
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.align 4
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB4-.
	.long	.LFE4-.LFB4
	.uleb128 0
	.byte	0x4
	.long	.LCFI6-.LFB4
	.byte	0xc
	.uleb128 0x1
	.uleb128 0
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0x10
	.byte	0x5
	.uleb128 0x2
	.byte	0x75
	.sleb128 0
	.byte	0x4
	.long	.LCFI8-.LCFI7
	.byte	0xf
	.uleb128 0x3
	.byte	0x75
	.sleb128 -4
	.byte	0x6
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xc
	.uleb128 0x1
	.uleb128 0
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xc5
	.byte	0x4
	.long	.LCFI11-.LCFI10
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.align 4
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB5-.
	.long	.LFE5-.LFB5
	.uleb128 0
	.align 4
.LEFDE7:
	.ident	"GCC: (Debian 8.3.0-6) 8.3.0"
	.section	.note.GNU-stack,"",@progbits
