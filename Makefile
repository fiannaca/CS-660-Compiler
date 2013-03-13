#Add SymTable.o as a dependency to all and to the g++ cmd for all
all: parse.o lex.o main.cc
	g++ --std=c++0x -o CFrontEnd main.cc parse.o lex.o

parse.o: lex.cc parse.cc Parserbase.h Parser.h Parser.ih
	g++ --std=c++0x -c parse.cc

lex.o: Scannerbase.h Scanner.h Scanner.ih lex.cc
	g++ --std=c++0x -c lex.cc

#SymTable.o: SymTable.cc SymTable.h
#	g++ -std=c++11 -c SymTable.cc

#--scanner indicates that bison is being used in conjunction with flex
#--error-verbose dumps parser state information when a syntactic error is encountered
#-t prints out the tokens as they are encountered by the parser
#--error-verbose -t
parse.cc: CParser.y
	bisonc++ CParser.y --scanner=Scanner.h --error-verbose

lex.cc: CScanner.l
	flexc++ CScanner.l

#This will delete all object files and the files which are recreated by
# flexc++ and bisonc++ everytime
clean:
	rm *.o parse.cc lex.cc *base.h
