// Author: Noman Rafiq
// Dated: Aug 28, 2024
// Description: The program reads a string containing 5 signed 4-digit decimal numbers separated by spaces. It then packs the least significant bits (LSB) of each number into a single 32-bit value. The resulting value is printed as a hexadecimal value.

#include <header.h>

int main() {
    // array of test cases, each containing a space-separated string of numbers
    char test_cases[][100] = {
    	"-0001 -0001 -0001 -0001 -0001\n",
        "+0001 +0001 -0001 -0001 -0001\n",
        "+0003 -0002 +0025 +0030 +1000\n",
        "+9999 +9999 +9999 +9999 +9999\n"
    };

    // iterate through each test case
    for (int i = 0; i < sizeof(test_cases) / sizeof(test_cases[0]); ++i) {
        // array to store decimal values
        int decimals[5];
        
        // break the test case string using space as a delimiter
        char *token = strtok(test_cases[i], " ");
        for (int j = 0; j < 5; ++j) {
            // convert each string to an integer and store it in the decimals array
            decimals[j] = atoi(token);
            token = strtok(NULL, " ");
        }
        
        // calculate a packed value using the binary_packed function
        int packed_value = binary_packed(decimals);
        
        // UART
        uartInit();
        
        // Print the result
        printfNexys("Test Case %d: Packed Value: 0x%X\n", i + 1, packed_value);
    }

    return 0;
}
