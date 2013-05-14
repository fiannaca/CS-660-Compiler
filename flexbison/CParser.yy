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
    double   dval;
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
%type <ast> relational_expression equality_expression and_expression
%type <ast> exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <ast> constant_expression conditional_expression assignment_operator assignment_expression


%type <ast>  expression cast_expression type_name  
%type <ast>  jump_statement iteration_statement statement selection_statement statement_list compound_statement declaration_list
%type <ast>  expression_statement  labeled_statement  direct_abstract_declarator parameter_type_list abstract_declarator
%type <ast>  pointer  type_specifier  type_qualifier struct_declaration_list storage_class_specifier 
%type <ast>  translation_unit  external_declaration function_definition declaration  declarator declaration_specifiers
%type <ast>  init_declarator_list  struct_or_union_specifier enum_specifier  type_qualifier_list
%type <ast>  struct_declarator_list struct_declaration init_declarator initializer direct_declarator identifier_list
%type <ast>  specifier_qualifier_list initializer_list  parameter_list parameter_declaration
%type <ast>  enumerator enumerator_list  struct_declarator  
%%
translation_unit
    : external_declaration
        {
            driver.printRed("translation_unit -> external_declaration");
                    $$ = (AST *) new AstTrans( NULL , ( AstExternDec *) $1);
                    driver.source_ast = $$;   
        }
    | translation_unit external_declaration
        {
            driver.printRed("translation_unit -> translation_unit external_declaration");
                    $$ = (AST *) new AstTrans( (AstTrans*) $1 , ( AstExternDec *) $2);
                    driver.source_ast = $$;  
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

          //  driver.leaveScope();
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
            driver.printRed("exterfunction_definitionnal_declaration -> function_declaration");
            $$ = (AST *)$1;
             

        }
    | declaration
        {
            driver.printRed("external_declaration -> declaration");
            $$ = (AST *)$1;
        }
    ;

function_definition
    : declarator set_function_name compound_statement
        {
            driver.printRed("function_definition -> declarator compound_statement");
            $$ = (AST *) new AstFuncDef ( ( AstDeclarator *) $1 , ( AstCompound *) $3  , NULL , NULL ) ;
            driver.currentFunctionName = ((AstFuncDef*)$$)->GetFunctionName(); 
            driver.leaveScope();
              
        }
    | declarator set_function_name declaration_list compound_statement
        {
            driver.printRed("function_definition -> declarator declaration_list compound_statement");
             $$ = (AST *) new AstFuncDef ( ( AstDeclarator *) $1 , ( AstCompound *) $4  ,(AstDeclList *)$3 , NULL ) ; 
            driver.currentFunctionName = ((AstFuncDef*)$$)->GetFunctionName();
            driver.leaveScope();  
        }
    | declaration_specifiers  declarator  set_function_name compound_statement
        {
            driver.printRed("function_definition -> declaration_specifiers declarator coumpound_statement");
            $$ = (AST *) new AstFuncDef ( ( AstDeclarator *) $2 , ( AstCompound *) $4  ,NULL  , (AstDecSpeci*)$1 ) ;
            driver.currentFunctionName = ((AstFuncDef*)$$)->GetFunctionName();
            driver.leaveScope(); 
        }
    | declaration_specifiers  declarator  set_function_name declaration_list compound_statement
        {
            driver.printRed("function_definition -> declaration_specifiers declarator declaration_list compound)_statement");
            $$ = (AST *) new AstFuncDef ( ( AstDeclarator *) $2 , ( AstCompound *) $5  ,(AstDeclList *)$4, (AstDecSpeci*)$1 ) ;
            driver.currentFunctionName = ((AstFuncDef*)$$)->GetFunctionName();
            driver.leaveScope(); 
        }
    ;
set_function_name:
     {
        //driver.currentFunctionName = driver.currentSymbol->symbol_name;
        //cout<<"Current function name = "<< driver.currentFunctionName << endl;
     
     }
     
     ;
declaration
    : declaration_specifiers SEMI
        {
            driver.printDebug("Declaration .... "); 
                    driver.printRed("declaration -> declaration_specifiers SEMI");
            $$ = (AST *) new AstDecl ( (AstDecSpeci *)$1 , NULL);
                                     
        }
    | declaration_specifiers init_declarator_list SEMI
        {
            driver.printRed("declaration -> declaration_specifiers init_declarator_list SEMI");
                    
               SymbolInfo *inf  = driver.currentSymbol;
                       /*
                       if ( inf->storage_class == TYPEDEF)
                       {
                         inf->symbolType = new TypedefType(inf->symbolType,inf->symbol_name);  

                       } 
                       //inf->lineNum = yylloc.begin.line;
                       driver.SymbolTable.insert_symbol(*inf);
                       driver.allocateSymbol();

                       if ( driver.trace_symtab) 
                       {
                           std::cout << "Inserted symbol:  < declaration_specifiers init_declarator_list SEMI > " << inf->symbol_name
                                     << ", Type: " <<  (( inf->symbolType != NULL ) ? inf->symbolType->GetName() : "not  known" )
                                     << std::endl; 
                       }
                        */   
             $$ = (AST *) new AstDecl ( (AstDecSpeci *)$1 , (AstInitSpecList *)$2);       
        }
    ;

declaration_list
    : declaration
        {
            driver.printRed("declaration_list -> declaration");
            $$ = (AST *) new AstDeclList(NULL ,(AstDecl *) $1) ;
        }
    | declaration_list declaration
        {
            driver.printRed("declaration_list -> declaration_list declaration");
            $$ = (AST *) new AstDeclList((AstDeclList *)$1 ,(AstDecl *) $2) ;
        }
    ;

