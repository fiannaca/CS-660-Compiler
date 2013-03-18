%{
//Includes
#include <cstdlib>
#include <climits>
#include <string>
#include <cerrno>

#include "CParser.hpp"
#include "CCompiler.h"

//Handles a bug in Flex 2.5.33
#undef yywrap
#define yywrap() 1

#define yyterminate() return token::END

%}

ws		[ \t\v\f]+
letter		[a-zA-Z]
digit		[0-9]
hexdig		[0-9a-fA-F]
octdig		[0-7]
id		({letter}|_)({letter}|{digit})*

lu		[lL][lL]?[uU]?
ul		[uU][lL]?[lL]?
intsuf		({lu}|{ul})
hexint		(0[xX]){hexdig}+
octint		(0){octdig}*
decint		[1-9]{digit}*
intconst	({decint}|{octint}|{hexint})({intsuf}?)

fltsuf		[fFlL]
fltexp		[eE][+-]?{digit}+
real		{digit}*\.{digit}+
intexp		{digit}+{fltexp}
realexp		{real}{fltexp}?
hexexp		(0[xX]){hexdig}*(\.{hexdig}*)?[pP][+-]?{digit}+
fltconst	({intexp}|{realexp}|{hexexp}){fltsuf}?

flthexerror	(0[xX]){hexdig}*(\.{hexdig}*)

simescseq	\\['\"\?abfnrtv]
octescseq	\\{octdig}{octdig}?{octdig}?
hexescseq	\\x{hexdig}+
unicharname	\\[uU]{hexdig}{hexdig}{hexdig}{hexdig}
escseq		{simescseq}|{octescseq}|{hexescseq}|{unicharname}
charconst	L?'({escseq}|[^'\\])+'

stringlit	L?\"({escseq}|[^\\"])*\"

ctxt		[^*\n]*
cstr		"*"+[^*/\n]*
cend		"*"+"/"

%x COMMENT

%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}
%%
%{
yylloc->step();
%}

"!!S"		{
		    driver.SymbolTable.dump_table();
		}

"//".*		{ 
		    driver.printTok("COMMENT - not really a token");
		}

"/*"		{   BEGIN(COMMENT); }

<COMMENT>{ctxt}
<COMMENT>{cstr}	
<COMMENT>\n	{   yylloc->lines(); }
<COMMENT>{cend}	{
		    driver.printTok("COMMENT - not really a token");
		    BEGIN(INITIAL); 
		}
<COMMENT><<EOF>> {
		    driver.error(*yylloc, "Unclosed comment"); 
		    BEGIN(INITIAL);
		}

{ws}		{   yylloc->step(); } 
\n.*		{
		    //Save a buffer of each line -- for error reporting
		    strncpy(driver.linebuf, yytext + 1, sizeof(driver.linebuf));
                    yyless(1);

                    //Update the locations in yylloc
		    yylloc->lines();
		    yylloc->step(); 
		}

%{
typedef yy::CParser::token token;
%}

"sizeof"	{ 
		    driver.printTok("SIZEOF");
		    return token::SIZEOF; 
		} 
"typedef"	{ 
		    driver.printTok("TYPEDEF");
		    return token::TYPEDEF; 
		} 
"extern"	{ 
		    driver.printTok("EXTERN");
		    return token::EXTERN; 
		} 
"static"	{ 
		    driver.printTok("STATIC");
		    return token::STATIC; 
		} 
"auto"		{  
		    driver.printTok("AUTO");
		    return token::AUTO; 
		} 
"register"	{ 
		    driver.printTok("REGISTER");
		    return token::REGISTER;
		} 

"char"		{ 
		    driver.printTok("CHAR");
		    return token::CHAR; 
		} 
"short"		{ 
		    driver.printTok("SHORT");
		    return token::SHORT; 
		} 
"int"		{ 
		    driver.printTok("INT");
		    return token::INT; 
		} 
"long"		{ 
		    driver.printTok("LONG");
		    return token::LONG; 
		} 
"signed"	{ 
		    driver.printTok("SIGNED");
		    return token::SIGNED; 
		} 
"unsigned"	{ 
		    driver.printTok("UNSIGNED");
		    return token::UNSIGNED; 
		} 
