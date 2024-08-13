#if defined(D_NEXYS_A7)
   #include <bsp_printf.h>
   #include <bsp_mem_map.h>
   #include <bsp_version.h>
#else
   PRE_COMPILED_MSG("no platform was defined")
#endif
#include <psp_api.h>
#include <stdlib.h>

// memory-mapped I/O addresses
#define GPIO_SWs    0x80001400
#define GPIO_LEDs   0x80001404
#define GPIO_INOUT  0x80001408

#define DELAY 	0x1	         /* Define the DELAY - empirical number approximately equal to 1 ms */
#define MAXWAIT 20		 /* Maximum number of seconds to wait before lighting LEDs is 10 seconds */

#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, val) { (*(volatile unsigned *)dir) = (val); }

// Function Prototypes
void initGPIO();
unsigned int readSwitches();
void initGame();
void delay(int num);
void startGame();
void lightLEDs();
unsigned int waitForUser();
void displayReactionTime(unsigned int time);
