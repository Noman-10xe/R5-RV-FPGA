#include <header.h>

// Initialize GPIO I/O
void initGPIO() {
  int En_Value=0xFFFF;
  WRITE_GPIO(GPIO_INOUT, En_Value);
}

// delays for num milliseconds
void delay(int num) {
  volatile int i, j;
  
  for (i = 0; i < num; i++){
  	for ( j = 0; j < DELAY; j++){
  	}
}
}

// READING SWITCHES
unsigned int readSwitches() {
  unsigned int switches_value = READ_GPIO(GPIO_SWs);   // read value on switches
  switches_value = switches_value >> 16;               // shift into lower 16 bits

  return switches_value;
}


// Waits for user to toggle right-most switch on and then off to start the game
void initGame() {
  unsigned int numTicks = 0;

  printfNexys("Toggle ON the Switch (RMB)");
  // if not already on, wait for user to toggle switch on first
  while ( !(readSwitches() & 1) ) {
    numTicks++;
}
  printfNexys("Toggle OFF the Switch to get Started");
  while (  (readSwitches() & 1) ){    // wait for user to toggle switch off
    numTicks++;
  }
  srand(numTicks);
}

// Waits for user to toggle right-most switch (SW[0]) on and then off to initiate game
void startGame() {
  unsigned int numTicks = 0;
  while (  (readSwitches() & 1)) numTicks++; // wait for user to toggle switch off
  WRITE_GPIO(GPIO_LEDs, 0);
  delay(numTicks);
  srand(numTicks);
}

void lightLEDs() {
  int val;

  WRITE_GPIO(GPIO_LEDs, 0);           // deassert all LEDs
  val = rand() % MAXWAIT;
  delay(val);
  WRITE_GPIO(GPIO_LEDs, 0xFFFF);      // assert all LEDs
}

unsigned int waitForUser() {
  unsigned int numTicks = 0;
  unsigned int numTicksPer_ms = 4 * DELAY;
  
  while ( readSwitches() & 1 );
  
  // wait for user to toggle switch on
  while ( !(readSwitches() & 1) ) 
    numTicks++;    

  numTicks = numTicks / numTicksPer_ms;
  return numTicks;
}

// display reaction time on LEDs and serial monitor
void displayReactionTime(unsigned int time) {
  WRITE_GPIO(GPIO_LEDs, time);
  printfNexys("Reaction Time: %d ms\n", time);
}
