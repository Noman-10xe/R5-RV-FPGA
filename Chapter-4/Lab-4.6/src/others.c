#include <header.h>

// Initialize GPIO I/O
void initGPIO() {
  int En_Value = 0xFFFF;
  WRITE_GPIO(GPIO_INOUT, En_Value);
}

// delays for num milliseconds
void delay(int num) {
  volatile int i, j;
  for (i = 0; i < num; i++) {
    for (j = 0; j < DELAY; j++) {
    }
  }
}

// READING SWITCHES
unsigned int readSwitches() {
  unsigned int switches_value = READ_GPIO(GPIO_SWs);   // read value on switches
  switches_value = switches_value >> 16;               // shift into lower 16 bits
  return switches_value;
}

// Resets the game if the leftmost button (SW[15]) is pressed
void checkForReset() {
  if (readSwitches() & 0x8000) {  // Check if the leftmost switch is on
    printfNexys("Game Reset!");
    
    printfNexys("Toggle Off the reset-button to complete Reset");
    while ((readSwitches() & 0x8000));
    WRITE_GPIO(GPIO_LEDs, 0);     // Turn off all LEDs
    initGame();                   // Reinitialize the game
  }
}

// Waits for user to toggle right-most switch on and then off to start the game
void initGame() {
  unsigned int numTicks = 0;
  printfNexys("Toggle ON the Switch on the Right");
  while (!(readSwitches() & 1)) {  // Wait for the rightmost switch to be toggled on
    checkForReset();               // Check for reset during this wait
    numTicks++;
  }
  printfNexys("Toggle OFF the Switch to get Started");
  while ((readSwitches() & 1)) {   // Wait for the rightmost switch to be toggled off
    checkForReset();               // Check for reset during this wait
    numTicks++;
  }
  srand(numTicks);
}

// Waits for user to toggle right-most switch (SW[0]) on and then off to initiate game
void startGame() {
  unsigned int numTicks = 0;
  delay(1000);
  while ((readSwitches() & 1)) numTicks++; // wait for user to toggle switch off
  WRITE_GPIO(GPIO_LEDs, 0);
  delay(numTicks);  // Delay of random milliseconds
  srand(numTicks);  // Seed the random generator
}

// Compare if the user-made guess is correct
void compare(unsigned int pattern, int level) {
  unsigned int user_input = 0;

  do {
    user_input = waitForUser(level); // Get the user's input for this level
    
    if (user_input != pattern) {
      delay(1500);
      printfNexys("Incorrect! Try again");
      while (!(readSwitches() & 1));
      delay(200);
      checkForReset();  // Check for reset before retrying
      }
    }
  while (user_input != pattern);

  printfNexys("Correct!");
  while (readSwitches() & 1);
  printfNexys("Moving to the next Level...");
  delay(1500);
}

unsigned int lightLEDs(int level) {
  unsigned int pattern = 0;
  for (int i = 0; i < level; i++) {
    unsigned int led = 1 << (rand() % level);  // Random LED pattern within the three right-most LEDs
    pattern |= led; // Store the sequence

    WRITE_GPIO(GPIO_LEDs, led);
    delay(600);

    WRITE_GPIO(GPIO_LEDs, 0);
    delay(600);
  }

  WRITE_GPIO(GPIO_LEDs, pattern);  // Show the full pattern at the end
  delay(800);  // Pause to let the user memorize the pattern

  WRITE_GPIO(GPIO_LEDs, 0);  // Turn off LEDs before user input
  return pattern;  // Return the full pattern for comparison
}

unsigned int waitForUser(int level) {
  unsigned int user_input = 0;
  unsigned int input_value;

  printfNexys("Enter the pattern by toggling switches.");
  while (!(readSwitches() & 1)) checkForReset();  // Check for reset during this wait
  do {
    input_value = readSwitches() & ((1 << level) - 1);  // Mask to only consider the switches up to the current level
    if (input_value) {
      user_input |= input_value;  // Add the current input to the user_input
      WRITE_GPIO(GPIO_LEDs, user_input);  // Light up corresponding LEDs
    }
    delay(200);  // Short delay to debounce switches
    checkForReset();  // Check for reset during user input
  } while ((input_value));  // Continue until all switches are turned off

  return user_input;
}
