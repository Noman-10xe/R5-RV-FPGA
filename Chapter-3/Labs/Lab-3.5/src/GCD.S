// Author: Noman Rafiq
// Dated: Aug 10, 2024
// Description: This program used the Euclidean Algorithm to find the Greatest Common Divisor (GCD) of 2 integers.

.globl main

.data
a: .word 57	# a = 57
b: .word 81	# b = 81

.bss
GCD: .space 4

.text
main: 
	la t0, a		# load the address of variable a
	lw a0, 0(t0)		# load value into register t0 = 57
	
	la t1, b		# load the address of variable b
	lw a1, 0(t1)		# load value into register t1 = 81
	
	jal gcd
	la t2, GCD
	sw a0, 0(t2)		# store word to memory
	j exit

gcd:
	addi t1, a1, 0		# t1 now holds b
	rem a1, a0, a1 		# Get remainder -> b = a % b
	add a0, t1, zero	# a0 gets a1
	
	bne a0, zero, check_a1
	addi a0, a1, 0 		# a0 == 0, then GCD is a1
	jr ra		

check_a1:
	bne a1, zero, gcd
	addi a0, a0, 0 		# a1 == 0, then GCD is a0
	jr ra

exit:
	
