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
	beq $t0, $zero, label1
	sw $t0, -4($fp)
	j label2
label1:
	li $t0, 1
	sw $ra, -8($fp)
	move $a0, $t0
	jal write
	lw $ra, -8($fp)
	j label3
label2:
	lw $t0, -4($fp)
	bne $t0, $zero, label4
	sw $t0, -4($fp)
	j label5
label4:
	addi $t0, $t0, -1
	sw $ra, -12($fp)
	move $a0, $t0
	jal write
	lw $ra, -12($fp)
	j label6
	sw $t0, -8($fp)
label5:
	sw $ra, -12($fp)
	move $a0, $zero
	jal write
	lw $ra, -12($fp)
label6:
label3:
	move $v0, $0
	jr $ra
