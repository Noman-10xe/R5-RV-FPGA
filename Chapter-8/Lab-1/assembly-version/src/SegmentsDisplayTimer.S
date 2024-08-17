# Author: Noman Rafiq
# Dated: Aug 17, 2024
# Description: This program displays an ascending count on 8-digit 7-segment displays, updating every second. 
# It uses the timer module to create the delay, the processor 
# periodically polls the peripheral to check if the count is complete.

# Seven - Segments Display Registers (memory map)
# En_REG    0x80001038
# DIGITS_REG   0x8000103C

# PTC Register
# RPTC_CNTR 0x80001200
# RPTC_HRC  0x80001204
# RPTC_LRC  0x80001208
# RPTC_CTRL 0x8000120C


.globl main

.equ En_REG, 0x80001038          # Define physical address for 7-Segment Displays
.equ RPTC_CNTR, 0x80001200	 # Define physical address for PTC registers


.text

main:
	################ PROLOGUE ################ 
	addi sp, sp, -12    # allocate space on stack
	sw ra, 0(sp)	    # store return address on stack
	sw s0, 4(sp)	    # store saved register before using
	sw s1, 8(sp)	    # store saved register before using
	
	li s0, RPTC_CNTR    # load the value of RPTC_CNTR -> s0 = 0x80001200
	li s1, En_REG	    # load the value of En_REG -> s1 = 0x80001038
	
	########### configure 7-Segment Display ###########
	li t0, 0x0	    # set enable for all digits of 7-Segment Display
	sw t0, 0(s1)	    # enable the corresponding digits on display
	
	########### Initialize 7-Segment Display ###########
	li t0, 0x0	    # set enable for all digits of 7-Segment Display
	sw t0, 4(s1)	    # write the corresponding value to display
	
	########### Initialize RPTC_LRC ###########
	li t0, 5000         # load the counter value for 1 second delay
	sw t0, 8(s0)	    # Initialize RPTC_LRC to the count value
	
	########### reset the counter ###########
	li t0, 0x80	    # set reset for RPTC_CTRL register -> 0 1000 0000
	sw t0, 12(s0)	    # apply reset to RPTC_CTRL
	
	########### de-assert reset and enable count ###########
	li t0, 0x01	    # set enable for RPTC_CTRL register -> 0 0000 0001
	sw t0, 12(s0)	    # apply enable to RPTC_CTRL
	
	li t1, 0x0	    # initialize counter value for display
	
while:
	########### Poll the timer ###########
	lw t0, 0(s0)	    # get value from RPTC_CNTR
	bnez t0, while	    # if timer has not reached zero, continue polling
	
	########### Update the display ###########
	sw t1, 4(s1)	    # write counter value to 7 segment display register
	addi t1, t1, 1	    # increment counter value
	
	########### Reset the timer ###########
	li t0, 0x80	    # set reset for RPTC_CTRL register -> 0 1000 0000
	sw t0, 12(s0)	    # apply reset to RPTC_CTRL
	li t0, 0x01	    # set enable for RPTC_CTRL register -> 0 0000 0001
	sw t0, 12(s0)	    # apply enable to RPTC_CTRL
	
	j while
	
end:
	################ EPILOGUE ################ 
	lw ra, 0(sp)	    # restore return address on stack
	lw s0, 4(sp)	    # restore saved from stack
	lw s1, 8(sp)	    # restore saved from stack
	addi sp, sp, 12	    # de-allocate space on stack
	jr ra

