/**
 * Test7.c is the final test. This test evaluates the ability of the compiler to
 * handle 2 dimensional arrays by running a simple matrix multiplication
 * algorithm.
 */
 
int main()
{
    int i, j, k;
    int a[2][2];
    int b[2][2];
    int c[2][2];
    
    //a is the identity matrix
    a[0][0] = 1;
    a[0][1] = 0;
    a[1][0] = 0;
    a[1][1] = 1;
    
    //b is the matrix [[1,2],[3,4]]
    b[0][0] = 1;
    b[0][1] = 2;
    b[1][0] = 3;
    b[1][1] = 4;
    
    //Matrix Multiplication: c = a * b (c should have the same values as b above)
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < 2; j++)
        {
            for(k = 0; k < 2; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    
    return 0;
}
