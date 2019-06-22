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
	addi $t0, $zero, -9
	sw $t0, -4($fp)
	ble $t0, $zero, label1
	li $t1, 1
	sw $ra, -8($fp)
	move $a0, $t1
	jal write
	lw $ra, -8($fp)
	sw $t0, -4($fp)
	j label2
label1:
	bge $t0, $zero, label3
	addi $t2, $zero, -1
	sw $ra, -12($fp)
	move $a0, $t2
	jal write
	lw $ra, -12($fp)
	sw $t0, -4($fp)
	sw $t2, -8($fp)
	j label4
label3:
	sw $ra, -12($fp)
	move $a0, $zero
	jal write
	lw $ra, -12($fp)
label4:
label2:
	move $v0, $0
	jr $ra
