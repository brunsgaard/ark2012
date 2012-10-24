    j realstart
    addi $t0, $t0, 1
    addi $s0, $t0, 0
realstart:
    addi $t0, $t0, 1
    addi $s1, $t0, 0
    jal somefunc
    addi $t0, $t0, 1
    addi $s3, $t0, 0
    j end
somefunc:
    addi $t0, $t0, 1
    addi $s2, $t0, 0
    jr $ra
end:
    addi $t0, $t0, 1
    addi $s4, $t0, 0