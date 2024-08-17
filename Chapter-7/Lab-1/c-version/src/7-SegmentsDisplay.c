// Author: Noman Rafiq
// Dated: Aug 17, 2024
// Description: This program reads the binary values from switches and displays the corresponding hex output on four of the eight digits of a seven-segment display.

#include<header.h>

// main
int main ( void )
{

	int switches_value;
	
	// Enable 4 displays from the right (active low enabled) -> Least Significant 4 digits
	WRITE_7Seg(En_REG, 0xF0);
	
	// Enable GPIO I/O
	WRITE_GPIO(GPIO_INOUT, 0xFFFF);
	
	while (1){
		switches_value = READ_GPIO(GPIO_SWs); // Read switch values
		switches_value >>= 16; // shift swicthes to least significant bits
		
		WRITE_7Seg(DIGITS_REG, switches_value); // write switches value to Digits Registers for Display
		
		delay(200);
		
	}
	return(0);
}
