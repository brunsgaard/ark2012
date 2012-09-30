	.data

	.align 2
messageStr:
	.asciiz	"The original message: "
encryptedStr:
	.asciiz	"The encrypted message: "
decryptedStr:
	.asciiz	"The decrypted message: "
usage:
	.asciiz	"Usage: g2 cipher_shift message\n"

newLine:
	.byte		10,0

	.text

	.globl g2

g2:	# main
	beq $a0, 2, start_function

	la $a0, usage			# Print usage string
	li $v0, 4
	syscall
	li $a0, -1			# Return value
	j exit

start_function:
	lw $a0, ($a1)			# Load integer as first argument
	jal atoi
	lw $a1, 4($a1)			# Load string as second argument
	jal caesar_encryption
	move $a0, $zero			# Return value

exit:
	li $v0, 10			# 'exit' system call
	syscall

caesar_encryption:
	subu $sp, $sp, 44		# Push the according stack size to include 'ra' and 'fp' and the buffer
	sw $ra, 40($sp)			# Push return address into the stack
	sw $s0, 36($sp)			# Push register 's0' used in the procedure into the stack
	sw $s1, 32($sp)			# Push register 's1' used in the procedure into the stack

	move $s0, $a0			# Save the the integer (a call to a procedure does not preserve it)
	move $s1, $a1			# Save the address of the original string (a call to a procedure does not preserve it)

	move $a0, $sp			# Address where 'buffer' starts ('$a1' already contains the original string)
	jal strcpy

	la $a0, messageStr		# Message
	move $a1, $s1			# Original string
	jal print_message

	# encrypt
	move $a0, $s0
	move $a1, $sp
	jal encrypt

	la $a0, encryptedStr		# Message
	move $a1, $sp			# buffer
	jal print_message

	# decrypt
	move $a0, $s0
	move $a1, $sp
	jal decrypt

	la $a0, decryptedStr		# Message
	move $a1, $sp			# buffer
	jal print_message

	lw $s1, 32($sp)			# Pop register 's1' from the stack
	lw $s0, 36($sp)			# Pop register 's0' from the stack
	lw $ra, 40($sp)			# Pop return address
	addu $sp, $sp, 44		# Pop the according stack size

	jr $ra				# Return to caller

print_message:
	li $v0, 4			# Print message string
	syscall
	move $a0, $a1
	syscall				# Print buffer
	la $a0, newLine			# Print new line character
	syscall

	jr $ra				# Return to caller

strcpy:
loop:
	lbu $t0, ($a1)
	sb $t0, ($a0)
	addiu $a0, $a0, 1
	addiu $a1, $a1, 1
	sleu $t0, $t0, $zero
	beqz $t0, loop

	jr $ra				# Return to caller

atoi:
	move $t0, $a0			# $t0 -> *ptr = string
	move $t1, $zero			# $t1 -> result = 0
	addiu $t2, $zero, 1		# $t2 -> acc = 1

loop1:
	lb $t3, ($t0)			# $t3 = ptr[0]
	beqz $t3, loop2s
	addi $t0, $t0, 1
	j loop1

loop2s:
	addi $t0, $t0, -1		# *ptr--
loop2:
	blt $t0, $a0, fin
	lb $t3, ($t0)			# $t3 = ptr[0]
	subiu $t3,$t3, 48		# $t3 = ptr[0] - 48
	mul $t3, $t3, $t2		# $t3 = (ptr[0] - 48) * acc
	add $t1, $t1, $t3		# result += (ptr[0] - 48) * acc
	mul $t2, $t2, 10		# acc *= 10
	addi $t0, $t0, -1		# *ptr--
	j loop2

fin:
	move $a0, $t1
	jr $ra				# Return to caller

#
# Functions you have to implement
#
# Remember to save all the registers that you use and should be saved for the
# caller.
# The argument 'cipher_shift' is in '$a0' and 'string' in '$a1'

encrypt:
    li $t0, 32                       # t0 = ' '
    li $t1, 6                        # t1 = '`' - '[' + 1
    li $t2, 65                       # t2 = 'A'
    li $t3, 91                       # t3 = '['
    li $t4, 96                       # t4 = '`'
    li $t6, 58                       # t6 = 'z' - 'A' + 1

    sub $t2, $t2, $a0                # t2 = 'A' - cipher_shift

    j encrypt_check

encrypt_while:
    beq $t5, $t0, encrypt_inc        # if (*string != ' ')

    sub $t5, $t5, $t2                # *string = *string - ('A' - cipher_shift)
    div $t5, $t6
    mfhi $t5                         # *string %= 'z' - 'A' + 1
    addi $t5, $t5, 65                # *string += 'A'

    blt $t5, $t3, encrypt_inc        # if (*string < '[')
    bgt $t5, $t4, encrypt_inc        # if (*string > '`')

    add $t5, $t5, $t1                # *string = *string + ('`' - '[' + 1)

encrypt_inc:
    sb $t5, ($a1)
    addi $a1, $a1, 1                 # string++

encrypt_check:
    lbu $t5, ($a1)
    bne $t5, $zero, encrypt_while   # while (*string != 0)
    jr $ra			            	# Return to caller

decrypt:
    li $t0, 32                       # t0 = ' '
    li $t1, 186                      # t1 = '`' + '[' - 1
    li $t2, 65                       # t2 = 'A'
    li $t3, 91                       # t3 = '['
    li $t4, 96                       # t4 = '`'
    li $t6, 58                       # t6 = 'z' - 'A' + 1

    add $t2, $t2, $a0                # t2 = 'A' + cipher_shift

    j decrypt_check

decrypt_while:
    beq $t5, $t0, decrypt_inc        # if (*string != ' ')

    sub $t5, $t5, $t2                # *string = *string - ('A' + cipher_shift)
    div $t5, $t6
    mfhi $t5                         # *string %= 'z' - 'A' + 1
    addi $t5, $t5, 65                # *string += 'A'

    blt $t5, $t3, decrypt_inc        # if (*string < '[')
    bgt $t5, $t4, decrypt_inc        # if (*string > '`')

    sub $t5, $t5, $t1                # *string = *string - ('`' + '[' - 1)

decrypt_inc:
    sb $t5, ($a1)
    addi $a1, $a1, 1                 # string++

decrypt_check:
    lbu $t5, ($a1)
    bne $t5, $zero, decrypt_while   # while (*string != 0)
    jr $ra	             			# Return to caller
