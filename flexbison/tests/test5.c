/**
 * Test5.c is designed to test scoping of variables and calculated array 
 * indices (i.e. line 25). This bubble sort algorithm will be used in the next 
 * test which tests function calls.
 */
 
 //The bubble sort algorithm
 int main()
 {
    int arr[3];
    bool swapped;
    int i;
    int tmp;
    
    //Initialize the array to sort
    arr[0] = 3;
    arr[1] = 2;
    arr[2] = 1;
    
    //Perform the sort
    do
    {
        swapped = false;
        
        for(i = 1; i < 3; ++i)
        {
            if(a[i - 1] > a[i])
            {
		        tmp = a[i - 1];
				a[i - 1] = a[i];
				a[i] = tmp;
                swapped = true;
            }
        }
        
    } while (swapped);
    
    //Expected output of arr: [1, 2, 3]
    
    return 0;
 }
