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
	sw $t3, -16($fp)
label1:
	bge $t2, $t3, label2
	add $t4, $t0, $t1
	sw $t4, -20($fp)
	sw $ra, -24($fp)
	move $a0, $t1
	jal write
	lw $ra, -24($fp)
	move $t0, $t1
	sw $t0, -4($fp)
	move $t1, $t4
	sw $t1, -8($fp)
	addi $t2, $t2, 1
	sw $t2, -12($fp)
	sw $t3, -16($fp)
	sw $t4, -20($fp)
	j label1
label2:
	move $v0, $0
	jr $ra
