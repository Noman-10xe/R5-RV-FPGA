// Author: Noman Rafiq
// Dated: Aug 10, 2024
// Description: This program uses a Vector A to generate a vector B, such that B only contains those elements of A that are even numbers greater than 0. The program also counts the number of elements in B.

.globl main

.equ N, 12 	# Define Constant N = 12

.data
A: .word 13,-2,3,98732,323,1221,482,18273,94,1000,179,10	# define Vector A with 12 Elements


.bss
B: .space 4*N	# Define a vector with N elements of size 4 Bytes each.

.text
main: 
	li t0, 0		# sets the i = 0 in t0
	add t1, zero, N 	# sets loop count = N
	addi a0, a0, 0		# set a0 = 0
	
	addi sp, sp, -8		# allocate stack
	sw s0, 0(sp)		# save preserved register before using
	sw s1, 4(sp)		# save preserved register before using
	la s0, A		# loads the base address of A in s0
	la s1, B		# loads the base address of B in s1
	
loop:
	beq t0, t1, end		# check if loop count has reached 12
	slli t2, t0, 2		# calculate offset i * 4
	add t3, s0, t2		# add the offset to base address in s0 and save in t3
	
	lw t4, 0(t3)		# loads the ith element from Vector A
	
	blt t4, zero, negative_number	# discard negative numbers
	
	andi t5, t4, 1		# take bitwise and to check for even
	
	beq t5, zero, even	# check if the lsb == 0, if it is, then even
	
	addi t0, t0, 1		# increment i = i + 1
	j loop			# if odd, move to the next element
		
even:
	slli t5, a0, 2		# calculate offset i * 4
	add t5, s1, t5		#  add the offset to base address
	sw t4, 0(t5)		# store t4 to B[i]
	addi a0, a0, 1		# increment a0 to count the number of elements
	addi t0, t0, 1		# increment i = i + 1
	j loop
	
negative_number:
	addi t0, t0, 1		# increment i = i + 1
	j loop			# jump back to loop to check the next element in A
	
end:
	add x0, x0, x0
	lw s0, 0(sp)		# restore s0 before returning
	lw s1, 4(sp)		# restore s1 before returning
	addi sp, sp, 8		# de-allocate stack
