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

bbb:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	subu $v1, $fp, 36
	move $t0, $v1
	sw $t0, -36($fp)
	addi $t1, $t0, 20
	li $t2, 6
	sw $t2, 0($t1)
	addi $t3, $t0, 24
	li $t4, 7
	sw $t4, 0($t3)
	addi $t5, $t0, 20
	lw $t6, 0($t5)
	sw $t6, -52($fp)
	addi $t7, $t0, 24
	lw $s0, 0($t7)
	sw $s0, -60($fp)
	add $s1, $t6, $s0
	move $v0, $s1
	addi $sp, $sp, 2048
	jr $ra

main:
	subu $sp, $sp, 2048
	addi $fp, $sp, 2048
	sw $ra, 2040($sp)
	sw $fp, 2036($sp)
	jal bbb
	lw $fp, 2036($sp)
	lw $ra, 2040($sp)
	move $t0, $v0
	sw $ra, -8($fp)
	move $a0, $t0
	jal write
	lw $ra, -8($fp)
	move $v0, $0
	jr $ra
