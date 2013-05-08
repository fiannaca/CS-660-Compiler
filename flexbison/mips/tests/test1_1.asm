################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test1_1.asm
# Input file:   tests/test1_1.tac
# Generated on: Wed May  8 08:16:20 2013
#
################################################################################

	.include "macros.asm"

	.data
spills:	.space 80

	#3AC For the Input Code File: tests/test1.c

	.text
	.globl	main

	jal	main
	done

	.ent	main
main:	subu	$sp, $sp, 16
	sw	$31, 12($sp)
	li	$t0, 1
	sw 	$t0, 8($sp)

	#Output the stored value to verify program correctness...
	print_str("The value of i is: ")
	print_int($t0)
	print_newline

	li	$t1, 2
	sw 	$t1, 0($sp)

	#Output the stored value to verify program correctness...
	print_str("The value of j is: ")
	print_int($t1)
	print_newline

	lw 	$t2, 0($sp)
	lw 	$t3, 8($sp)
	add	$t4, $t2, $t3
	sw 	$t2, 0($sp)
	sw 	$t3, 8($sp)
	sw 	$t4, 4($sp)

	#Output the stored value to verify program correctness...
	print_str("The value of k is: ")
	print_int($t4)
	print_newline

	lw 	$t2, 8($sp)
	lw 	$t3, 0($sp)
	sub	$t5, $t3, $t2
	sw 	$t2, 8($sp)
	sw 	$t3, 0($sp)
	sw 	$t5, 4($sp)

	#Output the stored value to verify program correctness...
	print_str("The value of k is: ")
	print_int($t5)
	print_newline

	lw 	$t2, 0($sp)
	lw 	$t3, 8($sp)
	mult	$t2, $t3
	mflo	$t6
	sw 	$t2, 0($sp)
	sw 	$t3, 8($sp)
	sw 	$t6, 4($sp)

	#Output the stored value to verify program correctness...
	print_str("The value of k is: ")
	print_int($t6)
	print_newline

	lw 	$t2, 8($sp)
	lw 	$t3, 0($sp)
	add	$t7, $t2, $t3
	sw 	$t2, 8($sp)
	sw 	$t3, 0($sp)
	sw 	$t7, 4($sp)

	#Output the stored value to verify program correctness...
	print_str("The value of k is: ")
	print_int($t7)
	print_newline

	li	$t2, 0
	lw	$31, 12($sp)
	addu	$sp, $sp, 16
	jr	$31
	.end	main

