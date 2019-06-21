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

fact:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $a0, -4($fp)
	li $t0, 1
	bne $a0, $t0, label1
	move $v0, $a0
	addi $sp, $sp, 2048
	jr $ra
label1:
	addi $t1, $a0, -1
	sw $t1, -8($fp)
	sw $a0, 2044($sp)
	move $a0, $t1
	sw $ra, 2032($sp)
	sw $fp, 2028($sp)
	jal fact
	lw $fp, 2028($sp)
	lw $ra, 2032($sp)
	lw $a0, 2044($sp)
	lw $t1, -8($fp)
	move $t2, $v0
	mul $t3, $a0, $t2
	sw $t3, -16($fp)
	move $v0, $t3
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $ra, -8($fp)
	jal read
	lw $ra, -8($fp)
	move $t0, $v0
	sw $t0, -4($fp)
	li $t1, 1
	ble $t0, $t1, label2
	sw $t0, -4($fp)
	move $a0, $t0
	sw $ra, 2036($sp)
	sw $fp, 2032($sp)
	jal fact
	lw $fp, 2032($sp)
	lw $ra, 2036($sp)
	lw $t0, -4($fp)
	move $t2, $v0
	sw $t0, -4($fp)
	sw $t2, -8($fp)
	j label3
label2:
	li $t2, 1
	sw $t2, -8($fp)
label3:
	sw $ra, -12($fp)
	move $a0, $t2
	jal write
	lw $ra, -12($fp)
	move $v0, $0
	jr $ra
