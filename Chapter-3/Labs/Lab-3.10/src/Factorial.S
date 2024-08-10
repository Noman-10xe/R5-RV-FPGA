// Author: Noman Rafiq
// Dated: Aug 10, 2024
// Description: This program computes Factorial of a non-negative number using iterative multiplications in RISC-V Assembly.

.globl main

.data
A: .word 7	# variable A = 7

.bss
Factorial: .space 4

.text
main:
	addi sp, sp, -8 	# allocate stack
	sw s0, 0(sp)		# save preserved register before using
 	sw s1, 4(sp)		# save preserved register before using
	la s0, A		# loads the base address of A in s0
	la s1, Factorial	# loads the base address of Factorial in s1
	lw t0, 0(s0)		# load value of A
	li t1, 1		# set factorial equal to 1 -> t1 = 1
	
fact:
	mul t1, t1, t0		# factorial = factorial * n
	addi t0, t0, -1		# decrement n = n -1
	bne t0, zero, fact	# keep multiplying while n != 0
	j end	
end:
	sw t1, 0(s1)		# store result in memory
	add x0, x0, x0
	lw s0, 0(sp)		# restore s0 before returning
	lw s1, 4(sp)		# restore s1 before returning
	addi sp, sp, 8		# de-allocate stack
