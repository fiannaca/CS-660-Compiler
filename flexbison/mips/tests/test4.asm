################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test4.asm
# Input file:   tests/test4.tac
# Generated on: Fri May 10 11:19:46 2013
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
	beq	$t2, 0, L00000001
	li	$t1, 2
	lw 	$t3, 4($sp)
	add	$t4, $t1, $t3
	sw 	$t3, 4($sp)
	sw 	$t4, 4($sp)

	print_str("The value of a is: ")
	print_int($t4)
	print_newline

	li	$t3, 1
	lw 	$t4, 0($sp)
	add	$t5, $t3, $t4
	sw 	$t4, 0($sp)
	sw 	$t5, 0($sp)

	print_str("The value of i is: ")
	print_int($t5)
	print_newline

	b	L00000000
L00000001:	li	$t4, 1
	sw 	$t4, 4($sp)

	print_str("The value of a is: ")
	print_int($t4)
	print_newline

L00000002:	li	$t4, 10
	lw 	$t5, 4($sp)
	slt	$t6, $t5, $t4
	sw 	$t5, 4($sp)
	beq	$t6, 0, L00000003
	li	$t5, 2
	lw 	$t7, 4($sp)
	sw 	$t0, spills + 0

	add	$t0, $t5, $t7
	sw 	$t7, 4($sp)
	lw 	$t7, spills + 0

	sw 	$t0, 4($sp)

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	b	L00000002
L00000003:	li	$t0, 1
	sw 	$t0, 4($sp)

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

L00000004:	li	$t0, 2
	sw 	$t2, spills + 0

	lw 	$t2, 4($sp)
	sw 	$t1, spills + 4

	add	$t1, $t0, $t2
	sw 	$t2, 4($sp)
	lw 	$t2, spills + 0

	sw 	$t1, 4($sp)
	lw 	$t1, spills + 4


	print_str("The value of a is: ")
	print_int($t1)
	print_newline

	sw 	$t3, spills + 0

	li	$t3, 10
	sw 	$t4, spills + 4

	lw 	$t4, 4($sp)
	sw 	$t6, spills + 8

	slt	$t6, $t4, $t3
	sw 	$t4, 4($sp)
	lw 	$t4, spills + 0

	beq	$t6, 0, L00000005
	b	L00000004
L00000005:	sw 	$t5, spills + 0

	li	$t5, 0
	lw	$31, 8($sp)
	addu	$sp, $sp, 12
	jr	$31
	.end	main