declaration_specifiers
    : storage_class_specifier
        {
            driver.printRed("declaration_specifiers -> storage_class_specifier");
            $$ = (AST *) new AstDecSpeci(driver.currentStorageType,"",NULL,NULL); 
        }
    | storage_class_specifier declaration_specifiers
        {
            driver.printRed("declaration_specifiers -> storage_class_specifier declaration_specifiers");
            $$ = (AST *) new AstDecSpeci(driver.currentStorageType,"",(AstDecSpeci *)$2,NULL);
        }
    | type_specifier
        {
            driver.printRed("declaration_specifiers -> type_specifier");
            $$ = (AST *) new AstDecSpeci(driver.currentStorageType,"",NULL,(AstTypeSpeci*)$1);
        }
    | type_specifier declaration_specifiers
        {
            driver.printRed("declaration_specifiers -> type_specifier declaration_specifiers");
            $$ = (AST *) new AstDecSpeci(driver.currentStorageType,"",(AstDecSpeci *)$2,(AstTypeSpeci*)$1);
        }
    | type_qualifier 
        {
            driver.printRed("declaration_specifiers -> type_qualifier");
            $$ = (AST *) new AstDecSpeci("",driver.currentTypeQual ,NULL,NULL);
        }
    | type_qualifier declaration_specifiers
        {
            driver.printRed("declaration_specifiers -> type_qualifier declaration_specifiers");
            $$ = (AST *) new AstDecSpeci("",driver.currentTypeQual ,(AstDecSpeci *)$2,NULL);
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
             driver.currentStorageType = "REGISTER";
 
        }
    | STATIC
        {
            driver.printRed("storage_class_specifier -> STATIC");
            driver.currentSymbol->storage_class = STATIC;  
            driver.currentStorageType = "STATIC";

        }
    | EXTERN
        {
            driver.printRed("storage_class_specifier -> EXTERN");
                    driver.currentSymbol->storage_class = EXTERN;  
             driver.currentStorageType = "EXTERN";
            
        }
    | TYPEDEF
        {
            driver.printRed("storage_class_specifier -> TYPEDEF");
                    driver.currentSymbol->storage_class = TYPEDEF;
                    driver.currentStorageType = "TYPEDEF";    
 
        }
    ;

type_specifier
    : VOID
        {
               
                    driver.printRed("type_specifier -> VOID");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType("VOID",INT_SIZE);
                    $$  =(AST *) new AstTypeSpeci( "VOID" , NULL , NULL  );

 
        }
    | CHAR
        {
            driver.printRed("type_specifier -> CHAR");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType("CHAR",CHAR_SIZE);
             $$  =(AST *) new AstTypeSpeci( "CHAR" , NULL, NULL  );
        }
    | SHORT
        {
            driver.printRed("type_specifier -> SHORT");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType( "SHORT", SHORT_SIZE);
            $$  =(AST *) new AstTypeSpeci( "SHORT" , NULL , NULL );
        }
    | INT
        {
            driver.printRed("type_specifier -> INT");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType( "INT", INT_SIZE);
            $$  =(AST *) new AstTypeSpeci( "INT" , NULL, NULL  );

        }
    | LONG
        {
            driver.printRed("type_specifier -> LONG");
                    if ( driver.currentSymbol->symbolType == NULL )
                        driver.currentSymbol->symbolType = new PODType("LONG" , LONG_SIZE);
                   $$  =(AST *) new AstTypeSpeci( "LONG" , NULL , NULL );
        }
    | FLOAT 
        {
            driver.printRed("type_specifier -> FLOAT");
                    if ( driver.currentSymbol->symbolType == NULL )
                       driver.currentSymbol->symbolType = new PODType ("FLOAT" , FLOAT_SIZE); 
                   $$  =(AST *) new AstTypeSpeci( "FLOAT" , NULL , NULL );
            
        }
    | DOUBLE
        {
            driver.printRed("type_specifier -> DOUBLE");
                    //std::cout<<"Double ...";
                    if ( driver.currentSymbol->symbolType == NULL )
                      driver.currentSymbol->symbolType = new PODType( "DOUBLE", DOUBLE_SIZE);
                    //else 
                      //std::cout<<  driver.currentSymbol->symbolType->GetName();  
                    $$  =(AST *) new AstTypeSpeci( "DOUBLE" , NULL, NULL  );
        }
    | SIGNED
        {
            PODType *newPod = new PODType("INT",INT_SIZE);
                    newPod->SetSigned(true); 
                    driver.printRed("type_specifier -> SIGNED"); 
                    driver.currentSymbol->symbolType = newPod;
                    $$  =(AST *) new AstTypeSpeci( "SIGNED" , NULL, NULL  );
                     

        }
    | UNSIGNED
        {
            PODType *newPod = new PODType("INT",INT_SIZE);
                    newPod->SetSigned(false); 
                    driver.printRed("type_specifier -> UNSIGNED");
                    driver.currentSymbol->symbolType = newPod; 
            $$  =(AST *) new AstTypeSpeci( "UNSIGNED" , NULL , NULL );  
               
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
            driver.currentTypeQual = "CONST";       
        }
    | VOLATILE
        {
            driver.printRed("type_qualifier -> VOLATILE");
                    driver.currentSymbol->type_qualifier = VOLATILE;
            driver.currentTypeQual = "VOLATILE";
             
        }
    ;

struct_or_union_specifier
    : struct_or_union identifier new_struct_union_decl LBRACE struct_declaration_list RBRACE  struct_union_decl_end

        {
            driver.printRed("struct_or_union_specifier -> struct_or_union identifier LBRACE struct_declaration_list RBRACE");
            $$  = (AST *)new AstStructUniSpeci("STRUCT" , (AstID  *) $2 , (AstStructDeclList *)$5); 
                      
        }
    | struct_or_union LBRACE struct_declaration_list RBRACE
        {
            driver.printRed("struct_or_union_specifier -> struct_or_union LBRACE struct_declaration_list RBRACE");
            $$  = (AST *)new AstStructUniSpeci("STRUCT" , NULL , (AstStructDeclList *)$3); 
        }
    | struct_or_union identifier
        {
            driver.printRed("struct_or_union_specifier -> struct_or_union identifier");
            $$  = (AST *)new AstStructUniSpeci("STRUCT" , (AstID  *) $2 , NULL); 
            
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
            $$ = (AST *)new  AstStructDeclList(  (AstStructDecl *)  $2 , (AstStructDeclList *) $1   ); 
        }
    ;

