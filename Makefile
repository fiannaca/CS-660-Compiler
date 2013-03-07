#Add SymTable.o as a dependency to all and to the g++ cmd for all
all: parse.o lex.o main.cc
	g++ -std=c++11 -o CFrontEnd main.cc parse.o lex.o

parse.o: parse.cc Parserbase.h Parser.h Parser.ih
	g++ -std=c++11 -c parse.cc

lex.o: Scannerbase.h Scanner.h Scanner.ih lex.cc
	g++ -std=c++11 -c lex.cc

#SymTable.o: SymTable.cc SymTable.h
#	g++ -std=c++11 -c SymTable.cc

parse.cc: CParser.y
	bisonc++ CParser.y --scanner=Scanner.h

lex.cc: CScanner.l
	flexc++ CScanner.l

#This will delete all object files and the files which are recreated by
# flexc++ and bisonc++ everytime
clean:
	rm *.o
	rm lex.cc
	rm parse.cc
