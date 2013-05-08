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
    
    k = i + j; //3
    
    k = j - i; //1
    
    k = i * j; //2
    
    k = j / i; //2
    
    //Extra operations to test proper register allocation (and releasing)
    k = i + j; //3
    
    k = j - i; //1
    
    k = i * j; //2
    
    k = j / i; //2
    
    k = i + j; //3
    
    k = j - i; //1
    
    k = i * j; //2
    
    k = j / i; //2
    
    return 0;
}
