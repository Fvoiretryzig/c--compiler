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

a:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	li $t0, 4
	sw $t0, -4($fp)
	addi $t1, $t0, 6
	sw $t1, -8($fp)
	move $v0, $t1
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	li $t0, 40
	sw $t0, -4($fp)
	sw $ra, 2036($sp)
	sw $fp, 2032($sp)
	jal a
	lw $fp, 2032($sp)
	lw $ra, 2036($sp)
	lw $t0, -4($fp)
	move $t0, $v0
	sw $ra, -12($fp)
	move $a0, $t0
	jal write
	lw $ra, -12($fp)
	move $v0, $0
	jr $ra
