################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test1.asm
# Input file:   tests/test1.tac
# Generated on: Fri May 10 13:29:09 2013
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

	print_str("The value of i is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 8($sp)
	li	$t0, 2

	print_str("The value of j is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
	lw 	$t0, 0($sp)
	lw 	$t1, 8($sp)
	add	$t2, $t0, $t1
	sw 	$t0, 0($sp)
	sw 	$t1, 8($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 4($sp)
	lw 	$t0, 8($sp)
	lw 	$t1, 0($sp)
	sub	$t2, $t1, $t0
	sw 	$t0, 8($sp)
	sw 	$t1, 0($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 4($sp)
	lw 	$t0, 0($sp)
	lw 	$t1, 8($sp)
	mult	$t0, $t1
	mflo	$t2
	sw 	$t0, 0($sp)
	sw 	$t1, 8($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 4($sp)
	lw 	$t0, 8($sp)
	lw 	$t1, 0($sp)
	div	$t0, $t1
	mflo	$t2
	sw 	$t0, 8($sp)
	sw 	$t1, 0($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 4($sp)
	li	$t0, 1
	li	$t1, 2
	add	$t2, $t1, $t0
	li	$t0, 3
	li	$t1, 4
	add	$t3, $t1, $t0
	add	$t0, $t3, $t2
	li	$t1, 5
	li	$t2, 6
	add	$t3, $t2, $t1
	li	$t1, 7
	li	$t2, 8
	add	$t4, $t2, $t1
	add	$t1, $t4, $t3
	add	$t2, $t1, $t0
	li	$t0, 9
	li	$t1, 10
	add	$t3, $t1, $t0
	add	$t0, $t3, $t2

	print_str("The value of k is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 4($sp)
	li	$t0, 0
	lw	$31, 12($sp)
	addu	$sp, $sp, 16
	jr	$31
	.end	main

