// Regex definitions
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

%%

//Comments
"//".*		{ /* no action, consume one line comment */ }
"/*"		{ /* We need a comment function to consume a multi line comment */ }
{ws}		{ /* no action, consume whitespace */ }

//Keywords
"sizeof"	{ return(ParserBase::SIZEOF); }
"typedef"	{ return(ParserBase::TYPEDEF); }
"extern"	{ return(ParserBase::EXTERN); }
"static"	{ return(ParserBase::STATIC); }
"auto"		{ return(ParserBase::AUTO); }
"register"	{ return(ParserBase::REGISTER); }

"char"		{ return(ParserBase::CHAR); }
"short"		{ return(ParserBase::SHORT); }
"int"		{ return(ParserBase::INT); }
"long"		{ return(ParserBase::LONG); }
"signed"	{ return(ParserBase::SIGNED); }
"unsigned"	{ return(ParserBase::UNSIGNED); }
"float" 	{ return(ParserBase::FLOAT); }
"double"	{ return(ParserBase::DOUBLE); }
"const"		{ return(ParserBase::CONST); }
"volatile"	{ return(ParserBase::VOLATILE); }
"void"		{ return(ParserBase::VOID); }
"struct"	{ return(ParserBase::STRUCT); }
"union"		{ return(ParserBase::UNION); }
"enum"		{ return(ParserBase::ENUM); }

"case"		{ return(ParserBase::CASE); }
"default"	{ return(ParserBase::DEFAULT); }
"if"		{ return(ParserBase::IF); }
"else"		{ return(ParserBase::ELSE); }
"switch"	{ return(ParserBase::SWITCH); }
"while"		{ return(ParserBase::WHILE); }
"do"		{ return(ParserBase::DO); }
"for"		{ return(ParserBase::FOR); }
"goto"		{ return(ParserBase::GOTO); }
"continue"	{ return(ParserBase::CONTINUE); }
"break"		{ return(ParserBase::BREAK); }
"return"	{ return(ParserBase::RETURN); }

//identifier - First figure out what type of id this is...
{id}		{ return(ParserBase::IDENTIFIER); }

//Constants
{charconst}	{ return(ParserBase::CHARACTER_CONSTANT); }

//enumeration_constant

{intconst}	{ return(ParserBase::INTEGER_CONSTANT); }
{fltconst}	{ return(ParserBase::FLOATING_CONSTANT); }
{stringlit}	{ return(ParserBase::STRING_LITERAL); }

//Punctuators
"..."		{ return(ParserBase::ELIPSIS); }
"->"		{ return(ParserBase::PTR_OP); }
"++"		{ return(ParserBase::INC_OP); }
"--"		{ return(ParserBase::DEC_OP); }
"<<"		{ return(ParserBase::LEFT_OP); }
">>"		{ return(ParserBase::RIGHT_OP); }
"<="		{ return(ParserBase::LE_OP); }
">="		{ return(ParserBase::GE_OP); }
"=="		{ return(ParserBase::EQ_OP); }
"!="		{ return(ParserBase::NE_OP); }
"&&"		{ return(ParserBase::AND_OP); }
"||"		{ return(ParserBase::OR_OP); }
"*="		{ return(ParserBase::MUL_ASSIGN); }
"/="		{ return(ParserBase::DIV_ASSIGN); }
"%="		{ return(ParserBase::MOD_ASSIGN); }
"+="		{ return(ParserBase::ADD_ASSIGN); }
"-="		{ return(ParserBase::SUB_ASSIGN); }
"<<="		{ return(ParserBase::LEFT_ASSIGN); }
">>="		{ return(ParserBase::RIGHT_ASSIGN); }
"&="		{ return(ParserBase::AND_ASSIGN); }
"^="		{ return(ParserBase::XOR_ASSIGN); }
"|="		{ return(ParserBase::OR_ASSIGN); }
"*"		{ return('*'); }
"|"		{ return('|'); }
"^"		{ return('^'); }
"&"		{ return('&'); }
"<"		{ return('<'); }
">"		{ return('>'); }
"+"		{ return('+'); }
"-"		{ return('-'); }
"*"		{ return('*'); }
"/"		{ return('/'); }
"%"		{ return('%'); }
"~"		{ return('~'); }
"!"		{ return('!'); }
"."		{ return('.'); }
"?"		{ return('?'); }
"{"|"<%"	{ return('{'); }
"}"|"%>"	{ return('}'); }
"["|"<:"	{ return('['); }
"]"|":>"	{ return(']'); }
"("		{ return('('); }
")"		{ return(')'); }
"="		{ return('='); }
","		{ return(','); }
":"		{ return(':'); }
";"		{ return(';'); }

.		{ printf("\nYikes! We just ran into an error...\n\n"); }