init_declarator_list
    : init_declarator new_symbol_declaration
        {
            driver.printRed("init_declarator_list -> init_declarator");
            $$ = (AST *)new AstInitDeclList((AstInitDeclarator *)$1 , NULL);
        }
    | init_declarator_list COMMA  new_symbol_declaration init_declarator
        {
            driver.printRed("init_declarator_list COMMA init_declarator");
            $$ = (AST *)new AstInitDeclList((AstInitDeclarator *)$4 , ( AstInitDeclList *) $1);
        }
    ;
new_symbol_declaration
        :
        {
           SymbolInfo *inf  = driver.currentSymbol;          
           if (driver.structUnionMode )
              driver.structUnionTypes.push_back(*inf);  
           else    
             { 
              if ( inf->storage_class == TYPEDEF)
              {
                   inf->symbolType = new TypedefType(inf->symbolType,inf->symbol_name);  

              } 

              driver.SymbolTable.insert_symbol(*inf);
              if ( driver.trace_symtab) 
                       {
                           std::cout << "Inserted symbol: < new_symbol_declaration > " << inf->symbol_name
                                     << ", Type: " << (( inf->symbolType != NULL ) ? inf->symbolType->GetName() : "not  known " )

                                     << std::endl; 
                       }
             }   
           driver.allocateSymbol();
           driver.currentSymbol->symbolType = inf->symbolType;    
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
                  if ( driver.trace_symtab) 
                       {
                           std::cout << "Inserted symbol: < struct_union_decl_end > " << structPos->symbol_name
                                     << ", Type: " << (( structPos->symbolType != NULL ) ? structPos->symbolType->GetName() : "not  known " )
                                     << std::endl; 
                       }
                  driver.structUnionTypes.clear(); 
             }   
             
        }
        ;
                   
 
init_declarator
    : declarator
        {
            driver.printRed("init_declarator -> declarator");
            $$ = (AST *)new AstInitDeclarator( ( AstDeclarator *)$1 , NULL);
           
        }
    | declarator EQ initializer
        {
            driver.printRed("init_declarator -> declarator EQ initializer");
            $$ = (AST *) new AstInitDeclarator( ( AstDeclarator *)$1 , (AstInitializer *)$3);
        }
    ;

struct_declaration
    : specifier_qualifier_list set_member_type  struct_declarator_list  fix_struct_member_types SEMI
        {
            driver.printRed("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMI");
            $$ = (AST *) new AstStructDecl ( (AstSpeciQualList*)$1 , (AstStructDeclList *)$3 );
                    
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
            $$ = (AST *)new AstSpeciQualList ( NULL , driver.currentTypeQual , NULL);
        }
    | type_qualifier specifier_qualifier_list
        {
            driver.printRed("specifier_qualifier_list -> type_qualifier specifier_qualifier_list");
            $$ = (AST *)new AstSpeciQualList ( NULL , driver.currentTypeQual , (AstSpeciQualList*)$2 );
        }
    ;

struct_declarator_list
    : struct_declarator reset_current_symbol
        {
            $$ = (AST *)  new AstStructDeclatorList ( (AstStructDeclarator *)$1 , NULL );
            driver.printRed("struct_declarator_list -> struct_declarator");
        }
    | struct_declarator_list   COMMA   struct_declarator
        {
            $$ = (AST *)  new AstStructDeclatorList ( (AstStructDeclarator *)$3 , ( AstStructDeclList *) $1 );
            driver.printRed("struct_declarator_list -> struct_declarator_list COMMA struct_declarator");
        }
    ;

struct_declarator
    : declarator 
        {
            $$ = (AST *) new AstStructDeclarator( (AstDeclarator *)$1 , NULL);
            driver.printRed("struct_declarator -> declarator");
                    //std::cout<< " --->CURRENT SYM : " << driver.currentSymbol->symbol_name;
                    SymbolInfo *inf = driver.currentSymbol;  
                    driver.structUnionTypes.push_back(*inf);    
                    driver.structVarCount++; 
                
        }
    | COLON constant_expression
        {
            $$ = (AST *) new AstStructDeclarator( NULL , (AstExpression *)$2);
            driver.printRed("struct_declarator -> COLON constant_expression");
        }
    | declarator  COLON constant_expression
        {
            $$ = (AST *) new AstStructDeclarator( (AstDeclarator *)$1 , (AstExpression *)$3);
            driver.printRed("struct_declarator -> declarator COLON constant_expression");
                    //std::cout<< " --->CURRENT SYM : " << driver.currentSymbol->symbol_name;
                    driver.structUnionTypes.push_back(*(driver.currentSymbol));
        }
    ;

enum_specifier
    : ENUM LBRACE enumerator_list RBRACE
        {
             $$ = (AST *) new EnumSpecifier ( NULL , (AstEnumList *)$3);
             list<string>::iterator enumItems = driver.enumConsts.begin();
                     driver.printRed("enum_specifier -> ENUM LBRACE enumerator_list RBRACE");
                     while( enumItems != driver.enumConsts.end())
                     {
                            SymbolInfo *inf = new SymbolInfo();
                            inf->isEnumConst = true;
                            inf->symbolType = new PODType("ENUMCONST",INT_SIZE);
                            inf->symbol_name = *enumItems; 
                            driver.SymbolTable.insert_symbol(*inf); 
                            if ( driver.trace_symtab) 
                            {
                                   std::cout << "Inserted symbol:  <enum_specifier >  " << inf->symbol_name
                                     << ", Type: " << (( inf->symbolType != NULL ) ? inf->symbolType->GetName() : "not  known " )
                                     << std::endl; 
                            } 
                                 enumItems++;
                     }   
                     driver.enumConsts.clear();
                     driver.allocateSymbol();       
        }
    | ENUM identifier  new_enum_type LBRACE enumerator_list RBRACE
        {
                    $$ = (AST *) new EnumSpecifier ( (AstID *)$2 , (AstEnumList *)$5);
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
                            if ( driver.trace_symtab) 
                            {
                               std::cout << "Inserted symbol:  < ENUM identifier  new_enum_type LBRACE enumerator_list RBRACE>" << inf->symbol_name
                                     << ", Type: " << (( inf->symbolType != NULL ) ? inf->symbolType->GetName() : "not  known " )
                                     << std::endl; 
                            }
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
            $$ = (AST *) new AstEnumList ( (AstEnumerator *) $1 , NULL );
        }
    | enumerator_list COMMA enumerator
        {
            driver.printRed("enumerator_list -> enumerator_list COMMA enumerator");
            $$ = (AST *) new AstEnumList ( (AstEnumerator *) $3 , (AstEnumList *)$1 );
        }
    ;

