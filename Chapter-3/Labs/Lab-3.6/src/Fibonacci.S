// Author: Noman Rafiq
// Dated: Aug 10, 2024
// Description: This program Finds the first 12 numbers in Fiboannaci Series.

.globl main

.equ N, 12 	# Define Constant N = 12

.bss
V: .space 4*N	# Define a vector with N elements of size 4 Bytes

.text
main: 
	li t0, 0		# load fibim1 in t0 -> t0 = 0
	li t1, 1		# load fibim1 in t1 -> t1 = 1
	
	li t2, 12		# Set loop count to 12
	add t3, zero, zero	# initialize variable t3 = i = 0
	
	addi sp, sp, -4		# allocate stack
	sw s0, 0(sp)		# save preserved register before using
	la s0, V		# load base address of Vector in s0
	
fib:
	beq t3, t2, end		# check if i == 12; if true, exits loop
	slli t5, t3, 2		# calculate offset i * 4
	add t6, s0, t5		# add the offset to base address in s0 and save in t6
	
	sw t0, 0(t6)		# stores the first element in Fib(i) series
	sw t1, 4(t6)		# stores the 2nd element in Fib(i) series
	
	add t4, t0, t1		# calculates next element in series i.e. V(i+1)
	
	add t0, t1, zero	# update the elements for the next iteration
	add t1, t4, zero	# update the elements
	
	addi t3, t3, 1		# increment i = i + 1
	j fib

end:
	add x0, x0, x0
	lw s0, 0(sp)		# restore s0 before returning
	addi sp, sp, 4		# de-allocate stack
	ret
