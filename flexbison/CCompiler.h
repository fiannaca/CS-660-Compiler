#ifndef CCompiler_H
#define CCompiler_H

#include <string>
#include <map>
#include <list>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "SymTab.h"
#include "CParser.hpp"
#include "Ast.h"

//! Macro defining the scanner's lex function
#define YY_DECL                                     \
    yy::CParser::token_type                         \
    yylex(yy::CParser::semantic_type* yylval,       \
          yy::CParser::location_type* yylloc,       \
          CCompiler& driver)

YY_DECL;

/**
 * A structure for buffering lines input code.
 */
struct InputLine 
{
    int line; /**< The line number */
    string text; /**< The line of code */

    /**
     * Defualt constructor
     */
    InputLine(int l, string s)
    {
        line = l;
        text = s;
    }
};

/**
 * A minimalist C programming language compiler class. This class handles the 
 * entire operation of compiling C code, from lexing and parsing, to walking the 
 * AST, generating 3AC, and generating ASM.
 */
class CCompiler
{
    public:
        /**
         * Default constructor
         */
        CCompiler();
        
        /**
         * Destructor
         */
        virtual ~CCompiler();

        int result; /**< A flag indicating the result of an attempted compilation */

        /**
         * Initializes the scanning process. This function sets up the scanner
         * output streams, sets the scanner's debug level, and begins the 
         * FIRSTLINE state.
         *
         * @param debug_scanning Indicates if the scanner should output debug info
         */
        void scan_begin(bool debug_scanning);
        
        /**
         * Closes the different output streams used in the scanner
         */
        void scan_end();
        
        bool  trace_scanning; /**< Scanner trace state */

        //Handles the parser. Return 0 on success
        /**
         * Runs the parsing (and consequently the scanning) process. This is
         * equivalent to a call to a Run() like function.
         *
         * @param fname The input code file filename
         *
         * @return The result value of the parse process
         */
        int parse(const std::string& fname);
        
        std::string fname; /**< Standard compiler output stream filename */
        
        /**
         * Sets the filename of the standard compiler output file stream and 
         * opens the stream.
         *
         * @param fname The filename
         */
        void setOutfile(std::string fname);
        
        /**
         * Trace parsing flag.
         */
        bool trace_parsing;
        
        /**
         * The current symbol table symbol
         */
        SymbolInfo *currentSymbol;  
        
        Type *structMemberType;
        SymTab SymbolTable;
        bool anonymousEnum; 
        int structUnionMode;  
        list<string> enumConsts;
        list<SymbolInfo> structUnionTypes; 
        EnumType *enumType;
        SymbolInfo *enumSym; 
        int structVarCount;
        string currentStorageType;
        string currentTypeQual; 
	string currentFunctionName; 
        AST * source_ast;
	bool isFuncDef; 
        
        /**
         * Should check the type of the symbol with the input key and insert any
         * symbol not currently in the symbol table.
         *
         * @param key The string key for the token
         * @param loc The location of the token
         * @param sym a pointer to the symbol in the symbol table
         *
         * @return Returns either IDENTIFIER, ENUM_CONSTANT, or TYPEDEF_NAME
         */
        yy::CParser::token::yytokentype checkType(char* key, const yy::location& loc, SymbolInfo* sym);
        
        /**
         * Allocates a new current symbol.
         */
        void allocateSymbol();
        
        /**
         * Initializes the global scope for the input program.
         */
        void globalScope();
        
        /**
         * Enters a new scope in the input program.
         */
        void enterScope();
        
        /**
         * Leaves a scope in the input program.
         */
        void leaveScope();
        
        /**
         * Sets the insert mode flag to the provided value.
         *
         * @param iMode Value to set the insert mode flag to
         */
        void set_insert_mode(bool iMode);
        
        /**
         * Gets TRUE if the compiler is currently in insert mode and false 
         * otherwise
         *
         * @return The value of the insert mode flag;
         */
        bool get_insert_mode();
        
        /**
         * Flag indicating whether or not trace data should be output for the 
         * symbol table.
         */
        bool trace_symtab;
         
        //TODO - remove? 
        //char linebuf[500];
        
