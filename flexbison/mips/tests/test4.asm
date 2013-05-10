################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test4.asm
# Input file:   tests/test4.tac
# Generated on: Fri May 10 12:33:26 2013
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

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 4($sp)
	li	$t0, 0

	print_str("The value of i is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
L0000:	li	$t0, 10
	lw 	$t1, 0($sp)
	slt	$t2, $t1, $t0
	sw 	$t1, 0($sp)
	beq	$t2, 0, L0001
	li	$t0, 2
	lw 	$t1, 4($sp)
	add	$t2, $t0, $t1
	sw 	$t1, 4($sp)

	print_str("The value of a is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 4($sp)
	li	$t0, 1
	lw 	$t1, 0($sp)
	add	$t2, $t0, $t1
	sw 	$t1, 0($sp)

	print_str("The value of i is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 0($sp)
	b	L0000
L0001:	li	$t0, 1

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 4($sp)
L0002:	li	$t0, 10
	lw 	$t1, 4($sp)
	slt	$t2, $t1, $t0
	sw 	$t1, 4($sp)
	beq	$t2, 0, L0003
	li	$t0, 2
	lw 	$t1, 4($sp)
	add	$t2, $t0, $t1
	sw 	$t1, 4($sp)

	print_str("The value of a is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 4($sp)
	b	L0002
L0003:	li	$t0, 1

	print_str("The value of a is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 4($sp)
L0004:	li	$t0, 2
	lw 	$t1, 4($sp)
	add	$t2, $t0, $t1
	sw 	$t1, 4($sp)

	print_str("The value of a is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 4($sp)
	li	$t0, 10
	lw 	$t1, 4($sp)
	slt	$t2, $t1, $t0
	sw 	$t1, 4($sp)
	beq	$t2, 0, L0005
	b	L0004
L0005:	li	$t0, 0
	lw	$31, 8($sp)
	addu	$sp, $sp, 12
	jr	$31
	.end	main

