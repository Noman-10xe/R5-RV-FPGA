// Author: Noman Rafiq
// Dated: Aug 7, 2024
// Description: This program uses a Vector A to generate a vector B, such that B only contains those elements of A that are even numbers greater than 0. The program also counts the number of elements in B and print that value at the end of the program.

#include "header.h"  // Include the custom header file

int main (void) {

    int A[N] = {13, -2, 3, 98732, 323, 1221, 482, 18273, 94, 1000, 179, 10};  // Initialize array A with given integers
    
    int j;  // Initialize counter j to 0
    int B[j];   // Declare array B
    
    j = 0; //initilize counter to 0
    
    for (int i = 0; i < N; i++) {  // Loop through each element in array A
        if (A[i] % 2 == 0 && A[i] > 2) {  // Check if A[i] is even and greater than 2
            B[j] = A[i];  // If condition is true, assign A[i] to B[j]
            j++;  // Increment counter j
        } else {
            // Do Nothing
        }
    }
    
    /* Initialize Uart */
    uartInit();  // Call function to initialize UART
    
    printfNexys("Number of Elements in B: %d", j);  // Print the number of elements in array B
    
    while(1);  // Infinite loop to keep the program running
}