enumerator
    : identifier new_enum_constant
        {
            driver.printRed("enumerator -> identifier");
            $$ = (AST *) new AstEnumerator ( (AstID *)$1 , NULL );
        }
    | identifier new_enum_constant EQ constant_expression
        {
            driver.printRed("enumerator -> identifier EQ constant_expression");
            $$ = (AST *) new AstEnumerator ( (AstID *)$1 , (AstExpression *)$4 );
        }
    ;

declarator
    : direct_declarator 
        {
            driver.printRed("declarator -> direct_declarator");
            $$ = (AST *) new AstDeclarator( NULL  , (AstDirectDecl *) $1);
           
        }
    | pointer direct_declarator 
        {
            driver.printRed("declarator -> pointer direct_declarator");
            $$ = (AST *) new AstDeclarator( (AstPointer * )$1  , (AstDirectDecl *) $2);
        }
    ;

direct_declarator
    : identifier 
        {
            
                    driver.printRed("direct_declarator -> identifier");
                    $$ = (AST *) new AstDirectDecl( (AstID *) $1 , NULL , NULL , NULL , NULL , NULL ,1);
                    
                   
        }
    | LPAREN declarator RPAREN
        {
            driver.printRed("direct_declarator -> LPAREN declarator RPAREN");
            $$ = (AST *) new AstDirectDecl( NULL , NULL , NULL , ( AstDeclarator *)$2 , NULL , NULL ,2 );
        }
    | direct_declarator LBRAK RBRAK
        {
            driver.printRed("direct_declarator -> LBRAK RBRAK");
            driver.currentSymbol->symbolType  = new ArrayType(driver.currentSymbol->symbolType,"ARRAY", 0);
            $$ = (AST *) new AstDirectDecl( NULL , (AstDirectDecl *) $1 , NULL , NULL , NULL , NULL,3 );

        }
    | direct_declarator LBRAK constant_expression RBRAK
        {
            driver.printRed("direct_declarator -> direct_declarator LBRAK constant_expression RBRAK");
            std::cout<< " Current Constant expresssion , Value = "<< AST::currentConstantValue;
            driver.currentSymbol->symbolType  = new ArrayType(driver.currentSymbol->symbolType,"ARRAY", AST::currentConstantValue);
            $$ = (AST *) new AstDirectDecl( NULL , (AstDirectDecl *) $1 , (AstExpression * )$3, NULL , NULL , NULL ,4);
 
        }
    | direct_declarator LPAREN RPAREN
        {
            driver.printRed("direct_declarator -> direct_declarator LPAREN RPAREN");
            $$ = (AST *) new AstDirectDecl( NULL , (AstDirectDecl *) $1 , NULL , NULL , NULL , NULL,5 );
        }
    | direct_declarator LPAREN parameter_type_list RPAREN
        {
            driver.printRed("direct_declarator -> LPAREN parameter_type_list RPAREN");
            $$ = (AST *) new AstDirectDecl( NULL , (AstDirectDecl *) $1 , NULL , NULL , (AstTypeParamList *)$3 , NULL,6 );
        }
    | direct_declarator LPAREN identifier_list RPAREN
        {
            driver.printRed("direct_declarator -> LPAREN identifier_list RPAREN");
            $$ = (AST *) new AstDirectDecl( NULL , (AstDirectDecl *) $1 , NULL , NULL , NULL, (AstIDList *)$3,7 );
        }
    ;

pointer
    : STAR
        {
            driver.printRed("pointer -> star");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);
            $$ = (AST *) new AstPointer(NULL,NULL);
        }
    | STAR type_qualifier_list
        {
            driver.printRed("pointer -> STAR type_qualifier_list");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);
            $$ = ( AST *) new AstPointer(NULL , (AstTypeQualList *)$2);
 
  
        }
    | STAR pointer
        {
            driver.printRed("pointer -> STAR pointer");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);
            $$ = ( AST *) new AstPointer((AstPointer *)$2 , NULL);

                         
        }
    | STAR type_qualifier_list pointer
        {
            driver.printRed("pointer -> STAR type_qualifier_list pointer");
                    driver.currentSymbol->symbolType  = new PointerType(driver.currentSymbol->symbolType,"POINTER", INT_SIZE);
            $$ = ( AST *) new AstPointer((AstPointer *)$3 , (AstTypeQualList *)$2);
             
        }
    ;

type_qualifier_list
    : type_qualifier
        {
            driver.printRed("type_qualifier_list -> type_qualifier");
            $$ = (AST *)new AstTypeQualList( driver.currentTypeQual, NULL);
        }
    | type_qualifier_list type_qualifier
        {
            driver.printRed("type_qualifier_list -> type_qualifier_list type_qualifier");
            $$ = (AST *)new AstTypeQualList( driver.currentTypeQual,(AstTypeQualList *) $1);
        }
    ;

parameter_type_list
    : parameter_list
        {
            driver.printRed("parameter_type_list -> parameter_list");
            $$ = (AST *) new AstTypeParamList ( 1 , (AstParamList *)$1 ) ;
        }
    | parameter_list COMMA ELIPSIS
        {
            driver.printRed("parameter_type_list -> parameter_list COMMA ELIPSIS");
            $$ = (AST *) new AstTypeParamList ( 2 , (AstParamList *)$1 ) ;
        }
    ;

parameter_list
    : parameter_declaration
        {
            driver.printRed("parameter_list -> parameter_declaration");
            $$ = (AST *) new AstParamList ( (AstParamDec *)$1 , NULL );
        }
    | parameter_list COMMA parameter_declaration
        {
            driver.printRed("parameter_list -> parameter_list COMMA parameter_declaration");
            $$ = (AST *) new AstParamList ( (AstParamDec *)$3 , (AstParamList *)$1 );
        }
    ;

