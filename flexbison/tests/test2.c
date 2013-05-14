/**
 * Test2.c is designed to test the proper allocation of arrays and calculation 
 * of array indices and access operations. The lines of code from 35 - 37 demonstrate
 * the effect of spilling in the register allocation scheme.
 */
int main()
{
    int a[3];
    int b[2][3];
	int temp;
    
    a[0] = 3;
    a[1] = 2;
    a[2] = 1;
    
    //Expected values on the stack for a: 3, 2, 1
    
    b[0][0] = 4;
    b[0][1] = 4;
    b[0][2] = 4;
    b[1][0] = 4;
    b[1][1] = 4;
    b[1][2] = 4;

	//Expected values on the stack from $sp: 4, 4, 4, 4, 4, 4

	temp = 3;
	
	a[temp - 2] = 3;
	a[temp - 1] = 3;
	
	//Expected values on the stack from b: 3, 3, 3
	
	temp = 2;
	
	b[temp - 1][temp - temp] = a[temp];
	b[temp - 1][temp - 1] = a[temp];
	b[temp - 1][temp] = a[temp];
	
	//Expected values on the stack for b: 4, 4, 4, 3, 3, 3
	
    return 0;    
}
