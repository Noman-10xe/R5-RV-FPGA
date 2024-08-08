// Author: Noman Rafiq
// Dated: Aug 8, 2024
// Description: This program mirrors the value of the switches on the LEDs. For instance, if the switches are set to 1010 0001, the LEDs display 1000 0101.

#include "header.h"

int main (void)
{
    
    int en = 0xFFFF, inp_val; // Declare and initialize variables
    short int output;
    write(GPIO_inout, en); // Enable GPIO input/output    
    
    while (1) // Infinite loop
    {
      inp_val = read_switch(GPIO_sw); // Read input value from switches
      output = inp_val >> 16; // Shift input value 16 bits to the right
      
      output = reverse(output);  //Function Call to mirror bits
     
      write(GPIO_led, output); // Write the output value to the LEDs
      
      }
 return(0);
}

