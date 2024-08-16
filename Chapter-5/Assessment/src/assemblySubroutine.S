

.global binary_packed

.text

binary_packed:
    # Load the address of the decimals array into a register
    lw t0, 0(a0)    		# Load 1st number into t0
    lw t1, 4(a0)    		# Load 2nd number into t1
    lw t2, 8(a0)    		# Load 3rd number into t2
    lw t3, 12(a0)   		# Load 4th number into t3
    lw t4, 16(a0)   		# Load 5th number into t4

    # Extract LSBs and pack them
    andi t0, t0, 0x7           # Extract 3 LSBs from 1st number (0x7 = 000...0111)
    
    slli t1, t1, 3             # Shift 2nd number left by 3 bits
    andi t1, t1, 0x7F8         # Extract 8 LSBs from 2nd number (0x7F8 = 000...1111111000)
    or t0, t0, t1              # Combine with 1st number

    slli t2, t2, 11            # Shift 3rd number left by 11 bits
    li t5, 0xF800 
    and t2, t2, t5             # Extract 5 LSBs from 3rd number (0xF800 = 000...111110000000000)
    or t0, t0, t2              # Combine with previous result

    slli t3, t3, 16            # Shift 4th number left by 16 bits
    li t5, 0x1F0000
    and t3, t3, t5	       # Extract 5 LSBs from 4th number (0x1F0000 = 000...11111000000000000000)
    or t0, t0, t3              # Combine with previous result

    slli t4, t4, 21            # Shift 5th number left by 21 bits
    li t5, 0xFFE00000
    and t4, t4, t5             # Extract 11 LSBs from 5th number (0xFFE00000 = 11111111111000000000000000000000)
    or t0, t0, t4              # Combine with previous result

    # Return the packed value
    mv a0, t0
    jr ra
