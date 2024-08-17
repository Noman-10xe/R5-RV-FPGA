// Seven - Segments Display Registers (memory map)
#define En_REG    0x80001038
#define DIGITS_REG   0x8000103C

// GPIO I/O Registers (memory map)
#define GPIO_SWs      0x80001400
#define GPIO_LEDs     0x80001404
#define GPIO_INOUT    0x80001408

// Write to 7-Segments
#define WRITE_7Seg(dir, value) { (*(volatile unsigned *)dir) = (value); }

// Read & Write to 7-Segments
#define READ_GPIO(dir) (*(volatile unsigned *)dir)
#define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); }

// DELAY
#define DELAY 	0x1    /* Define the DELAY - empirical number approximately equal to 1 ms */

// delay function Prototype
void delay(int num);
