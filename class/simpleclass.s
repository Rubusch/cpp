	.file	"simpleclass.cpp"
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
	movl	8(%ebp), %eax
	movl	$7, (%eax)
	popl	%ebp
.LCFI2:
	ret
.LFE1:
	.size	_ZN5HelloC2Ev, .-_ZN5HelloC2Ev
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
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	leal	99(%eax), %edx
	movl	8(%ebp), %eax
	movl	%edx, (%eax)
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
	pushl	%ebp
.LCFI6:
	movl	%esp, %ebp
.LCFI7:
	andl	$-16, %esp
	subl	$32, %esp
.LCFI8:
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN5HelloC1Ev
	leal	28(%esp), %eax
	movl	%eax, (%esp)
	call	_ZN5Hello9print_varEv
	movl	$0, %eax
	leave
.LCFI9:
	ret
.LFE4:
	.size	main, .-main
	.weak	_ZN5HelloC1Ev
	.set	_ZN5HelloC1Ev,_ZN5HelloC2Ev
	.section	.eh_frame,"a",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0
	.byte	0x1
	.string	""
	.uleb128 0x1
	.sleb128 -4
	.byte	0x8
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
	.long	.LFB1
	.long	.LFE1-.LFB1
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
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0xc5
	.align 4
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB3
	.long	.LFE3-.LFB3
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
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.byte	0xc5
	.align 4
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB4
	.long	.LFE4-.LFB4
	.byte	0x4
	.long	.LCFI6-.LFB4
	.byte	0xe
	.uleb128 0x8
	.byte	0x85
	.uleb128 0x2
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xd
	.uleb128 0x5
	.byte	0x4
	.long	.LCFI9-.LCFI7
	.byte	0xc5
	.byte	0xc
	.uleb128 0x4
	.uleb128 0x4
	.align 4
.LEFDE5:
	.ident	"GCC: (Ubuntu/Linaro 4.6.3-1ubuntu5) 4.6.3"
	.section	.note.GNU-stack,"",@progbits
