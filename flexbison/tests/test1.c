/**
 * Test1.c is designed to test the most basic features of C, including variable
 * declarations, simple assignments, and simple arithmetic operations. In order
 * to demonstrate the effect of spill registers, the tac2mips compiler can be
 * compiled with only having 4 registers instead of 8, and this example will show
 * what happens when spilling needs to occur.
 */
int main()
{
    int i;
    int j;
    int k;
    
    i = 1; //Expected value of i: 1
    j = 2; //Expected value of j: 2
    
    k = i + j; //Expected value of k: 3
    
    k = j - i; //Expected value of k: 1
    
    k = i * j; //Expected value of k: 2
    
    k = j / i; //Expected value of k: 2
    
    k = j % i; //Expected value of k: 0
    
    
    //If the maximum # of registers is set to 4, this expression will require
    // spilling one register
    k = (((1 + 2) + (3 + 4)) + ((5 + 6) + (7 + 8))) + (9 + 10); //Expected value of k: 55
    
    return 0;
}
