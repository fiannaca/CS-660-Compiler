#ifndef CCompiler_H
#define CCompiler_H

//The include below for map.h is simply a stand-in for the Symbol Table
#include <string>
#include <map>
#include <list>
#include <stdio.h>
#include <fstream>
#include <iostream>

#include "SymTab.h"
#include "CParser.hpp"
#include "Ast.h"

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
        void scan_begin(bool debug_scanning);
        void scan_end();
        bool  trace_scanning;

        //Handles the parser. Return 0 on success
        int parse(const std::string& fname);
        std::string fname;
        void setOutfile(std::string fname);
        bool trace_parsing;

        //Handles the Symbol Table
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
        AST * source_ast; 
        yy::CParser::token::yytokentype checkType(char* key, const yy::location& loc, SymbolInfo *sym);
        void allocateSymbol(); 
        void globalScope();
        void enterScope();
        void leaveScope();
        void set_insert_mode(bool iMode);
        bool get_insert_mode();
        bool trace_symtab;
         
        //Error reporting
        char linebuf[500];
        void error(const yy::location& loc, const std::string& msg);
        void error(const std::string& msg);
        void warning(const yy::location& loc, const std::string& msg);
        void warning(const std::string& msg);

        //Debug reporting
        void printTok(std::string);
        void printTok(std::string, char*);
        void printRed(std::string);
        void turnDebugOn(bool);
        void printDebug(std::string);
        fstream ydbFile;

    private:
        bool debug_on;
        bool insert_mode;
        bool outfile_set;   
        fstream tFile;
        fstream rFile;
        fstream outfile;
};

#endif // ! CCompiler_H
