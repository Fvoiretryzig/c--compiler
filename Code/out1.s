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

modulo:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $a0, -4($fp)
	sw $a1, -8($fp)
	div $a0, $a1
	mflo $t0
	sw $t0, -12($fp)
	mul $t1, $t0, $a1
	sw $t1, -16($fp)
	sub $t2, $a0, $t1
	sw $t2, -20($fp)
	move $v0, $t2
	addi $sp, $sp, 2048
	jr $ra

gcd:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $a0, -4($fp)
	sw $a1, -8($fp)
	bne $a0, $zero, label1
	move $v0, $a1
	addi $sp, $sp, 2048
	jr $ra
label1:
	sw $a0, 2044($sp)
	lw $a0, 2040($sp)
	sw $a1, 2040($sp)
	lw $a1, 2044($sp)
	sw $ra, 2032($sp)
	sw $fp, 2028($sp)
	jal modulo
	lw $fp, 2028($sp)
	lw $ra, 2032($sp)
	lw $a1, 2040($sp)
	lw $a0, 2044($sp)
	move $t0, $v0
	sw $t0, -12($fp)
	sw $a0, 2044($sp)
	move $a0, $t0
	sw $a1, 2040($sp)
	lw $a1, 2044($sp)
	sw $ra, 2028($sp)
	sw $fp, 2024($sp)
	jal gcd
	lw $fp, 2024($sp)
	lw $ra, 2028($sp)
	lw $a1, 2036($sp)
	lw $a0, 2044($sp)
	lw $t0, -12($fp)
	move $t1, $v0
	move $v0, $t1
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $ra, -8($fp)
	jal read
	lw $ra, -8($fp)
	move $t0, $v0
	sw $ra, -12($fp)
	jal read
	lw $ra, -12($fp)
	move $t1, $v0
	sw $t0, -4($fp)
	sw $t1, -8($fp)
	move $a0, $t0
	move $a1, $t1
	sw $ra, 2032($sp)
	sw $fp, 2028($sp)
	jal gcd
	lw $fp, 2028($sp)
	lw $ra, 2032($sp)
	lw $a1, 2044($sp)
	lw $a0, 2040($sp)
	lw $t0, -4($fp)
	lw $t1, -8($fp)
	move $t2, $v0
	sw $ra, -16($fp)
	move $a0, $t2
	jal write
	lw $ra, -16($fp)
	move $v0, $0
	jr $ra
