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

string toString(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}

string toString(int i, string txt)
{
	stringstream ss;
	ss << i << txt;
	return ss.str();
}

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
	
	| commands command
		
	;

command
	: tac_command
	
	| allocate_command_list
    	{
    		//Change the stack pointer after the allocate list is complete    		
    		int space = driver.funtab.GetStackSpace(CurrentFunction);
    		 		
    		driver.toMIPS("subu", "$sp", "$sp", toString(space + 4));    		
    		driver.toMIPS("sw", "$31", toString(space, "($sp)"));
    	}
	;
	
allocate_command_list
	:
	
	| allocate_command_list allocate_command
	
	;
	
allocate_command
    : ALLOC STRING STRING STRING
    	{
    		//Add a variable reference to the function table and address table
    		driver.funtab.AddVariable(CurrentFunction, *$2,  std::stoi(*$4));
    		driver.addtab.Add(*$2, driver.funtab.GetVarOffset(CurrentFunction, *$2));
    	}
    ;
    		
tac_command
    : ADD STRING STRING STRING
        {
            //adds $2 and $3 and places the result in $4
            			
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);
			
			driver.toMIPS("add", reg3, reg1, reg2);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | SUB STRING STRING STRING
        {
            //subtracts $2 and $3 and places the result in $4
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);
			
			driver.toMIPS("sub", reg3, reg2, reg1);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | MULT STRING STRING STRING
        {
            //multiplies $2 and $3 and places the result in $4
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);
			
			driver.toMIPS("mult", reg1, reg2);			
			driver.toMIPS("mflo", reg3);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | DIV STRING STRING STRING
        {
            //divides $2 by $3 and places the result in $4
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);
			
			driver.toMIPS("div", reg1, reg2);			
			driver.toMIPS("mflo", reg3);
			
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
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);			
			
			driver.toMIPS("seq", reg3, reg1, reg2);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | GT STRING STRING STRING
        {
            //if $2 is greater than $3, then $4 is set to 1, else $4 is set to 0
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);			
			
			driver.toMIPS("sgt", reg3, reg1, reg2);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | LT STRING STRING STRING
        {
            //if $2 is less than $3, then $4 is set to 1, else $4 is set to 0
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);			
			
			driver.toMIPS("slt", reg3, reg1, reg2);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | GE STRING STRING STRING
        {
            //if $2 is greater than $3, then $4 is set to 1, else $4 is set to 0
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);			
			
			driver.toMIPS("sge", reg3, reg1, reg2);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | REM STRING STRING STRING
        {
            //TODO
        }
    | LE STRING STRING STRING
        {
            //if $2 is less than or equal to $3, then $4 is set to 1, else $4 is set to 0
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);			
			
			driver.toMIPS("sle", reg3, reg1, reg2);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | NE STRING STRING STRING
        {
            //if $2 is not equal to $3, then $4 is set to 1, else $4 is set to 0
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);			
			
			driver.toMIPS("sne", reg3, reg1, reg2);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | BREQ STRING STRING STRING
        {
            //if $2 is equal to $3, then branch to $4
            
			string reg1 = driver.GetRegister(*$2);
			//string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("beq", reg1, (*$3), (*$4));
			
			driver.FreeRegister(reg1);
			//driver.FreeRegister(reg2);
        }
    | BRGT STRING STRING STRING
        {
            //if $2 is greater than $3, then branch to $4
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("bgt", reg1, reg2, (*$4));
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | BRLT STRING STRING STRING
        {
            //if $2 is less than $3, then branch to $4
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("blt", reg1, reg2, (*$4));
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | BRGE STRING STRING STRING
        {
            //if $2 is greater than or equal to $3, then branch to $4
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("bge", reg1, reg2, (*$4));
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | BRLE STRING STRING STRING
        {
            //if $2 is less than or equal to $3, then branch to $4
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("ble", reg1, reg2, (*$4));
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | BRNE STRING STRING STRING
        {
            //if $2 is not equal to $3, then branch to $4
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("bne", reg1, reg2, (*$4));
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
        }
    | BOUND STRING STRING STRING
        {
            //TODO
        }
    | MOV STRING STRING 
        {
            //This one does a store (it stores a register into a variable memory location)
            stringstream ss;
            
            string reg = driver.GetRegister(*$2);
            
            driver.addtab.Store(reg, *$3);
            
            ss << "\"The value of " << (*$3) << " is: \"";
                        
            driver.WS();
            driver.Comment("Output the stored value to verify program correctness...", true);
            driver.Macro("print_str", ss.str());
            driver.Macro("print_int", reg);
            driver.Macro("print_newline");            
            driver.WS();
        }
    | NEG STRING STRING 
        {
            //$3 is set to the negative value of $2
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("neg", reg1, reg2);
			
			driver.FreeRegister(reg2);
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
			ss << "\"" << (*$3) << "\"";
			driver.toMIPS(".asciiz", ss.str());
        }
    | IMMEDIATE_I STRING STRING
        {
            //load the value of $3 into the temporary $2 (integer)
			
			string reg = driver.GetRegister(*$2);
			
			driver.toMIPS("li", reg, (*$3));
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
			//if(driver.LabelExists(*$2))
			//{
				stringstream ss;
				ss << "b " << (*$2);
				
				driver.toMIPS("b", (*$2));
			//}
			//else
			//{
			//	driver.error("Attempted to branch to an unknown label");
			//}
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
            	driver.WS();
            	driver.toMIPS(".text");
            	driver.toMIPS(".globl", "main");
            	driver.WS();
            	driver.toMIPS("jal", "main");
            	driver.Macro("done");
            	driver.WS();
            	driver.toMIPS(".ent", "main");
            	driver.Label("main");
            }
        }
    | COMMENT_STRING
        {
            //output the comment $1
            driver.Comment(*$1, false);
        }
    | BEGINFRAME STRING
        {
            //begin a new frame and allocate $2 words of memory on the stack for variables
        }
    | HALT
        {
            //call the 'done' macro to immediately terminate execution
            driver.WS();
            driver.Comment("Immediately terminating execution", false);
			driver.Macro("done");
        }
    | ENDPROC
        {
            //mark the end of a procedure - output the epilog
            
    		int space = driver.funtab.GetStackSpace(CurrentFunction);
    		
    		driver.toMIPS("lw", "$31", toString(space, "($sp)"));   		
    		driver.toMIPS("addu", "$sp", "$sp", toString(space + 4));
    		driver.toMIPS("jr", "$31");
    		driver.toMIPS(".end", CurrentFunction);  
        	driver.WS();
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




































