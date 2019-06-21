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

b:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	subu $v1, $fp, 32
	move $t1, $v1
	addi $t0, $t1, 20
	sw $t0, -36($fp)
	li $t2, 6
	sw $t2, 0($t0)
	addi $t3, $t1, 20
	sw $t3, -40($fp)
	lw $t4, 0($t3)
	sw $t4, -44($fp)
	lw $t4, 0($t4)
	move $v0, $t4
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $ra, 2040($sp)
	sw $fp, 2036($sp)
	jal b
	lw $fp, 2036($sp)
	lw $ra, 2040($sp)
	move $t0, $v0
	move $v0, $0
	jr $ra
