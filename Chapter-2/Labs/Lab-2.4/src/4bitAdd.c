// Author: Noman Rafiq
// Dated: Aug 7, 2024
// Description: Adds the 4-Bit (MSB) with a 4-Bit (LSB) of a 16-bit Number(Switch Inputs) and writes the result as a 4-bit number which is used to toggle LEDs on.


#include "header.h"

int main (void)
{
    unsigned int en = 0xFFFF, inp_val, LSB, MSB, Output; // Declare and initialize variables
    write(GPIO_inout, en); // Enable GPIO input/output
    while (1) // Infinite loop
    {
      inp_val = read_switch(GPIO_sw); // Read input value from switches
      inp_val = inp_val >> 16; // Shift input value 16 bits to the right
      LSB = inp_val & 0x000F; // Extract the least significant 4 bits
      MSB = (inp_val & 0xF000) >> 12; // Extract the most significant 4 bits and shift right by 12 bits
      Output = LSB + MSB; // Sum the LSB and MSB
      write(GPIO_led, Output); // Write the output value to the LEDs
    }
  return(0);
}
