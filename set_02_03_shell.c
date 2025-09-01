#include <stdio.h>

void shellSort(int array[], int n) {
    // Start with a large gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort for this gap size
        // The first 'gap' elements a[0...gap-1] are already in gapped order
        // Keep adding one more element until the entire array is gap sorted
        for (int i = gap; i < n; i += 1) {
            // Store a[i] in temp and make a hole at position i
            int temp = array[i];

            // Shift earlier gap-sorted elements up until
            // the correct location for a[i] is found
            int j;
            for (j = i; j >= gap && array[j - gap] > temp; j -= gap) {
                array[j] = array[j - gap];
            }

            // Put temp (the original array[i]) in its correct location
            array[j] = temp;
        }
    }
}

// Function to print an array
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Driver code
int main() {
    int array[] = {12, 34, 54, 2, 3};
    int n = sizeof(array) / sizeof(array[0]);

    printf("Array before sorting: \n");
    printArray(array, n);

    shellSort(array, n);

    printf("Array after sorting: \n");
    printArray(array, n);

    return 0;
}
