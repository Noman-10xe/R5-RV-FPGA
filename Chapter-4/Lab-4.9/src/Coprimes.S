// Author: Noman Rafiq
// Date: Aug 13, 2024
// Description: The program Coprimes.S in RISC-V assembly checks pairs of integers in an array D to determine if they are coprime. 
// For each pair (xi, yi) in the array, the program calculates the greatest common divisor (GCD) using the 'gcd' function. 
// If the GCD is 1, indicating the numbers are coprime, it sets the corresponding 'ci' value to 2; otherwise, it sets 'ci' to 1. 
// The array 'D' is updated in-place with these results.

.globl main

.equ N, 6

.data
D: .word 3,5,0, 6,18,0, 15,45,0, 13,10,0, 24,3,0, 24,35,0

.text

gcd:
	addi sp, sp, -4		# allocate stack space
	sw ra, 0(sp)		# store ra
	
	addi t1, a1, 0		# t1 now holds b
	rem a1, a0, a1 		# Get remainder -> b = a % b
	add a0, t1, zero	# a0 gets a1
	
	bne a0, zero, check_a1
	addi a0, a1, 0 		# a0 == 0, then GCD is a1
	
	lw ra, 0(sp)		# restore ra
	addi sp, sp, 4		# de-allocate stack space
	jr ra

check_a1:
	bne a1, zero, gcd
	addi a0, a0, 0 		# a1 == 0, then GCD is a0
	lw ra, 0(sp)		# restore ra
	addi sp, sp, 4		# de-allocate stack space
	jr ra


check_coprime:
	################ Callee Saved Rule ################
	addi sp, sp, -4		# allocate stack space
	sw ra, 0(sp)		# saved return address
	
	li t5, 3		# load value 3 in t5
	mul t0, t0, t5	 	# get index [3*pos]
	slli t0, t0, 2		# calculate offset for that index -> (3*pos)*4
	add t0, s0, t0		# add the offset to base address -> (D + ((3*pos)*4))
	
	lw a0, 0(t0)		# Get A[3*pos] 
	lw a1, 4(t0)		# Get A[3*pos + 1]
	
	jal gcd			# call function -> gcd
	
	li t4, 1		# load 1 in t4 for comparison
	
if:
	bne a0, t4, else	# if gcd != 1, go to else
	li t5, 2		# load value 2 in t5
	sw t5, 8(t0)		# store t5 at index = A[(3*pos) + 2]
	
	lw ra, 0(sp)		# restore ra from the stack
	addi sp, sp, 4		# de-allocate stack
	jr ra

else:
	li t5, 1		# load value 1 in t5
	sw t5, 8(t0)		# store t5 at index = A[(3*pos) + 2]
	lw ra, 0(sp)		# restore ra from the stack
	addi sp, sp, 4		# de-allocate stack
	jr ra
	


main:
	################### PROLOGUE ###################
	addi sp, sp, -8 	# allocate space on stack
	sw s0, 0(sp)		# save preserved register before using
	sw ra, 4(sp)		# save preserved register before using
	la s0, D		# load address of D into s0

	li t0, 0		# set i, t0 = 0
	add t2, zero, N		# load N into t2
	
for:	
	bge t0, t2, exit	# exits loop after N iterations
	
	addi a0, s0, 0		# set a0 = D for function call
	addi a1, t0, 0		# set a1 = i for function call
	
	############ Caller Saved Convention ############
	addi sp, sp, -4		# allocate space on stack
	sw t0, 0(sp)		# store i on the stack
	
	jal check_coprime	# function call. check_coprime(D,i)
	
	# mv s1, t0		# save t0 to s1, i.e. Address where 
	
	
	lw t0, 0(sp)		# restore i from stack
	addi sp, sp, 4		# de-allocate stack
	
	addi t0, t0, 1		# increment i = i + 1
	j for
	
exit:
	addi zero, zero, 0
	################### Epilogue ###################
	lw s0, 0(sp)		# restore preserved register from stack
	lw ra, 4(sp)		# restore preserved register from stack
	addi sp, sp, 8		# de-allocate space on stack
	jr ra
