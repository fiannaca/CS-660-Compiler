################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test2.c.asm
# Input file:   tests/test2.c.tac
# Generated on: Tue May 14 22:14:45 2013
#
################################################################################

	.include	"macros.asm"

	.data
spills:	.space	80

	.text
	.globl	main

	jal	main
	done

	# 3AC For the Input Code File: tests/test2.c

	.ent	main
main:	subu	$sp, $sp, 44
	sw	$ra, 40($sp)
	li	$t0, 3
	li	$t1, 2
	li	$t2, 3
	add	$t3, $sp, 28
	li	$t4, 0
	li	$t5, 4
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 3
	sw	$t3, ($t4)
	add	$t3, $sp, 28
	li	$t4, 1
	li	$t5, 4
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 2
	sw	$t3, ($t4)
	add	$t3, $sp, 28
	li	$t4, 2
	li	$t5, 4
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 1
	sw	$t3, ($t4)
	add	$t3, $sp, 0
	li	$t4, 0
	li	$t5, 12
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 0
	li	$t5, 4
	mult	$t3, $t5
	mflo	$t6
	add	$t3, $t4, $t6
	li	$t4, 4
	sw	$t4, ($t3)
	add	$t3, $sp, 0
	li	$t4, 0
	li	$t5, 12
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 1
	li	$t5, 4
	mult	$t3, $t5
	mflo	$t6
	add	$t3, $t4, $t6
	li	$t4, 4
	sw	$t4, ($t3)
	add	$t3, $sp, 0
	li	$t4, 0
	li	$t5, 12
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 2
	li	$t5, 4
	mult	$t3, $t5
	mflo	$t6
	add	$t3, $t4, $t6
	li	$t4, 4
	sw	$t4, ($t3)
	add	$t3, $sp, 0
	li	$t4, 1
	li	$t5, 12
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 0
	li	$t5, 4
	mult	$t3, $t5
	mflo	$t6
	add	$t3, $t4, $t6
	li	$t4, 4
	sw	$t4, ($t3)
	add	$t3, $sp, 0
	li	$t4, 1
	li	$t5, 12
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 1
	li	$t5, 4
	mult	$t3, $t5
	mflo	$t6
	add	$t3, $t4, $t6
	li	$t4, 4
	sw	$t4, ($t3)
	add	$t3, $sp, 0
	li	$t4, 1
	li	$t5, 12
	mult	$t4, $t5
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 2
	li	$t5, 4
	mult	$t3, $t5
	mflo	$t6
	add	$t3, $t4, $t6
	li	$t4, 4
	sw	$t4, ($t3)
	li	$t3, 3

	print_str("The value of temp is: ")
	print_int($t3)
	print_newline

	sw 	$t3, 24($sp)
	add	$t3, $sp, 28
	li	$t4, 2
	lw 	$t5, 24($sp)
	sub	$t6, $t5, $t4
	sw 	$t5, 24($sp)
	li	$t4, 4
	mult	$t6, $t4
	mflo	$t5
	add	$t4, $t3, $t5
	li	$t3, 3
	sw	$t3, ($t4)
	add	$t3, $sp, 28
	li	$t4, 1
	lw 	$t5, 24($sp)
	sub	$t6, $t5, $t4
	sw 	$t5, 24($sp)
	li	$t4, 4
	mult	$t6, $t4
	mflo	$t5
	add	$t4, $t3, $t5
	li	$t3, 3
	sw	$t3, ($t4)
	li	$t3, 2

	print_str("The value of temp is: ")
	print_int($t3)
	print_newline

	sw 	$t3, 24($sp)
	add	$t3, $sp, 0
	li	$t4, 1
	lw 	$t5, 24($sp)
	sub	$t6, $t5, $t4
	sw 	$t5, 24($sp)
	li	$t4, 12
	mult	$t6, $t4
	mflo	$t5
	add	$t4, $t3, $t5
	lw 	$t3, 24($sp)
	sub	$t5, $t3, $t3
	sw 	$t3, 24($sp)
	li	$t3, 4
	mult	$t5, $t3
	mflo	$t6
	add	$t3, $t4, $t6
	add	$t4, $sp, 28
	li	$t5, 4
	lw 	$t6, 24($sp)
	mult	$t6, $t5
	mflo	$t7
	sw 	$t6, 24($sp)
	add	$t5, $t4, $t7
	lw	$t4, ($t5)
	sw	$t4, ($t3)
	add	$t3, $sp, 0
	li	$t4, 1
	lw 	$t6, 24($sp)
	sub	$t7, $t6, $t4
	sw 	$t6, 24($sp)
	li	$t4, 12
	mult	$t7, $t4
	mflo	$t6
	add	$t4, $t3, $t6
	li	$t3, 1
	lw 	$t6, 24($sp)
	sub	$t7, $t6, $t3
	sw 	$t6, 24($sp)
	li	$t3, 4
	mult	$t7, $t3
	mflo	$t6
	add	$t3, $t4, $t6
	add	$t4, $sp, 28
	li	$t6, 4
	lw 	$t7, 24($sp)
	sw 	$t0, spills + 0

	mult	$t7, $t6
	mflo	$t0
	sw 	$t7, 24($sp)
	lw 	$t7, spills + 0

	add	$t6, $t4, $t0
	lw	$t0, ($t6)
	sw	$t0, ($t3)
	add	$t0, $sp, 0
	li	$t3, 1
	lw 	$t4, 24($sp)
	sw 	$t1, spills + 0

	sub	$t1, $t4, $t3
	lw 	$t3, spills + 0

	sw 	$t4, 24($sp)
	li	$t4, 12
	sw 	$t2, spills + 0

	mult	$t1, $t4
	mflo	$t2
	lw 	$t1, spills + 0

	add	$t4, $t0, $t2
	li	$t0, 4
	lw 	$t2, 24($sp)
	sw 	$t5, spills + 0

	mult	$t2, $t0
	mflo	$t5
	sw 	$t2, 24($sp)
	lw 	$t2, spills + 0

	add	$t0, $t4, $t5
	add	$t4, $sp, 28
	li	$t5, 4
	sw 	$t7, spills + 0

	lw 	$t7, 24($sp)
	sw 	$t6, spills + 4

	mult	$t7, $t5
	mflo	$t6
	sw 	$t7, 24($sp)
	lw 	$t7, spills + 0

	lw 	$t5, spills + 4

	sw 	$t3, spills + 0

	add	$t3, $t4, $t6
	lw 	$t4, spills + 0

	lw	$t6, ($t3)
	sw	$t6, ($t0)
	li	$t0, 0
	add	$v0, $zero, $t0
	lw	$ra, 40($sp)
	addu	$sp, $sp, 44
	jr	$ra
	.end	main

