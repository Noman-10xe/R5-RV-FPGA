// Author: Noman Rafiq
// Dated: Aug 7, 2024
// Description: This program sums two Vectors A, B, and strores the result in another vector C such that C[i] = A[i] + B[N - i - 1].


#include "header.h"  // Include the custom header file

int main (void) {
    int A[N] = {13, -2, 3, 982, 33, 121, 482, 73, 94, 101, 19, 10};  // Initialize array A with given integers
    
    int B[N] = {42, -17, 56, 79, 24, 57, 80, 14, 58, -90, 112, 314}; // Initialize array B with given integers

    int C[N];  // Declare array C to store the sum of corresponding elements from A and B

    Sum(A, B, C);  // Call function Sum to compute the element-wise sum of A and B, storing the result in C

    /* Initialize Uart */
    uartInit();  // Call function to initialize UART

    for (int i = 0; i < N; i++) {  
    
    	// Loop through each element in array C
        printfNexys("%d", C[i]);  // Print each element of array C
    }

    while(1);  // Infinite loop to keep the program running
}
