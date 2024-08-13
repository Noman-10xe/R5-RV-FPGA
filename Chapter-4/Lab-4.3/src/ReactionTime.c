// Author: Noman Rafiq
// Date: Aug 11, 2024
// Description: Measure the number of milliseconds it takes for a user to switch 
// the right-most switch on after the LEDs all light up at a random time. 
// The user initiates the game by toggling the right-most switch on and then off.

#include <header.h>

int main ( void )
{
  unsigned int reactionTime;

  initGPIO();
  uartInit();

  WRITE_GPIO(GPIO_LEDs, 0);            // deassert all LEDs
  
  while (1) { 
    startGame();
    printfNexys("Press the Right most Button to Start");
    lightLEDs();
    reactionTime = waitForUser();
    displayReactionTime(reactionTime);
  }

  return(0);
}


