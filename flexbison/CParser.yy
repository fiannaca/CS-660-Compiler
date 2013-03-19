%require "2.7"

%define parser_class_name "CParser"

%code requires {
#include <string>
#include "SymTab.h"
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
    std::string *sval;
    SymbolInfo  *sym;
};

%code {
#include "CCompiler.h"
}

%token END 0 "EOF"
%token IDENTIFIER
%token INTEGER_CONSTANT 
%token FLOATING_CONSTANT CHARACTER_CONSTANT ENUMERATION_CONSTANT 
%token STRING_LITERAL 
%token SIZEOF
%token PTR_OP 
%token INC_OP DEC_OP 
%token LEFT_OP RIGHT_OP 
%token LE_OP GE_OP EQ_OP NE_OP
%token AND_OP OR_OP 
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN 
%token LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN 
%token TYPEDEF_NAME

%token STAR BIN_OR BIN_XOR BIN_AND 
%token LT_OP GT_OP PLUS MINUS DIV MOD TILDE BANG DOT WHAT
%token LBRACE RBRACE LBRAK RBRAK LPAREN RPAREN EQ COMMA COLON SEMI

%token TYPEDEF EXTERN STATIC AUTO REGISTER
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%printer    { yyoutput << *$$; } <sval>
%destructor { delete $$; } <sval>

%printer    { yyoutput << $$; } <ival>

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
		    driver.printRed("declaration -> declaration_specifiers SEMI");
		}
	| declaration_specifiers init_declarator_list SEMI
		{
		    driver.printRed("declaration -> declaration_specifiers init_declarator_list SEMI");
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
		}
	| REGISTER
		{
		    driver.printRed("storage_class_specifier -> REGISTER");
		}
	| STATIC
		{
		    driver.printRed("storage_class_specifier -> STATIC");
		}
	| EXTERN
		{
		    driver.printRed("storage_class_specifier -> EXTERN");
		}
	| TYPEDEF
		{
		    driver.printRed("storage_class_specifier -> TYPEDEF");
		}
	;

type_specifier
	: VOID
		{
		    driver.printRed("type_specifier -> VOID");
		}
	| CHAR
		{
		    driver.printRed("type_specifier -> CHAR");
		}
	| SHORT
		{
		    driver.printRed("type_specifier -> SHORT");
		}
	| INT
		{
		    driver.printRed("type_specifier -> INT");
		}
	| LONG
		{
		    driver.printRed("type_specifier -> LONG");
		}
	| FLOAT 
		{
		    driver.printRed("type_specifier -> FLOAT");
		}
	| DOUBLE
		{
		    driver.printRed("type_specifier -> DOUBLE");
		}
	| SIGNED
		{
		    driver.printRed("type_specifier -> SIGNED");
		}
	| UNSIGNED
		{
		    driver.printRed("type_specifier -> UNSIGNED");
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
		}
	| VOLATILE
		{
		    driver.printRed("type_qualifier -> VOLATILE");
		}
	;

