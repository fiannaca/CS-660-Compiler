################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test3.asm
# Input file:   tests/test3.tac
# Generated on: Sun May 12 19:44:49 2013
#
################################################################################

	.include	"macros.asm"

	.data
spills:	.space	80

	.text
	.globl	main

	jal	main
	done

	# 3AC For the Input Code File: tests/test3.c

	.ent	main
main:	subu	$sp, $sp, 8
	sw	$ra, 4($sp)
	li	$t0, 1

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
	li	$t0, 2
	lw 	$t1, 0($sp)
	seq	$t2, $t0, $t1
	sw 	$t1, 0($sp)
	beq	$t2, 0, L0000
	li	$t0, 0

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
	b	L0001
L0000:	li	$t0, 3

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
L0001:	li	$t0, 0
	lw	$ra, 4($sp)
	addu	$sp, $sp, 8
	jr	$ra
	.end	main

