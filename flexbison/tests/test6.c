/**
 * Test6.c is designed to test scoping of variables and calculated array 
 * indices (i.e. line 25). This bubble sort algorithm will be used in the next 
 * test which tests function calls.
 */
 
 //The bubble sort algorithm
 int main()
 {
    int tarr[3];
    int swapped;
    int i;
    int tmp;
    
    //Initialize the array to sort
    tarr[0] = 3;
    tarr[1] = 2;
    tarr[2] = 1;
    
    //Perform the sort
    do
    {
        swapped = 0;
        
        for(i = 1; i < 3; i++)
        {
            if(tarr[i - 1] > tarr[i])
            {
		        tmp = tarr[i - 1];
				tarr[i - 1] = tarr[i];
				tarr[i] = tmp;
                swapped = 1;
            }
        }
        
    } while (swapped);
    
    //Expected output of arr: [1, 2, 3]
    
    return 0;
 }
