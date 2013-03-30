%require "2.7"

%define parser_class_name "CParser"

%code requires {
#include <string>
#include <sstream>
#include <iostream>
#include "SymTab.h"

#include "Ast.h"

class CCompiler;
}

%parse-param { CCompiler& driver }
%lex-param   { CCompiler& driver }

%initial-action
{
    //Initialize the filename
    @$.begin.filename = @$.end.filename = &driver.fname;
};

%error-verbose

%union 
{
    int          ival;
    double	 dval;
    std::string *sval;
    SymbolInfo  *sym;
    AST         *ast;
};

%printer { driver.ydbFile << "Value: " << $$; } <ival> <dval>
%printer { driver.ydbFile << "Value: " << *$$; } <sval>
%printer { driver.ydbFile << "Name: " << $$->symbol_name; } <sym>

%destructor { if(!$$) delete $$; } <sval> <sym>

%code {
#include "CCompiler.h"
}

%token END 0 "EOF"
%token <sym>  IDENTIFIER
%token <ival> INTEGER_CONSTANT 
%token <dval> FLOATING_CONSTANT 
%token <sval> CHARACTER_CONSTANT 
%token <sym>  ENUMERATION_CONSTANT 
%token <sval> STRING_LITERAL
%token <sym>  TYPEDEF_NAME

%token SIZEOF
%token PTR_OP 
%token INC_OP DEC_OP 
%token LEFT_OP RIGHT_OP 
%token LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP 
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN 
%token LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN 
%token STAR BIN_OR BIN_XOR BIN_AND 
%token LT_OP GT_OP PLUS MINUS DIV MOD TILDE BANG DOT WHAT
%token LBRACE RBRACE LBRAK RBRAK LPAREN RPAREN EQ COMMA COLON SEMI
%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <ast> identifier string constant argument_expression_list primary_expression
%type <ast> postfix_expression unary_operator unary_expression
%type <ast> multiplicative_expression additive_expression shift_expression

%type <ast> assignment_expression expression cast_expression type_name

%%
translation_unit
	: external_declaration
		{
		    driver.printRed("translation_unit -> external_declaration");
		}
	| translation_unit external_declaration
		{
		    driver.printRed("translation_unit -> translation_unit external_declaration");
		}
	;

enter_scope
	: /* Empty - This is a dummy production used for entering scopes */
		{
		    std::stringstream ss;
		    ss << "Entering new scope: line - " << @$.begin.line << ", col - " << @$.begin.column;
		    driver.printDebug(ss.str());

		    driver.enterScope();
		}
	;

leave_scope
	: /* Empty - This is a dummy production used for leaving scopes */
		{
		    std::stringstream ss;
		    ss << "Leaving scope: line - " << @$.begin.line << ", col - " << @$.begin.column;
		    driver.printDebug(ss.str());

		    driver.leaveScope();
		}
	;

insert_mode
	: /* Empty - This is a dummy production used for setting insert mode */
		{
		    std::stringstream ss;
		    ss << "Starting insert mode: line - " << @$.begin.line << ", col - " << @$.begin.column;
		    driver.printDebug(ss.str());

		    driver.set_insert_mode(true);
		}
	;

lookup_mode
	: /* Empty - This is a dummy production used for setting lookup mode */
		{
		    std::stringstream ss;
		    ss << "Starting lookup mode: line - " << @$.begin.line << ", col - " << @$.begin.column;
		    driver.printDebug(ss.str());

		    driver.set_insert_mode(false);
		}
	;

external_declaration
	: function_definition
		{
		    driver.printRed("external_declaration -> function_declaration");
		}
	| declaration
		{
		    driver.printRed("external_declaration -> declaration");
		}
	;

function_definition
	: declarator compound_statement
		{
		    driver.printRed("function_definition -> declarator compound_statement");
		}
	| declarator declaration_list compound_statement
		{
		    driver.printRed("function_definition -> declarator declaration_list compound_statement");
		}
	| declaration_specifiers declarator compound_statement
		{
		    driver.printRed("function_definition -> declaration_specifiers declarator coumpound_statement");
		}
	| declaration_specifiers declarator declaration_list compound_statement
		{
		    driver.printRed("function_definition -> declaration_specifiers declarator declaration_list compound)_statement");
		}
	;

declaration
	: declaration_specifiers SEMI
		{
		    driver.printDebug("Declaration .... "); 
                    driver.printRed("declaration -> declaration_specifiers SEMI");
                                     
		}
	| declaration_specifiers init_declarator_list SEMI
		{
		    driver.printRed("declaration -> declaration_specifiers init_declarator_list SEMI");
                    
		       SymbolInfo *inf  = driver.currentSymbol;
                       if ( inf->storage_class == TYPEDEF)
                       {
                         inf->symbolType = new TypedefType(inf->symbolType,inf->symbol_name);  

                       } 
                       driver.SymbolTable.insert_symbol(*inf);
                       driver.allocateSymbol();

                       if ( driver.trace_symtab) 
                       {
                           std::cout << "Inserted symbol: " << inf->symbol_name
                                     << ", Type: " << inf->symbolType->GetName()
                                     << std::endl; 
                       }
                    
		}
	;

declaration_list
	: declaration
		{
		    driver.printRed("declaration_list -> declaration");
		}
	| declaration_list declaration
		{
		    driver.printRed("declaration_list -> declaration_list declaration");
		}
	;

