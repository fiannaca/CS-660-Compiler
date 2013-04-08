all: TAC_Generator.o tac_test.o
	g++ -o test TAC_Generator.o tac_test.o

%.o: %.cpp
	g++ -g -c -o $@ $<

clean:
	rm *.o *~
