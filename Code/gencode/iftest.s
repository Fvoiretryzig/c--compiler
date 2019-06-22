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

f:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $a0, -4($fp)
	sw $a1, -8($fp)
	sw $a2, -12($fp)
	bne $a0, $zero, label1
	bne $a1, $zero, label1
	beq $a2, $zero, label1
	li $a0, 4
	sw $a0, -4($fp)
	add $t0, $a0, $a1
	move $v0, $t0
	addi $sp, $sp, 2048
	jr $ra
	sw $t0, -16($fp)
label1:
	li $a2, 6
	sw $a2, -12($fp)
	move $v0, $a2
	addi $sp, $sp, 2048
	jr $ra
	move $v0, $0
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	li $t1, 5
	move $a0, $t1
	li $t2, 6
	move $a1, $t2
	li $t3, 7
	move $a2, $t3
	sw $ra, 2040($sp)
	sw $fp, 2036($sp)
	jal f
	lw $fp, 2036($sp)
	lw $ra, 2040($sp)
	move $t0, $v0
	sw $ra, -8($fp)
	move $a0, $t0
	jal write
	lw $ra, -8($fp)
	move $v0, $0
	jr $ra
