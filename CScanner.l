// Regex definitions
letter		[a-zA-Z]
digit		[0-9]
hexdig		[0-9a-fA-F]
octdig		[0-7]
id		({letter}|_)(letter|digit)*

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

simseq		\\['\"\?\\abfnrtv]
octesc		\\{octdig}{octdig}?{octdig}?
hexesc		\\x{hexdig}+
unicharname	\\[uU]{hexdig}{hexdig}{hexdig}{hexdig}
escseq		{simseq}|{octseq}|{hexseq}|{unicharname}
charconst	L?'({escseq}|[^'\\])+'

stringlit	L?\"({escseq}|[^\\"])*\"

%%

//Comments
"//".*		{ //no action, consume one line comment }
"/*"		{ //We need a comment function to consume a multi line comment }

//Keywords
"sizeof"	{ return(SIZEOF); }
"typedef"	{ return(TYPEDEF); }
"extern"	{ return(EXTERN); }
"static"	{ return(STATIC); }
"auto"		{ return(AUTO); }
"register"	{ return(REGISTER); }

"char"		{ return(CHAR); }
"short"		{ return(SHORT); }
"int"		{ return(INT); }
"long"		{ return(LONG); }
"signed"	{ return(SIGNED); }
"unsigned"	{ return(UNSIGNED); }
"float" 	{ return(FLOAT); }
"double"	{ return(DOUBLE); }
"const"		{ return(CONST); }
"volatile"	{ return(VOLATILE); }
"void"		{ return(VOID); }
"struct"	{ return(STRUCT); }
"union"		{ return(UNION); }
"enum"		{ return(ENUM); }

"case"		{ return(CASE); }
"default"	{ return(DEFAULT); }
"if"		{ return(IF); }
"else"		{ return(ELSE); }
"switch"	{ return(SWITCH); }
"while"		{ return(WHILE); }
"do"		{ return(DO); }
"for"		{ return(FOR); }
"goto"		{ return(GOTO); }
"continue"	{ return(CONTINUE); }
"break"		{ return(BREAK); }
"return"	{ return(RETURN); }

//identifier - First figure out what type of id this is...
{id}		{ return(IDENTIFIER); }

//Constants
{charconst}	{ return(CHARACTER_CONSTANT); }

//enumeration_constant

{intconst}	{ return(INTEGER_CONSTANT); }
{fltconst}	{ return(FLOATING_CONSTANT); }
{stringlit}	{ return(STRING_LITERAL); }

//Punctuators
"..."		{ return(ELLIPSIS); }
"->"		{ return(PTR_OP); }
"++"		{ return(INC_OP); }
"--"		{ return(DEC_OP); }
"<<"		{ return(LEFT_OP); }
">>"		{ return(RIGHT_OP); }
"<="		{ return(LE_OP); }
">="		{ return(GE_OP); }
"=="		{ return(EQ_OP); }
"!="		{ return(NE_OP); }
"&&"		{ return(AND_OP); }
"||"		{ return(OR_OP); }
"*="		{ return(MUL_ASSIGN); }
"/="		{ return(DIV_ASSIGN); }
"%="		{ return(MOD_ASSIGN); }
"+="		{ return(ADD_ASSIGN); }
"-="		{ return(SUB_ASSIGN); }
"<<="		{ return(LEFT_ASSIGN); }
">>="		{ return(RIGHT_ASSIGN); }
"&="		{ return(AND_ASSIGN); }
"^="		{ return(XOR_ASSIGN); }
"|="		{ return(OR_ASSIGN); }
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

.		{ printf("WTF? Learn to code!"); }
