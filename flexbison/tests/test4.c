/**
 * Test4.c is designed to test the basic loops including the for, do-while, and 
 * while loops. In addition, this file tests the incrementor and decrementor.
 */
 int main()
 {
    int i;
    int a;
    
    //This will increment a from 1 to 10
    a = 1;
    
    for(i = 0; i < 10; i++)
    {
        a = a + 2;
    }
    
    //This will increment a from 1 to 10
    a = 1;
    
    while(a < 10)
    {
        a = a + 2;
    }
    
    //This will increment a from 1 to 10
    a = 1;
    
    do
    {
        a = a + 2;
    } while (a < 10);
    
    return 0;
 }
