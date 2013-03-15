YACC_FLAGS= --skeleton=lalr1.cc --defines --debug
FLEX_FLAGS=
CXX_FLAGS=
LIBS=

all: CParser.o CScanner.o main.o CCompiler.o
	g++ -o ccomp CParser.o CScanner.o main.o CCompiler.o $(LIBS)

%.o: %.cpp
	g++ $(CXX_FLAGS) -c -o $@ $<

CParser.cpp: CParser.yy
	bison -o CParser.cpp $(YACC_FLAGS) CParser.yy

CScanner.cpp: CScanner.ll
	flex -o CScanner.cpp $(FLEX_FLAGS) CScanner.ll

clean:
	rm CScanner.cpp CParser.cpp *.o *.hpp *.hh
