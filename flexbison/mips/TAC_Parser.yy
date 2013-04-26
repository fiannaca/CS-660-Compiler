%require "2.7"

%define parser_class_name "TAC_Parser"

%code requires {
#include <string>
#include <sstream>
#include <iostream>

class tac2mips;
}

%parse-param { tac2mips& driver }
%lex-param   { tac2mips& driver }

%initial-action
{
    //Initialize the filename
    @$.begin.filename = @$.end.filename = &driver.fname;
};

%union 
{
    std::string *sval;
};

%error-verbose

%code {
#include "tac2mips.h"
}

%token END 0 "EOF"
%token <sval> STRING COMMENT_STRING 
%token ADD SUB MULT DIV
%token SHIFTL SHIFTR AND LAND XOR OR LOR
%token EQ GT LT GE REM LE NE
%token BREQ BRGT BRLT BRGE BRLE BRNE
%token BOUND MOV
%token NEG NOT ASSIGN ADDR GLOBAL STR
%token IMMEDIATE_I IMMEDIATE_F
%token LABEL BR ARGS REFOUT VALOUT CALL PROCENTRY
%token HALT ENDPROC RETURN
%token BEGINFRAME ENDFRAME

%%
tac_command
    : ADD STRING STRING STRING
        {
            //adds $2 and $3 and places the result in $4
        }
    | SUB STRING STRING STRING
        {
            //subtracts $2 and $3 and places the result in $4
        }
    | MULT STRING STRING STRING
        {
            //multiplies $2 and $3 and places the result in $4
        }
    | DIV STRING STRING STRING
        {
            //divides $2 by $3 and places the result in $4
        }
    | SHIFTL STRING STRING STRING
        {
            //TODO
        }
    | SHIFTR STRING STRING STRING
        {
            //TODO
        }
    | AND STRING STRING STRING
        {
            //TODO
        }
    | LAND STRING STRING STRING
        {
            //TODO
        }
    | XOR STRING STRING STRING
        {
            //TODO
        }
    | OR STRING STRING STRING
        {
            //TODO
        }
    | LOR STRING STRING STRING
        {
            //TODO
        }
    | EQ STRING STRING STRING
        {
            //if $2 and $3 are equal, then $4 is set to 1, else $4 is set to 0
        }
    | GT STRING STRING STRING
        {
            //if $2 is greater than $3, then $4 is set to 1, else $4 is set to 0
        }
    | LT STRING STRING STRING
        {
            //if $2 is less than $3, then $4 is set to 1, else $4 is set to 0
        }
    | GE STRING STRING STRING
        {
            //if $2 is greater than $3, then $4 is set to 1, else $4 is set to 0
        }
    | REM STRING STRING STRING
        {
            //TODO
        }
    | LE STRING STRING STRING
        {
            //if $2 is less than or equal to $3, then $4 is set to 1, else $4 is set to 0
        }
    | NE STRING STRING STRING
        {
            //if $2 is not equal to $3, then $4 is set to 1, else $4 is set to 0
        }
    | BREQ STRING STRING STRING
        {
            //if $2 is equal to $3, then branch to $4
        }
    | BRGT STRING STRING STRING
        {
            //if $2 is greater than $3, then branch to $4
        }
    | BRLT STRING STRING STRING
        {
            //if $2 is less than $3, then branch to $4
        }
    | BRGE STRING STRING STRING
        {
            //if $2 is greater than or equal to $3, then branch to $4
        }
    | BRLE STRING STRING STRING
        {
            //if $2 is less than or equal to $3, then branch to $4
        }
    | BRNE STRING STRING STRING
        {
            //if $2 is not equal to $3, then branch to $4
        }
    | BOUND STRING STRING STRING
        {
            //TODO
        }
    | MOV STRING STRING 
        {
            //TODO
        }
    | NEG STRING STRING 
        {
            //$3 is set to the negative value of $2
        }
    | NOT STRING STRING
        {
            //$3 is set to 1 if $2 is equal to 0, else $3 is set to 0
        }
    | ASSIGN STRING STRING
        {
            //the value in register $2 to stored in memory offset $3
        }
    | ADDR STRING STRING 
        {
            //$3 is set to the address of $2
        }
    | GLOBAL STRING STRING
        {
            //create a global named $2 of size $3
        }
    | STR STRING STRING
        {
            //associate string $3 with label $2
        }
    | IMMEDIATE_I STRING STRING
        {
            //load the value of $3 into the temporary $2 (integer)
        }
    | IMMEDIATE_F STRING STRING
        {
            //load the value of $3 into the temporary $2 (float)
        }
    | LABEL STRING 
        {
            //create a label $2
        }
    | BR STRING
        {
            //branch to label $2
        }
    | ARGS STRING
        {
            //the upcoming procedure has $2 arguments
        }
    | REFOUT STRING
        {
            //the upcoming procedure passes $2 by reference
        }
    | VALOUT STRING
        {
            //the upcoming procedure passes $2 by value
        }
    | CALL STRING 
        {
            //call the procedure labeled $2
        }
    | PROCENTRY STRING
        {
            //declare the beginning of a procedure named $2 - output the prolog
        }
    | COMMENT_STRING
        {
            //output the comment $1
            driver.Comment(*$1);
        }
    | BEGINFRAME STRING
        {
            //begin a new frame and allocate $2 words of memory on the stack for variables
        }
    | HALT
        {
            //immediately terminate execution
        }
    | ENDPROC
        {
            //mark the end of a procedure - output the epilog
        }
    | RETURN
        {
            //return control to the caller
        }
    | ENDFRAME 
        {
            //end the current frame
        }
    ;
%%
void yy::TAC_Parser::error(const yy::TAC_Parser::location_type& loc,
                        const std::string& msg)
{
    driver.error(msg);
}




































