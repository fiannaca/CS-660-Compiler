################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test3.asm
# Input file:   tests/test3.tac
# Generated on: Wed May  8 12:55:09 2013
#
################################################################################

	.include "macros.asm"

	.data
spills:	.space 80

	# 3AC For the Input Code File: tests/test3.c

	.text
	.globl	main

	jal	main
	done

	.ent	main
main:	subu	$sp, $sp, 8
	sw	$31, 4($sp)
	li	$t0, 1
	sw 	$t0, 0($sp)

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	li	$t0, 2
	lw 	$t1, 0($sp)
	seq	$t2, $t0, $t1
	sw 	$t1, 0($sp)
	beq	$t2, 0, L00000000
	li	$t1, 0
	sw 	$t1, 0($sp)

	print_str("The value of a is: ")
	print_int($t1)
	print_newline

	b	L00000001
L00000000:	li	$t1, 1
	sw 	$t1, 0($sp)

	print_str("The value of a is: ")
	print_int($t1)
	print_newline

L00000001:	li	$t1, 0
	lw	$31, 4($sp)
	addu	$sp, $sp, 8
	jr	$31
	.end	main

