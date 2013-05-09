################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test1.asm
# Input file:   tests/test1.tac
# Generated on: Wed May  8 14:49:44 2013
#
################################################################################

	.include "macros.asm"

	.data
spills:	.space 80

	# 3AC For the Input Code File: tests/test1.c

	.text
	.globl	main

	jal	main
	done

	.ent	main
main:	subu	$sp, $sp, 16
	sw	$31, 12($sp)
	li	$t0, 1
	sw 	$t0, 8($sp)

	print_str("The value of i is: ")
	print_int($t0)
	print_newline

	li	$t0, 2
	sw 	$t0, 0($sp)

	print_str("The value of j is: ")
	print_int($t0)
	print_newline

	lw 	$t0, 0($sp)
	lw 	$t1, 8($sp)
	add	$t2, $t0, $t1
	sw 	$t0, 0($sp)
	sw 	$t1, 8($sp)
	sw 	$t2, 4($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	lw 	$t0, 8($sp)
	lw 	$t1, 0($sp)
	sub	$t2, $t1, $t0
	sw 	$t0, 8($sp)
	sw 	$t1, 0($sp)
	sw 	$t2, 4($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	lw 	$t0, 0($sp)
	lw 	$t1, 8($sp)
	mult	$t0, $t1
	mflo	$t2
	sw 	$t0, 0($sp)
	sw 	$t1, 8($sp)
	sw 	$t2, 4($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	lw 	$t0, 8($sp)
	lw 	$t1, 0($sp)
	div	$t0, $t1
	mflo	$t2
	sw 	$t0, 8($sp)
	sw 	$t1, 0($sp)
	sw 	$t2, 4($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	li	$t0, 1
	li	$t1, 2
	add	$t2, $t1, $t0
	li	$t3, 3
	li	$t4, 4
	add	$t5, $t4, $t3
	add	$t6, $t5, $t2
	li	$t7, 5
	sw 	$t0, spills + 0

	li	$t0, 6
	sw 	$t1, spills + 4

	add	$t1, $t0, $t7
	sw 	$t2, spills + 8

	add	$t2, $t1, $t6
	sw 	$t3, spills + 12

	li	$t3, 7
	sw 	$t4, spills + 16

	li	$t4, 8
	sw 	$t5, spills + 20

	add	$t5, $t4, $t3
	sw 	$t6, spills + 24

	add	$t6, $t5, $t2
	sw 	$t7, spills + 28

	li	$t7, 9
	sw 	$t0, spills + 32

	li	$t0, 10
	sw 	$t1, spills + 36

	add	$t1, $t0, $t7
	sw 	$t2, spills + 40

	add	$t2, $t1, $t6
	sw 	$t2, 4($sp)
	#lw 	$t2, spills + 0


	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	sw 	$t3, spills + 0

	li	$t3, 0
	lw	$31, 12($sp)
	addu	$sp, $sp, 16
	jr	$31
	.end	main

