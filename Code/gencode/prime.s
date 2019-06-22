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
	mul $t1, $t0, $a1
	sub $t2, $a0, $t1
	move $v0, $t2
	addi $sp, $sp, 2048
	jr $ra

is_prime:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $a0, -4($fp)
	li $t0, 2
	sw $t0, -8($fp)
label1:
	mul $t1, $t0, $t0
	sw $t0, -8($fp)
	sw $t1, -12($fp)
	bgt $t1, $a0, label2
	sw $t1, -12($fp)
	sw $a0, 2044($sp)
	move $a1, $t0
	sw $ra, 2028($sp)
	sw $fp, 2024($sp)
	jal modulo
	lw $fp, 2024($sp)
	lw $ra, 2028($sp)
	lw $a0, 2044($sp)
	lw $t0, -8($fp)
	lw $t1, -12($fp)
	move $t2, $v0
	sw $t0, -8($fp)
	sw $t2, -16($fp)
	bne $t2, $zero, label3
	move $v0, $0
	addi $sp, $sp, 2048
	jr $ra
	sw $t2, -16($fp)
label3:
	addi $t0, $t0, 1
	sw $t0, -8($fp)
	j label1
label2:
	li $v1, 1
	move $v0, $v1
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	li $t0, 2
	sw $t0, -4($fp)
label4:
	li $t1, 100
	bgt $t0, $t1, label5
	sw $t0, -4($fp)
	move $a0, $t0
	sw $ra, 2036($sp)
	sw $fp, 2032($sp)
	jal is_prime
	lw $fp, 2032($sp)
	lw $ra, 2036($sp)
	lw $t0, -4($fp)
	move $t2, $v0
	sw $t0, -4($fp)
	sw $t2, -8($fp)
	beq $t2, $zero, label6
	sw $ra, -12($fp)
	move $a0, $t0
	jal write
	lw $ra, -12($fp)
	sw $t0, -4($fp)
	sw $t2, -8($fp)
label6:
	addi $t0, $t0, 1
	sw $t0, -4($fp)
	j label4
label5:
	move $v0, $0
	jr $ra
