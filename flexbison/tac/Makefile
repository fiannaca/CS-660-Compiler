CXX_FLAGS= -std=c++0x -g

all: TAC_Generator.o tac_test.o
	g++ -o test TAC_Generator.o tac_test.o

%.o: %.cpp
	g++ $(CXX_FLAGS) -c -o $@ $<

clean:
	rm *.o *~ test output
