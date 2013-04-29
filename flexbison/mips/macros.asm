# File: macros.asm
# Created: 4/29/2012
# Author:  Alex Fiannaca
#
# Note: some of these macros were pulled from the MARS help website: http://courses.missouristate.edu/kenvollmar/mars/Help/MacrosHelp.html
#

#
# Terminates the program
#
	.macro done
	li $v0, 10
	syscall
	.end_macro
    

#
# Prints an integer (either a register or an immediate)
#
	.macro print_int (%immediate)
	li $v0, 1
	add $a0, $zero, %immediate
	syscall
	.end_macro

#
# Prints a string (pass this a literal string!)
#
	.macro print_str (%str)
	.data
strlab:	.asciiz %str
	.text
	li $v0, 4
	la $a0, strlab
	syscall
	.end_macro