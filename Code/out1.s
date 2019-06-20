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
	subu $sp, $sp, 1024
	addi $fp, $sp, 1024
	li $t0, 40
	sw $ra, -8($fp)
	move $a0, $t0
	jal write
	lw $ra, -8($fp)
	move $v0, $0
	jr $ra
