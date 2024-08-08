 #include<header.h>


//Function Definition
unsigned long long Factorial(int n) {
    unsigned long long result = 1;
    
    for (int i = 1; i <= n; ++i) {
        result *= i;
    
    }
    return result;
}
