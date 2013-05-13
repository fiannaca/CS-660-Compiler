################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test2.asm
# Input file:   tests/test2.tac
# Generated on: Sun May 12 19:44:46 2013
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
main:	subu	$sp, $sp, 16
	sw	$ra, 12($sp)
	li	$t0, 3
	add	$t1, $sp, 0
	li	$t2, 0
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 3
	sw	$t1, ($t2)
	add	$t1, $sp, 0
	li	$t2, 1
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 2
	sw	$t1, ($t2)
	add	$t1, $sp, 0
	li	$t2, 2
	li	$t3, 4
	mult	$t2, $t3
	mflo	$t4
	add	$t2, $t1, $t4
	li	$t1, 1
	sw	$t1, ($t2)
	li	$t1, 0
	lw	$ra, 12($sp)
	addu	$sp, $sp, 16
	jr	$ra
	.end	main

