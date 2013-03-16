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

simescseq	\\['\"\?abfnrtv]
octescseq	\\{octdig}{octdig}?{octdig}?
hexescseq	\\x{hexdig}+
unicharname	\\[uU]{hexdig}{hexdig}{hexdig}{hexdig}
escseq		{simescseq}|{octescseq}|{hexescseq}|{unicharname}
charconst	L?'({escseq}|[^'\\])+'

stringlit	L?\"({escseq}|[^\\"])*\"

%x COMMENT

%{
#define YY_USER_ACTION yylloc->columns(yyleng);
%}
%%
%{
yylloc->step();
%}

"!!S"		{
		    //Dump the symbol table contents to the screen
		    std::cout << "Printing the symbol table..." << std::endl;
		}

"//".*		{ 
		    /* no real action - just remove the comment */
		    //printInfo(1, "Comment removed... (single line)\n"); 
		}

"/*"		{   BEGIN(COMMENT); }
<COMMENT>[^*\n]*
<COMMENT>"*"+[^*/\n]*
<COMMENT>\n		{   yylloc->lines(); }
<COMMENT>"*"+"/"	{   BEGIN(INITIAL); }
<COMMENT><<EOF>> 	{
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
"*"		{ return token::STAR; } 
"|"		{ return token::BIN_OR; } 
"^"		{ return token::BIN_XOR; } 
"&"		{ return token::BIN_AND; } 
"<"		{ return token::LT_OP; } 
">"		{ return token::GT_OP; } 
"+"		{ return token::PLUS; } 
"-"		{ return token::MINUS; }
"/"		{ return token::DIV; } 
"%"		{ return token::MOD; } 
"~"		{ return token::TILDE; } 
"!"		{ return token::BANG; } 
"."		{ return token::DOT; } 
"?"		{ return token::WHAT; } 
"{"|"<%"	{ return token::LBRACE; } 
"}"|"%>"	{ return token::RBRACE; } 
"["|"<:"	{ return token::LBRAK; } 
"]"|":>"	{ return token::RBRAK; } 
"("		{ return token::LPAREN; } 
")"		{ return token::RPAREN; } 
"="		{ return token::EQ; } 
","		{ return token::COMMA; } 
":"		{ return token::COLON; } 
";"		{ return token::SEMI; } 

.		{ 
		    driver.error(*yylloc, "Invalid character!");
		} 
%%
void CCompiler::scan_begin(int debug_level)
{
    yyset_debug(debug_level);

    if(in_fname.empty() || in_fname == "-")
        yyin = stdin;
    else if(!(yyin = fopen(in_fname.c_str(), "r")))
    {
        error("Cannot open" + in_fname + ": " + strerror(errno));
        exit(EXIT_FAILURE);
    }

    if(out_fname.empty() || out_fname == "-")
        yyout = stderr;
    else if(!(yyout = fopen(out_fname.c_str(), "w")))
    {
        error("Cannot open" + out_fname + ": " + strerror(errno));
        exit(EXIT_FAILURE);
    }
}

void CCompiler::scan_end()
{
    fclose(yyin);
    fclose(yyout);
}
