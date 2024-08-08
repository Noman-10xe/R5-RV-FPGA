// Author: Noman Rafiq
// Dated: Aug 7, 2024
// Description: This program Finds the first 12 numbers in Fiboannaci Series.

#include "header.h" // Include the header file

int main (void)
{
    int i = 2, fibim1 = 0, fibim2 = 1; // Initialize variables for Fibonacci calculation
    int fibi[N]; // Declare an array to store Fibonacci numbers
   	
    fibi[i-2] = fibim1; // Assign the first Fibonacci number
    fibi[i-1] = fibim2; // Assign the second Fibonacci number
   
    for (i = 2; i < N; i++) { // Loop to calculate the rest of the Fibonacci series
        fibi[i] = fibi[i-2] + fibi[i-1]; // Calculate the next Fibonacci number
    } 
   	      
    /* Initialize Uart */
    uartInit(); // Initialize UART for communication
   
    printfNexys("Fibonacci Series (First 12):\n");
    
    for (i = 0; i < N; i++) { 
    	
    	// Loop to print the Fibonacci series
        printfNexys("%d", fibi[i]); // Print each Fibonacci number
    }
   
    while(1); // Infinite loop to keep the program running
}

