#ifndef CCompiler_H
#define CCompiler_H

//The include below for map.h is simply a stand-in for the Symbol Table
#include <string>
#include <map>
#include <stdio.h>

#include "SymTab.h"
#include "CParser.hpp"

#define YY_DECL                                     \
    yy::CParser::token_type                         \
    yylex(yy::CParser::semantic_type* yylval,       \
          yy::CParser::location_type* yylloc,       \
          CCompiler& driver)

YY_DECL;

class CCompiler
{
    public:
        CCompiler();
        virtual ~CCompiler();

        int result;

        //Initializes/destructs the scanner input -- implemented in CScanner.ll
        void scan_begin(int debug_level);
        void scan_end();
        bool  trace_scanning;

        //Handles the parser. Return 0 on success
        int parse(const std::string& fname);
        std::string in_fname;
        std::string out_fname;
        void setOutfile(std::string fname);
        bool trace_parsing;

        //Handles the Symbol Table
        SymTab SymbolTable;
        void set_insert_mode(bool iMode);
        bool get_insert_mode();
        bool trace_symtab;

        //Error reporting
        char linebuf[500];
        void error(const yy::location& loc, const std::string& msg);
        void error(const std::string& msg);

    private:
        bool insert_mode;
        bool outfile_set;
};

#endif // ! CCompiler_H
