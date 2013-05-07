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
	.macro print_int (%val)
	li $v0, 1
	add $a0, $zero, %val
	syscall
	.end_macro

#
# Prints a string (pass this a literal string!)
#
	.macro print_str (%str)
	.data
stringlabel:	.asciiz %str
	.text
	li $v0, 4
	la $a0, stringlabel
	syscall
	.end_macro

#
# Prints a newline
#
	.macro print_newline
	.data
nl:	.asciiz "\n"
	.text
	li $v0, 4
	la $a0, nl
	syscall	
	.end_macro

#
# Prints a function prolog
#
	.macro prolog (%name)
	.ent %name
%name:
	.frame $sp, 0, %31
	.end_macro
	
#
# Prints a function prolog for a function which allocates space on the stack
#
	.macro prolog_s (%name, %stacksize)
	.ent %name
%name:
	subu $sp, %stacksize
	.frame $sp, %stacksize, %31
	.end_macro
