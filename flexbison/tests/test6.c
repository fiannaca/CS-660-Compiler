/**
 * Test6.c is designed to test scoping of variables and calculated array 
 * indices (i.e. line 25). This bubble sort algorithm will be used in the next 
 * test which tests function calls.
 */
 
 //The bubble sort algorithm
 int main()
 {
    int tarr[5];
    int swapped;
    int i;
    int a;
    int b;
    int tmp;
    
    //Initialize the array to sort
    tarr[0] = 5;
    tarr[1] = 4;
    tarr[2] = 3;
    tarr[3] = 2;
    tarr[4] = 1;
    
    
    //Perform the sort
    do
    {
        swapped = 0;
        
        for(i = 1; i < 5; i++)
        {
        	a = tarr[i - 1];
        	b = tarr[i];
        	
            if(a > b)
            {
		        tmp = tarr[i - 1];
				tarr[i - 1] = tarr[i];
				tarr[i] = tmp;
                swapped = 1;
            }
        }
        
    } while (swapped == 1);
    
    //Expected output of arr: [1, 2, 3, 4, 5]
    
    return 0;
 }
