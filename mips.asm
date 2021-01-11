.text
main:
      addi $sp, $sp, -4
      li $t1, 3
      move $t2, $t1
      li $t1, 2
      move $t3, $t1
      add $t1, $t2, $t3
      move $a1, $t1
      sw $a1, x
      addi $sp, $sp, -4
      li $t1, 2
      move $a1, $t1
      sw $a1, y
      addi $sp, $sp, -4
      lw $a1, x
      sw $a1, z
      lw $a1, y
      li $v0, 1
      move $a0, $a1
      syscall
      li $t1, 1
      move $t2, $t1
      li $t1, 2
      move $t3, $t1
      add $t1, $t2, $t3
      move $a0, $t1
      syscall
      li $t1, 3
      move $t2, $t1
      li $t1, 3
      move $t3, $t1
      bne $t2, $t3, L1
      j L2
L1:
      lw $a1, x
      li $v0, 1
      move $a0, $a1
      syscall
L2:
      li $v0, 5
      syscall
      move $a1, $v0
      sw $a1 z
L3:
      li $t1, 0
      move $t2, $t1
      li $t1, 0
      move $t3, $t1
      beq $t2, $t3, L4
      lw $a1, x
      li $v0, 1
      move $a0, $a1
      syscall
      j L3
L4:
      li $t1, 0
      move $t2, $t1
      li $t1, 0
      move $t3, $t1
      bne $t2, $t3, L5
      lw $a1, z
      li $v0, 1
      move $a0, $a1
      syscall
      j L5
L5:
      li $v0, 10
      syscall
