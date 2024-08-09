// Author: Noman Rafiq
// Dated: Aug 9, 2024
// Description: Adds two 4-bit values encoded in the 4 most significant and 4 least significant switches. The sum is displayed on the least significant 4 LEDs (LED[3:0]). The carryout is displayed in the next most significant LED (LED[4]).

// memory-mapped I/O addresses
# GPIO_SWs   = 0x80001400
# GPIO_LEDs  = 0x80001404
# GPIO_INOUT = 0x80001408

.globl main
main: 
	li t0, 0x80001400	# load the address for GPIO_SWs
	li t1, 0xFFFF		# Set enable for GPIO_INOUT
	
	sw t1, 8(t0) 		# Sets GPIO_INOUT for I/Os
	addi sp, sp, -4		# decrement stack
	sw s0, 0(sp)
	li t6, 0x000F		# Mask for LSBs
	li s0, 0xF000		# Mask for MSBs
loop:
	lw t2, 0(t0)		# Get Switch Values
	srli t2, t2, 16		# shift switch values 16-bits to the right
	
	and t3, t2, t6		# Extract LSBs
	and t4, t2, s0		# Extract MSBs
	srli t4, t4, 12		# Shift MSbs to the right to get the MSBs in appropriate position
	
	add t5, t3, t4		# Add MSBs + LSBs
	sw t5, 4(t0)		# Store the result back to LEDs to display the result
	j loop			# repeat loop	

exit:
	lw s0, 0(sp)
	addi sp, sp, 4
