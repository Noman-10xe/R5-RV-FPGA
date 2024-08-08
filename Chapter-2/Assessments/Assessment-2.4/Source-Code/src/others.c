 #include<header.h>


//Function Definition for checking Palindrome
bool palindrome(int n){
	bool flag;
	short int reversed = reverse(n);
	
	if (reversed == n){
		flag = true; // Palindrome
	}
	else{
		flag = false; // Not a Palindrome
	}
	
	return flag;
}

//Function Definition for reversing
short int reverse(int n){
	
	short int reversed = 0;
	for (int i = 0; i < 16; i++){
	
	reversed <<= 1; // Shift reversed left by 1 bit
	
	reversed |= (n & 1); // Copy the least significant bit of number to reversed
	
	n >>= 1; // Shift number right by 1 bit 
	
	}
	
	return reversed;
}
