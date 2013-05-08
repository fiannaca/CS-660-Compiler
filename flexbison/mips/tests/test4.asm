################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test4.asm
# Input file:   tests/test4.tac
# Generated on: Wed May  8 14:35:49 2013
#
################################################################################

	.include "macros.asm"

	.data
spills:	.space 80

	# 3AC For the Input Code File: tests/test4.c

	.text
	.globl	main

	jal	main
	done

	.ent	main
main:	subu	$sp, $sp, 12
	sw	$31, 8($sp)
	li	$t0, 1
	sw 	$t0, 4($sp)

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	li	$t0, 0
	sw 	$t0, 0($sp)

	print_str("The value of i is: ")
	print_int($t0)
	print_newline

L00000000:	li	$t0, 10
	lw 	$t1, 0($sp)
	slt	$t2, $t1, $t0
	sw 	$t1, 0($sp)
	lw 	$t3, 0($sp)
	add	$t4, $t1, $t3
	sw 	$t3, 0($sp)
	lw 	$t3, 0($sp)

	print_str("The value of I00000010 is: ")
	print_int($t3)
	print_newline

	beq	$t3, 0, L00000001
	sw 	$t3, 0($sp)
	li	$t3, 2
	lw 	$t5, 4($sp)
	add	$t6, $t3, $t5
	sw 	$t5, 4($sp)
	sw 	$t6, 4($sp)

	print_str("The value of a is: ")
	print_int($t6)
	print_newline

	b	L00000000
L00000001:	li	$t5, 1
	sw 	$t5, 4($sp)

	print_str("The value of a is: ")
	print_int($t5)
	print_newline

L00000002:	li	$t5, 10
	lw 	$t6, 4($sp)
	slt	$t7, $t6, $t5
	sw 	$t6, 4($sp)
	beq	$t7, 0, L00000003
	li	$t6, 2
	sw 	$t0, spills + 0

	lw 	$t0, 4($sp)
	sw 	$t2, spills + 4

	add	$t2, $t6, $t0
	sw 	$t0, 4($sp)
	lw 	$t0, spills + 0

	sw 	$t2, 4($sp)
	lw 	$t2, spills + 4


	print_str("The value of a is: ")
	print_int($t2)
	print_newline

	b	L00000002
L00000003:	sw 	$t1, spills + 0

	li	$t1, 1
	sw 	$t1, 4($sp)
	lw 	$t1, spills + 0


	print_str("The value of a is: ")
	print_int($t1)
	print_newline

L00000004:	sw 	$t4, spills + 0

	li	$t4, 2
	sw 	$t3, spills + 4

	lw 	$t3, 4($sp)
	sw 	$t5, spills + 8

	add	$t5, $t4, $t3
	sw 	$t3, 4($sp)
	lw 	$t3, spills + 0

	sw 	$t5, 4($sp)
	lw 	$t5, spills + 4


	print_str("The value of a is: ")
	print_int($t5)
	print_newline

	sw 	$t7, spills + 0

	li	$t7, 10
	sw 	$t6, spills + 4

	lw 	$t6, 4($sp)
	sw 	$t0, spills + 12

	slt	$t0, $t6, $t7
	sw 	$t6, 4($sp)
	lw 	$t6, spills + 0

	beq	$t0, 0, L00000005
	b	L00000004
L00000005:	sw 	$t2, spills + 0

	li	$t2, 0
	lw	$31, 8($sp)
	addu	$sp, $sp, 12
	jr	$31
	.end	main

