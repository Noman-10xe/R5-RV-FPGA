// Author: Noman Rafiq
// Dated: Aug 7, 2024
// Description: This program used the Euclidean Algorithm to find the Greatest Common Divisor (GCD) of 2 integers.


#include "header.h"

int main (void)
{
    int a = 68, b = 119, result; // Declare and initialize variables a and b

    result = GCD(&a, &b); // Call the GCD function and store the result

    /* Initialize Uart */
    uartInit(); // Initialize UART for communication

    /* Print result of GCD */
    printfNexys("Greatest Common Divisor = %d\n", result); // Print the GCD result to the console

    while(1); // Infinite loop to keep the program running
}
