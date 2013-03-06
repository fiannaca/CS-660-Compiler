all: Parser.o Scanner.o SymTable.o main.cc
	g++ -o CFrontEnd main.cc Parser.o Scanner.o SymTable.o

Parser.o: parse.cc Parserbase.h Parser.h Parser.ih
	g++ -c parse.cc

Scanner.o: Scannerbase.h Scanner.h Scanner.ih lex.cc
	g++ -c lex.cc

SymTable.o: SymTable.cc SymTable.h
	g++ -c SymTable.cc

parse.cc: CParser.y
	bisonc++ CParser.y --scanner=Scanner.h

lex.cc: CScanner.l
	flexc++ CScanner.l

clean:
	rm -rf *.o
