YACC_FLAGS= --skeleton=lalr1.cc --defines --debug
FLEX_FLAGS= --debug --warn --nodefault --noyywrap --batch --header-file=TAC_Scanner.h
CXX_FLAGS= -std=c++0x -g
LIBS=

all: TAC_Parser.o TAC_Scanner.o RegAllocTable.o AddressTable.o tac2mips.o main.o
	g++ -o tac2mips main.o tac2mips.o RegAllocTable.o AddressTable.o TAC_Parser.o TAC_Scanner.o $(LIBS)

testreg: SpillTest.o RegAllocTable.o AddressTable.o
	g++ -o spill SpillTest.o RegAllocTable.o AddressTable.o

testaddr: AddressTest.o AddressTable.o
	g++ -o addr AddressTest.o AddressTable.o

%.o: %.cpp
	g++ $(CXX_FLAGS) -c -o $@ $<

TAC_Parser.cpp: TAC_Parser.yy
	bison -o TAC_Parser.cpp $(YACC_FLAGS) TAC_Parser.yy

TAC_Scanner.cpp: TAC_Scanner.ll
	flex -o TAC_Scanner.cpp $(FLEX_FLAGS) TAC_Scanner.ll

clean:
	rm TAC_Scanner.cpp TAC_Scanner.h TAC_Parser.cpp *.o *.hpp *.hh *~ spill