parameter_declaration
    : declaration_specifiers declarator
        {
            driver.printRed("parameter_declaration -> declaration_specifiers declarator");
            $$ = (AST *) new AstParamDec((AstDecSpeci *)$1 , (AstDeclarator *)$2 , NULL );
        }
    | declaration_specifiers
        {
            driver.printRed("parameter_declaration -> declaration_specifiers");
             $$ = (AST *) new AstParamDec((AstDecSpeci *)$1 , NULL , NULL );
        }
    | declaration_specifiers abstract_declarator
        {
            driver.printRed("parameter_declaration -> declaration_specifiers abstract_declarator");
            $$ = (AST *) new AstParamDec((AstDecSpeci *)$1 , NULL , (AstAbstractDecl *) $2);
        }
    ;

identifier_list
    : identifier
        {
            driver.printRed("identifier_list -> identifier");
            $$ = (AST *) new  AstIDList ( (AstID *)$1 , NULL );
        }
    | identifier_list COMMA identifier
        {
            driver.printRed("identifier_list -> identifier_list COMMA indentifier");
            $$ = (AST *) new  AstIDList ( (AstID *)$3 , ( AstIDList *) $1 );
        }
    ;

initializer
    : assignment_expression
        {
            driver.printRed("initializer -> assignment_expression");
            $$ = (AST *) new AstInitializer ( (AstAssignExpr *)$1 , NULL , 1); 
        }
    | LBRACE initializer_list RBRACE
        {
            driver.printRed("initializer -> LBRACE initializer_list RBRACE");
            $$ = (AST *) new AstInitializer (NULL , (AstInitList *)$2 , 2);
        }
    | LBRACE initializer_list COMMA RBRACE
        {
            driver.printRed("initializer -> LBRACE initializer_list COMMA RBRACE");
             $$ = (AST *) new AstInitializer (NULL , (AstInitList *)$2 , 3);
        }
    ;

initializer_list
    : initializer
        {
            driver.printRed("initializer_list -> initializer");
            $$ = (AST *) new AstInitList((AstInitializer *)$1 , NULL );
        }
    | initializer_list COMMA initializer
        {
            driver.printRed("initializer_list -> initializer_list COMMA initializer");
            $$ = (AST *) new AstInitList( (AstInitializer *)$3 , (AstInitList *)$1 );
        }
    ;

type_name
    : specifier_qualifier_list
        {
            driver.printRed("type_name -> specifier_qualifier_list");
            $$ = (AST *) new AstTypeName((AstSpeciQualList *)$1 , NULL );
        }
    | specifier_qualifier_list abstract_declarator
        {
            driver.printRed("type_name -> specifier_qualifier_list abstract_declarator");
            $$ = (AST *) new AstTypeName((AstSpeciQualList *)$1 , (AstAbstractDecl *)$2 );
        }
    ;

abstract_declarator
    : pointer
        {
            driver.printRed("abstract_declarator -> pointer");
            $$ = (AST *) $1;
            
        }
    | direct_abstract_declarator
        {
            driver.printRed("abstract_declarator -> direct_abstract_declarator");
            $$ = (AST *) $1;
        }
    | pointer direct_abstract_declarator
        {
            driver.printRed("abstract_declarator -> pointer direct_abstract_declarator");
            $$ = (AST *) new AstAbstractDecl( (AstPointer *)$1 , (AstDirectAbsDecl *)$2);
        }
    ;

direct_abstract_declarator
    : LPAREN abstract_declarator RPAREN
        {
            driver.printRed("direct_abstract_declarator -> LPAREN abstract_declarator RPAREN");
            $$ = (AST *) new  AstDirectAbsDecl ( 1, (AstAbstractDecl *)$2 , NULL, NULL , NULL); 
        }
    | LBRAK RBRAK
        {
            driver.printRed("direct_abstract_declarator -> LBRAK RBRAK");
            $$ = (AST *) new  AstDirectAbsDecl ( 2, NULL , NULL, NULL , NULL);
        }
    | LBRAK constant_expression RBRAK
        {
            driver.printRed("direct_abstract_declarator -> LBRAK constant_expression RBRAK");
            $$ = (AST *) new  AstDirectAbsDecl ( 3, NULL , (AstExpression *)$2, NULL , NULL);
        }
    | direct_abstract_declarator LBRAK RBRAK
        {
            driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LBRAK RBRAK");
            $$ = (AST *) new  AstDirectAbsDecl ( 4, NULL , NULL , (AstDirectAbsDecl*) $1 , NULL);
            
        }
    | direct_abstract_declarator LBRAK constant_expression RBRAK
        {
            driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LBRAK constant_expression RBRAK");
            $$ = (AST *) new  AstDirectAbsDecl ( 5, NULL , (AstExpression *)$3 , NULL , NULL);
        }
    | LPAREN RPAREN
        {
            driver.printRed("direct_abstract_declarator -> LPAREN RPAREN");
            $$ = (AST *) new  AstDirectAbsDecl ( 6, NULL , NULL, NULL , NULL);
        }
    | LPAREN parameter_type_list RPAREN
        {
            driver.printRed("direct_abstract_declarator -> LPAREN parameter_type_list RPAREN");
            $$ = (AST *) new  AstDirectAbsDecl ( 7, NULL , NULL, NULL , (AstTypeParamList * )$2 );
        }
    | direct_abstract_declarator LPAREN RPAREN
        {
            driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LPAREN RPAREN");
            $$ = (AST *) new  AstDirectAbsDecl ( 8, NULL , NULL , (AstDirectAbsDecl*) $1 , NULL);
            
        }
    | direct_abstract_declarator LPAREN parameter_type_list RPAREN
        {
            driver.printRed("direct_abstract_declarator -> direct_abstract_declarator LPAREN parameter_type_list RPAREN");
            $$ = (AST *) new  AstDirectAbsDecl ( 9, NULL , NULL , (AstDirectAbsDecl*) $1 ,(AstTypeParamList * )$3 );
        }
    ;