declaration_specifiers
	: storage_class_specifier
		{
		    driver.printRed("declaration_specifiers -> storage_class_specifier");
		}
	| storage_class_specifier declaration_specifiers
		{
		    driver.printRed("declaration_specifiers -> storage_class_specifier declaration_specifiers");
		}
	| type_specifier
		{
		    driver.printRed("declaration_specifiers -> type_specifier");
		}
	| type_specifier declaration_specifiers
		{
		    driver.printRed("declaration_specifiers -> type_specifier declaration_specifiers");
		}
	| type_qualifier 
		{
		    driver.printRed("declaration_specifiers -> type_qualifier");
		}
	| type_qualifier declaration_specifiers
		{
		    driver.printRed("declaration_specifiers -> type_qualifier declaration_specifiers");
		}
	;

storage_class_specifier
	: AUTO
		{
		    driver.printRed("storage_class_specifier -> AUTO");
		    driver.currentSymbol->storage_class = AUTO;  
		}
	| REGISTER
		{
		    driver.printRed("storage_class_specifier -> REGISTER");
                    driver.currentSymbol->storage_class = REGISTER;  
 
		}
	| STATIC
		{
		    driver.printRed("storage_class_specifier -> STATIC");
                    driver.currentSymbol->storage_class = STATIC;  

		}
	| EXTERN
		{
		    driver.printRed("storage_class_specifier -> EXTERN");
                    driver.currentSymbol->storage_class = EXTERN;  
            
		}
	| TYPEDEF
		{
		    driver.printRed("storage_class_specifier -> TYPEDEF");
                    driver.currentSymbol->storage_class = TYPEDEF;  
 
		}
	;

type_specifier
	: VOID
		{
		       
                    driver.printRed("type_specifier -> VOID");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType("VOID",INT_SIZE);

 
		}
	| CHAR
		{
		    driver.printRed("type_specifier -> CHAR");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType("CHAR",CHAR_SIZE);
		}
	| SHORT
		{
		    driver.printRed("type_specifier -> SHORT");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType( "SHORT", SHORT_SIZE);
		}
	| INT
		{
		    driver.printRed("type_specifier -> INT");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType( "INT", INT_SIZE);

		}
	| LONG
		{
		    driver.printRed("type_specifier -> LONG");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType("LONG" , LONG_SIZE);
		}
	| FLOAT 
		{
		    driver.printRed("type_specifier -> FLOAT");
                    if ( driver.currentSymbol->symbolType == NULL )
                       driver.currentSymbol->symbolType = new PODType ("FLOAT" , FLOAT_SIZE); 
		}
	| DOUBLE
		{
		    driver.printRed("type_specifier -> DOUBLE");
                    ////std::cout<<"Double ...";
                    if ( driver.currentSymbol->symbolType == NULL )
                      driver.currentSymbol->symbolType = new PODType( "DOUBLE", DOUBLE_SIZE);
                    ///else 
                      //////std::cout<<  driver.currentSymbol->symbolType->GetName();  
		}
	| SIGNED
		{
		    PODType *newPod = new PODType("INT",INT_SIZE);
                    newPod->SetSigned(true); 
                    driver.printRed("type_specifier -> SIGNED"); 
                    driver.currentSymbol->symbolType = newPod;
                     

		}
	| UNSIGNED
		{
		    PODType *newPod = new PODType("INT",INT_SIZE);
                    newPod->SetSigned(false); 
                    driver.printRed("type_specifier -> UNSIGNED");
                    driver.currentSymbol->symbolType = newPod; 


	        }
	| struct_or_union_specifier
		{
		    driver.printRed("type_specifier -> struct_or_union_specifier");

		}
	| enum_specifier
		{
		    driver.printRed("type_specifier -> enum_specifier");
		}
	| TYPEDEF_NAME
		{
		    driver.printRed("type_specifier -> TYPEDEF_NAME");
		}
	;

type_qualifier
	: CONST
		{
		    driver.printRed("type_qualifier -> CONST");
                    driver.currentSymbol->type_qualifier = CONST;
		}
	| VOLATILE
		{
		    driver.printRed("type_qualifier -> VOLATILE");
                    driver.currentSymbol->type_qualifier = VOLATILE;
             
		}
	;

struct_or_union_specifier
	: struct_or_union identifier new_struct_union_decl LBRACE struct_declaration_list RBRACE  struct_union_decl_end

		{
		    driver.printRed("struct_or_union_specifier -> struct_or_union identifier LBRACE struct_declaration_list RBRACE");
                      
		}
	| struct_or_union LBRACE struct_declaration_list RBRACE
		{
		    driver.printRed("struct_or_union_specifier -> struct_or_union LBRACE struct_declaration_list RBRACE");
		}
	| struct_or_union identifier
		{
		    driver.printRed("struct_or_union_specifier -> struct_or_union identifier");
		}
	;

struct_or_union
	: STRUCT
		{
		    driver.printRed("struct_or_union -> STRUCT");
                    ++driver.structUnionMode; 
		}
	| UNION
		{
		    driver.printRed("struct_or_union -> UNION");
                    driver.currentSymbol->symbolType = new StructType("UNION");
                    ++driver.structUnionMode;     
		}
	;

struct_declaration_list
	: struct_declaration
		{
		    driver.printRed("struct_declaration_list -> struct_declaration");
		}
	| struct_declaration_list struct_declaration
		{
		    driver.printRed("struct_declaration_list -> struct_declaration_list struct_declaration");
		}
	;

init_declarator_list
	: init_declarator new_symbol_declaration
		{
		    driver.printRed("init_declarator_list -> init_declarator");
		}
	| init_declarator_list COMMA  new_symbol_declaration init_declarator
		{
		    driver.printRed("init_declarator_list COMMA init_declarator");
		}
	;