        /**
         * Prints an error to the standard compiler output stream with the 
         * coordinates of the code that caused the error and terminates the
         * program with with an EXIT_FAILURE return value.
         *
         * @param loc The coordinates of the error
         * @param msg The error message
         */
        void error(const yy::location& loc, const std::string& msg);
        
        /**
         * Prints an error to the standard compiler output stream and terminates
         * the program with with an EXIT_FAILURE return value.
         *
         * @param msg The error message
         */
        void error(const std::string& msg);
        
        /**
         * Prints a warning to the standard compiler output stream with the 
         * coordinates of the code that caused the warning.
         *
         * @param loc The coordinates of the warning
         * @param msg The warning message
         */
        void warning(const yy::location& loc, const std::string& msg);
        
        /**
         * Prints a warning to the standard compiler output stream
         *
         * @param msg The warning message to print
         */
        void warning(const std::string& msg);
        
        /**
         * Prints the recognized token to the token file.
         *
         * @param ttxt The token
         */
        void printTok(std::string ttxt);
        
        /**
         * Prints the recognized token to the token file with the matched text.
         *
         * @param ttxt The token
         * @param yytext The matched text
         */
        void printTok(std::string ttxt, char* yytext);
        
        /**
         * Prints a reduction to the reduction file.
         *
         * @param ptxt Reduction string
         */
        void printRed(std::string ptxt);
        
        /**
         * Sets the debug output flag to the value provided.
         *
         * @param flag Flag value
         */
        void turnDebugOn(bool flag);
        
        /**
         * Prints a debug string to the standard compiler output stream if 
         * the debug output flag is set to true.
         *
         * @param txt The debug string to print
         */
        void printDebug(std::string txt);
        
        fstream ydbFile; /**< Bison debug output file */

        map<int, string> input_text; /**< Input code buffer */
        
        /**
         * Stores a line of code in the input code buffer
         *
         * @param i Line number
         * @param s Line of input code
         */
        void save_line(int i, string s);

    private:
        bool debug_on; /**< Debug output flag */
        bool insert_mode; /**< Insert mode flag */
        bool outfile_set; /**< Output to file flag */
        fstream tFile; /**< Token output stream */
        fstream rFile; /**< Reduction output stream */
        fstream outfile; /**< Standard compiler output stream */
};

/** \file CScanner.ll
 *
 * NOTE: USE THE LINK BELOW TO VIEW THE SOURCE FOR THIS FILE, THE GENERATED 
 * DOCUMENTATION IS NOT VALID SINCE DOXYGEN CANNOT PROPERLY PARSE FLEX FILES!
 */
 
/** \file CParser.yy
 *
 * NOTE: USE THE LINK BELOW TO VIEW THE SOURCE FOR THIS FILE, THE GENERATED 
 * DOCUMENTATION IS NOT VALID SINCE DOXYGEN CANNOT PROPERLY PARSE BISON FILES!
 */
 
