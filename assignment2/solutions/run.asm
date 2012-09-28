#include <g2.asm>

	.data

cipher_shift: .byte	0x31,0x0
	.align 2
message: .byte		0x41,0x41,0x41,0x0
	.align 2
sp:	.space 32

	.text

main:
	la $a1, sp
	la $a0, cipher_shift
	sw $a0, ($a1)
	la $a0, message
	sw $a0, 4($a1)
	la $a0, 2

	jal g2
