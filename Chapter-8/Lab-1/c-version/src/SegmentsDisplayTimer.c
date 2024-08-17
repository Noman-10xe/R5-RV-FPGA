// Author: Noman Rafiq
// Dated: Aug 17, 2024
// Description: This program displays an ascending count on 8-digit 7-segment displays, updating every second. 
// It uses the timer module to create the delay, the processor 
// periodically polls the peripheral to check if the count is complete.


#include<header.h>

int main (void) {

	// Configure 7-Segment Display
	WRITE_Reg(En_REG, 0x0);
	WRITE_Reg(DIGITS_REG, 0x0);
	
	// Initialize RPTC_LRC = 5000
	WRITE_Reg(RPTC_LRC, 5000);
	
	// Reset the counter
	WRITE_Reg(RPTC_CTRL, 0x80);
	
	// de-assert reset and enable count
	WRITE_Reg(RPTC_CTRL, 0x1);
	
	int count = 0; 
	int clks;
	
	while (1) {
		// Poll the timer
		clks = READ_Reg(RPTC_CNTR);
		while ( clks != 0 ){ // if timer has not reached zero, continue polling
		clks = READ_Reg(RPTC_CNTR);
		}
		
		WRITE_Reg(DIGITS_REG, count); // update display on 7-segments after clks
		count++; // increment counters	
		
		// Reset the timer
		WRITE_Reg(RPTC_CTRL, 0x80);
		
		//short delay for proper reset
		for (int i = 0; i < 100; i++);
		
		// de-assert reset and enable count
		WRITE_Reg(RPTC_CTRL, 0x1);
	}

	return(0);
}


/*#include<header.h>

int main (void) {

    // Configure 7-Segment Display
    WRITE_Reg(En_REG, 0x0);
    WRITE_Reg(DIGITS_REG, 0x0);
    
    // Initialize RPTC_LRC = 5000
    WRITE_Reg(RPTC_LRC, 5000);
    
    // Reset the counter
    WRITE_Reg(RPTC_CTRL, 0x80);
    
    // de-assert reset and enable count
    WRITE_Reg(RPTC_CTRL, 0x1);
    
    int count = 0; 
    int clks;
    
    while (1) {
        // Poll the timer
        clks = READ_Reg(RPTC_CNTR);
        while ( clks != 0 ) {
            clks = READ_Reg(RPTC_CNTR); // continue polling
        }
        
        WRITE_Reg(DIGITS_REG, count % 10); // update display on 7-segments after clks
        count++; // increment counters    
        
        // Reset the timer
        WRITE_Reg(RPTC_CTRL, 0x80);
        
        // Small delay to ensure timer reset
        for (volatile int i = 0; i < 1000; i++);
        
        // de-assert reset and enable count
        WRITE_Reg(RPTC_CTRL, 0x1);
    }

    return(0);
}
*/