/** \example test1.c
 * \section ABOUT About This Example:
 * The most basic example. This example demonstrates the basic capabilities of 
 * the compiler to generate valid MIPS assembler code for variable declarations,
 * simple assignments, and basic arithmetic. In addition, this example demonstrates
 * the ability of the register allocation algorithm to handle the need for utelizing
 * spill registers. Spilling is demonstrated by recompiling the tac2mips program
 * with passing the value 4 to the constructor of the register allocation table int
 * the constructor for the tac2mips object (this sets the maximum registers to 4
 * instead of 8).
 *
 * \section INSTRUCTIONS Running This Example:
 * This example can be tested by by invoking the demo.sh script (__THE PREFERRED METHOD!__)
 *
 *	\code
 *	./demo.sh <filename>
 *	\endcode
 *
 * or by manually invoking the ccomp and tac2mips programs (see instructions on 
 * the 'Main Page' tab above).
 *
 * This will generate the output file test1.asm, which can be assembled and run 
 * in the MARS MIPS simulator. Please note, assembly code in this project was 
 * created with the MARS simulator in mind. The code is therefore MARS compliant,
 * but may not be SPIM compliant. In addition, the generated code relies upon a
 * MARS asm macro file located in the mips/tests/ directory, and the assembly
 * file should therefore only be run in MARS from the directory it is originally
 * generated in. If you wish to move the asm file to a different folder, you must
 * also move the macros.asm file.
 *
 * 
 * \section OUTPUT The Expected Output:
   The __tac2mips__ program is designed to output a MIPS macro which prints the
   value of a variable whenever a value is stored to the variable. This provides
   a simple method of verfiying the output of this example is correct. It is 
   expected that the following statements should be printed to the MARS console:
   
   \code
   The value of i is: 1
   The value of j is: 2
   The value of k is: 3
   The value of k is: 1
   The value of k is: 2
   The value of k is: 2
   The value of k is: 0
   The value of k is: 55
   \endcode
   
 * \section CODE The Example Code:
 */
 
 
 
 /** \example test2.c
 * \section ABOUT About This Example:
 * This test is designed to test the proper allocation of arrays and calculation 
 * of array indices and access operations. In addition, this example demonstrates 
 * the use of indexed arrays as both lvalues and rvalues (see the final three 
 * lines in which the values of certain indexes of b are set to values from a). 
 * Finally, the last several lines of code in this example require the use of 
 * spill registers and are therefore a good demonstration of register spilling
 * in our compiler.
 *
 * \section INSTRUCTIONS Running This Example:
 * This example can be tested by by invoking the demo.sh script (__THE PREFERRED METHOD!__)
 *
 *	\code
 *	./demo.sh <filename>
 *	\endcode
 *
 * or by manually invoking the ccomp and tac2mips programs (see instructions on 
 * the 'Main Page' tab above).
 *
 * This will generate the output file test2.asm, which can be assembled and run 
 * in the MARS MIPS simulator. Please note, assembly code in this project was 
 * created with the MARS simulator in mind. The code is therefore MARS compliant,
 * but may not be SPIM compliant. In addition, the generated code relies upon a
 * MARS asm macro file located in the mips/tests/ directory, and the assembly
 * file should therefore only be run in MARS from the directory it is originally
 * generated in. If you wish to move the asm file to a different folder, you must
 * also move the macros.asm file.
 *
 * \section OUTPUT The Expected Output:
   Verifying the output of this example is slightly more complex than that of the 
   previous example. In order to view the contents of each array, you must use
   the 'Data Segment' pane in the MARS Simulator. After pressing F3 to assemble
   the MIPS code, add breakpoints at __lines 131, 160, and 272__ in the 'Text Segment'
   pane. These breakpoints will allow you to observe the arrays' contents as they
   are altered throughout the example. Next, in the 'Data Segment' pane, click
   on the dropdown and select the 'current $sp' option. This will display the 
   values on the stack. Finally, press F5 to begin running the example. At the 
   first breakpoint, the array b will contain the values 4, 4, 4, 4, 4. The next 
   item on the stack is the variable 'temp' which will have a value of 0 since it 
   has not been set at this point. After temp will be the array a with the values
   3, 2, 1.
   
   Click the Play button on the top of the screen to run the simulator until the 
   next breakpoint. At this point, temp will have the value 3 and the array a will
   have the values 3, 3, 3.
   
   Click the Play button one more time to complete the example. At this final point,
   temp will have the value 2 and the array b will now have the values 4, 4, 4, 
   3, 3, 3.
   
 * \section CODE The Example Code:
 */
 
 
 
 /** \example test3.c
 * \section ABOUT About This Example:
 * This test is designed to test the use of if-else statements.
 *
 * \section INSTRUCTIONS Running This Example:
 * This example can be tested by running the following commands in a bash 
 * terminal:
 * This example can be tested by by invoking the demo.sh script (__THE PREFERRED METHOD!__)
 *
 *	\code
 *	./demo.sh <filename>
 *	\endcode
 *
 * or by manually invoking the ccomp and tac2mips programs (see instructions on 
 * the 'Main Page' tab above).
 *
 * This will generate the output file test3.asm, which can be assembled and run 
 * in the MARS MIPS simulator. Please note, assembly code in this project was 
 * created with the MARS simulator in mind. The code is therefore MARS compliant,
 * but may not be SPIM compliant. In addition, the generated code relies upon a
 * MARS asm macro file located in the mips/tests/ directory, and the assembly
 * file should therefore only be run in MARS from the directory it is originally
 * generated in. If you wish to move the asm file to a different folder, you must
 * also move the macros.asm file.
 *
 * \section OUTPUT The Expected Output:
   The output from this simple example can be verified by looking at the console
   output in MARS in a similar fashion to the first example. The expected output 
   is as follows:
   
   \code
   The value of a is: 1
   The value of a is: 45
   The value of a is: -1
   \endcode
 *
 * \section CODE The Example Code:
 */
 
 
 
 /** \example test4.c
 * \section ABOUT About This Example:
 * This test is designed to test all of the C loops including the for, do-while, 
 * and while loops. In addition, this file tests the incrementor and simple 
 * relational operators.
 *
 * \section INSTRUCTIONS Running This Example:
 * This example can be tested by running the following commands in a bash 
 * terminal:
 * This example can be tested by by invoking the demo.sh script (__THE PREFERRED METHOD!__)
 *
 *	\code
 *	./demo.sh <filename>
 *	\endcode
 *
 * or by manually invoking the ccomp and tac2mips programs (see instructions on 
 * the 'Main Page' tab above).
 *
 * This will generate the output file test4.asm, which can be assembled and run 
 * in the MARS MIPS simulator. Please note, assembly code in this project was 
 * created with the MARS simulator in mind. The code is therefore MARS compliant,
 * but may not be SPIM compliant. In addition, the generated code relies upon a
 * MARS asm macro file located in the mips/tests/ directory, and the assembly
 * file should therefore only be run in MARS from the directory it is originally
 * generated in. If you wish to move the asm file to a different folder, you must
 * also move the macros.asm file.
 *
 * \section OUTPUT The Expected Output:
   The output from this example can once again be tested in the same fashion as
   the first example. Everytime a value is stored to the variables a and i, a 
   message is printed to the console. Therefore, the expected output is as follows:
   
   For the FOR loop:
   
   \code
   The value of a is: 1
   The value of i is: 0
   The value of a is: 3
   The value of i is: 1
   The value of a is: 5
   The value of i is: 2
   The value of a is: 7
   The value of i is: 3
   The value of a is: 9
   The value of i is: 4
   The value of a is: 11
   The value of i is: 5
   The value of a is: 13
   The value of i is: 6
   The value of a is: 15
   The value of i is: 7
   The value of a is: 17
   The value of i is: 8
   The value of a is: 19
   The value of i is: 9
   The value of a is: 21
   The value of i is: 10
   \endcode
   
   For the WHILE loop:
   \code
   The value of a is: 1
   The value of a is: 3
   The value of a is: 5
   The value of a is: 7
   The value of a is: 9
   The value of a is: 11
   \endcode
   
   For the DO WHILE loop:
   
   \code
   The value of a is: 1
   The value of a is: 3
   The value of a is: 5
   The value of a is: 7
   The value of a is: 9
   The value of a is: 11
   \endcode
 *
 * \section CODE The Example Code:
 */
 
 
 
 /** \example test5.c
 * \section ABOUT About This Example:
 * This test is designed to test the most basic possible function call. This 
 * example demonstrates how function parameters can be passed to methods.
 *
 * \section INSTRUCTIONS Running This Example:
 * This example can be tested by running the following commands in a bash 
 * terminal:
 * This example can be tested by by invoking the demo.sh script (__THE PREFERRED METHOD!__)
 *
 *	\code
 *	./demo.sh <filename>
 *	\endcode
 *
 * or by manually invoking the ccomp and tac2mips programs (see instructions on 
 * the 'Main Page' tab above).
 *
 * This will generate the output file test5.asm, which can be assembled and run 
 * in the MARS MIPS simulator. Please note, assembly code in this project was 
 * created with the MARS simulator in mind. The code is therefore MARS compliant,
 * but may not be SPIM compliant. In addition, the generated code relies upon a
 * MARS asm macro file located in the mips/tests/ directory, and the assembly
 * file should therefore only be run in MARS from the directory it is originally
 * generated in. If you wish to move the asm file to a different folder, you must
 * also move the macros.asm file.
 *
 * \section OUTPUT The Expected Output:
   This example can be tested in a similar fashion to that of the first example.
   The expected output is as follows:
   
   \code
   The value of x is: 1
   The value of y is: 2
   The value of temp is: 3
   \endcode
 *
 * \section CODE The Example Code:
 */
 
 
 
 /** \example test6.c
 * \section ABOUT About This Example:
 * This test is designed to test scoping of variables and calculated array 
 * indices (i.e. line 35). This bubble sort algorithm will be used in the next 
 * test which tests function calls. This test does not present any new concepts,
 * it simply shows a combination of previous presented concepts in a more
 * complicated example of code.
 *
 * \section INSTRUCTIONS Running This Example:
 * This example can be tested by running the following commands in a bash 
 * terminal:
 * This example can be tested by by invoking the demo.sh script (__THE PREFERRED METHOD!__)
 *
 *	\code
 *	./demo.sh <filename>
 *	\endcode
 *
 * or by manually invoking the ccomp and tac2mips programs (see instructions on 
 * the 'Main Page' tab above).
 *
 * This will generate the output file test6.asm, which can be assembled and run 
 * in the MARS MIPS simulator. Please note, assembly code in this project was 
 * created with the MARS simulator in mind. The code is therefore MARS compliant,
 * but may not be SPIM compliant. In addition, the generated code relies upon a
 * MARS asm macro file located in the mips/tests/ directory, and the assembly
 * file should therefore only be run in MARS from the directory it is originally
 * generated in. If you wish to move the asm file to a different folder, you must
 * also move the macros.asm file.
 *
 * \section OUTPUT The Expected Output:
   Since this example is based on sorting an array of integers (on the stack), it
   must be evaluated in the same manner as the second example, using the 'Data
   Segment' pane of the MARS Simulator, and breakpoints in the MIPS code. After
   assembling the code, create a breakpoint at __line 67__ and __line 200__. The first 
   breakpoint will demonstrate the unsorted array containing the values 5, 4, 3,
   2, 1. After the breakpoint at line 67 has been hit once, turn it off so that
   the simulator will run all the way until line 200 before stopping again. The 
   breakpoint at line 200 will demonstrate the sorted array containing the values 
   1, 2, 3, 4, 5.
 *
 * \section CODE The Example Code:
 */
 
 
 
 /** \example test7.c
 * \section ABOUT About This Example:
 * This test is designed to test function calls. This is the primary goal of the 
 * compiler project. This is a very simple bubble sort algorithm which uses a
 * call to a swap function to swap two integers in a small array. The input 
 * array is [3, 2, 1] and the output array should be [1, 2, 3].
 *
 * \section INSTRUCTIONS Running This Example:
 * This example can be tested by running the following commands in a bash 
 * terminal:
 * This example can be tested by by invoking the demo.sh script (__THE PREFERRED METHOD!__)
 *
 *	\code
 *	./demo.sh <filename>
 *	\endcode
 *
 * or by manually invoking the ccomp and tac2mips programs (see instructions on 
 * the 'Main Page' tab above).
 *
 * This will generate the output file test7.asm, which can be assembled and run 
 * in the MARS MIPS simulator. Please note, assembly code in this project was 
 * created with the MARS simulator in mind. The code is therefore MARS compliant,
 * but may not be SPIM compliant. In addition, the generated code relies upon a
 * MARS asm macro file located in the mips/tests/ directory, and the assembly
 * file should therefore only be run in MARS from the directory it is originally
 * generated in. If you wish to move the asm file to a different folder, you must
 * also move the macros.asm file.
 *
 * \section OUTPUT The Expected Output:
   As would be expected, verifying the output of this example is very similar to
   the method used to verify the output of the previous example. Again,
   breakpoints must be set so that the contents of the stack can be viewed in the
   MARS 'Data Segment' pane. After pressing F3 to assemble the code, create 
   breakpoints at __line 94__ and __line 192__. Upon hitting the first breakpoint,
   the values of the array tarr will be 5, 4, 3, 2, 1. Once this first breakpoint is
   hit, it should be turned off so that the next breakpoint occurs after the array
   has been completely sorted. Upon hitting the breakpoint on line 192, the values
   of the tarr array will be 1, 2, 3, 4, 5.
 *
 * \section CODE The Example Code:
 */
 
 
#endif // ! CCompiler_H
