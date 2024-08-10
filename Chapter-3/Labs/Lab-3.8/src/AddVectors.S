// Author: Noman Rafiq
// Dated: Aug 10, 2024
// Description: This program sums two Vectors A, B, and strores the result in another vector C such that C[i] = A[i] + B[N - i - 1].

.globl main

.equ N, 12 	# Define Constant N = 12

.data
A: .word 13, -2, 3, 982, 33, 121, 482, 73, 94, 101, 19, 10	# define Vector A with 12 Elements
B: .word 42, -17, 56, 79, 24, 57, 80, 14, 58, -90, 112, 314	# define Vector B with 12 Elements

.bss
C: .space 4*N	# Define a vector with N elements of size 4 Bytes each.

.text
main: 
	li t0, 0		# sets the i = 0 in t0
	add t1, zero, N 	# sets loop count = N
	
	addi sp, sp, -12	# allocate stack
	sw s0, 0(sp)		# save preserved register before using
	sw s1, 4(sp)		# save preserved register before using
	sw s2, 8(sp)		# save preserved register before using
	
	la s0, A		# loads the base address of A in s0
	la s1, B		# loads the base address of B in s1
	la s2, C		# loads the base address of C in s2

Sum:
	beq t0, t1, end		# check if loop count has reached 12
	
	################## VECTOR A ################## 
	slli t2, t0, 2		# calculate offset i * 4
	add t3, s0, t2		# add the offset to base address in s0 and save in t3
	lw t4, 0(t3)		# loads the ith element from Vector A
	
	################## VECTOR B ##################
	sub t5, t1, t0		# t5 = N - i
	addi t5, t5, -1		# t5 = t5 - 1 -> N-i-1
	slli t2, t5, 2		# calculate offset i * 4
	add t3, s1, t2		# add the offset to base address in s1 and save in t3
	lw t5, 0(t3)		# loads the [N-i-1]th element from Vector B
	
	############# Intermediate Result #############
	add t6, t4, t5		# add the A[i] + B[N-i-1] and saved the result in t6
	
	################## VECTOR C ##################
	slli t2, t0, 2		# calculate offset i * 4
	add t3, s2, t2		# add the offset to base address in s2 and save in t3
	sw t6, 0(t3)		# Store the result at C[i]
	
	addi t0, t0, 1		# increment i = i + 1
	j Sum			# move to the next element
	
end:
	add x0, x0, x0
	lw s0, 0(sp)		# restore s0 before returning
	lw s1, 4(sp)		# restore s1 before returning
	lw s2, 8(sp)		# restore s1 before returning
	addi sp, sp, 12		# de-allocate stack
