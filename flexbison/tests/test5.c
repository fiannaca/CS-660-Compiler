/** 
 * Test5.c is designed to test the most basic possible function call. This 
 * example demonstrates how function parameters can be passed to methods.
 */

void add(int a, int b)
{
	int temp;
	temp = a + b; //Expected value of temp: 3
}

int main()
{
	int x;
	int y;
	int result;
	
	x = 1; //Expected value of x: 1
	y = 2; //Expected value of y: 2
	
	add(x, y); //Executes a function call
	
	return 0;
}
