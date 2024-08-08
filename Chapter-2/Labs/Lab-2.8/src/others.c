#include <header.h>  // Include the custom header file

// Function Definition
void Sum(int *A, int *B, int *C) {
    for (int i = 0; i < N; i++) {  
    
    	// Loop through each element from 0 to N-1
    
    	C[i] = A[i] + B[N-i-1];  // Sum the ith element of A with the (N-i-1)th element of B and store the result in C[i]
    }
}