new_symbol_declaration
        :
        {
           SymbolInfo *inf  = driver.currentSymbol;          
           if (driver.structUnionMode )
              driver.structUnionTypes.push_back(*inf);  
           else     
              driver.SymbolTable.insert_symbol(*inf);
           driver.allocateSymbol();
           driver.currentSymbol = inf;   
           if ( inf->symbolType->GetName() == "POINTER"|| inf->symbolType->GetName() == "ARRAY") 
           {
	       driver.currentSymbol->symbolType = GetInnerType(inf->symbolType);        
                
           }
           
             
           
        }   
        ;
new_enum_constant
        :
        {
            driver.enumConsts.push_back(driver.currentSymbol->symbol_name); 
                       
        }   
        ;
reset_current_symbol
        :
        {
 
            driver.allocateSymbol(); 

        }
        ;
new_struct_union_decl
        :
        {
             SymbolInfo *inf = driver.currentSymbol;
             driver.structUnionTypes.push_back(*inf);
             driver.allocateSymbol();     
        }     
        ;
struct_union_decl_end
        :
        {
             driver.structUnionTypes.pop_back();
             list<SymbolInfo >::iterator endItem =  driver.structUnionTypes.end() , structPos; 
             SymbolInfo currentStruct; 
             StructType *currentStructType;
             int count = 0 ; 
             endItem++;          
             while( endItem !=  driver.structUnionTypes.begin() && (endItem)->symbolType->GetName() != "STRUCT")
             {
                    --endItem;

             } 
             structPos  = endItem;  
             endItem++;
                           
             while( endItem != driver.structUnionTypes.end())
             {
                if( structPos->symbolType == NULL )
                {
                      ////std::cout<<"\n Null type :(  \n"; 
                }
                else 
                    ////std::cout<< "\n TYPE = "<<structPos->symbolType->GetName();
                currentStructType  = new StructType("STRUCT");
                ///currentStructType->AddMember(endItem->symbol_name,new PODType("INT",INT_SIZE)); 
                structPos->symbolType = currentStructType; 

                 endItem++;  
                 count++;         
             }           
                         
             while(count )
             {
                --count ; 
                 driver.structUnionTypes.pop_back();   
             }   
             --driver.structUnionMode;
              
             if ( driver.structUnionMode == 0  )
             {
                  driver.SymbolTable.insert_symbol(*structPos);  
                  driver.structUnionTypes.clear(); 
             }   
             
        }
        ;
                   
 
init_declarator
	: declarator
		{
		    driver.printRed("init_declarator -> declarator");
		}
	| declarator EQ initializer
		{
		    driver.printRed("init_declarator -> declarator EQ initializer");
		}
	;

struct_declaration
	: specifier_qualifier_list set_member_type  struct_declarator_list  fix_struct_member_types SEMI
		{
		    driver.printRed("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMI");
                    
		}
	;

set_member_type
       :
              {
                  driver.structMemberType = driver.currentSymbol->symbolType;

              }
       ;
            
fix_struct_member_types
       :
           {
                    ////std::cout<<" \n Current Type : " << driver.structMemberType->GetName();
                    ////std::cout<<" \n Current Structure Variable Count : " << driver.structVarCount;
                     
                     
                    list<SymbolInfo>::iterator itemFixStart = driver.structUnionTypes.end()  ;
                    Type *innerType; 
                    for ( int count =0 ; count < driver.structVarCount ; count++)
                       itemFixStart--; 
                    while( itemFixStart != driver.structUnionTypes.end() )
                    {
                           if ( itemFixStart->symbolType == NULL )
                           {
                                  itemFixStart->symbolType = driver.structMemberType;
                           }
                           else 
                           {
                                  innerType = itemFixStart->symbolType;
                                  while( innerType->GetName() == "POINTER" || innerType->GetName() == "ARRAY" )
                                  {
                                       if ( innerType->GetName() == "POINTER")
                                               innerType = ((PointerType *)innerType)->GetBase();
                                       else
                                               innerType = ((ArrayType*)innerType)->GetBase();
   
                                  }
                                  innerType = driver.structMemberType;
                                  itemFixStart->symbolType = innerType; 
                           }
                          ++itemFixStart; 
                    }
                    driver.structVarCount = 0 ; 
                      
           }
                    

       ;

