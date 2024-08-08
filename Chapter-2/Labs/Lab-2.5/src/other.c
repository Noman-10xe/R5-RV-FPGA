int GCD(int *a, int *b) {
    if (*b == 0) { 
    	// Base case: if b is 0, return a
        return *a;
    }
     
    else if (*a == 0) { 
    	// Base case: if a is 0, return b
        return *b;
    }
    
    else {
        int temp = *b; // Store the value of b in a temporary variable
        *b = *a % *b; // Update b to be the remainder of a divided by b
        *a = temp; // Update a to be the original value of b
        return GCD(a, b); // Recursively call GCD with updated values of a and b
    }
}
