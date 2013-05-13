/**
 *  Test3.c is designed to test the use of if-else statements.
 */
int main()
{
    int a;
    
    a = 1; //Expected value of a: 1
  
    a = ( 4 + 5 ) * ( 2 + 3 ); //Expected value of a: 45
    
    if(a == 2)
    {
        a = 0;
    }
    else
    {
        a = -1;
    }
    
    //Expected value of a: -1
    
    return 0;
}
