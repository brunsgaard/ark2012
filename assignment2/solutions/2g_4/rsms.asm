start:
	add $a0, $0, 1337
	add $v0, $zero, 1
	syscall
	and $a0, $zero, $zero
	add $t1, $zero, 1
	add $t0, $t0, 1
	j end
	add $a0, $a0, 1
	add $a0, $a0, 1
	add $a0, $a0, 1
	add $a0, $a0, 1
middle:
	add $a0, $a0, 1
	add $a0, $a0, 1
	add $a0, $a0, 1
	add $a0, $a0, 1
end:
	beq $t1, $t0, start
	add $v0, $zero, 10
	syscall;