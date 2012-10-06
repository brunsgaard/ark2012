space: .asciiz " you code like monkeys "
main:
	sub $a0, $0, 123
	add $v0, $zero, 1
	syscall
	la $a0, space
	add $v0, $zero, 4
	syscall
	add $a0, $0, 321
	add $v0, $zero, 1
	syscall
	and $a0, $zero, $zero
	add $v0, $zero, 10
	syscall