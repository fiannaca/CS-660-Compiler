#ifndef CCompiler_H
#define CCompiler_H

//The include below for map.h is simply a stand-in for the Symbol Table
#include <string>
#include <map>

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

        //Initializes/destructs the scanner input
        void scan_begin(int debug_level);
        void scan_end();
        bool  trace_scanning;

        //Handles the parser. Return 0 on success
        int parse(const std::string& fname);
        std::string in_fname;
        std::string out_fname;
        bool trace_parsing;

        //Handles the Symbol Table
        std::map<std::string, int> symtab;
        void setInsertMode(bool insertMode);
        bool temp_insert_mode; //This will be replaced with a flag in the symbol table class
        bool trace_symtab;

        //Error reporting
        char linebuf[500];
        void error(const yy::location& loc, const std::string& msg);
        void error(const std::string& msg);
};

#endif // ! CCompiler_H
