# Author: Noman Rafiq
# Dated: Aug 17, 2024
# Description: This program reads the binary values from switches and displays the corresponding hex output on four of the eight digits of a seven-segment display.

# Seven - Segments Display Registers (memory map)
# En_REG    0x80001038
# DIGITS_REG   0x8000103C

# GPIO I/O Registers (memory map)
# GPIO_SWs      0x80001400
# GPIO_LEDs     0x80001404
# GPIO_INOUT    0x80001408



.globl main

.equ GPIO_SWs, 0x80001400        # Define physical address for GPIO switches
.equ En_REG, 0x80001038          # Define physical address for GPIO switches
.equ DELAY, 0x1                  # Define delay constant


.text

##################### delay function #####################

delay:
    ################# Callee Saved Rule ################
    addi sp, sp, -8         # Allocate stack space
    sw ra, 0(sp)            # Save return address
    sw s0, 4(sp)            # Save s0 before using

    mv s0, a0               # Move num (a0) to s0
    li t0, 0                # Initialize outer loop counter
    li t2, DELAY            # Load DELAY value into t2

delay_outer:
    bge t0, s0, delay_end_outer # If t0 >= num, end outer loop
    li t1, 0                # Initialize inner loop counter

delay_inner:
    bge t1, t2, delay_end_inner # If t1 >= DELAY, end inner loop
    addi t1, t1, 1          # Increment inner loop counter
    j delay_inner

delay_end_inner:
    addi t0, t0, 1          # Increment outer loop counter
    j delay_outer

delay_end_outer:
    lw ra, 0(sp)            # Restore return address
    lw s0, 4(sp)            # Restore saved register
    addi sp, sp, 8          # Deallocate stack space
    jr ra                   # Return from delay function


main:
	################ PROLOGUE ################ 
	addi sp, sp, -12    # allocate space on stack
	sw ra, 0(sp)	    # store return address on stack
	sw s0, 4(sp)	    # store saved register before using
	sw s1, 8(sp)	    # store saved register before using
	
	li s0, GPIO_SWs	    # load the value of GPIO_SWs -> s0 = 0x80001400
	li s1, En_REG	    # load the value of En_REG -> s1 = 0x80001038
	
	########### configure GPIO I/O ###########
	
	li t0, 0xFFFF	    # set enable for GPIO pins
	sw t0, 8(s0)	    # enable GPIO pins as I/O
	
	########### configure 7-Segment Display ###########

	li t0, 0xF0	    # set enable for lower four digits of 7-Segment Display
	sw t0, 0(s1)	    # enable the corresponding 4 digits on display

while:
	lw t0, 0(s0)	    # read switches value in t0
	srli t0, t0, 16	    # shift the switches_value to right -> switches_value >>= 16
	sw t0, 4(s1)	    # store the switches value to DIGITS_REG (4-bytes ahead of 0x80001038 i.e. 0x8000103C)
	
	li a0, 200	    # load 200 in a0 for calling delay function
	jal delay	    # function call
	
	j while
	
end: 
	################ EPILOGUE ################ 
	lw ra, 0(sp)	    # restore return address on stack
	lw s0, 4(sp)	    # restore saved from stack
	lw s1, 8(sp)	    # restore saved from stack
	addi sp, sp, 12	    # de-allocate space on stack
	jr ra
