/**
 * Test5.c is designed to test scoping of variables and calculated array 
 * indices (i.e. line 25). This bubble sort algorithm will be used in the next 
 * test which tests function calls.
 */
 
 //The bubble sort algorithm
 int main()
 {
    int swapped;
    int i;
    int tmp;
    int arr[3];
    
    //Initialize the array to sort
    arr[0] = 3;
    arr[1] = 2;
    arr[2] = 1;
    
    //Perform the sort
    do
    {
        swapped = 0;
        
        i = 1;
        
        while(i < 3)
        {
            if(a[i - 1] > a[i])
            {
		        tmp = a[i - 1];
				a[i - 1] = a[i];
				a[i] = tmp;
                swapped = 1;
            }
            
            i++;
        }
        
    } while (swapped == 1);
    
    //Expected output of arr: [1, 2, 3]
    
    return 0;
 }
