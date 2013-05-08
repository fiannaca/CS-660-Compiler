#ifndef TAC2MIPS_H
#define TAC2MIPS_H

#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <set>

#include "TAC_Parser.hpp"
#include "RegAllocTable.h"
#include "AddressTable.h"
#include "FunctionTable.h"

//! Macro defining the scanner's lex function
#define YY_DECL                                     \
    yy::TAC_Parser::token_type                         \
    yylex(yy::TAC_Parser::semantic_type* yylval,       \
          yy::TAC_Parser::location_type* yylloc,       \
          tac2mips& driver)

YY_DECL;

class tac2mips {
    public:
        /**
         * Standard constructor.
         *
         * @param filename The name of the input 3AC file
         */
        tac2mips(std::string filename);
        
        /**
         * Standard destructor
         */
        ~tac2mips();
        
        /**
         * Runs the conversion from 3AC to MIPS
         */
        void Run();
        
        /**
         * Standard assembly code output stream filename 
         */
        std::string fname;
        
        /**
         * Initializes the scanning process. This function sets up the scanner
         * input streams.
         */
        void scan_begin();
        
        /**
         * Closes the different output streams used in the scanner
         */
        void scan_end();
        
        /**
         * Prints an error to the standard compiler output stream and terminates
         * the program with with an EXIT_FAILURE return value.
         *
         * @param msg The error message
         */
        void error(const std::string& msg);
        
        /**
         * Handles the allocation of registers including spilling when required.
         *
         * @param tempName The name of the temporary register in the 3AC which 
         *                 needs to be mapped to a real register.
         * @return The name of the real register to which the temp register has
         *         been mapped/assigned.
         */
        std::string GetRegister(std::string tempName);
        
		/**
		 * Frees a register after when it is no longer live.
		 *
		 * @param name The name of the owner of a register which needs to be freed
		 */
		void FreeRegister(std::string name);
		
		/**
		 * The register allocation table 
		 */
        RegAllocTable regtab;
        
        /**
         * The address table 
         */
        AddressTable addtab;
        
        /** 
         * A table for tracking functions and the associated information for 
         * each function such as the required stack space for the variables in 
         * the function and the parameters to the function.
         */
        FunctionTable funtab; 
		
		/**
		 * Checks if a label exists
		 */
		bool LabelExists(std::string name);
		
		/**
		 * Adds a label to the collection of labels
		 */
		void AddLabel(std::string name);
		
        /**
         * Outputs the beginning of the MIPS file. This includes items like an
         * include directive to include the macros file which is used for 
         * simplifying the MIPS output. This also output comments referring to
         * the source 3AC file.
         */
        void OutputPreamble();
        
        /**
         * Outputs a comment into the MIPS file.
         *
         * @param txt The comment text to output.
         * @param VerboseOnly Indicates if this comment should only be printed 
         *                    if the verbose flag is true
         */
        void Comment(std::string txt, bool VerboseOnly);
		
		/**
		 * Outputs the specified number of blank lines to the MIPS file in order 
		 * make the MIPS easier to read.
		 *
		 * @param lines The number of blank lines to output
		 */
		void WS(int lines = 1);
		
		/**
		 * Adds a line of code to the MIPS file and formats it correctly.
		 *
		 * @param psuedoop A MIPS psuedo-opcode command, i.e. ".globl"
		 */
		void toMIPS(std::string psuedoop);
		
		/**
		 * Adds a line of code to the MIPS file and formats it correctly.
		 *
		 * @param opcode A MIPS command, i.e. "jr" 
		 * @param op1 The operand, i.e. "$t31"
		 */
		void toMIPS(std::string opcode, std::string op1);
		
		/**
		 * Adds a line of code to the MIPS file and formats it correctly.
		 *
		 * @param opcode A MIPS command, i.e. "sw" 
		 * @param op1 The operand, i.e. "$t0"
		 * @param op2 The operand, i.e. "0($sp)"
		 */
		void toMIPS(std::string opcode, std::string op1, std::string op2);
		
		/**
		 * Adds a line of code to the MIPS file and formats it correctly.
		 *
		 * @param opcode A MIPS command, i.e. "add" 
		 * @param op1 The operand, i.e. "$t0"
		 * @param op2 The operand, i.e. "$t1"
		 * @param op3 The operand, i.e. "$t2"
		 */
		void toMIPS(std::string opcode, std::string op1, std::string op2, std::string op3);
		
		/**
		 * Outputs a macro with the given name and parameters
		 *
		 * @param name The name of the macro to output
		 * @param params The parameters for the macro
		 */
		void Macro(std::string name, std::string params);
		
		/**
		 * Outputs a macro with the given name and no parameters
		 *
		 * @param name The name of the macro to output
		 */
		void Macro(std::string name);
		
		/**
		 * Adds a label to the MIPS file and formats it correctly.
		 *
		 * @param txt A MIPS label to output, i.e. "spills"
		 */
		void Label(std::string txt);
        
        /**
         * Turns verbose comments on or off
         */
        void SetVerbose(bool flag);
        
    private:
        
        /**
         * The name of the output MIPS file 
         */
        std::string outfname; 
        
        /**
         * The MIPS output file stream 
         */
        std::fstream fout; 
        
		/**
		 * A collection of all of the labels in the MIPS output
		 */
		set<string> labels;
		
        /**
         * Indicates if verbose comments should be output in the MIPS
         */
        bool verbose;
};

#endif // ! TAC2MIPS_H
