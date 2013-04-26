#ifndef TAC2MIPS_H
#define TAC2MIPS_H

#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>

#include "TAC_Parser.hpp"
#include "RegAllocTable.h"
#include "AddressTable.h"

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
        
        std::string fname; /**< Standard assembly code output stream filename */
        std::string outfname; /**< The name of the output MIPS file */
        std::fstream fout; /**< The MIPS output file stream */
        
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
         * @param isNew    An output ref parameter indicating if the temp register
         *                 was already mapped to this real register, or if the
         *                 mapping is new.
         * @return The name of the real register to which the temp register has
         *         been mapped/assigned.
         */
        std::string GetRegister(std::string tempName, bool &isNew);
        
        RegAllocTable regtab; /**< The register allocation table */
        AddressTable addtab; /**< The address table */
        
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
         */
        void Comment(std::string txt);
};

#endif // ! TAC2MIPS_H
