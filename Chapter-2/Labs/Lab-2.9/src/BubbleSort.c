// Author: Noman Rafiq
// Dated: Aug 7, 2024
// Description: This program implements the BubbleSort Algorithm. This Algo sorts the components of a vector in ascending order.

#include "header.h"

int main (void)
{
    
    int A[N] = {13, -2, 3, 982, 33, 121, 482, 73, 94, 101, 19, 10 };

    // Call the BubbleSort function to sort the array
    BubbleSort(A); 
    
    /* Initialize Uart */
   uartInit();
   
   
   // Print the sorted array
    printfNexys("Sorted array:");
    
   for (int i = 0; i < N; i++) {
        printfNexys("%d", A[i]);
    }
   
   while(1);
}
