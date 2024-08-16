#include<header.h>

int main() {
    char string[100];
    int decimals[5];

    printf("Enter a String in the format: SDDDD SDDDD SDDDD SDDDD SDDDD\n");
    fgets(string, sizeof(string), stdin);

    sscanf(string, "%d %d %d %d %d", &decimals[0], &decimals[1], &decimals[2], &decimals[3], &decimals[4]);

    // Call the assembly function and get the packed value
    int packed_value = binary_packed(decimals);

    printf("Packed Value: 0x%X\n", packed_value);

    return 0;
}