statement
    : labeled_statement
        {
            driver.printRed("statement -> labeled_statement");
                    $$ = (AST*) new AstStatement((AstLabeledStmt*)$1);
        }
    | compound_statement 
        {
            driver.printRed("statement -> compound_statement");
                    $$ = (AST*) new AstStatement((AstCompoundStmt*)$1);
        }
    | expression_statement
        {
            driver.printRed("statement -> expression_statement");
                    $$ = (AST*) new AstStatement((AstExprStmt*)$1);
                   //  Nasty :- may have here for testing ((AstStatement*)$$)->Visit();
        }
    | selection_statement
        {
            driver.printRed("statement -> selection_statement");
                    $$ = (AST*) new AstStatement((AstSelection*)$1);
        }
    | iteration_statement
        {
            driver.printRed("statement -> iteration_statement");
                    $$ = (AST*) new AstStatement((AstIteration*)$1);
        }
    | jump_statement
        {
            driver.printRed("statement -> jump_statement");
                    $$ = (AST*) new AstStatement((AstJump*)$1);
        }
    ;

labeled_statement
    : identifier COLON statement
        {
            driver.printRed("labeled_statement -> identifier COLON statement");
                    $$ = (AST*) new AstLabeledStmt((AstID*)$1, (AstStatement*)$3);
        }
    | CASE constant_expression COLON statement
        {
            driver.printRed("labeled_statement -> CASE constant_expression COLON statement");
                    $$ = (AST*) new AstLabeledStmt((AstConstantExpr*)$2, (AstStatement*)$4);
        }
    | DEFAULT COLON statement
        {
            driver.printRed("labeled_statement -> DEFAULT COLON statement");
                    $$ = (AST*) new AstLabeledStmt((AstStatement*)$3);
        }
    ;

expression_statement
    : SEMI
        {
            driver.printRed("expression_statement -> SEMI");
                    $$ = (AST*) new AstExprStmt(NULL);
        }
    | expression SEMI
        {
            driver.printRed("expression_statement -> expression SEMI");
                    $$ = (AST*) new AstExprStmt((AstExpression*)$1);
        }
    ;

compound_statement
    : LBRACE reset_current_symbol RBRACE
        {
            driver.printRed("compound_statement -> LBRACE RBRACE");
                    $$ = (AST*) new AstCompoundStmt(NULL, NULL);
        }
    | LBRACE reset_current_symbol enter_scope lookup_mode statement_list leave_scope RBRACE
        {
            driver.printRed("compound_statement -> LBRACE statement_list RBRACE");
                    $$ = (AST*) new AstCompoundStmt(NULL, (AstStatementList*)$5);
        }
    | LBRACE  reset_current_symbol enter_scope insert_mode declaration_list lookup_mode leave_scope RBRACE
        {
            driver.printRed("compound_statement -> LBRACE declaration_list RBRACE");
                    $$ = (AST*) new AstCompoundStmt((AstDeclarationList*)$5, NULL);
        }
    | LBRACE  reset_current_symbol enter_scope insert_mode declaration_list lookup_mode statement_list leave_scope RBRACE
        {
            driver.printRed("compound_statement -> LBRACE declaration_list statement_list RBRACE");
                    $$ = (AST*) new AstCompoundStmt((AstDeclarationList*)$5, (AstStatementList*)$7);
        }
    ;

statement_list
    : statement
        {
            driver.printRed("statement_list -> statement");
                    $$ = (AST*) new AstStatementList((AstStatement*)$1);
        }
    | statement_list statement
        {
            driver.printRed("statement_list -> statement_list statement");
                    $$ = (AST*) new AstStatementList((AstStatementList*)$1, (AstStatement*)$2);
        }
    ;

selection_statement
    : IF LPAREN expression RPAREN statement
        {
            driver.printRed("selection_statement -> IF LPAREN expression RPAREN statement");
                    $$ = (AST*) new AstSelection(new AstIfElse((AstExpression*)$3, (AstStatement*)$5, NULL));
        }
    | IF LPAREN expression RPAREN statement ELSE statement
        {
            driver.printRed("selection_statement -> IF LPAREN expression RPAREN statement ELSE statement");
                    $$ = (AST*) new AstSelection(new AstIfElse((AstExpression*)$3, (AstStatement*)$5, (AstStatement*)$7));
        }
    | SWITCH LPAREN expression RPAREN statement
        {
            driver.printRed("selection_statement -> SWITCH LPAREN expression RPAREN statement");
                    $$ = (AST*) new AstSelection(new AstSwitch((AstExpression*)$3, (AstStatement*)$5));
        }
    ;

iteration_statement
    : WHILE LPAREN expression RPAREN statement
        {
            driver.printRed("iteration_statement -> WHILE LPAREN expression RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstWhile((AstExpression*)$3, (AstStatement*)$5));
        }
    | DO statement WHILE LPAREN expression RPAREN SEMI
        {
            driver.printRed("iteration_statement -> DO statement WHILE LPAREN expression RPAREN SEMI");
                    $$ = (AST*) new AstIteration(new AstDoWhile((AstStatement*)$2, (AstExpression*)$5));
        }
    | FOR LPAREN SEMI SEMI RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN SEMI SEMI RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor(NULL, NULL, NULL, (AstStatement*)$6));
        }
    | FOR LPAREN SEMI SEMI expression RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN SEMI SEMI expression RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor(NULL, NULL, (AstExpression*)$5, (AstStatement*)$7));
        }
    | FOR LPAREN SEMI expression SEMI RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN SEMI expression SEMI RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor(NULL, (AstExpression*)$4, NULL, (AstStatement*)$7));
        }
    | FOR LPAREN SEMI expression SEMI expression RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN SEMI expression SEMI expression RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor(NULL, (AstExpression*)$4, (AstExpression*)$6, (AstStatement*)$8));
        }
    | FOR LPAREN expression SEMI SEMI RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN expression SEMI SEMI RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor((AstExpression*)$3, NULL, NULL, (AstStatement*)$7));
        }
    | FOR LPAREN expression SEMI SEMI expression RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN expression SEMI SEMI expression RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor((AstExpression*)$3, NULL, (AstExpression*)$6, (AstStatement*)$8));
        }
    | FOR LPAREN expression SEMI expression SEMI RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN expression SEMI expression SEMI RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor((AstExpression*)$3, (AstExpression*)$5, NULL, (AstStatement*)$8));
        }
    | FOR LPAREN expression SEMI expression SEMI expression RPAREN statement
        {
            driver.printRed("iteration_statement -> FOR LPAREN expression SEMI expression SEMI expression RPAREN statement");
                    $$ = (AST*) new AstIteration(new AstFor((AstExpression*)$3, (AstExpression*)$5, (AstExpression*)$7, (AstStatement*)$9));
        }
    ;

