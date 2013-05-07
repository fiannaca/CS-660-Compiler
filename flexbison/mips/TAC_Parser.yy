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

string CurrentFunction = "";
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
%token LABEL BR ARGS REFOUT VALOUT CALL PROCENTRY ALLOC
%token HALT ENDPROC RETURN
%token BEGINFRAME ENDFRAME

%%
commands
	: 
	
	| tac_command commands
	
	;
	
tac_command
    : allocate_list
    	{
    		//Change the stack pointer after the allocate list is complete
    		stringstream ss1, ss2, ss3, ss4;
    		
    		int space = driver.funtab.GetStackSpace(CurrentFunction);
    		
    		ss1 << "subu $sp, $sp, " << (space + 4);    		
    		driver.toMIPS(ss1.str());
    		
    		ss2 << "sw $31, " << space << "($sp)";
    		driver.toMIPS(ss2.str());
    		
    		//Apparently MARS doesn't recognize these commands
    		//driver.toMIPS(".mask 0x80000000, -4");
    		
    		//ss3 << ".frame $sp, " << (space + 4) << ", $31";
    		//driver.toMIPS(ss3.str());
    	}    
    | ADD STRING STRING STRING
        {
            //adds $2 and $3 and places the result in $4
			bool isNew = false;
			
			string reg1 = driver.GetRegister(*$2, isNew);
			string reg2 = driver.GetRegister(*$3, isNew);
			string reg3 = driver.GetRegister(*$4, isNew);
			
			stringstream ss;
			ss << "add " << reg3 << " " << reg1 << " " << reg2;
			
			driver.toMIPS(ss.str());
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | SUB STRING STRING STRING
        {
            //subtracts $2 and $3 and places the result in $4
			bool isNew = false;
			
			string reg1 = driver.GetRegister(*$2, isNew);
			string reg2 = driver.GetRegister(*$3, isNew);
			string reg3 = driver.GetRegister(*$4, isNew);
			
			stringstream ss;
			ss << "sub " << reg3 << " " << reg1 << " " << reg2;
			
			driver.toMIPS(ss.str());
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | MULT STRING STRING STRING
        {
            //multiplies $2 and $3 and places the result in $4
			bool isNew = false;
			
			string reg1 = driver.GetRegister(*$2, isNew);
			string reg2 = driver.GetRegister(*$3, isNew);
			string reg3 = driver.GetRegister(*$4, isNew);
			
			stringstream ss1, ss2;
			ss1 << "mult " << reg1 << " " << reg2;
			
			driver.toMIPS(ss1.str());
			
			ss2 << "mflo " << reg3;
			
			driver.toMIPS(ss2.str());
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | DIV STRING STRING STRING
        {
            //divides $2 by $3 and places the result in $4
			bool isNew = false;
			
			string reg1 = driver.GetRegister(*$2, isNew);
			string reg2 = driver.GetRegister(*$3, isNew);
			string reg3 = driver.GetRegister(*$4, isNew);
			
			stringstream ss1, ss2;
			ss1 << "div " << reg1 << " " << reg2;
			
			driver.toMIPS(ss1.str());
			
			ss2 << "mflo " << reg3;
			
			driver.toMIPS(ss2.str());
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
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
            //This one does a store (it stores a register into a variable memory 
            // location)
            bool isNew = false;
            
            string reg = driver.GetRegister(*$2, isNew);
            
            driver.addtab.Store(reg, *$3);
            
            //for verifying program correctness
            stringstream ss, ss1;
            ss << "print_str(\"The value of " << (*$3) << " is: \")";
            driver.toMIPS(ss.str());
            
            ss1 << "print_int(" << reg << ")";
            driver.toMIPS(ss1.str());
            driver.toMIPS("print_newline");
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
			
			//TODO This needs to be moved into the data section
			driver.Label(*$2);
			
			stringstream ss;
			ss << ".asciiz \"" << (*$3) << "\"";
			driver.toMIPS(ss.str());
        }
    | IMMEDIATE_I STRING STRING
        {
            //load the value of $3 into the temporary $2 (integer)
			bool isNew = false;
			
			string reg = driver.GetRegister(*$2, isNew);
			
			stringstream ss;
			ss << "li " << reg << ", " << (*$3);
			
			driver.toMIPS(ss.str());
        }
    | IMMEDIATE_F STRING STRING
        {
            //load the value of $3 into the temporary $2 (float)
			
			//TODO This is probably the exact same as IMMEDIATE_I
        }
    | LABEL STRING 
        {
            //create a label $2
			driver.Label(*$2);
        }
    | BR STRING
        {
            //branch to label $2
			
			//TODO This check probably isn't valid and may need to be removed later
			if(driver.LabelExists(*$2))
			{
				stringstream ss;
				ss << "b " << (*$2);
				
				driver.toMIPS(ss.str());
			}
			else
			{
				driver.error("Attempted to branch to an unknown label");
			}
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
            CurrentFunction = (*$2);
            
            if((*$2) == "main")
            {
            	driver.funtab.AddFunction(CurrentFunction);
            	driver.toMIPS(".text");
            	driver.toMIPS(".globl main");
            	driver.toMIPS("jal main");
            	driver.toMIPS("done");
            	driver.toMIPS(".ent main");
            	driver.Label("main");
            }
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
            //call the 'done' macro to immediately terminate execution
			driver.toMIPS("done");
        }
    | ENDPROC
        {
            //mark the end of a procedure - output the epilog
    		stringstream ss1, ss2, ss3;
    		
    		int space = driver.funtab.GetStackSpace(CurrentFunction);
    		
    		ss2 << "lw $31, " << space << "($sp)";
    		driver.toMIPS(ss2.str());     
    		
    		ss1 << "addu $sp, $sp, " << (space + 4);    		
    		driver.toMIPS(ss1.str());   
    		
    		driver.toMIPS("jr $31");
    		
    		ss3 << ".end " << CurrentFunction;
    		driver.toMIPS(ss3.str());  
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

allocate_list
	: 
	
	| allocate allocate_list
	
	;
	
allocate
    : ALLOC STRING STRING STRING
    	{
    		//Add a variable reference to the function table and address table
    		driver.funtab.AddVariable(CurrentFunction, *$2,  std::stoi(*$4));
    		driver.addtab.Add(*$2, driver.funtab.GetVarOffset(CurrentFunction, *$2));
    	}
%%
void yy::TAC_Parser::error(const yy::TAC_Parser::location_type& loc,
                        const std::string& msg)
{
    driver.error(msg);
}




































