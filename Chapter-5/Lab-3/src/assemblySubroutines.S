.globl ColourToGrey
.equ N, 128
.equ M, 128


.text

# ColourToGrey(RGB Colour[N][M], unsigned char Grey[N][M]);

# {
#    int i,j;
    
#    for (i=0;i<N;i++)
#        for (j=0; j<M; j++)
#            Grey[i][j] =  ColourToGrey_Pixel(Colour[i][j].R, Colour[i][j].G, Colour[i][j].B); 
# }

ColourToGrey:
	
	############### Prologue ###############
	addi sp, sp, -12	# allocate stack
	sw ra, 0(sp)		# store return address 
	sw s0, 4(sp)		# store saved registers before using
	sw s1, 8(sp)		# store saved registers before using
	
	
	li t0, 0		# set i = 0 in t0
	
	mv s0, a0		# move a0 to s0 = address of Colour matrix
	mv s1, a1		# move a1 to s1

	li t2, N		# t2 = N
	li t3, M		# t3 = M
	
	############ calculate offsets ############
for1:
	bge t0, t2, end		# for (i < N)
	li t1, 0 		# set j = 0 in t1
for2:
	bge t1, t3, end2	# for (j < M)
	mul t4, t0, t3		# t4 = (i*M)
	add t4, t4, t1		# t4 = (i*M + j)
	li t5, 3
	mul t4, t4, t5		# t4 = (i*M + j) * 3
	add t4, t4, s0		# add the offset to base address -> address of colour[i][j] = 3 Bytes Structs (contains R, G & B)

	lbu a0, 0(t4)         # a0 = Colour[i][j].R
    lbu a1, 1(t4)         # a1 = Colour[i][j].G
    lbu a2, 2(t4)         # a2 = Colour[i][j].B 
	
	jal ColourToGrey_Pixel
	
	mul t4, t0, t3		# t4 = (i*M)
	add t4, t4, t1		# t4 = (i*M + j)
	li t5, 1
	mul t4, t4, t5		# t4 = (i*M + j) * 1
	add t4, t4, s1		# add the offset to base address -> address of Grey[i][j]

	sb a0, 0(t4)		# store the returned value to Grey[i][j]

	addi t1, t1, 1		# increment j = j + 1
	j for2
	
end2:
	addi t0, t0, 1		# increment i = i + 1
	j for1

end:
	add zero, zero, zero
	############### Epilogue ###############
	lw ra, 0(sp)		# store return address 
	lw s0, 4(sp)		# store saved registers before using
	lw s1, 8(sp)		# store saved registers before using
	addi sp, sp, 12 	# de-allocate stack