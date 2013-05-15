################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test6.c.asm
# Input file:   tests/test6.c.tac
# Generated on: Tue May 14 22:15:01 2013
#
################################################################################

	.include	"macros.asm"

	.data
spills:	.space	80

	.text
	.globl	main

	jal	main
	done

	# 3AC For the Input Code File: tests/test6.c

	.ent	main
main:	subu	$sp, $sp, 44
	sw	$ra, 40($sp)
	li	$t0, 5
	add	$t1, $sp, 4
	li	$t2, 0
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 5
	sw	$t1, ($t2)
	add	$t1, $sp, 4
	li	$t2, 1
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 4
	sw	$t1, ($t2)
	add	$t1, $sp, 4
	li	$t2, 2
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 3
	sw	$t1, ($t2)
	add	$t1, $sp, 4
	li	$t2, 3
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 2
	sw	$t1, ($t2)
	add	$t1, $sp, 4
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

	sw 	$t1, 0($sp)
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
	add	$t1, $sp, 4
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
	add	$t1, $sp, 4
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
	add	$t1, $sp, 4
	li	$t4, 1
	lw 	$t5, 28($sp)
	sub	$t6, $t5, $t4
	sw 	$t5, 28($sp)
	li	$t4, 4
	mult	$t6, $t4
	mflo	$t5
	add	$t4, $t1, $t5
	lw	$t1, ($t4)

	print_str("The value of tmp is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 24($sp)
	add	$t1, $sp, 4
	li	$t5, 1
	lw 	$t6, 28($sp)
	sub	$t7, $t6, $t5
	sw 	$t6, 28($sp)
	li	$t5, 4
	mult	$t7, $t5
	mflo	$t6
	add	$t5, $t1, $t6
	add	$t1, $sp, 4
	li	$t6, 4
	lw 	$t7, 28($sp)
	sw 	$t0, spills + 0

	mult	$t7, $t6
	mflo	$t0
	sw 	$t7, 28($sp)
	lw 	$t7, spills + 0

	add	$t6, $t1, $t0
	lw	$t0, ($t6)
	sw	$t0, ($t5)
	add	$t0, $sp, 4
	li	$t1, 4
	lw 	$t5, 28($sp)
	sw 	$t2, spills + 0

	mult	$t5, $t1
	mflo	$t2
	sw 	$t5, 28($sp)
	lw 	$t5, spills + 0

	add	$t1, $t0, $t2
	lw 	$t0, 24($sp)
	sw	$t0, ($t1)
	sw 	$t0, 24($sp)
	li	$t0, 1

	print_str("The value of swapped is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
L0004:	li	$t0, 1
	lw 	$t1, 28($sp)
	add	$t2, $t0, $t1
	sw 	$t1, 28($sp)

	print_str("The value of i is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 28($sp)
	b	L0002
L0003:	li	$t0, 1
	lw 	$t1, 0($sp)
	seq	$t2, $t0, $t1
	sw 	$t1, 0($sp)
	beq	$t2, 0, L0001
	b	L0000
L0001:	li	$t0, 0
	add	$v0, $zero, $t0
	lw	$ra, 40($sp)
	addu	$sp, $sp, 44
	jr	$ra
	.end	main