specifier_qualifier_list
	: type_specifier
		{
		    driver.printRed("specifier_qualifier_list -> type_specifier");
		}
	| type_specifier specifier_qualifier_list
		{
		    driver.printRed("specifier_qualifier_list -> type_specifier specifier_qualifier_list");
		}
	| type_qualifier
		{
		    driver.printRed("specifier_qualifier_list -> type_qualifier");
		}
	| type_qualifier specifier_qualifier_list
		{
		    driver.printRed("specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
		}
	;

struct_declarator_list
	: struct_declarator reset_current_symbol
		{
		    driver.printRed("struct_declarator_list -> struct_declarator");
		}
	| struct_declarator_list   COMMA   struct_declarator
		{
		    driver.printRed("struct_declarator_list -> struct_declarator_list COMMA struct_declarator");
		}
	;

struct_declarator
	: declarator 
		{
		    driver.printRed("struct_declarator -> declarator");
                    //std::cout<< " --->CURRENT SYM : " << driver.currentSymbol->symbol_name;
                    SymbolInfo *inf = driver.currentSymbol;  
                    driver.structUnionTypes.push_back(*inf);    
                    driver.structVarCount++; 
		}
	| COLON constant_expression
		{
		    driver.printRed("struct_declarator -> COLON constant_expression");
		}
	| declarator  COLON constant_expression
		{
		    driver.printRed("struct_declarator -> declarator COLON constant_expression");
                    //std::cout<< " --->CURRENT SYM : " << driver.currentSymbol->symbol_name;
                    driver.structUnionTypes.push_back(*(driver.currentSymbol));
		}
	;

enum_specifier
	: ENUM LBRACE enumerator_list RBRACE
		{
		     list<string>::iterator enumItems = driver.enumConsts.begin();
                     driver.printRed("enum_specifier -> ENUM LBRACE enumerator_list RBRACE");
                     while( enumItems != driver.enumConsts.end())
                     {
                            SymbolInfo *inf = new SymbolInfo();
                            inf->isEnumConst = true;
                            inf->symbolType = new PODType("ENUMCONST",INT_SIZE);
                            inf->symbol_name = *enumItems; 
                            driver.SymbolTable.insert_symbol(*inf);  
                            enumItems++;
                     }   
                     driver.enumConsts.clear();
                     driver.allocateSymbol();       
		}
	| ENUM identifier  new_enum_type LBRACE enumerator_list RBRACE
		{
                    driver.printRed("enum_specifier -> ENUM identifier LBRACE enumerator_list RBRACE");
                    list<string>::iterator enumItems = driver.enumConsts.begin();
                     driver.printRed("enum_specifier -> ENUM LBRACE enumerator_list RBRACE");
                     while( enumItems != driver.enumConsts.end())
                     {
                            SymbolInfo *inf = new SymbolInfo();
                            inf->isEnumConst = true;
                            inf->symbolType = new PODType("ENUMCONST",INT_SIZE);
                            inf->symbol_name = *enumItems; 
                            driver.SymbolTable.insert_symbol(*inf);  
                            driver.enumType->AddEnumConst(*enumItems);
                            enumItems++;
                     }  
                     driver.enumSym->symbolType =  driver.enumType;
                     driver.SymbolTable.insert_symbol(*(driver.enumSym));
                     driver.enumConsts.clear();
                     driver.allocateSymbol();       

		}
	| ENUM identifier
		{
		    driver.printRed("enum_specifier -> ENUM identifier");
		}
	;

new_enum_type:
       {
                    driver.enumSym = new SymbolInfo(); 
                    driver.enumType = new EnumType("ENUM", 0); 
                    driver.enumSym->symbol_name = driver.currentSymbol->symbol_name;
                    driver.allocateSymbol();     
        
       }
       ;

enumerator_list
	: enumerator
		{
		    driver.printRed("enumerator_list -> enumerator");
		}
	| enumerator_list COMMA enumerator
		{
		    driver.printRed("enumerator_list -> enumerator_list COMMA enumerator");
		}
	;

enumerator
	: identifier new_enum_constant
		{
		    driver.printRed("enumerator -> identifier");
		}
	| identifier new_enum_constant EQ constant_expression
		{
		    driver.printRed("enumerator -> identifier EQ constant_expression");
		}
	;

declarator
	: direct_declarator 
		{
		    driver.printRed("declarator -> direct_declarator");
		}
	| pointer direct_declarator 
		{
		    driver.printRed("declarator -> pointer direct_declarator");
		}
	;

direct_declarator
	: identifier 
		{
		    
                    driver.printRed("direct_declarator -> identifier");
                    
                   
		}
	| LPAREN declarator RPAREN
		{
		    driver.printRed("direct_declarator -> LPAREN declarator RPAREN");
		}
	| direct_declarator LBRAK RBRAK
		{
		    driver.printRed("direct_declarator -> LBRAK RBRAK");
                    driver.currentSymbol->symbolType  = new ArrayType(driver.currentSymbol->symbolType,"ARRAY", 0);

		}
	| direct_declarator LBRAK constant_expression RBRAK
		{
		    driver.printRed("direct_declarator -> direct_declarator LBRAK constant_expression RBRAK");
                    driver.currentSymbol->symbolType  = new ArrayType(driver.currentSymbol->symbolType,"ARRAY", 0);
 
		}
	| direct_declarator LPAREN RPAREN
		{
		    driver.printRed("direct_declarator -> direct_declarator LPAREN RPAREN");
		}
	| direct_declarator LPAREN parameter_type_list RPAREN
		{
		    driver.printRed("direct_declarator -> LPAREN parameter_type_list RPAREN");
		}
	| direct_declarator LPAREN identifier_list RPAREN
		{
		    driver.printRed("direct_declarator -> LPAREN identifier_list RPAREN");
		}
	;

pointer
	: STAR
		{
		    driver.printRed("pointer -> star");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);
		}
	| STAR type_qualifier_list
		{
		    driver.printRed("pointer -> STAR type_qualifier_list");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);
  
		}
	| STAR pointer
		{
		    driver.printRed("pointer -> STAR pointer");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);

                         
		}
	| STAR type_qualifier_list pointer
		{
		    driver.printRed("pointer -> STAR type_qualifier_list pointer");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);
 
		}
	;

type_qualifier_list
	: type_qualifier
		{
		    driver.printRed("type_qualifier_list -> type_qualifier");
		}
	| type_qualifier_list type_qualifier
		{
		    driver.printRed("type_qualifier_list -> type_qualifier_list type_qualifier");
		}
	;

parameter_type_list
	: parameter_list
		{
		    driver.printRed("parameter_type_list -> parameter_list");
		}
	| parameter_list COMMA ELIPSIS
		{
		    driver.printRed("parameter_type_list -> parameter_list COMMA ELIPSIS");
		}
	;

parameter_list
	: parameter_declaration
		{
		    driver.printRed("parameter_list -> parameter_declaration");
		}
	| parameter_list COMMA parameter_declaration
		{
		    driver.printRed("parameter_list -> parameter_list COMMA parameter_declaration");
		}
	;

parameter_declaration
	: declaration_specifiers declarator
		{
		    driver.printRed("parameter_declaration -> declaration_specifiers declarator");
		}
	| declaration_specifiers
		{
		    driver.printRed("parameter_declaration -> declaration_specifiers");
		}
	| declaration_specifiers abstract_declarator
		{
		    driver.printRed("parameter_declaration -> declaration_specifiers abstract_declarator");
		}
	;

