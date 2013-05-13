################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test4.asm
# Input file:   tests/test4.tac
# Generated on: Sat May 11 12:38:26 2013
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
	lw 	$t1, 0($sp)
	add	$t2, $t0, $t1
	sw 	$t1, 0($sp)
	lw 	$t0, 0($sp)

	print_str("The value of I0015 is: ")
	print_int($t0)
	print_newline

	b	L0000
L0001:	li	$t1, 1

	print_str("The value of a is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 4($sp)
L0002:	li	$t1, 10
	lw 	$t3, 4($sp)
	slt	$t4, $t3, $t1
	sw 	$t3, 4($sp)
	beq	$t4, 0, L0003
	li	$t1, 2
	lw 	$t3, 4($sp)
	add	$t4, $t1, $t3
	sw 	$t3, 4($sp)

	print_str("The value of a is: ")
	print_int($t4)
	print_newline

	sw 	$t4, 4($sp)
	b	L0002
L0003:	li	$t1, 1

	print_str("The value of a is: ")
	print_int($t1)
	print_newline

	sw 	$t1, 4($sp)
L0004:	li	$t1, 2
	lw 	$t3, 4($sp)
	add	$t4, $t1, $t3
	sw 	$t3, 4($sp)

	print_str("The value of a is: ")
	print_int($t4)
	print_newline

	sw 	$t4, 4($sp)
	li	$t1, 10
	lw 	$t3, 4($sp)
	slt	$t4, $t3, $t1
	sw 	$t3, 4($sp)
	beq	$t4, 0, L0005
	b	L0004
L0005:	li	$t1, 0
	lw	$31, 8($sp)
	addu	$sp, $sp, 12
	jr	$31
	.end	main

