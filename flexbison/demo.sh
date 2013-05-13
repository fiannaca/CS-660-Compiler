#!/bin/bash
# File:    demo.sh
# Author:  Alex Fiannaca
# Purpose: demo.sh is a bash script designed to make the process of running demos
#          of the entire compilation process simple and straightforward. This 
#          script will compile the input to 3AC and then compile the 3AC to MIPS.
#          This demo script expects a single argument which is the name of a 
#          sample code file in the tests/ directory. This should only be the 
#          name, NOT the path!
HELP="help"

if [ $# -eq 1 ] ; then

	#Start by compiling to 3AC
	echo $'\nCompiling '$1' to three address code'
	echo 'Executing: ./ccomp tests/'$1
	./ccomp tests/$1

	#Rename to output file to something more understandable
	echo $'\nRenaming the output to '$1'.tac and moving it to the tac2mips directory'
	echo 'Executing:  mv TAC.out '$1'.tac'
	mv TAC.out $1.tac

	#Move this 3AC file into the test directory for the tac2mips compiler
	echo 'Executing:  mv '$1'.tac mips/tests/'
	mv $1.tac mips/tests/

	#Move into that directory as well
	echo 'Executing:  cd mips/'
	cd mips/

	#Run the tac2mips compiler
	echo $'\nCompiling '$1'.tac into MIPS assembly code'
	echo 'Executing:  ./tac2mips tests/'$1'.tac'
	./tac2mips tests/$1.tac

	#Return to the start directory
	echo 'Executing:  cd ../'
	cd ../

	#Signal success
	echo $'\nCompleted! You can now open mips/tests/'$1'.tac in the MARS simulator'
	
else
	#Signal error
	echo 'Error: usage - ./demo.sh [filename]'
	echo 'Note: [filename] is only the name of a file in the tests/ directory, NOT a path to a file!'
fi