jump_statement
    : GOTO identifier SEMI
        {
            driver.printRed("jump_statement -> GOTO identifier SEMI");
                    $$ = (AST*) new AstJump(new AstGoto(), (AstID*)$2);
        }
    | CONTINUE SEMI
        {
            driver.printRed("jump_statement -> CONTINUE SEMI");
                    $$ = (AST*) new AstJump(new AstContinue());
        }
    | BREAK SEMI
        {
            driver.printRed("jump_statement -> BREAK SEMI");
                    $$ = (AST*) new AstJump(new AstBreak());
        }
    | RETURN SEMI
        {
            driver.printRed("jump_statement -> RETURN SEMI");
                    $$ = (AST*) new AstJump(new AstReturn());
        }
    | RETURN expression SEMI
        {
            driver.printRed("jump_statement -> RETURN expression SEMI");
                    $$ = (AST*) new AstJump(new AstReturn(), (AstExpression*)$2);
        }
    ;

expression
    : assignment_expression
        {
            driver.printRed("expression -> assignment_expression");
                    $$ = (AST*) new AstExpression((AstAssignExpr*)$1);
        }
    | expression COMMA assignment_expression
        {
            driver.printRed("expression -> expression COMMA assignment_expression");
                    $$ = (AST*) new AstExpression((AstExpression*)$1, (AstAssignExpr*)$3);
        }
    ;

assignment_expression
    : conditional_expression
        {
            driver.printRed("assignment_expression -> conditional_expression");
                    $$ = (AST*) new AstAssignExpr((AstConditionalExpr*)$1);
        }
    | unary_expression assignment_operator assignment_expression
        {
            driver.printRed("assignment_expression -> unary_expression assignment_operator assignment_expression");
                    $$ = (AST*) new AstAssignExpr((AstUnaryExpr*)$1, (AstAssignOp*)$2, (AstAssignExpr*)$3);
        }
    ;

