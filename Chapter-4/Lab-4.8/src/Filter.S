// Author: Noman Rafiq
// Date: Aug 13, 2024
// Description: The program in Filter.S processes an array of integers A using a filter function myFilter. It iterates through the array, 
// and for each pair of consecutive elements, if the first element is a multiple of 16 and the second is greater than the first, their sum plus 2
// is stored in another array B. The program uses RISC-V assembly to implement this logic, including memory management and function calls.

.globl main

.equ N, 6

.data
A: .word 48,64,56,80,96,48

.bss
B: .space 4*N

.text
main:
	################### PROLOGUE ###################
	addi sp, sp, -12	# allocate space on stack
	sw s0, 0(sp)		# save preserved register before using
	sw s1, 4(sp)		# save preserved register before using
	sw ra, 8(sp)		# save preserved register before using
	la s0, A		# load address of A into s0
	la s1, B		# load address of B into s1

	li t0, 0		# set i, t0 = 0
	li t1, 0		# set j, t1 = 0
	add t2, zero, N		# load N into t2
	addi t2, t2, -1		# t2 = N -1

for:	
	bge t0, t2, exit	# exits loop after (N - 1)-1 iterations
	
	slli t3, t0, 2		# calculate offset -> i * 4
	add t3, t3, s0		# add offset to base address -> (A + i)
	
	lw a0, 0(t3)		# Get A[i] -> *(A+i)
	lw a1, 4(t3)		# Get A[i+1] -> *(A+i+1)
	
	jal myFilter		# function call
	
if:
	beq a0, zero, else 	# check if return value is == 1, if not, go to else
	
	lw t5, 0(t3)		# Get A[i] -> *(A+i)
	lw t6, 4(t3)		# Get A[i+1] -> *(A+i)
	add t5, t5, t6		# t5 = A[i+1] + A[i]
	addi t5, t5, 2		# t5 = A[i+1] + A[i] + 2
	
	slli t6, t1, 2		# Calculate offset -> j * 4
	add t6, t6, s1		# add the offset to base address of B in s1 -> (B + j)
	sw t5, 0(t6)		# store t5 to B[j]
	addi t1, t1, 1		# increment j = j + 1

else:
	addi t0, t0, 1		# increment i = i + 1
		
	j for

myFilter: 
	andi t4, a0, 0xF	# Perform bitwise and to find if any of the first 4 bits are on
	beq t4, zero, multiple_16	# if t4 == 0, i.e. a0 was multiple of 16
	
	li a0, 0		# return 0 if not multiple of 16
	jr ra
	
multiple_16:
	bge a1, a0, one		# if (multiple of 16) && (a1 > a0) -> return 1 
	li a0, 0		# else return 0
	jr ra
one:	
	li a0, 1		# return 1
	jr ra

exit:
	addi zero, zero, 0
	################### Epilogue ###################
	lw s0, 0(sp)		# restore preserved register from stack
	lw s1, 4(sp)		# restore preserved register from stack
	lw ra, 8(sp)		# restore preserved register from stack
	addi sp, sp, 12		# de-allocate space on stack
	jr ra
