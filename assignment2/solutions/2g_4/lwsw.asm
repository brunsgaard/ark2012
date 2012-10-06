start:
	sub $t0, $0, 123
	sub $sp, $sp, 4
	sw $t0, 0($sp)
	lw $a0, 0($sp)
	add $v0, $zero, 1
	syscall
	and $a0, $zero, $zero
	add $v0, $zero, 10
	syscall