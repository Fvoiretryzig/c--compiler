.data
_prompt: .asciiz "Enter an interger:"
_ret: .asciiz "\n"
.globl main
.text
read:
	li $v0, 4
	la $a0, _prompt
	syscall
	li $v0, 5
	syscall
	jr $ra

write:
	li $v0, 1
	syscall
	li $v0, 4
	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra

aaa:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $a0, -4($fp)
	sw $a1, -8($fp)
	sw $a2, -12($fp)
	sw $a3, -16($fp)
	lw $t0, 0($fp)
	lw $t1, 4($fp)
	lw $t2, 8($fp)
	div $a0, $a1
	mflo $t3
	sw $t3, -32($fp)
	add $t4, $a2, $a3
	sw $t4, -36($fp)
	sub $t5, $t0, $t1
	sw $t5, -40($fp)
	move $t6, $t2
	sw $t6, -44($fp)
	mul $t7, $t4, $t6
	move $v0, $t7
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	subu $v1, $fp, 40
	move $t0, $v1
	sw $t0, -40($fp)
	li $t1, 0
	sw $t1, -44($fp)
	addi $t2, $t0, 0
	li $t3, 5
	sw $t3, 0($t2)
	addi $t4, $t0, 4
	li $t5, 6
	sw $t5, 0($t4)
	li $t6, 1
	sw $t6, -56($fp)
	li $t7, 2
	sw $t7, -60($fp)
	li $s0, 3
	sw $s0, -64($fp)
	li $s1, 4
	sw $s1, -68($fp)
	li $s2, 5
	sw $s2, -72($fp)
	li $s3, 6
	sw $s3, -76($fp)
	li $s4, 7
	sw $s4, -80($fp)
	sw $t0, -40($fp)
	sw $t2, -48($fp)
	sw $t4, -52($fp)
label1:
	li $s5, 9
	bge $t1, $s5, label2
	add $t6, $t6, $t1
	sw $t6, -56($fp)
	addi $t1, $t1, 1
	sw $t1, -44($fp)
	j label1
label2:
	sw $ra, -84($fp)
	move $a0, $t6
	jal write
	lw $ra, -84($fp)
	sw $ra, -88($fp)
	jal read
	lw $ra, -88($fp)
	move $s6, $v0
	sw $t6, -56($fp)
	sw $s6, -84($fp)
	ble $s6, $zero, label3
	addi $s7, $t0, 16
	li $t8, 40
	sw $t8, 0($s7)
	addi $t9, $t0, 16
	sw $t0, -40($fp)
	lw $t0, 0($t9)
	sw $t0, -96($fp)
	sw $ra, -100($fp)
	move $a0, $t0
	jal write
	lw $ra, -100($fp)
	sw $t0, -96($fp)
	sw $s6, -84($fp)
	sw $s7, -88($fp)
	sw $t9, -92($fp)
label3:
	move $a0, $t6
	move $a1, $t7
	move $a2, $s0
	move $a3, $s1
	subu $sp, $sp, 8
	sw $s2, 0($sp)
	sw $s3, 4($sp)
	sw $s4, 8($sp)
	sw $ra, 1944($sp)
	sw $fp, 1940($sp)
	jal aaa
	lw $fp, 1940($sp)
	lw $ra, 1944($sp)
	addi $sp, $sp, 8
	lw $t0, -96($fp)
	lw $t1, -44($fp)
	lw $t2, -48($fp)
	lw $t4, -52($fp)
	lw $t6, -56($fp)
	lw $t7, -60($fp)
	lw $t9, -92($fp)
	move $t1, $v0
	sw $ra, -104($fp)
	move $a0, $t1
	jal write
	lw $ra, -104($fp)
	move $v0, $0
	jr $ra
