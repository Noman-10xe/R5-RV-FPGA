#if defined(D_NEXYS_A7)
    #include <bsp_printf.h>
    #include <bsp_mem_map.h>
    #include <bsp_version.h>
 #else
    PRE_COMPILED_MSG("no platform was defined")
 #endif
 #include <psp_api.h>
 
 #define GPIO_INOUT 0x80001408 // phyiscal address of the general purpose IOs
 #define GPIO_sw 0x80001400 // phyiscal address from where input will read the data (Input register bit field address)
 #define GPIO_led 0x80001404 // phyiscal address at where output will write (output register bit field address)
 #define READ_GPIO(dir) (*(volatile unsigned *)dir) // reading the value from address using dereferencing pointer
 #define WRITE_GPIO(dir, value) { (*(volatile unsigned *)dir) = (value); } // writing some value at output using dereferencing pointer
 #define DELAY 	0x1	         /* Define the DELAY - empirical number approximately equal to 1 ms */


 void delay(int num);
