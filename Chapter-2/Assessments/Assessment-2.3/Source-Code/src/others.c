 #include<header.h>


//Function Definition
short int reverse(short int n){
	
	short int reversed = 0;
	for (int i = 0; i < 16; i++){
	
	reversed <<= 1; // Shift reversed left by 1 bit
	
	reversed |= (n & 1); // Copy the least significant bit of number to reversed
	
	n >>= 1; // Shift number right by 1 bit 
	
	}
	
	return reversed;
}
