// Author: Noman Rafiq
// Date: Aug 12, 2024
// Description: This program displays a random sequence of patterns on the 3 right-most LEDs. 
// The user must mimic this pattern using the 3 right-most switches. If the user does not 
// enter the correct pattern, all of the LEDs stay lit.
// The program is initiated or restarted by the user toggling the left-most switch (Switch[15]) on and then off.

#include <header.h>

int main ( void )
{
  int n = 1;
  
  initGPIO();
  uartInit();

  WRITE_GPIO(GPIO_LEDs, 0);            // deassert all LEDs
  initGame();
  
  while (1) {
    unsigned int pattern = lightLEDs(n);
    compare(pattern, n);
    startGame();
    n++;
   }
  return(0);
}

