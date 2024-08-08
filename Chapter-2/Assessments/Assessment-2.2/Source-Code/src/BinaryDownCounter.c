// Author: Noman Rafiq
// Dated: Aug 8, 2024
// Description: This program displays the Binary down counter on LEDs, starting from the value of the switches.

#include "header.h"

int main (void)
{
    
    int en = 0xFFFF, inp_val, counter; // Declare and initialize variables
    write(GPIO_inout, en); // Enable GPIO input/output
    
    /* Initialize Uart */
   uartInit();
    
    
    while (1) // Infinite loop
    {
      
      inp_val = read_switch(GPIO_sw); // Read input value from switches
      counter = inp_val >> 16; // Shift input value 16 bits to the right  
      
      while (counter != 0)
      {
      	counter = counter - 1; // Down-Count
      	write(GPIO_led, counter); // Write the output value to the LEDs
      	
      	// Print the result
       printfNexys("Counter=");
       printfNexys("%d", counter);
       
      }
      
      DELAY(10000);
      
      while(1){
      inp_val = read_switch(GPIO_sw); // Read input again from switches
      
      if (inp_val != 0){
      	break;
      }
     }
      
      }
 return(0);
}

