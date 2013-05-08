################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test1_2.asm
# Input file:   tests/test1_2.tac
# Generated on: Wed May  8 09:35:38 2013
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
	add	$t2, $t0, $t1
	sw 	$t0, 8($sp)
	sw 	$t1, 0($sp)
	sw 	$t2, 4($sp)

	print_str("The value of k is: ")
	print_int($t2)
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
	add	$t2, $t0, $t1
	sw 	$t0, 8($sp)
	sw 	$t1, 0($sp)
	sw 	$t2, 4($sp)

	print_str("The value of k is: ")
	print_int($t2)
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
	add	$t2, $t0, $t1
	sw 	$t0, 8($sp)
	sw 	$t1, 0($sp)
	sw 	$t2, 4($sp)

	print_str("The value of k is: ")
	print_int($t2)
	print_newline

	li	$t0, 0
	lw	$31, 12($sp)
	addu	$sp, $sp, 16
	jr	$31
	.end	main

