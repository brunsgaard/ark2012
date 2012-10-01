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
    j normalize_check

normalize:
    addi $a0, $a0, 26                # cipher_shift += ALPHA_LEN

normalize_check:
    slt $t0, $a0, $zero
    bne $t0, $zero, normalize        # while (cipher_shift < 0)
    li $t0, 26
    div $a0, $t0
    mfhi $a0                         # cipher_shift %= ALPHA_LEN

    j encrypt_check

encrypt_while:
    ####################
    # isalpha(*string) #
    ####################

    li $t1, 65
    slt $t2, $t0, $t1
    bne $t2, $zero, encrypt_inc      # if (*string < 'A')

    li $t1, 122
    slt $t2, $t1, $t0
    bne $t2, $zero, encrypt_inc      # if (*string > 'z')

    li $t1, 90
    slt $t2, $t1, $t0                # if (*string >= '[')
    li $t1, 97
    slt $t3, $t0, $t1                # if (*string <= '`')
    and $t2, $t2, $t3
    bne $t2, $zero, encrypt_inc

    ####################
    # toupper(*string) #
    ####################

    slti $t1, $t0, 97
    bne $t1, $zero, encrypt_do

    # Convert lowercase characters to uppercase
    # by subtracting the ascii table offset
    li $t2, 32
    sub $t0, $t0, $t2                # *string -= ('a' - 'A')

encrypt_do:
    ###########
    # encrypt #
    ###########

    add $t0, $t0, $a0                # *string += cipher_shift
    li $t1, 91
    div $t0, $t1
    mfhi $t0                         # *string %= ALPHA_END + 1

    slti $t1, $t0, 65
    beq $t1, $zero, encrypt_inc      # if (*string < ALPHA_START)
    addi $t0, $t0, 65                # *string += ALPHA_START

encrypt_inc:
    sb $t0, ($a1)
    addi $a1, $a1, 1                 # string++

encrypt_check:
    lbu $t0, ($a1)
    bne $t0, $zero, encrypt_while   # while (*string != 0)
    jr $ra			            	# Return to caller

decrypt:
    sub $sp, $sp, 4
    sw $ra, 0($sp)

    neg $a0, $a0                    # cipher_shift = -cipher_shift
    jal encrypt                     # encrypt(-cipher_shift, string)

    lw $ra, 0($sp)
    add $sp, $sp, 4
    jr $ra	             			# Return to caller