"float" 	{ 
		    driver.printTok("FLOAT");
		    return token::FLOAT; 
		} 
"double"	{ 
		    driver.printTok("DOUBLE");
		    return token::DOUBLE; 
		} 
"const"		{ 
		    driver.printTok("CONST");
		    return token::CONST; 
		} 
"volatile"	{ 
		    driver.printTok("VOLATILE");
		    return token::VOLATILE; 
		} 
"void"		{ 
		    driver.printTok("VOID");
		    return token::VOID; 
		} 
"struct"	{ 
		    driver.printTok("STRUCT");
		    return token::STRUCT; 
		} 
"union"		{ 
		    driver.printTok("UNION");
		    return token::UNION; 
		} 
"enum"		{ 
		    driver.printTok("ENUM");
		    return token::ENUM; 
		}
"case"		{ 
		    driver.printTok("CASE");
		    return token::CASE; 
		}
"default"	{ 
		    driver.printTok("DEFAULT");
		    return token::DEFAULT; 
		} 
"if"		{ 
		    driver.printTok("IF");
		    return token::IF; 
		} 
"else"		{ 
		    driver.printTok("ELSE");
		    return token::ELSE; 
		} 
"switch"	{ 
		    driver.printTok("SWITCH");
		    return token::SWITCH; 
		} 
"while"		{ 
		    driver.printTok("WHILE");
		    return token::WHILE; 
		} 
"do"		{ 
		    driver.printTok("DO");
		    return token::DO; 
		} 
"for"		{ 
		    driver.printTok("FOR");
		    return token::FOR; 
		} 
"goto"		{ 
		    driver.printTok("GOTO");
		    return token::GOTO; 
		} 
"continue"	{ 
		    driver.printTok("CONTINUE");
		    return token::CONTINUE; 
		} 
"break"		{ 
		    driver.printTok("BREAK");
		    return token::BREAK; 
		} 
"return"	{ 
		    driver.printTok("RETURN");
		    return token::RETURN; 
		} 

{id}		{ 
		    return driver.checkType(yytext); 
		} 

{charconst}	{ 
		    driver.printTok("CHARACTER_CONSTANT", yytext);
		    return token::CHARACTER_CONSTANT; 
		} 

	/* enumeration consts should go here */

{intconst}	{ 
		    driver.printTok("INTERGER_CONSTANT", yytext);
		    return token::INTEGER_CONSTANT; 
		} 
{fltconst}	{ 
		    driver.printTok("FLOATING_CONSTANT", yytext);
		    return token::FLOATING_CONSTANT; 
		}
{flthexerror}	{ 
		    std::string err("Hex floating point constants must have a binary exponent part, i.e. ");
		    std::string txt(yytext);
		    std::string exp(" should be ");
		    exp += txt + "p0";
		    driver.error(*yylloc, err + txt + exp); 
		} 
{stringlit}	{ 
		    driver.printTok("STRING_LITERAL", yytext);
		    return token::STRING_LITERAL; 
		} 

"..."		{ 
		    driver.printTok("ELIPSIS");
		    return token::ELIPSIS; 
		} 
"->"		{ 
		    driver.printTok("PTR_OP");
		    return token::PTR_OP; 
		} 
"++"		{ 
		    driver.printTok("INC_OP");
		    return token::INC_OP; 
		} 
"--"		{ 
		    driver.printTok("DEC_OP");
		    return token::DEC_OP; 
		} 
"<<"		{ 
		    driver.printTok("LEFT_OP");
		    return token::LEFT_OP; 
		} 
">>"		{ 
		    driver.printTok("RIGHT_OP");
		    return token::RIGHT_OP; 
		} 
"<="		{ 
		    driver.printTok("LE_OP");
		    return token::LE_OP; 
		} 
">="		{ 
		    driver.printTok("GE_OP");
		    return token::GE_OP; 
		} 
"=="		{ 
		    driver.printTok("EQ_OP");
		    return token::EQ_OP; 
		} 
"!="		{ 
		    driver.printTok("NE_OP");
		    return token::NE_OP; 
		} 
"&&"		{ 
		    driver.printTok("AND_OP");
		    return token::AND_OP; 
		} 
