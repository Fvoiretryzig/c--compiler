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

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	li $t0, 0
	sw $t0, -4($fp)
	li $t1, 1
	sw $t1, -8($fp)
	li $t2, 0
	sw $t2, -12($fp)
	sw $ra, -20($fp)
	jal read
	lw $ra, -20($fp)
	move $t3, $v0
	sw $t0, -4($fp)
	sw $t1, -8($fp)
	sw $t2, -12($fp)
	sw $t3, -16($fp)
label1:
	lw $t0, -12($fp)
	lw $t1, -16($fp)
	bge $t0, $t1, label2
	lw $t3, -4($fp)
	lw $t4, -8($fp)
	add $t2, $t3, $t4
	sw $t2, -20($fp)
	sw $ra, -24($fp)
	move $a0, $t4
	jal write
	lw $ra, -24($fp)
	move $t3, $t4
	move $t4, $t2
	addi $t0, $t0, 1
	sw $t0, -12($fp)
	sw $t1, -16($fp)
	sw $t2, -20($fp)
	sw $t3, -4($fp)
	sw $t4, -8($fp)
	j label1
label2:
	move $v0, $0
	jr $ra