assignment_operator
    : EQ
        {
            driver.printRed("assignment_operator -> EQ");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::EQ);
        }
    | MUL_ASSIGN
        {
            driver.printRed("assignment_operator -> MUL_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::MUL_ASSIGN);
        }
    | DIV_ASSIGN
        {
            driver.printRed("assignment_operator -> DIV_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::DIV_ASSIGN);
        }
    | MOD_ASSIGN
        {
            driver.printRed("assignment_operator -> MOD_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::MOD_ASSIGN);
        }
    | ADD_ASSIGN
        {
            driver.printRed("assignment_operator -> ADD_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::ADD_ASSIGN);
        }
    | SUB_ASSIGN
        {
            driver.printRed("assignment_operator -> SUB_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::SUB_ASSIGN);
        }
    | LEFT_ASSIGN
        {
            driver.printRed("assignment_operator -> LEFT_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::LEFT_ASSIGN);
        }
    | RIGHT_ASSIGN
        {
            driver.printRed("assignment_operator -> RIGHT_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::RIGHT_ASSIGN);
        }
    | AND_ASSIGN
        {
            driver.printRed("assignment_operator -> AND_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::AND_ASSIGN);
        }
    | XOR_ASSIGN
        {
            driver.printRed("assignment_operator -> XOR_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::XOR_ASSIGN);
        }
    | OR_ASSIGN
        {
            driver.printRed("assignment_operator -> OR_ASSIGN");
                    $$ = (AST*) new AstAssignOp(AstAssignOp::OR_ASSIGN);
        }
    ;

conditional_expression
    : logical_or_expression
        {
            driver.printRed("conditional_expression -> logical_or_expression");
                    $$ = (AST*) new AstConditionalExpr((AstLogicOrExpr*)$1);
        }
    | logical_or_expression WHAT expression COLON conditional_expression
        {
            driver.printRed("conditional_expresion -> logical_or_expression WHAT expression COLON conditional_expression");
                    $$ = (AST*) new AstConditionalExpr((AstLogicOrExpr*)$1, (AstExpression*)$3, (AstConditionalExpr*)$5);
                    if($$->needsCast)
                        driver.error(yyloc, "These types must match!");
                    
        }
    ;

constant_expression
    : conditional_expression
        {
            driver.printRed("constant_expression -> conditional_expression");
                    $$ = (AST*) new AstConstantExpr((AstConditionalExpr*)$1);
        }
    ;

logical_or_expression
    : logical_and_expression
        {
            driver.printRed("logical_or_expression -> logical_and_expression");
                    $$ = (AST*) new AstLogicOrExpr((AstLogicAndExpr*)$1);
        }
    | logical_or_expression OR_OP logical_and_expression    
        {
            driver.printRed("logical_or_expression -> logical_or_epression OR_OP logical_and_expression");
                    $$ = (AST*) new AstLogicOrExpr((AstLogicOrExpr*)$1, (AstLogicAndExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    ;

logical_and_expression
    : inclusive_or_expression
        {
            driver.printRed("logical_and_expression -> inclusive_or_expression");
                    $$ = (AST*) new AstLogicAndExpr((AstORExpr*)$1);
        }
    | logical_and_expression AND_OP inclusive_or_expression
        {
            driver.printRed("logical_and_expression -> logical_and_expression AND_OP inclusive_or_expression");
                    $$ = (AST*) new AstLogicAndExpr((AstLogicAndExpr*)$1, (AstORExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    ;

inclusive_or_expression
    : exclusive_or_expression
        {
            driver.printRed("inclusive_or_expression -> exclusive_or_expression");
                    $$ = (AST*) new AstORExpr((AstXORExpr*)$1);
        }
    | inclusive_or_expression BIN_OR exclusive_or_expression
        {
            driver.printRed("inclusive_or_expression -> inclusive_or_expression BIN_OR exclusive_or_expression");
                    $$ = (AST*) new AstORExpr((AstORExpr*)$1, (AstXORExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    ;

exclusive_or_expression
    : and_expression
        {
            driver.printRed("exclusive_or_expression -> and_expression");
                    $$ = (AST*) new AstXORExpr((AstAndExpr*)$1);
        }
    | exclusive_or_expression BIN_XOR and_expression
        {
            driver.printRed("exclusive_or_expression -> exclusive_or_expression BIN_XOR and_expression");
                    $$ = (AST*) new AstXORExpr((AstXORExpr*)$1, (AstAndExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    ;

and_expression
    : equality_expression
        {
            driver.printRed("and_expression -> equality_expression");
                    $$ = (AST*) new AstAndExpr((AstEqExpr*)$1);
        }
    | and_expression BIN_AND equality_expression
        {
            driver.printRed("and_expression -> and_expression BIN_AND equality_expression");
                    $$ = (AST*) new AstAndExpr((AstAndExpr*)$1, (AstEqExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    ;

equality_expression
    : relational_expression
        {
            driver.printRed("equality_expression -> relational_expression");
                    $$ = (AST*) new AstEqExpr((AstRelExpr*)$1);
        }
    | equality_expression EQ_OP relational_expression
        {
            driver.printRed("equality_expression -> equality_expression EQ_OP relational_expression");
                    $$ = (AST*) new AstEqExpr((AstEqExpr*)$1, AstEqExpr::EQ_OP, (AstRelExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | equality_expression NE_OP relational_expression
        {
            driver.printRed("equality_expression -> equality_expression NE_OP relational_expression");
                    $$ = (AST*) new AstEqExpr((AstEqExpr*)$1, AstEqExpr::NE_OP, (AstRelExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    ;

relational_expression
    : shift_expression
        {
            driver.printRed("relational_expression -> shift_expression");
                    $$ = (AST*) new AstRelExpr((AstShiftExpr*)$1);
        }
    | relational_expression LT_OP shift_expression
        {
            driver.printRed("relational_expression -> relational_expression LT_OP shift_expression");
                    $$ = (AST*) new AstRelExpr((AstRelExpr*)$1, AstRelExpr::LT_OP, (AstShiftExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | relational_expression GT_OP shift_expression
        {
            driver.printRed("relational_expression -> relational_expression GT_OP shift_expression");
                    $$ = (AST*) new AstRelExpr((AstRelExpr*)$1, AstRelExpr::GT_OP, (AstShiftExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | relational_expression LE_OP shift_expression
        {
            driver.printRed("relational_expression -> relational_expression LE_OP shift_expression");
                    $$ = (AST*) new AstRelExpr((AstRelExpr*)$1, AstRelExpr::LE_OP, (AstShiftExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | relational_expression GE_OP shift_expression
        {
            driver.printRed("relational_expression -> relational_expression GE_OP shift_expression");
                    $$ = (AST*) new AstRelExpr((AstRelExpr*)$1, AstRelExpr::GE_OP, (AstShiftExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
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
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | shift_expression RIGHT_OP additive_expression
        {
            driver.printRed("shift_expression -> shift_expression RIGHT_OP additive_expression");
                    $$ = (AST*) new AstShiftExpr((AstShiftExpr*)$1, AstShiftExpr::RIGHT_OP, (AstAddExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
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
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | additive_expression MINUS multiplicative_expression
        {
            driver.printRed("additive_expression -> additive_expression MINUS multiplicative_expression");
                    $$ = (AST*) new AstAddExpr((AstAddExpr*)$1, AstAddExpr::MINUS, (AstMultExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
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
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | multiplicative_expression DIV cast_expression
        {
            driver.printRed("multiplicative_expression -> multiplicative_expression DIV cast_expression");
                    $$ = (AST*) new AstMultExpr((AstMultExpr*)$1, AstMultExpr::DIV, (AstCastExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
        }
    | multiplicative_expression MOD cast_expression
        {
            driver.printRed("multiplicative_expression -> multiplicative_expression MOD cast_expression");
                    $$ = (AST*) new AstMultExpr((AstMultExpr*)$1, AstMultExpr::MOD, (AstCastExpr*)$3);
                    if($$->needsCast && !$$->isConv)
                        driver.error(yyloc, "These types cannot be implicitly converted!");
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
            // TODO we need to verify if this is a valid cast and then insert the cast into the AST
            
            driver.printRed("cast_expression -> LPAREN type_name RPAREN cast_expression");
            driver.error(yylloc, "Cast expressions are not currently supported by this compiler!");
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
            // TODO function call?
            
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
            $$ = (AST*) new AstConstant(
                    ((EnumType*)$1->symbolType)->GetConstVal($1->symbol_name), 
                    $1->symbol_name,
                    $1->symbolType
                 );
        }
    ;

string
    : STRING_LITERAL
        {
            driver.printRed("string -> STRING_LITERAL");
                    $$ = (AST*) new AstString(*$1, new Type("STRING_LITERAL", 0));
        }
    ;

identifier
    : IDENTIFIER
        {
            // TODO if this ID is a function, then we need to pass ((FunctionType*)$1->symbolType)->GetReturnType(), rather than $1->symbolType
            driver.currentSymbol->symbol_name = $1->symbol_name;  
            driver.printRed("identifier -> IDENTIFIER");
            
            //This is a hack to get the correct type information
            int level;
            SymbolInfo s;
            s.symbol_name = $1->symbol_name;
            
            if(driver.SymbolTable.find_symbol(s, level))
            {
                $$ = (AST*) new AstID($1->symbol_name, 
                        driver.SymbolTable.fetch_symbol(s, level)->symbolType);
            }
            else
            {
                $$ = (AST*) new AstID($1->symbol_name, NULL);
            }
        }
    ;
%%
void yy::CParser::error(const yy::CParser::location_type& loc,
                        const std::string& msg)
{
    driver.error(loc, msg);
}
