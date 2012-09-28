# This code does not use any arguments you may call it with. It reads 10 integers from console,
# performs the calculations and outputs the result containing the same integers.

# This code uses the instructions found in the MIPS-lite set, together with some pseudo-instructions
# and 'syscall'.
	
	.data
	.align 2
array:	.space 40
space:	.asciiz " "
	.text
main:
	add $a1, $zero, 10
	la $a0, array
	jal readInts
	la $a0, array
	add $a1, $a0, 36
	jal partition
	add $a1, $zero, 10
	la $a0, array
	jal printInts
	add $v0, $zero, 10
	syscall
	
swap:
	lw $t0, 0($a0)
	lw $t1, 0($a1)
	sw $t1, 0($a0)
	sw $t0, 0($a1)
	jr $ra

partition:
	sub $sp, $sp, 24
	sw   $ra, 20($sp)
	sw   $s5, 16($sp)
	sw   $s4, 12($sp)
	sw   $s3, 8($sp)
	sw   $s1, 4($sp)
	sw   $s0, 0($sp)

	move $s0, $a0
	move $s1, $a1
	lw   $s3, 0($s1)
	move $s4, $s0
	sub $s4, $s4, 4
	move $s5, $s0
	
loop:
	beq  $s5, $s1, exit
	lw   $t0, 0($s5)
	slt  $t1, $t0, $s3
	beq  $t1, $zero, over
	add $s4, $s4, 4
	move $a0, $s4
	move $a1, $s5
	jal  swap

over:
	add $s5, $s5, 4
	j    loop

exit:
	add $a0, $s4, 4
	move $a1, $s1
	jal  swap

	add $v0, $s4, 4 
	lw   $s0, 0($sp)
	lw   $s1, 4($sp)
	lw   $s3, 8($sp)
	lw   $s4, 12($sp)
	lw   $s5, 16($sp)
	lw   $ra, 20($sp)
	add $sp, $sp, 24
	jr   $ra
	
readInts:
	add $v0, $zero, 5
	beq $a1, $zero, endRead
	syscall
	sub $a1, $a1, 1
	sw $v0, ($a0)
	add $a0, $a0, 4
	j readInts
endRead:
	jr $ra
	
printInts:
	move $t0, $a0
print:
	add $v0, $zero, 1
	beq $a1, $zero, endPrint
	lw $a0, ($t0)
	syscall
	sub $a1, $a1, 1
	add $t0, $t0, 4
	la $a0, space
	add $v0, $zero, 4
	syscall
	j print
endPrint:
	jr $ra
	