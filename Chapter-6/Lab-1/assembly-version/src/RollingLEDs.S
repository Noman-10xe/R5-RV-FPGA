# Author: Noman Rafiq
# Dated: Aug 17, 2024

.globl main

.equ GPIO_sw, 0x80001400         # Define physical address for GPIO switches
.equ DELAY, 0x1                  # Define delay constant


.text
main:
    ###################### PROLOGUE ######################
    addi sp, sp, -12         # Allocate stack space for ra and s0
    sw ra, 0(sp)	    # save the return address on stack
    sw s0, 4(sp)	    # save the preserved register before using
    sw s1, 8(sp)	    # save the preserved register before using

    li s0, GPIO_sw          # Load GPIO_sw address into s0 = 0x80001400 
    li t0, 0xFFFF           # Load En_Value = 0xFFFF into t0
    sw t0, 8(t1)            # WRITE_GPIO(GPIO_INOUT, En_Value)

    li t0, 0xF              # Load initial value = 0xF into t0
    sw t0, 4(s0)            # WRITE_GPIO(GPIO_led, value)
    
while:
    lw t1, 0(s0)	    # switches value in t1 = READ_GPIO(GPIO_sw)
    srli t1, t1, 16	    # switches_value = switches_value >> 16  
    
    li t2, 0x2		    # load 0x2 in t2
    and t2, t1, t2	    # take (switches_values & 0x2)
    li s1, 0x2		    # load 0x2 in s1

if_button2: 
    beq t2, s1, shift_right  # if t2 == s1, then shift to the right

################# Left Direction #################    
else_shift_left:
    li t3, 0x8000          # load 0x8000 in t3
    and t3, t0, t3	   # t3 = msb = value & 0x8000
    srli t3, t3, 15	   # t3 = t3 >> 15
    slli t0, t0, 1	   # value = value << 1
    or t0, t0, t3         # value = (value << 1) | (msb >> 15)
    
    li t2, 0x1		    # load 0x1 in t2
    and t2, t1, t2	    # take (switches_values & 0x1)
    li s1, 0x1		    # load 0x1 in s1
    
if_button1:
    beq t2, s1, faster      # if t2 == s1, then move faster

else_slower:
    li a0, 1000
    
    ########## caller saved rule ##########
    addi sp, sp, -12	    # allocate space on stack
    sw t0, 0(sp)	    # save t0 on stack
    sw t1, 4(sp)	    # save t0 on stack
    sw t2, 8(sp)	    # save t0 on stack
     
    jal delay		    # fucntion call delay(200)
    
    lw t0, 0(sp)	    # restore t0 from stack
    lw t1, 4(sp)	    # restore t1 from stack
    lw t2, 8(sp)	    # restore t2 from stack
    addi sp, sp, -12	    # de-allocate space on stack
    
    sw t0, 4(s0)	    # WRITE_GPIO(GPIO_led, value)
    j while
    
faster:
    li a0, 200
    
    ########## caller saved rule ##########
    addi sp, sp, -12	    # allocate space on stack
    sw t0, 0(sp)	    # save t0 on stack
    sw t1, 4(sp)	    # save t0 on stack
    sw t2, 8(sp)	    # save t0 on stack
     
    jal delay		    # fucntion call delay(200)
    
    lw t0, 0(sp)	    # restore t0 from stack
    lw t1, 4(sp)	    # restore t1 from stack
    lw t2, 8(sp)	    # restore t2 from stack
    addi sp, sp, -12	    # de-allocate space on stack
    
    sw t0, 4(s0)	    # WRITE_GPIO(GPIO_led, value)
    j while 
    
    
################# Right DIrection #################
    
shift_right:
    li t3, 0x1		   # load 0x1 in t3
    and t3, t0, t3	   # t3 = lsb = value & 0x1
    slli t3, t3, 15	   # t3 = t3 << 15
    srli t0, t0, 1	   # value = value >> 1
    or t0, t0, t3         # value = (value >> 1) | (lsb << 15)
    
    li t2, 0x1		    # load 0x1 in t2
    and t2, t1, t2	    # take (switches_values & 0x2)
    li s1, 0x1		    # load 0x1 in s1
    
    j if_button1


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
