// Author: Noman Rafiq
// Dated: Aug 8, 2024
// Description: This program checks if the switch value is a palindrome in binary form. If it is, all LEDs are turned on; otherwise, they are turn off.

#include "header.h"

int main (void)
{
    
    int en = 0xFFFF, inp_val; // Declare and initialize variables
    bool output;
    write(GPIO_inout, en); // Enable GPIO input/output    
    
    while (1) // Infinite loop
    {
      inp_val = read_switch(GPIO_sw); // Read input value from switches
      inp_val = inp_val >> 16; // Shift input value 16 bits to the right
      
      output = palindrome(inp_val);  //Function Call to check palindrome
      
      if (output == true){
      	int on = 0xFFFFFFFF;
      	write(GPIO_led, on); // Turn the LEDs ON
      }
      
      else {
      	int off = 0x0;
      	write(GPIO_led, off); // Turn the LEDs OFF
      }
      }
 return(0);
}

