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

%option noyywrap batch debug

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

simescseq	\\['\"\?\a\b\f\n\r\t\v]
octescseq	\\{octdig}{octdig}?{octdig}?
hexescseq	\\x{hexdig}+
unicharname	\\[uU]{hexdig}{hexdig}{hexdig}{hexdig}
escseq		{simescseq}|{octescseq}|{hexescseq}|{unicharname}
charconst	L?'({escseq}|[^'\\])+'

stringlit	L?\"({escseq}|[^\\"])*\"

%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}
%%
%{
yylloc->step();
%}

"//".*		{ 
		    //parserPtr->signalScanErr("This is a scanner error");
		    /* no real action - just remove the comment */
		    //printInfo(1, "Comment removed... (single line)\n"); 
		}
"/*"		{ 
		    /* no real action - just remove the multiline comment */ 
		    //comment();
		}
{ws}		{   yylloc->step(); } 
[\n]+		{
		    yylloc->lines(yyleng);
		    yylloc->step(); 
		}

%{
typedef yy::CParser::token token;
%}

"sizeof"	{ return token::SIZEOF; } 
"typedef"	{ return token::TYPEDEF; } 
"extern"	{ return token::EXTERN; } 
"static"	{ return token::STATIC; } 
"auto"		{ return token::AUTO; } 
"register"	{ return token::REGISTER; } 

"char"		{ return token::CHAR; } 
"short"		{ return token::SHORT; } 
"int"		{ return token::INT; } 
"long"		{ return token::LONG; } 
"signed"	{ return token::SIGNED; } 
"unsigned"	{ return token::UNSIGNED; } 
"float" 	{ return token::FLOAT; } 
"double"	{ return token::DOUBLE; } 
"const"		{ return token::CONST; } 
"volatile"	{ return token::VOLATILE; } 
"void"		{ return token::VOID; } 
"struct"	{ return token::STRUCT; } 
"union"		{ return token::UNION; } 
"enum"		{ return token::ENUM; } 

"case"		{ return token::CASE; } 
"default"	{ return token::DEFAULT; } 
"if"		{ return token::IF; } 
"else"		{ return token::ELSE; } 
"switch"	{ return token::SWITCH; } 
"while"		{ return token::WHILE; } 
"do"		{ return token::DO; } 
"for"		{ return token::FOR; } 
"goto"		{ return token::GOTO; } 
"continue"	{ return token::CONTINUE; } 
"break"		{ return token::BREAK; } 
"return"	{ return token::RETURN; } 

{id}		{ return token::IDENTIFIER; } 

{charconst}	{ return token::CHARACTER_CONSTANT; } 

	/* enumeration consts should go here */

{intconst}	{ return token::INTEGER_CONSTANT; } 
{fltconst}	{ return token::FLOATING_CONSTANT; } 
{stringlit}	{ return token::STRING_LITERAL; } 

"..."		{ return token::ELIPSIS; } 
"->"		{ return token::PTR_OP; } 
"++"		{ return token::INC_OP; } 
"--"		{ return token::DEC_OP; } 
"<<"		{ return token::LEFT_OP; } 
">>"		{ return token::RIGHT_OP; } 
"<="		{ return token::LE_OP; } 
">="		{ return token::GE_OP; } 
"=="		{ return token::EQ_OP; } 
"!="		{ return token::NE_OP; } 
"&&"		{ return token::AND_OP; } 
"||"		{ return token::OR_OP; } 
"*="		{ return token::MUL_ASSIGN; } 
"/="		{ return token::DIV_ASSIGN; } 
"%="		{ return token::MOD_ASSIGN; } 
"+="		{ return token::ADD_ASSIGN; } 
"-="		{ return token::SUB_ASSIGN; } 
"<<="		{ return token::LEFT_ASSIGN; } 
">>="		{ return token::RIGHT_ASSIGN; } 
"&="		{ return token::AND_ASSIGN; } 
"^="		{ return token::XOR_ASSIGN; } 
"|="		{ return token::OR_ASSIGN; } 
"*"		{ return '*'; } 
"|"		{ return '|'; } 
"^"		{ return '^'; } 
"&"		{ return '&'; } 
"<"		{ return '<'; } 
">"		{ return '>'; } 
"+"		{ return '+'; } 
"-"		{ return '-'; } 
"*"		{ return '*'; } 
"/"		{ return '/'; } 
"%"		{ return '%'; } 
"~"		{ return '~'; } 
"!"		{ return '!'; } 
"."		{ return '.'; } 
"?"		{ return '?'; } 
"{"|"<%"	{ return '{'; } 
"}"|"%>"	{ return '}'; } 
"["|"<:"	{ return '['; } 
"]"|":>"	{ return ']'; } 
"("		{ return '('; } 
")"		{ return ')'; } 
"="		{ return '='; } 
","		{ return ','; } 
":"		{ return ':'; } 
";"		{ return ';'; } 

.		{ 
		    driver.error(*yylloc, "Invalid character!");
		} 
%%
void CCompiler::scan_begin()
{
    if(in_fname.empty() || in_fname == "-")
        yyin = stdin;
    else if(!(yyin = fopen(in_fname.c_str(), "r")))
    {
        error("Cannot open" + in_fname + ": " + strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void CCompiler::scan_end()
{
    fclose(yyin);
}
