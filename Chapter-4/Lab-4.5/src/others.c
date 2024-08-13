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

// display Bar
void displayReactionTime(unsigned int time) {
  unsigned int Bar;
  
  if ( time > SLOW)
  Bar = 0xFFFF;
  else if ( time > (SLOW - 10))
  Bar = 0x7FFF;
  else if ( time > (SLOW - 20))
  Bar = 0x3FFF;
  else if ( time > (SLOW - 30))
  Bar = 0x1FFF;
  else if ( time > (SLOW - 40))
  Bar = 0x0FFF;
  else if ( time > (SLOW - 50))
  Bar = 0x07FF;
  else if ( time > (SLOW - 60))
  Bar = 0x03FF;
  else if ( time > (SLOW - 70))
  Bar = 0x01FF;
  else if ( time > (SLOW - 80))
  Bar = 0x00FF;
  else if ( time > (SLOW - 90))
  Bar = 0x007F;
  else if ( time > (SLOW - 100))
  Bar = 0x003F;
  else if ( time > (SLOW - 120))
  Bar = 0x001F;
  else if ( time > (SLOW - 140))
  Bar = 0x000F;
  else if ( time > (SLOW - 160))
  Bar = 0x0007;
  else if ( time > (SLOW - 180))
  Bar = 0x0003;
  else if ( time > (SLOW - 200))
  Bar = 0x0001;
  else
  Bar = 0xFFFF;
  
  printfNexys("Reaction Time: %d ms\n", time);
  WRITE_GPIO(GPIO_LEDs, Bar);
  
}
