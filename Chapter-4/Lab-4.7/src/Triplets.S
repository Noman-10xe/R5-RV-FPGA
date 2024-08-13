// Author: Noman Rafiq
// Date: Aug 13, 2024
// Description: The program generates a vector "B" of "N" elements from a vector "A" of "3*N" elements, where each element of "B" is the 
// absolute value of the sum of a triplet of consecutive elements from "A". Specifically, for each "i", "B[i]" is computed as "|A[3*i] + A[3*i + 1] + A[3*i + 2]|"

.globl main

.equ N, 4

.data
A: .word 2, -3, 4, 0, 6, 6, 3, -12, 3, -9, -16, 7

.bss
B: .space 4*N

.text

res_triplet:
	################### Callee Saved ###################
	addi sp, sp, -4
	sw ra, 0(sp)
	
	li t0, 0	# set i = 0 in t0
	li t3, 0 	# set sum = 0 in t3
	li t4, 3	# set count to 3 in t4
for1:	
	bge t0, t4, return
	add t5, a1, t0	# calculate index -> j + i
	slli t5, t5, 2	# index * 4 (for words)
	add t6, a0, t5 # adds the offset to base address
	lw t5, 0(t6)	# get A[i+j] in t5
	
	add t3, t3, t5  # sum = sum + A[i+j]
	
	addi t0, t0, 1	# increment i = i + 1
	j for1

return:
	mv a0, t3	# set the argument for the next function call
	jal abs		# Absolute function call
	
	##### returned a0 = sum = abs(sum) #########
	lw ra, 0(sp)	# restore return address
	addi sp, sp, 4	# de-allocate stack
	jr ra

abs:
	bge a0, zero, positive # return as is, if positive
	xori a0, a0, -1
	addi a0, a0, 1
positive:
	jr ra



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

for:	
	bge t0, t2, exit
	mv a0, s0		# set arguments for function call -> A
	mv a1, t1		# set arguments for function call -> j
	
	##### Caller Saved Convention #####
	addi sp, sp, -4
	sw t0, 0(sp)		# store t0 = i on the stack
	
	jal res_triplet		# function call
	
	lw t0, 0(sp)		# restore i from the stack
	addi sp, sp, 4		# de-allocate stack
	slli t4, t0, 2		# calculate-offset (i * 4)
	add t5, s1, t4		# add the offset to base address
	
	sw a0, 0(t5)		# store the returned sum to B[i]
	
	addi t0, t0, 1		# increment i = i + 1
	addi t1, t1, 3		# increment j = j + 3
	
	j for

exit:
	addi zero, zero, 0
	################### Epilogue ###################
	lw s0, 0(sp)		# restore preserved register from stack
	lw s1, 4(sp)		# restore preserved register from stack
	lw ra, 8(sp)		# restore preserved register from stack
	addi sp, sp, 12	# de-allocate space on stack
	jr ra
