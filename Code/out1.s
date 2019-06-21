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

a:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	lw $t0, 0($fp)
	lw $t1, 4($fp)
	add $t2, $a0, $a1
	sw $t2, -12($fp)
	add $t3, $a2, $a3
	sw $t3, -16($fp)
	add $t2, $t3, $t0
	sw $t2, -12($fp)
	mul $t4, $t2, $t1
	sw $t4, -20($fp)
	move $v0, $t4
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	li $t0, 1
	sw $t0, -4($fp)
	li $t1, 2
	sw $t1, -8($fp)
	li $t2, 3
	sw $t2, -12($fp)
	li $t3, 4
	sw $t3, -16($fp)
	li $t4, 5
	sw $t4, -20($fp)
	li $t5, 6
	sw $t5, -24($fp)
	lw $t0, -4($fp)
	move $a0, $t0
	lw $t1, -8($fp)
	move $a1, $t1
	lw $t2, -12($fp)
	move $a2, $t2
	lw $t3, -16($fp)
	move $a3, $t3
	subu $sp, $sp, 4
	lw $t4, -20($fp)
	sw $t4, 0($sp)
	lw $t5, -24($fp)
	sw $t5, 4($sp)
	sw $ra, 2016($sp)
	sw $fp, 2012($sp)
	jal a
	lw $fp, 2012($sp)
	lw $ra, 2016($sp)
	addi $sp, $sp, 4
	lw $t0, -4($fp)
	lw $t1, -8($fp)
	lw $t2, -12($fp)
	lw $t3, -16($fp)
	lw $t4, -20($fp)
	lw $t5, -24($fp)
	move $t6, $v0
	sw $ra, -32($fp)
	move $a0, $t6
	jal write
	lw $ra, -32($fp)
	move $v0, $0
	jr $ra
