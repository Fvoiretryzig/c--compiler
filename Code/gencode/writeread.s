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
	sw $ra, -8($fp)
	jal read
	lw $ra, -8($fp)
	move $t0, $v0
	sw $ra, -8($fp)
	move $a0, $t0
	jal write
	lw $ra, -8($fp)
	move $v0, $0
	jr $ra