identifier_list
	: identifier
		{
		    driver.printRed("identifier_list -> identifier");
		}
	| identifier_list COMMA identifier
		{
		    driver.printRed("identifier_list -> identifier_list COMMA indentifier");
		}
	;

initializer
	: assignment_expression
		{
		    driver.printRed("initializer -> assignment_expression");
		}
	| LBRACE initializer_list RBRACE
		{
		    driver.printRed("initializer -> LBRACE initializer_list RBRACE");
		}
	| LBRACE initializer_list COMMA RBRACE
		{
		    driver.printRed("initializer -> LBRACE initializer_list COMMA RBRACE");
		}
	;

initializer_list
	: initializer
		{
		    driver.printRed("initializer_list -> initializer");
		}
	| initializer_list COMMA initializer
		{
		    driver.printRed("initializer_list -> initializer_list COMMA initializer");
		}
	;

type_name
	: specifier_qualifier_list
		{
		    driver.printRed("type_name -> specifier_qualifier_list");
		}
	| specifier_qualifier_list abstract_declarator
		{
		    driver.printRed("type_name -> specifier_qualifier_list abstract_declarator");
		}
	;

abstract_declarator
	: pointer
		{
		    driver.printRed("abstract_declarator -> pointer");
		}
	| direct_abstract_declarator
		{
		    driver.printRed("abstract_declarator -> direct_abstract_declarator");
		}
	| pointer direct_abstract_declarator
		{
		    driver.printRed("abstract_declarator -> pointer direct_abstract_declarator");
		}
	;

direct_abstract_declarator
	: LPAREN abstract_declarator RPAREN
		{
		    driver.printRed("direct_abstract_declarator -> LPAREN abstract_declarator RPAREN");
		}
	| LBRAK RBRAK
		{
		    driver.printRed("direct_abstract_declarator -> LBRAK RBRAK");
		}
	| LBRAK constant_expression RBRAK
		{
		    driver.printRed("direct_abstract_declarator -> LBRAK constant_expression RBRAK");
		}
	| direct_abstract_declarator LBRAK RBRAK
		{
		    driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LBRAK RBRAK");
		}
	| direct_abstract_declarator LBRAK constant_expression RBRAK
		{
		    driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LBRAK constant_expression RBRAK");
		}
	| LPAREN RPAREN
		{
		    driver.printRed("direct_abstract_declarator -> LPAREN RPAREN");
		}
	| LPAREN parameter_type_list RPAREN
		{
		    driver.printRed("direct_abstract_declarator -> LPAREN parameter_type_list RPAREN");
		}
	| direct_abstract_declarator LPAREN RPAREN
		{
		    driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LPAREN RPAREN");
		}
	| direct_abstract_declarator LPAREN parameter_type_list RPAREN
		{
		    driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LPAREN parameter_type_list RPAREN");
		}
	;

statement
	: labeled_statement
		{
		    driver.printRed("statement -> labeled_statement");
		}
	| compound_statement 
		{
		    driver.printRed("statement -> compound_statement");
		}
	| expression_statement
		{
		    driver.printRed("statement -> expression_statement");
		}
	| selection_statement
		{
		    driver.printRed("statement -> selection_statement");
		}
	| iteration_statement
		{
		    driver.printRed("statement -> iteration_statement");
		}
	| jump_statement
		{
		    driver.printRed("statement -> jump_statement");
		}
	;

labeled_statement
	: identifier COLON statement
		{
		    driver.printRed("labeled_statement -> identifier COLON statement");
		}
	| CASE constant_expression COLON statement
		{
		    driver.printRed("labeled_statement -> CASE constant_expression COLON statement");
		}
	| DEFAULT COLON statement
		{
		    driver.printRed("labeled_statement -> DEFAULT COLON statement");
		}
	;

expression_statement
	: SEMI
		{
		    driver.printRed("expression_statement -> SEMI");
		}
	| expression SEMI
		{
		    driver.printRed("expression_statement -> expression SEMI");
		}
	;

compound_statement
	: LBRACE reset_current_symbol RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE RBRACE");
		}
	| LBRACE reset_current_symbol enter_scope lookup_mode statement_list leave_scope RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE statement_list RBRACE");
		}
	| LBRACE  reset_current_symbol enter_scope insert_mode declaration_list lookup_mode leave_scope RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE declaration_list RBRACE");
		}
	| LBRACE  reset_current_symbol enter_scope insert_mode declaration_list lookup_mode statement_list leave_scope RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE declaration_list statement_list RBRACE");
		}
	;

statement_list
	: statement
		{
		    driver.printRed("statement_list -> statement");
		}
	| statement_list statement
		{
		    driver.printRed("statement_list -> statement_list statement");
		}
	;

selection_statement
	: IF LPAREN expression RPAREN statement
		{
		    driver.printRed("selection_statement -> IF LPAREN expression RPAREN statement");
		}
	| IF LPAREN expression RPAREN statement ELSE statement
		{
		    driver.printRed("selection_statement -> IF LPAREN expression RPAREN statement ELSE statement");
		}
	| SWITCH LPAREN expression RPAREN statement
		{
		    driver.printRed("selection_statement -> SWITCH LPAREN expression RPAREN statement");
		}
	;

