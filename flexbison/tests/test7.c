/**
 * Test7.c is the final test. This test evaluates the ability of the compiler to
 * handle 2 dimensional arrays by running a simple matrix multiplication
 * algorithm.
 */
 
int main()
{
 
    int i ;
    int j;
    int k;  
  
    int a[2][2]; 
    int b[2][2];
    int c[2] [2];
   
    for ( i = 0 ;i < 2 ; i++ )
    {
          for ( j = 0 ; j < 2 ; j++ )
          {
                 a[i][j] = 3; 
          
          }

    }
    return 0;
}
