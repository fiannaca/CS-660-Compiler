################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test7.c.asm
# Input file:   tests/test7.c.tac
# Generated on: Tue May 14 22:15:05 2013
#
################################################################################

	.include	"macros.asm"

	.data
spills:	.space	80

	.text
	.globl	main

	jal	main
	done

	# 3AC For the Input Code File: tests/test7.c

	.ent	swap
swap:	subu	$sp, $sp, 16
	sw	$ra, 12($sp)
	sw	$a0, 4($sp)
	sw	$a1, 8($sp)
	lw 	$t1, 8($sp)
	lw	$t0, ($t1)

	print_str("The value of tmp is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
	lw 	$t2, 4($sp)
	lw	$t0, ($t2)
	sw	$t0, ($t1)
	sw 	$t1, 8($sp)
	lw 	$t0, 0($sp)
	sw	$t0, ($t2)
	sw 	$t0, 0($sp)
	sw 	$t2, 4($sp)
	lw	$ra, 12($sp)
	addu	$sp, $sp, 16
	jr	$ra
	.end	swap


	.ent	main
main:	subu	$sp, $sp, 44
	sw	$ra, 40($sp)
	li	$t0, 5
	add	$t1, $sp, 0
	li	$t2, 0
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 5
	sw	$t1, ($t2)
	add	$t1, $sp, 0
	li	$t2, 1
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 4
	sw	$t1, ($t2)
	add	$t1, $sp, 0
	li	$t2, 2
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 3
	sw	$t1, ($t2)
	add	$t1, $sp, 0
	li	$t2, 3
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 2
	sw	$t1, ($t2)
	add	$t1, $sp, 0
	li	$t2, 4
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 1
	sw	$t1, ($t2)
L0000:	li	$t1, 0

	print_str("The value of swapped is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 24($sp)
	li	$t1, 1

	print_str("The value of i is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 28($sp)
L0002:	li	$t1, 5
	lw 	$t2, 28($sp)
	slt	$t3, $t2, $t1
	sw 	$t2, 28($sp)
	beq	$t3, 0, L0003
	add	$t1, $sp, 0
	li	$t2, 1
	lw 	$t3, 28($sp)
	sub	$t4, $t3, $t2
	sw 	$t3, 28($sp)
	li	$t2, 4
	mult	$t4, $t2
	mflo	$t3
	add	$t2, $t1, $t3
	lw	$t1, ($t2)

	print_str("The value of a is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 32($sp)
	add	$t1, $sp, 0
	li	$t3, 4
	lw 	$t4, 28($sp)
	mult	$t4, $t3
	mflo	$t5
	sw 	$t4, 28($sp)
	add	$t3, $t1, $t5
	lw	$t1, ($t3)

	print_str("The value of b is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 36($sp)
	lw 	$t1, 32($sp)
	lw 	$t4, 36($sp)
	sgt	$t5, $t1, $t4
	sw 	$t1, 32($sp)
	sw 	$t4, 36($sp)
	beq	$t5, 0, L0004
	add	$t1, $sp, 0
	li	$t4, 1
	lw 	$t5, 28($sp)
	sub	$t6, $t5, $t4
	sw 	$t5, 28($sp)
	li	$t4, 4
	mult	$t6, $t4
	mflo	$t5
	add	$t4, $t1, $t5
	add	$t1, $sp, 0
	li	$t5, 4
	lw 	$t6, 28($sp)
	mult	$t6, $t5
	mflo	$t7
	sw 	$t6, 28($sp)
	add	$t5, $t1, $t7
	add	$a0, $zero, $t5
	add	$a1, $zero, $t4
	jal	swap
	li	$t1, 1

	print_str("The value of swapped is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 24($sp)
L0004:	li	$t1, 1
	lw 	$t4, 28($sp)
	add	$t5, $t1, $t4
	sw 	$t4, 28($sp)

	print_str("The value of i is: ")
	print_int($t5)
	print_newline

	sw 	$t5, 28($sp)
	b	L0002
L0003:	lw 	$t1, 24($sp)
	beq	$t1, 0, L0001
	sw 	$t1, 24($sp)
	b	L0000
L0001:	li	$t1, 0
	add	$v0, $zero, $t1
	lw	$ra, 40($sp)
	addu	$sp, $sp, 44
	jr	$ra
	.end	main

