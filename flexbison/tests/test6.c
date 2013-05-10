/**
 * Test6.c is designed to test function calls. This is the primary goal of the 
 * compiler project. This is a very simple bubble sort algorithm which uses a
 * call to a swap function to swap two integers in a small array. The input 
 * array is [3, 2, 1] and the output array should be [1, 2, 3].
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
    
    //Expected output of arr: [1, 2, 3]
    
    return 0;
 }
