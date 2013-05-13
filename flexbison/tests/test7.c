/**
 * Test7.c is designed to test function calls. This is the primary goal of the 
 * compiler project. This is a very simple bubble sort algorithm which uses a
 * call to a swap function to swap two integers in a small array. The input 
 * array is [3, 2, 1] and the output array should be [1, 2, 3].
 */
 
 //Swap takes two integers as reference parameters and swaps their values
 void swap(int *a, int *b)
 {
    int tmp;
    
    tmp = *a;
    *a = *b;
    *b = tmp;
 }
 
 //The bubble sort algorithm
 int main()
 {
    int tarr[3];
    int swapped;
    int i;
    
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
                swap(&tarr[i - 1], &tarr[i]);
                swapped = 1;
            }
        }
        
    } while (swapped);
    
    //Expected output of arr: [1, 2, 3]
    
    return 0;
 }