struct_or_union_specifier
	: struct_or_union identifier LBRACE struct_declaration_list RBRACE
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
		}
	| UNION
		{
		    driver.printRed("struct_or_union -> UNION");
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
	: init_declarator
		{
		    driver.printRed("init_declarator_list -> init_declarator");
		}
	| init_declarator_list COMMA init_declarator
		{
		    driver.printRed("init_declarator_list COMMA init_declarator");
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
	: specifier_qualifier_list struct_declarator_list SEMI
		{
		    driver.printRed("struct_declaration -> specifier_qualifier_list struct_declarator_list SEMI");
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
	: struct_declarator
		{
		    driver.printRed("struct_declarator_list -> struct_declarator");
		}
	| struct_declarator_list COMMA struct_declarator
		{
		    driver.printRed("struct_declarator_list -> struct_declarator_list COMMA struct_declarator");
		}
	;

struct_declarator
	: declarator
		{
		    driver.printRed("struct_declarator -> declarator");
		}
	| COLON constant_expression
		{
		    driver.printRed("struct_declarator -> COLON constant_expression");
		}
	| declarator COLON constant_expression
		{
		    driver.printRed("struct_declarator -> declarator COLON constant_expression");
		}
	;

enum_specifier
	: ENUM LBRACE enumerator_list RBRACE
		{
		    driver.printRed("enum_specifier -> ENUM LBRACE enumerator_list RBRACE");
		}
	| ENUM identifier LBRACE enumerator_list RBRACE
		{
		    driver.printRed("enum_specifier -> ENUM identifier LBRACE enumerator_list RBRACE");
		}
	| ENUM identifier
		{
		    driver.printRed("enum_specifier -> ENUM identifier");
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
	: identifier
		{
		    driver.printRed("enumerator -> identifier");
		}
	| identifier EQ constant_expression
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
		}
	| direct_declarator LBRAK constant_expression RBRAK
		{
		    driver.printRed("direct_declarator -> direct_declarator LBRAK constant_expression RBRAK");
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
		}
	| STAR type_qualifier_list
		{
		    driver.printRed("pointer -> STAR type_qualifier_list");
		}
	| STAR pointer
		{
		    driver.printRed("pointer -> STAR pointer");
		}
	| STAR type_qualifier_list pointer
		{
		    driver.printRed("pointer -> STAR type_qualifier_list pointer");
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
	: LBRACE RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE RBRACE");
		}
	| LBRACE lookup_mode statement_list RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE statement_list RBRACE");
		}
	| LBRACE insert_mode declaration_list lookup_mode RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE declaration_list RBRACE");
		}
	| LBRACE insert_mode declaration_list lookup_mode statement_list RBRACE
		{
		    driver.printRed("compound_statement -> LBRACE declaration_list statement_list RBRACE");
		}
	;

insert_mode
	: /* Empty - This is a dummy production used for setting insert mode */
		{
		    std::cout << "Starting insert mode: line - " << @$.begin.line << ", col - " << @$.begin.column << std::endl;
		    driver.set_insert_mode(true);
		}
	;

lookup_mode
	: /* Empty - This is a dummy production used for setting lookup mode */
		{
		    std::cout << "Starting lookup mode: line - " << @$.begin.line << ", col - " << @$.begin.column << std::endl;
		    driver.set_insert_mode(false);
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
		}
	| shift_expression LEFT_OP additive_expression
		{
		    driver.printRed("shift_expression -> shift_expression LEFT_OP additive_expression");
		}
	| shift_expression RIGHT_OP additive_expression
		{
		    driver.printRed("shift_expression -> shift_expression RIGHT_OP additive_expression");
		}
	;

additive_expression
	: multiplicative_expression
		{
		    driver.printRed("additive_expression -> multiplicative_expression");
		}
	| additive_expression PLUS multiplicative_expression
		{
		    driver.printRed("additive_expression -> additive_expression PLUS multiplicative_expression");
		}
	| additive_expression MINUS multiplicative_expression
		{
		    driver.printRed("additive_expression -> additive_expression MINUS multiplicative_expression");
		}
	;

multiplicative_expression
	: cast_expression
		{
		    driver.printRed("multiplicative_expression -> cast_expression");
		}
	| multiplicative_expression STAR cast_expression
		{
		    driver.printRed("multiplicative_expression -> multiplicative_expression STAR cast_expression");
		}
	| multiplicative_expression DIV cast_expression
		{
		    driver.printRed("multiplicative_expression -> multiplicative_expression DIV cast_expression");
		}
	| multiplicative_expression MOD cast_expression
		{
		    driver.printRed("multiplicative_expression -> multiplicative_expression MOD cast_expression");
		}
	;

cast_expression
	: unary_expression
		{
		    driver.printRed("cast_expression -> unary_expression");
		}
	| LPAREN type_name RPAREN cast_expression
		{
		    driver.printRed("cast_expression -> LPAREN type_name RPAREN cast_expression");
		}
	;

unary_expression
	: postfix_expression
		{
		    driver.printRed("unary_expression -> postfix_expression");
		}
	| INC_OP unary_expression
		{
		    driver.printRed("unary_expression -> INC_OP unary_expression");
		}
	| DEC_OP unary_expression
		{
		    driver.printRed("unary_expression -> DEC_OP unary_expression");
		}
	| unary_operator cast_expression
		{
		    driver.printRed("unary_expression -> unary_operator cast_expression");
		}
	| SIZEOF unary_expression
		{
		    driver.printRed("unary_expression -> SIZEOF unary_expression");
		}
	| SIZEOF LPAREN type_name RPAREN
		{
		    driver.printRed("unary_expression -> SIZEOF LPAREN type_name RPAREN");
		}
	;

unary_operator
	: BIN_AND
		{
		    driver.printRed("unary_operator -> BIN_AND");
		}
	| STAR
		{
		    driver.printRed("unary_operator -> STAR");
		}
	| PLUS
		{
		    driver.printRed("unary_operator -> PLUS");
		}
	| MINUS
		{
		    driver.printRed("unary_operator -> MINUS");
		}
	| TILDE
		{
		    driver.printRed("unary_operator -> TILDE");
		}
	| BANG
		{
		    driver.printRed("unary_operator -> BANG");
		}
	;

postfix_expression
	: primary_expression
		{
		    driver.printRed("postfix_expression -> primary_expression");
		}
	| postfix_expression LBRAK expression RBRAK
		{
		    driver.printRed("postfix_expression -> postfix_expression LBRAK expression RBRAK");
		}
	| postfix_expression LPAREN RPAREN
		{
		    driver.printRed("postfix_expression -> postfix_expression LPAREN RPAREN");
		}
	| postfix_expression LPAREN argument_expression_list RPAREN
		{
		    driver.printRed("postfix_expression -> postfix_expression LPAREN argument_expression_list RPAREN");
		}
	| postfix_expression DOT identifier
		{
		    driver.printRed("postfix_expression -> postfix_expression DOT identifier");
		}
	| postfix_expression PTR_OP identifier
		{
		    driver.printRed("postfix_expression -> postfix_expression PTR_OP identifier");
		}
	| postfix_expression INC_OP
		{
		    driver.printRed("postfix_expression -> INC_OP");
		}
	| postfix_expression DEC_OP
		{
		    driver.printRed("postfix_expression -> postfix_expression DEC_OP");
		}
	;

primary_expression
	: identifier
		{
		    driver.printRed("primary_expression -> identifier");
		}
	| constant
		{
		    driver.printRed("primary_expression -> constant");
		}
	| string
		{
		    driver.printRed("primary_expression -> string");
		}
	| LPAREN expression RPAREN
		{
		    driver.printRed("primary_expression -> LPAREN expression RPAREN");
		}
	;

argument_expression_list
	: assignment_expression
		{
		    driver.printRed("argument_expression_list -> assignment_expression");
		}
	| argument_expression_list COMMA assignment_expression
		{
		    driver.printRed("argument_expression_list -> argument_expression_list COMMA assignment_expression");
		}
	;

constant
	: INTEGER_CONSTANT
		{
		    driver.printRed("constant -> INTEGER_CONSTANT");
		}
	| CHARACTER_CONSTANT
		{
		    driver.printRed("constant -> CHARACTER_CONSTANT");
		}
	| FLOATING_CONSTANT
		{
		    driver.printRed("constant -> FLOATING_CONSTANT");
		}
	| ENUMERATION_CONSTANT
		{
		    driver.printRed("constant -> ENUMERATION_CONSTANT");
		}
	;

string
	: STRING_LITERAL
		{
		    driver.printRed("string -> STRING_LITERAL");
		}
	;

identifier
	: IDENTIFIER
		{
		    driver.printRed("identifier -> IDENTIFIER");
		}
	;
%%
void yy::CParser::error(const yy::CParser::location_type& loc,
                        const std::string& msg)
{
    driver.error(loc, msg);
}
