/**
 * Test2.c is designed to test the proper allocation of arrays and calculation 
 * of array indices and access operations.
 */
int main()
{
    int a[3];
    
    a[0] = 3;
    a[1] = 2;
    a[2] = 1;
    
    //Expected values on the stack from $sp: 1, 2, 3 (growing down from $sp)
    
    return 0;    
}