"||"		{ 
		    driver.printTok("OR_OP");
		    return token::OR_OP; 
		} 
"*="		{ 
		    driver.printTok("MUL_ASSIGN");
		    return token::MUL_ASSIGN; 
		} 
"/="		{ 
		    driver.printTok("DIV_ASSIGN");
		    return token::DIV_ASSIGN; 
		} 
"%="		{ 
		    driver.printTok("MOD_ASSIGN");
		    return token::MOD_ASSIGN; 
		} 
"+="		{ 
		    driver.printTok("ADD_ASSIGN");
		    return token::ADD_ASSIGN; 
		} 
"-="		{ 
		    driver.printTok("SUB_ASSIGN");
		    return token::SUB_ASSIGN; 
		} 
"<<="		{ 
		    driver.printTok("LEFT_ASSIGN");
		    return token::LEFT_ASSIGN; 
		} 
">>="		{ 
		    driver.printTok("RIGHT_ASSIGN");
		    return token::RIGHT_ASSIGN; 
		} 
"&="		{ 
		    driver.printTok("AND_ASSIGN");
		    return token::AND_ASSIGN; 
		} 
"^="		{ 
		    driver.printTok("XOR_ASSIGN");
		    return token::XOR_ASSIGN; 
		} 
"|="		{ 
		    driver.printTok("OR_ASSIGN");
		    return token::OR_ASSIGN; 
		} 
"*"		{ 
		    driver.printTok("STAR");
		    return token::STAR; 
		} 
"|"		{ 
		    driver.printTok("BIN_OR");
		    return token::BIN_OR; 
		} 
"^"		{ 
		    driver.printTok("BIN_XOR");
		    return token::BIN_XOR; 
		} 
"&"		{ 
		    driver.printTok("BIN_AND");
		    return token::BIN_AND; 
		} 
"<"		{ 
		    driver.printTok("LT_OP");
		    return token::LT_OP; 
		} 
">"		{ 
		    driver.printTok("GT_OP");
		    return token::GT_OP; 
		} 
"+"		{ 
		    driver.printTok("PLUS");
		    return token::PLUS; 
		} 
"-"		{ 
		    driver.printTok("MINUS");
		    return token::MINUS; 
		}
"/"		{ 
		    driver.printTok("DIV");
		    return token::DIV; 
		} 
"%"		{ 
		    driver.printTok("MOD");
		    return token::MOD; 
		} 
"~"		{ 
		    driver.printTok("TILDE");
		    return token::TILDE; 
		} 
"!"		{ 
		    driver.printTok("BANG");
		    return token::BANG; 
		} 
"."		{ 
		    driver.printTok("DOT");
		    return token::DOT; 
		} 
"?"		{ 
		    driver.printTok("WHAT");
		    return token::WHAT; 
		} 
"{"|"<%"	{ 
		    driver.printTok("LBRACE");
		    return token::LBRACE; 
		} 
"}"|"%>"	{ 
		    driver.printTok("RBRACE");
		    return token::RBRACE; 
		} 
"["|"<:"	{ 
		    driver.printTok("LBRAK");
		    return token::LBRAK; 
		} 
"]"|":>"	{ 
		    driver.printTok("RBRAK");
		    return token::RBRAK; 
		} 
"("		{ 
		    driver.printTok("LPAREN");
		    return token::LPAREN; 
		} 
")"		{ 
		    driver.printTok("RPAREN");
		    return token::RPAREN; 
		} 
"="		{ 
		    driver.printTok("EQ");
		    return token::EQ; 
		} 
","		{ 
		    driver.printTok("COMMA");
		    return token::COMMA; 
		} 
":"		{ 
		    driver.printTok("COLON");
		    return token::COLON; 
		} 
";"		{ 
		    driver.printTok("SEMI");
		    return token::SEMI; 
		} 

.		{ 
		    driver.error(*yylloc, "Invalid character!");
		} 
%%
void CCompiler::scan_begin(int debug_level)
{
    yyset_debug(debug_level);

    if(fname.empty() || fname == "-")
        yyin = stdin;
    else if(!(yyin = fopen(fname.c_str(), "r")))
    {
        error("Cannot open" + fname + ": " + strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void CCompiler::scan_end()
{
    fclose(yyin);
}
