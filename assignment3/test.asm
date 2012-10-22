start:
	addi $a0, $0, 1337
	addi $v0, $zero, 1
	and $a0, $zero, $zero
	addi $t1, $zero, 1
	addi $t0, $t0, 1
	j end
	addi $a0, $a0, 1
	addi $a0, $a0, 1
	addi $a0, $a0, 1
	addi $a0, $a0, 1
middle:
	addi $a0, $a0, 1
	addi $a0, $a0, 1
	addi $a0, $a0, 1
	addi $a0, $a0, 1
end:
	beq $t1, $t0, start
	addi $v0, $zero, 10