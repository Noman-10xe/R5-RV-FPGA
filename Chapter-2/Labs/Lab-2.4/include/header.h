#if defined(D_NEXYS_A7)
    #include <bsp_printf.h>
    #include <bsp_mem_map.h>
    #include <bsp_version.h>
 #else
    PRE_COMPILED_MSG("no platform was defined")
 #endif
 #include <psp_api.h>
 
 #define GPIO_inout 0x80001408 // phyiscal address of the general purpose IOs
 #define GPIO_sw 0x80001400 // phyiscal address from where input will read the data (Input register bit field address)
 #define GPIO_led 0x80001404 // phyiscal address at where output will write (output register bit field address)
 #define read_switch(dir) (*(volatile unsigned int *)dir)  // reading the value from address using dereferencing pointer
 #define write(dir, value) {*(volatile unsigned int *)dir = (value);}  // writing some value at output using dereferencing pointer
 #define DELAY(tick) {for(int i =0; i <tick; i++);}

