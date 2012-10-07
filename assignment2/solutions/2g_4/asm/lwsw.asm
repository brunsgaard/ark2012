start:
	sub $t0, $0, 123
	sub $sp, $sp, 40
	sw $t0, 0($sp)
	lw $a0, 0($sp)
	add $v0, $zero, 1
	syscall
	add $t0, $0, 123
	sw $t0, 4($sp)
	lw $a0, 4($sp)
	add $v0, $zero, 1
	syscall
	and $a0, $zero, $zero
	add $v0, $zero, 10
	syscall