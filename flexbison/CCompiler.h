#ifndef CCompiler_H
#define CCompiler_H

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
        void scan_begin();
        void scan_end();
        bool  trace_scanning;

        //Handles the parser. Return 0 on success
        int parse(const std::string& fname);
        std::string in_fname;
        std::string out_fname;
        bool trace_parsing;

        //Handles the Symbol Table
        std::map<std::string, int> symtab;
        bool trace_symtab;

        //Error reporting
        void error(const yy::location& loc, const std::string& msg);
        void error(const std::string& msg);
};

#endif // ! CCompiler_H
