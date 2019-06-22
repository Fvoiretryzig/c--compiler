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
	sw $ra, -12($fp)
	jal read
	lw $ra, -12($fp)
	move $t1, $v0
	sw $t0, -4($fp)
	sw $t1, -8($fp)
	beq $t1, $zero, label2
	sw $ra, -16($fp)
	jal read
	lw $ra, -16($fp)
	move $t2, $v0
	sw $t1, -8($fp)
	sw $t2, -12($fp)
	bne $t2, $zero, label1
	sw $t2, -12($fp)
	j label2
label1:
	li $t0, 1
	sw $t0, -4($fp)
label2:
	sw $ra, -16($fp)
	move $a0, $t0
	jal write
	lw $ra, -16($fp)
	move $v0, $0
	jr $ra
