 #include<header.h>


//Function Definition
void BubbleSort(int *A) {
    int i, j, temp;
    // Outer loop for each pass
    for (i = 0; i < N - 1; i++) {
        // Inner loop for comparing adjacent elements
        for (j = 0; j < N - i - 1; j++) {
            
            // If the current element is greater than the next element, swap them
            if (A[j] > A[j + 1]) {
                temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
}