iteration_statement
	: WHILE LPAREN expression RPAREN statement
		{
		    driver.printRed("iteration_statement -> WHILE LPAREN expression RPAREN statement");
		}
	| DO statement WHILE LPAREN expression RPAREN SEMI
		{
		    driver.printRed("iteration_statement -> DO statement WHILE LPAREN expression RPAREN SEMI");
		}
	| FOR LPAREN SEMI SEMI RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN SEMI SEMI RPAREN statement");
		}
	| FOR LPAREN SEMI SEMI expression RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN SEMI SEMI expression RPAREN statement");
		}
	| FOR LPAREN SEMI expression SEMI RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN SEMI expression SEMI RPAREN statement");
		}
	| FOR LPAREN SEMI expression SEMI expression RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN SEMI expression SEMI expression RPAREN statement");
		}
	| FOR LPAREN expression SEMI SEMI RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN expression SEMI SEMI RPAREN statement");
		}
	| FOR LPAREN expression SEMI SEMI expression RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN expression SEMI SEMI expression RPAREN statement");
		}
	| FOR LPAREN expression SEMI expression SEMI RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN expression SEMI expression SEMI RPAREN statement");
		}
	| FOR LPAREN expression SEMI expression SEMI expression RPAREN statement
		{
		    driver.printRed("iteration_statement -> FOR LPAREN expression SEMI expression SEMI expression RPAREN statement");
		}
	;

jump_statement
	: GOTO identifier SEMI
		{
		    driver.printRed("jump_statement -> GOTO identifier SEMI");
		}
	| CONTINUE SEMI
		{
		    driver.printRed("jump_statement -> CONTINUE SEMI");
		}
	| BREAK SEMI
		{
		    driver.printRed("jump_statement -> BREAK SEMI");
		}
	| RETURN SEMI
		{
		    driver.printRed("jump_statement -> RETURN SEMI");
		}
	| RETURN expression SEMI
		{
		    driver.printRed("jump_statement -> RETURN expression SEMI");
		}
	;

expression
	: assignment_expression
		{
		    driver.printRed("expression -> assignment_expression");
		}
	| expression COMMA assignment_expression
		{
		    driver.printRed("expression -> expression COMMA assignment_expression");
		}
	;

assignment_expression
	: conditional_expression
		{
		    driver.printRed("assignment_expression -> conditional_expression");
		}
	| unary_expression assignment_operator assignment_expression
		{
		    driver.printRed("assignment_expression -> unary_expression assignment_operator assignment_expression");
		}
	;

assignment_operator
	: EQ
		{
		    driver.printRed("assignment_operator -> EQ");
		}
	| MUL_ASSIGN
		{
		    driver.printRed("assignment_operator -> MUL_ASSIGN");
		}
	| DIV_ASSIGN
		{
		    driver.printRed("assignment_operator -> DIV_ASSIGN");
		}
	| MOD_ASSIGN
		{
		    driver.printRed("assignment_operator -> MOD_ASSIGN");
		}
	| ADD_ASSIGN
		{
		    driver.printRed("assignment_operator -> ADD_ASSIGN");
		}
	| SUB_ASSIGN
		{
		    driver.printRed("assignment_operator -> SUB_ASSIGN");
		}
	| LEFT_ASSIGN
		{
		    driver.printRed("assignment_operator -> LEFT_ASSIGN");
		}
	| RIGHT_ASSIGN
		{
		    driver.printRed("assignment_operator -> RIGHT_ASSIGN");
		}
	| AND_ASSIGN
		{
		    driver.printRed("assignment_operator -> AND_ASSIGN");
		}
	| XOR_ASSIGN
		{
		    driver.printRed("assignment_operator -> XOR_ASSIGN");
		}
	| OR_ASSIGN
		{
		    driver.printRed("assignment_operator -> OR_ASSIGN");
		}
	;

conditional_expression
	: logical_or_expression
		{
		    driver.printRed("conditional_expression -> logical_or_expression");
		}
	| logical_or_expression WHAT expression COLON conditional_expression
		{
		    driver.printRed("conditional_expresion -> logical_or_expression WHAT expression COLON conditional_expression");
		}
	;

constant_expression
	: conditional_expression
		{
		    driver.printRed("constant_expression -> conditional_expression");
		}
	;

logical_or_expression
	: logical_and_expression
		{
		    driver.printRed("logical_or_expression -> logical_and_expression");
		}
	| logical_or_expression OR_OP logical_and_expression	
		{
		    driver.printRed("logical_or_expression -> logical_or_epression OR_OP logical_and_expression");
		}
	;

logical_and_expression
	: inclusive_or_expression
		{
		    driver.printRed("logical_and_expression -> inclusive_or_expression");
		}
	| logical_and_expression AND_OP inclusive_or_expression
		{
		    driver.printRed("logical_and_expression -> logical_and_expression AND_OP inclusive_or_expression");
		}
	;

inclusive_or_expression
	: exclusive_or_expression
		{
		    driver.printRed("inclusive_or_expression -> exclusive_or_expression");
		}
	| inclusive_or_expression BIN_OR exclusive_or_expression
		{
		    driver.printRed("inclusive_or_expression -> inclusive_or_expression BIN_OR exclusive_or_expression");
		}
	;

exclusive_or_expression
	: and_expression
		{
		    driver.printRed("exclusive_or_expression -> and_expression");
		}
	| exclusive_or_expression BIN_XOR and_expression
		{
		    driver.printRed("exclusive_or_expression -> exclusive_or_expression BIN_XOR and_expression");
		}
	;

and_expression
	: equality_expression
		{
		    driver.printRed("and_expression -> equality_expression");
		}
	| and_expression BIN_AND equality_expression
		{
		    driver.printRed("and_expression -> and_expression BIN_AND equality_expression");
		}
	;

equality_expression
	: relational_expression
		{
		    driver.printRed("equality_expression -> relational_expression");
		}
	| equality_expression EQ_OP relational_expression
		{
		    driver.printRed("equality_expression -> equality_expression EQ_OP relational_expression");
		}
	| equality_expression NE_OP relational_expression
		{
		    driver.printRed("equality_expression -> equality_expression NE_OP relational_expression");
		}
	;

