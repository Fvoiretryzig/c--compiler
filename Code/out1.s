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
	li $t0, 2
	sw $t0, -4($fp)
	li $t1, 1
	sw $t1, -8($fp)
	li $t2, 0
	sw $t2, -12($fp)
	sw $ra, -20($fp)
	jal read
	lw $ra, -20($fp)
	move $t3, $v0
label1:
	sw $t0, -4($fp)
	sw $t1, -8($fp)
	sw $t2, -12($fp)
	sw $t3, -16($fp)
	lw $t0, -12($fp)
	lw $t1, -16($fp)
	bge $t0, $t1, label2
	sw $t0, -12($fp)
	sw $t1, -16($fp)
	lw $t1, -4($fp)
	lw $t2, -8($fp)
	add $t0, $t1, $t2
	sw $t0, -20($fp)
	sw $ra, -24($fp)
	move $a0, $t2
	jal write
	lw $ra, -24($fp)
	move $t1, $t2
	move $t2, $t0
	lw $t3, -12($fp)
	addi $t3, $t3, 1
	j label1
	sw $t0, -20($fp)
	sw $t1, -4($fp)
	sw $t2, -8($fp)
	sw $t3, -12($fp)
label2:
	move $v0, $0
	jr $ra
