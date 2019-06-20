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
	li $v0, 1	syscall
	li $v0, 4	la $a0, _ret
	syscall
	move $v0, $0
	jr $ra

main:
	subu $sp, $sp, 1024
	sw $ra, 1020($sp)
	sw $fp, 1016($sp)
	addi $fp, $sp, 1024
	lw $t0, -12($fp)
	li $t0, 40
	lw $t1, -16($fp)
	sw $ra, -12($fp)
	move $a0, $t1
	jal write
