/**
 * Test1.c is designed to test the most basic features of C, including variable
 * declarations, simple assignments, and simple arithmetic operations.
 */
int main()
{
    int i;
    int j;
    int k;
    
    i = 1;
    j = 2;
    
    k = i + j; //Expected value of k: 3
    
    k = j - i; //Expected value of k: 1
    
    k = i * j; //Expected value of k: 2
    
    k = j / i; //Expected value of k: 2
    
    k = j % i; //Expected value of k: 1
    
    k = (((1 + 2) + (3 + 4)) + ((5 + 6) + (7 + 8))) + (9 + 10); //Expected value of k: 55
    
    return 0;
}
