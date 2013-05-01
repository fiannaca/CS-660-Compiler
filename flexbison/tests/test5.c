/**
 * Test5.c is designed to test scoping of variables and calculated array 
 * indices (i.e. line 35). This bubble sort algorithm will be used in the next 
 * test which tests function calls.
 */
 
 //Swap takes two integers as reference parameters and swaps their values
 void swap(int &a, int &b)
 {
    int tmp;
    
    tmp = a;
    a = b;
    b = tmp;
 }
 
 //The bubble sort algorithm
 int main()
 {
    int arr[3];
    bool swapped;
    int i;
    
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
                swap(a[i - 1], a[i]);
                swapped = true;
            }
        }
        
    } while (swapped);
    
    return 0;
 }
