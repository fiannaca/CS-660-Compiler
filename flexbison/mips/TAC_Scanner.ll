%{
//Includes
#include <cstdlib>
#include <limits>
#include <string>
#include <stdexcept>
#include <cerrno>
#include <iostream>

#include "TAC_Parser.hpp"
#include "tac2mips.h"

//Handles a bug in Flex 2.5.33
#undef yywrap
#define yywrap() 1

#define yyterminate() return token::END

%}

ws		[ \t\v\f\n]+
letter	[a-zA-Z]
digit   [0-9]
punc    [-\.]
str     ({letter}|{digit}|{punc})*

%x COMMENT

%%

%{
typedef yy::TAC_Parser::token token;
%}

"ADD"   {
            return token::ADD;
        }
        
"SUB"   {
            return token::SUB;
        }
        
"MULT"  {
            return token::MULT;
        }
        
"DIV"   {
            return token::DIV;
        }
        
"SHIFTL" {
            return token::SHIFTL;
        }
        
"SHIFTR" {
            return token::SHIFTR;
        }
        
"AND"   {
            return token::AND;
        }

"LAND"  {
            return token::LAND;
        }

"XOR"   {
            return token::XOR;
        }
        
"OR"    {
            return token::OR;
        } 

"LOR"   {
            return token::LOR;
        }
        
"EQ"    {
            return token::EQ;
        }
        
"GT"    {
            return token::GT;
        }

"LT"    {
            return token::LT;
        }
        
"GE"    {
            return token::GE;
        }

"REM"   {
            return token::REM;
        } 

"LE"    {
            return token::LE;
        }

"NE"    {
            return token::NE;
        }
        
"BREQ"  {
            return token::BREQ;
        }
        
"BRGT"  {
            return token::BRGT;
        }
        
"BRLT"  {
            return token::BRLT;
        } 
        
"BRGE"  {
            return token::BRGE;
        } 

"BRLE"  {
            return token::BRLE;
        } 
        
"BRNE"  {
            return token::BRNE;
        }
        
"BOUND" {
            return token::BOUND;
        }

"MOV"   {
            return token::MOV;
        }
        
"NEG"   {
            return token::NEG;
        }

"NOT"   {
            return token::NOT;
        }

"ASSIGN" {
            return token::ASSIGN;
        } 
        
"ADDR"  {
            return token::ADDR;
        } 

"GLOBAL" {
            return token::GLOBAL;
        } 

"STR"   {
            return token::STR;
        }
"IMMEDIATE_I" {
            return token::IMMEDIATE_I;
        } 
        
"IMMEDIATE_F" {
            return token::IMMEDIATE_F;
        }

"LABEL" {
            return token::LABEL;
        } 

"BR"    {
            return token::BR;
        } 

"ARGS"  {
            return token::ARGS;
        } 

"REFOUT" {
            return token::REFOUT;
        } 

"VALOUT" {
            return token::VALOUT;
        }

"CALL"  {
            return token::CALL;
        } 

"PROCENTRY" {
            return token::PROCENTRY;
        }   

"ALLOC" {
			return token::ALLOC;
		}

"PARAM"	{
			return token::PARAM;
		}
		
"VALAT"	{
			return token::VALAT;
		}
		
"#"     {
            BEGIN(COMMENT);
        }

<COMMENT>.* {
            yylval->sval = new std::string(yytext);
            return token::COMMENT_STRING;
        }
        
<COMMENT>\n {
            BEGIN(INITIAL);
        }
                 
"HALT"  {
            return token::HALT;
        } 

"ENDPROC" {
            return token::ENDPROC;
       } 

"RETURN" {
            return token::RETURN;
        }

"BEGINFRAME" {
            return token::BEGINFRAME;
        } 

"ENDFRAME" {
            return token::ENDFRAME;
        }

{ws}    { 
            /* consume whitespace, need to keep location info */
        }

{str}   {
            yylval->sval = new std::string(yytext);
            return token::STRING;
        }
%%
void tac2mips::scan_begin()
{
    if(!(yyin = fopen(fname.c_str(), "r")))
    {
        error("Cannot open" + fname + ": " + strerror(errno));
        exit(EXIT_FAILURE);
    }
    
    BEGIN(0);
}

void tac2mips::scan_end()
{
    fclose(yyin);
}