relational_expression
	: shift_expression
		{
		    driver.printRed("relational_expression -> shift_expression");
		}
	| relational_expression LT_OP shift_expression
		{
		    driver.printRed("relational_expression -> relational_expression LT_OP shift_expression");
		}
	| relational_expression GT_OP shift_expression
		{
		    driver.printRed("relational_expression -> relational_expression GT_OP shift_expression");
		}
	| relational_expression LE_OP shift_expression
		{
		    driver.printRed("relational_expression -> relational_expression LE_OP shift_expression");
		}
	| relational_expression GE_OP shift_expression
		{
		    driver.printRed("relational_expression -> relational_expression GE_OP shift_expression");
		}
	;

shift_expression
	: additive_expression
		{
		    driver.printRed("shift_expression -> additive_expression");
                    $$ = (AST*) new AstShiftExpr((AstAddExpr*)$1);
		}
	| shift_expression LEFT_OP additive_expression
		{
		    driver.printRed("shift_expression -> shift_expression LEFT_OP additive_expression");
                    $$ = (AST*) new AstShiftExpr((AstShiftExpr*)$1, AstShiftExpr::LEFT_OP, (AstAddExpr*)$3);
		}
	| shift_expression RIGHT_OP additive_expression
		{
		    driver.printRed("shift_expression -> shift_expression RIGHT_OP additive_expression");
                    $$ = (AST*) new AstShiftExpr((AstShiftExpr*)$1, AstShiftExpr::RIGHT_OP, (AstAddExpr*)$3);
		}
	;

additive_expression
	: multiplicative_expression
		{
		    driver.printRed("additive_expression -> multiplicative_expression");
                    $$ = (AST*) new AstAddExpr((AstMultExpr*)$1);
		}
	| additive_expression PLUS multiplicative_expression
		{
		    driver.printRed("additive_expression -> additive_expression PLUS multiplicative_expression");
                    $$ = (AST*) new AstAddExpr((AstAddExpr*)$1, AstAddExpr::PLUS, (AstMultExpr*)$3);
		}
	| additive_expression MINUS multiplicative_expression
		{
		    driver.printRed("additive_expression -> additive_expression MINUS multiplicative_expression");
                    $$ = (AST*) new AstAddExpr((AstAddExpr*)$1, AstAddExpr::MINUS, (AstMultExpr*)$3);
		}
	;

multiplicative_expression
	: cast_expression
		{
		    driver.printRed("multiplicative_expression -> cast_expression");
                    $$ = (AST*) new AstMultExpr((AstCastExpr*)$1);
		}
	| multiplicative_expression STAR cast_expression
		{
		    driver.printRed("multiplicative_expression -> multiplicative_expression STAR cast_expression");
                    $$ = (AST*) new AstMultExpr((AstMultExpr*)$1, AstMultExpr::STAR, (AstCastExpr*)$3);
		}
	| multiplicative_expression DIV cast_expression
		{
		    driver.printRed("multiplicative_expression -> multiplicative_expression DIV cast_expression");
                    $$ = (AST*) new AstMultExpr((AstMultExpr*)$1, AstMultExpr::DIV, (AstCastExpr*)$3);
		}
	| multiplicative_expression MOD cast_expression
		{
		    driver.printRed("multiplicative_expression -> multiplicative_expression MOD cast_expression");
                    $$ = (AST*) new AstMultExpr((AstMultExpr*)$1, AstMultExpr::MOD, (AstCastExpr*)$3);
		}
	;

cast_expression
	: unary_expression
		{
		    driver.printRed("cast_expression -> unary_expression");
                    $$ = (AST*) new AstCastExpr((AstUnaryExpr*)$1);
		}
	| LPAREN type_name RPAREN cast_expression
		{
		    driver.printRed("cast_expression -> LPAREN type_name RPAREN cast_expression");
                    $$ = (AST*) new AstCastExpr((AstTypeName*)$2, (AstCastExpr*)$4);
		}
	;

unary_expression
	: postfix_expression
		{
		    driver.printRed("unary_expression -> postfix_expression");
                    $$ = (AST*) new AstUnaryExpr((AstPostfixExpr*)$1);
		}
	| INC_OP unary_expression
		{
		    driver.printRed("unary_expression -> INC_OP unary_expression");
                    $$ = (AST*) new AstUnaryExpr((AstUnaryExpr*)$2, true);
		}
	| DEC_OP unary_expression
		{
		    driver.printRed("unary_expression -> DEC_OP unary_expression");
                    $$ = (AST*) new AstUnaryExpr((AstUnaryExpr*)$2, false);
		}
	| unary_operator cast_expression
		{
		    driver.printRed("unary_expression -> unary_operator cast_expression");
                    $$ = (AST*) new AstUnaryExpr((AstUnaryOp*)$1, (AstCastExpr*)$2);
		}
	| SIZEOF unary_expression
		{
		    driver.printRed("unary_expression -> SIZEOF unary_expression");
                    $$ = (AST*) new AstUnaryExpr((AstUnaryExpr*)$2);
		}
	| SIZEOF LPAREN type_name RPAREN
		{
		    driver.printRed("unary_expression -> SIZEOF LPAREN type_name RPAREN");
                    $$ = (AST*) new AstUnaryExpr((AstTypeName*)$3);
		}
	;

