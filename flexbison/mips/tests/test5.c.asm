################################################################################
#
# MIPS Assembly Code
# Filename:     tests/test5.c.asm
# Input file:   tests/test5.c.tac
# Generated on: Tue May 14 22:14:58 2013
#
################################################################################

	.include	"macros.asm"

	.data
spills:	.space	80

	.text
	.globl	main

	jal	main
	done

	# 3AC For the Input Code File: tests/test5.c

	.ent	add
add:	subu	$sp, $sp, 16
	sw	$ra, 12($sp)
	sw	$a0, 4($sp)
	sw	$a1, 8($sp)
	lw 	$t0, 4($sp)
	lw 	$t1, 8($sp)
	add	$t2, $t0, $t1
	sw 	$t0, 4($sp)
	sw 	$t1, 8($sp)

	print_str("The value of temp is: ")
	print_int($t2)
	print_newline

	sw 	$t2, 0($sp)
	lw	$ra, 12($sp)
	addu	$sp, $sp, 16
	jr	$ra
	.end	add


	.ent	main
main:	subu	$sp, $sp, 16
	sw	$ra, 12($sp)
	li	$t0, 1

	print_str("The value of x is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 0($sp)
	li	$t0, 2

	print_str("The value of y is: ")
	print_int($t0)
	print_newline

	sw 	$t0, 4($sp)
	lw 	$t0, 4($sp)
	add	$a0, $zero, $t0
	sw 	$t0, 4($sp)
	lw 	$t0, 0($sp)
	add	$a1, $zero, $t0
	sw 	$t0, 0($sp)
	jal	add
	li	$t0, 0
	add	$v0, $zero, $t0
	lw	$ra, 12($sp)
	addu	$sp, $sp, 16
	jr	$ra
	.end	main

