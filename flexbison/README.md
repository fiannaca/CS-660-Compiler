#CS 460/660 - Compilers
##University of Nevada, Reno - Spring 2013

__Authors: Alex Fiannaca & Sandeep Matthew__

__Date:    03/25/2013__

###Description:

This is the front end of a simple C compiler being written for the CS660
Compiler course at the University of Nevada, Reno (Spring 2013). In order to
compile the scanner and parser, you must use the most recent versions of Flex
and Bison, the GNU scanner and parser generators.

Links to dependencies:
+ [Bison 2.7](http://ftp.gnu.org/gnu/bison/)
+ [Flex 2.5.37](http://flex.sourceforge.net/)

For more information, contact [fiannac4@live.com](mailto:fiannac4@live.com)

###How To: Compile this project

Clone the repository using the following command:

	git clone https://github.com/afiannac2/cs660.git

This repository is a private repository, meaning that you must be granted
access rights before you can clone the repository, but since you are
reading this, I am guessing you have been given rights.

Execute the following commands to compile the project:

	cd cs660/flexbison/
	make

This will run flex and bison and then compile all of the sources to produce
the C Compiler front end executable *__ccomp__*

###How To: Run this project (direct use)

The C Compiler front end can either be invoked by using the following command

	./ccomp

###How To: Run this project (using the test script)

A script has been written which allows you to automatically run any test *.c*
files located in the *tests/* folder. The script can be invoked through the 
makefile by running the command (after you have compiled the project)

	make test

This will copy the compiler executable into the *tests/* folder and will
run the compiler on every *.c* file in the *tests/* folder. This will invoke
the compiler with the *-d* flag (with the l, s, and p parameters) and the *-o*
flag (with an output filename of <filename>.out). In addition, it will group
the results of each attempted compilation into a folder with the same name
as the input C file. Some of the test files in the *tests/* folder are designed
to fail (to test error output and whatnot) and some are designed to compile
correctly (to test things like proper input into the symbol table).
