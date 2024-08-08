// Author: Noman Rafiq
// Dated: Aug 7, 2024
// Description: This program computes Factorial of a non-negative number using iterative multiplications.

#include "header.h"

int main (void)
{
    
    int n = 7;

    
    /* Initialize Uart */
   uartInit();
   
   // Call the Factorial function to sort the array
    unsigned long long result = Factorial(n); 
    
   // Print the result
    printfNexys("factorial(n)=");
    
    printfNexys("%llu", result);
   
   while(1);
}
