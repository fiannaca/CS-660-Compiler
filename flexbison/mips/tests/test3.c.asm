################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test3.c.asm
# Input file:   tests/test3.c.tac
# Generated on: Tue May 14 22:14:51 2013
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
	li	$t0, 4
	li	$t1, 5
	add	$t2, $t1, $t0
	li	$t0, 2
	li	$t1, 3
	add	$t3, $t1, $t0
	mult	$t3, $t2
	mflo	$t0

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
L0000:	li	$t0, 1
	neg	$t1, $t0

	print_str("The value of a is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 0($sp)
L0001:	li	$t1, 0
	add	$v0, $zero, $t1
	lw	$ra, 4($sp)
	addu	$sp, $sp, 8
	jr	$ra
	.end	main

