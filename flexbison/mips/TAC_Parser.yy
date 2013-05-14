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
int CurrentParamCount = 0;

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
%token LABEL BR ARGS REFOUT VALOUT CALL PROCENTRY ALLOC VALAT PARAM FPAR
%token HALT ENDPROC RETURN
%token BEGINFRAME ENDFRAME

%%
commands
	: 
	
	| commands tac_command
		
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
			
			driver.toMIPS("div", reg2, reg1);			
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
            //Calculates the remainder and puts it in reg3
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);
			string reg3 = driver.GetRegister(*$4);
			
			driver.toMIPS("div", reg2, reg1);			
			driver.toMIPS("mfhi", reg3);
			
			driver.FreeRegister(reg1);
			driver.FreeRegister(reg2);
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
			
			driver.toMIPS("beq", reg1, (*$3), (*$4));
			
			driver.FreeRegister(reg1);
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
                        
            ss << "\"The value of " << (*$3) << " is: \"";
            
            driver.WS();
            driver.Comment("Output the stored value to verify program correctness...", true);
            driver.Macro("print_str", ss.str());
            driver.Macro("print_int", reg);
            driver.Macro("print_newline");            
            driver.WS();
            
            driver.addtab.Store(reg, *$3);
        }
    | VALAT STRING STRING
    	{
    		//loads the value at the address in $2 into the register $3
    		
    		//TODO: these registers
            string reg1 = driver.GetRegister(*$2);
            string reg2 = driver.GetRegister(*$3);
            
            stringstream ss;
            ss << "(" << reg2 << ")";
            
            driver.toMIPS("lw", reg1, ss.str());
            
            driver.FreeRegister(reg1);
    	}
    | NEG STRING STRING 
        {
            //$3 is set to the negative value of $2
            
			string reg1 = driver.GetRegister(*$2);
			string reg2 = driver.GetRegister(*$3);			
			
			driver.toMIPS("neg", reg2, reg1);
			
			driver.FreeRegister(reg2);
        }
    | NOT STRING STRING
        {
            //$3 is set to 1 if $2 is equal to 0, else $3 is set to 0
        }
    | ASSIGN STRING STRING
        {
            //store the value in register $2 to memory offset $3
            string reg1 = driver.GetRegister(*$2);
            string reg2 = driver.GetRegister(*$3);
            
            stringstream ss;
            ss << "(" << reg2 << ")";
            
            driver.toMIPS("sw", reg1, ss.str());
            
            driver.FreeRegister(reg1);
            driver.FreeRegister(reg2);
        }
    | ADDR STRING STRING 
        {
            //$3 is set to the address of $2
			Address* addr = driver.addtab.Lookup(*$2);
			
			if(addr)
			{
				string reg = driver.GetRegister(*$3);
				
				driver.toMIPS("add", reg, "$sp", toString(addr->memOffset));
			}
			else
			{
				cout << "Error: tried to get the address of an unknown variable"
				     << ", TAC_Parser.yy:394" 
					 << endl; 
			}
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
			
			driver.toMIPS("b", (*$2));
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
    | fpar_command_list CALL STRING 
        {
            //call the procedure labeled $2
            driver.toMIPS("jal", *$3);
            CurrentParamCount = 0;
        }
    | PROCENTRY STRING
        {
            //declare the beginning of a procedure named $2 - output the prolog
            CurrentFunction = (*$2);
            driver.CurrentFunction = CurrentFunction;
            
        	driver.funtab.AddFunction(CurrentFunction);
        	driver.WS();
        	driver.toMIPS(".ent", *$2);
        	driver.Label(*$2);
        }
        BEGINFRAME STRING allocate_command_list parameter_command_list 
    	{
    		//Change the stack pointer after the allocate list is complete    		
    		int space = driver.funtab.GetStackSpace(CurrentFunction);
    		 		
    		driver.toMIPS("subu", "$sp", "$sp", toString(space + 4));    		
    		driver.toMIPS("sw", "$ra", toString(space, "($sp)"));
    		
    		
    		
    		//Move parameters onto the stack so that they aren't lost
    		// Yes, I know this is a very jankity way of doing this...
    		// If we have more time later, I will come back and redo this...
    		
    		Function* current = driver.funtab.GetFunction(CurrentFunction);
    		
    		if(current && current->HasParams())
    		{
				auto end = driver.funtab.ParamsEnd(CurrentFunction);
				for(auto it = driver.funtab.ParamsBegin(CurrentFunction); it != end; ++it)
				{
					int offset = driver.funtab.GetVarOffset(CurrentFunction, (*it)->name);
				
					stringstream ss;
					ss << offset << "($sp)";
			
					driver.toMIPS("sw", (*it)->regName, ss.str());
				}
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
    		
    		//TODO These next two lines should be moved into the ENDFRAME production
    		// in order to deal with scoping
    		driver.toMIPS("lw", "$ra", toString(space, "($sp)"));   		
    		driver.toMIPS("addu", "$sp", "$sp", toString(space + 4));
    		
    		driver.toMIPS("jr", "$ra");
    		driver.toMIPS(".end", CurrentFunction);  
        	driver.WS();
        }
    | RETURN STRING
        {
            //return control to the caller
            
            string reg = driver.GetRegister(*$2);
            
            driver.toMIPS("add", "$v0", "$zero", reg);
        }
    | ENDFRAME 
        {
            //end the current frame
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
    		if(*$3 == "INT")
    		{
    			driver.funtab.AddVariable(CurrentFunction, *$2,  std::stoi(*$4));
    			driver.addtab.Add(*$2, driver.funtab.GetVarOffset(CurrentFunction, *$2));
    		}
    		else
    		{
    			//it is an INTARRAY then
    			driver.funtab.AddVariable(CurrentFunction, *$2,  std::stoi(*$4) * 4);
    			driver.addtab.Add(*$2, driver.funtab.GetVarOffset(CurrentFunction, *$2));
    		}
    	}
    ;

parameter_command_list
	:
	
	| parameter_command_list parameter_command
	
	;

parameter_command
	: PARAM STRING STRING STRING
		{
			//This function has a parameter named $2 of type $3 and size $4
			string reg = driver.funtab.AddParameter(CurrentFunction, *$2);
			
			driver.funtab.AddVariable(CurrentFunction, *$2,  std::stoi(*$4));
			driver.addtab.Add(*$2, driver.funtab.GetVarOffset(CurrentFunction, *$2));
		}
	;

fpar_command_list
	:
	
	|	fpar_command_list fpar_command
	
	;
	
fpar_command
	: FPAR STRING
		{
			//Move the parameters into the $a0-3 registers
			
            string reg = driver.GetRegister(*$2);
            
            stringstream ss;
            ss << "$a" << CurrentParamCount;
            CurrentParamCount++;
            
            driver.toMIPS("add", ss.str(), "$zero", reg);
            
            driver.FreeRegister(reg);
		}
%%
void yy::TAC_Parser::error(const yy::TAC_Parser::location_type& loc,
                        const std::string& msg)
{
    driver.error(msg);
}




































