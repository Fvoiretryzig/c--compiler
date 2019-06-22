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
	li $v1, 1
	move $v0, $v1
	addi $sp, $sp, 2048
	jr $ra

func:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $ra, 2040($sp)
	sw $fp, 2036($sp)
	jal a
	lw $fp, 2036($sp)
	lw $ra, 2040($sp)
	move $t0, $v0
	sw $t0, -4($fp)
	beq $t0, $zero, label1
	li $v1, 2
	move $v0, $v1
	addi $sp, $sp, 2048
	jr $ra
	sw $t0, -4($fp)
label1:
	li $v1, 3
	move $v0, $v1
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	subu $v1, $fp, 12
	move $t0, $v1
	sw $t0, -12($fp)
	sw $t0, -12($fp)
	sw $ra, 2028($sp)
	sw $fp, 2024($sp)
	jal func
	lw $fp, 2024($sp)
	lw $ra, 2028($sp)
	lw $t0, -12($fp)
	move $t1, $v0
	move $v0, $0
	jr $ra
