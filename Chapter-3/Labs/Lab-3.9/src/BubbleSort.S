// Author: Noman Rafiq
// Dated: Aug 10, 2024
// Description: This program implements the BubbleSort Algorithm in RISC-V Assembly. This Algo sorts the components of a vector in ascending order.

.globl main

.equ N, 12 	# Define Constant N = 12

.data
A: .word 13, -2, 3, 982, 33, 121, 482, 73, 94, 101, 19, 10	# define Vector A with 12 Elements

.text
main: 
	li t0, 0		# sets the i = 0 in t0
	add t1, zero, N 	# sets loop count = N
	
	addi sp, sp, -8 	# allocate stack
	sw s0, 0(sp)		# save preserved register before using
	sw s1, 4(sp)		# save preserved register before using
	
	la s0, A		# loads the base address of A in s0
	
OuterLoop:
	li t0, 0		# i = 0 for each outer loop iteration
	addi t1, t1, -1		# Go to the end of array
	
	beqz t1, end		# check if t1 == 0, array is sorted, exit outer loop
	
InnerLoop:
	
	################## Get A[i] ################## 
	slli t2, t0, 2		# calculate offset i * 4
	add t3, s0, t2		# add the offset to base address in s0 and save in t3
	lw t4, 0(t3)		# loads the ith element from Vector A
	
	################## Get A[i+1] ##################
	lw t5, 4(t3)		# loads the [i+1]th element from Vector A
	
	############# Compare t4 & t5 #############
	blt t5, t4, BubbleSort	# check if A[i+1] < A[i]
	addi t0, t0, 1		# increment i = i + 1
	blt t0, t1, InnerLoop	# continue the pass if i < t1
	j OuterLoop		# move to the next pass
	
BubbleSort:
	sw t4, 4(t3)		# store t4 at index = i + 1  
	sw t5, 0(t3)		# store t5 at index = i
	addi t0, t0, 1		# increment i = i + 1
	blt t0, t1, InnerLoop   # continue the pass if i < t1
	j OuterLoop		# move to the next pass
	
end:
	add x0, x0, x0
	lw s0, 0(sp)		# restore s0 before returning
	lw s1, 4(sp)		# restore s0 before returning
	addi sp, sp, 8		# de-allocate stack