unary_operator
	: BIN_AND
		{
		    driver.printRed("unary_operator -> BIN_AND");
                    $$ = (AST*) new AstUnaryOp(AstUnaryOp::BIN_AND);
		}
	| STAR
		{
		    driver.printRed("unary_operator -> STAR");
                    $$ = (AST*) new AstUnaryOp(AstUnaryOp::STAR);
		}
	| PLUS
		{
		    driver.printRed("unary_operator -> PLUS");
                    $$ = (AST*) new AstUnaryOp(AstUnaryOp::PLUS);
		}
	| MINUS
		{
		    driver.printRed("unary_operator -> MINUS");
                    $$ = (AST*) new AstUnaryOp(AstUnaryOp::MINUS);
		}
	| TILDE
		{
		    driver.printRed("unary_operator -> TILDE");
                    $$ = (AST*) new AstUnaryOp(AstUnaryOp::TILDE);
		}
	| BANG
		{
		    driver.printRed("unary_operator -> BANG");
                    $$ = (AST*) new AstUnaryOp(AstUnaryOp::BANG);
		}
	;

postfix_expression
	: primary_expression
		{
		    driver.printRed("postfix_expression -> primary_expression");
                    $$ = (AST*) new AstPostfixExpr((AstPrimaryExpr*)$1);
		}
	| postfix_expression LBRAK expression RBRAK
		{
		    driver.printRed("postfix_expression -> postfix_expression LBRAK expression RBRAK");
                    $$ = (AST*) new AstPostfixExpr((AstPostfixExpr*)$1, (AstExpression*)$3);
		}
	| postfix_expression LPAREN RPAREN
		{
		    driver.printRed("postfix_expression -> postfix_expression LPAREN RPAREN");
                    $$ = (AST*) new AstPostfixExpr((AstPostfixExpr*)$1);
		}
	| postfix_expression LPAREN argument_expression_list RPAREN
		{
		    driver.printRed("postfix_expression -> postfix_expression LPAREN argument_expression_list RPAREN");
                    $$ = (AST*) new AstPostfixExpr((AstPostfixExpr*)$1, (AstArgExprList*)$3);
		}
	| postfix_expression DOT identifier
		{
		    driver.printRed("postfix_expression -> postfix_expression DOT identifier");
                    $$ = (AST*) new AstPostfixExpr((AstPostfixExpr*)$1, AstPostfixExpr::DOT_OP, (AstID*)$3);
		}
	| postfix_expression PTR_OP identifier
		{
		    driver.printRed("postfix_expression -> postfix_expression PTR_OP identifier");
                    $$ = (AST*) new AstPostfixExpr((AstPostfixExpr*)$1, AstPostfixExpr::PTR_OP, (AstID*)$3);
		}
	| postfix_expression INC_OP
		{
		    driver.printRed("postfix_expression -> INC_OP");
                    $$ = (AST*) new AstPostfixExpr((AstPostfixExpr*)$1, AstPostfixExpr::INC_OP);
		}
	| postfix_expression DEC_OP
		{
		    driver.printRed("postfix_expression -> postfix_expression DEC_OP");
                    $$ = (AST*) new AstPostfixExpr((AstPostfixExpr*)$1, AstPostfixExpr::DEC_OP);
		}
	;

primary_expression
	: identifier
		{
		    driver.printRed("primary_expression -> identifier");
                    $$ = (AST*) new AstPrimaryExpr((AstID*)$1);
		}
	| constant
		{
		    driver.printRed("primary_expression -> constant");
                    $$ = (AST*) new AstPrimaryExpr((AstConstant*)$1);
		}
	| string
		{
		    driver.printRed("primary_expression -> string");
                    $$ = (AST*) new AstPrimaryExpr((AstString*)$1);
		}
	| LPAREN expression RPAREN
		{
		    driver.printRed("primary_expression -> LPAREN expression RPAREN");
                    $$ = (AST*) new AstPrimaryExpr((AstExpression*)$2);
		}
	;

argument_expression_list
	: assignment_expression
		{
		    driver.printRed("argument_expression_list -> assignment_expression");

                    //Notice the casts - this is required because otherwise every type of
                    // AST derived class would have to be in the %union declaration
                    $$ = (AST*) new AstArgExprList((AstAssignExpr*)$1);
		}
	| argument_expression_list COMMA assignment_expression
		{
		    driver.printRed("argument_expression_list -> argument_expression_list COMMA assignment_expression");
                    $$ = (AST*) new AstArgExprList((AstArgExprList*)$1, (AstAssignExpr*)$3);
		}
	;

constant
	: INTEGER_CONSTANT
		{
		    driver.printRed("constant -> INTEGER_CONSTANT");
		    $$ = (AST*) new AstConstant($1);
		}
	| CHARACTER_CONSTANT
		{
		    driver.printRed("constant -> CHARACTER_CONSTANT");
                    $$ = (AST*) new AstConstant(*$1);
		}
	| FLOATING_CONSTANT
		{
		    driver.printRed("constant -> FLOATING_CONSTANT");
                    $$ = (AST*) new AstConstant($1);
		}
	| ENUMERATION_CONSTANT
		{
		    driver.printRed("constant -> ENUMERATION_CONSTANT");

                    // TODO check how to get the value from an enum const (checkType needs to be fixed)
                    // $$ = (AST*) new AstConstant($1->symbol_name /*value*/, /*enum const name*/);
		}
	;

string
	: STRING_LITERAL
		{
		    driver.printRed("string -> STRING_LITERAL");
                    $$ = (AST*) new AstString(*$1);
		}
	;

identifier
	: IDENTIFIER
		{
		    //cout << *$1;
                    driver.currentSymbol->symbol_name = $1->symbol_name;  
                    driver.printRed("identifier -> IDENTIFIER");
                    $$ = (AST*) new AstID($1->symbol_name);
		}
	;
%%
void yy::CParser::error(const yy::CParser::location_type& loc,
                        const std::string& msg)
{
    driver.error(loc, msg);
}
