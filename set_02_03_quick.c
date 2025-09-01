#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Function to find the partition position
// This implementation uses the last element as the pivot
int partition(int array[], int low, int high) {
    int pivot = array[high]; // Select the rightmost element as pivot
    int i = (low - 1); // Pointer for greater element

    // Traverse each element of the array and compare them with the pivot
    for (int j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++; // Increment pointer for greater element
            swap(&array[i], &array[j]); // Swap element at i with element at j
        }
    }
    // Swap the pivot element with the greater element at i+1
    swap(&array[i + 1], &array[high]);
    return (i + 1); // Return the partition point
}

// Main QuickSort function
void quickSort(int array[], int low, int high) {
    if (low < high) {
        // Find the pivot element such that:
        // elements smaller than pivot are on its left
        // elements greater than pivot are on its right
        int pi = partition(array, low, high);

        // Recursive call on the left of pivot
        quickSort(array, low, pi - 1);

        // Recursive call on the right of pivot
        quickSort(array, pi + 1, high);
    }
}

// Function to print the array elements
void printArray(int array[], int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Main function to test Quick Sort
int main() {
    int data[] = {8, 7, 2, 1, 0, 9, 6};
    int n = sizeof(data) / sizeof(data[0]);

    printf("Unsorted Array:\n");
    printArray(data, n);

    quickSort(data, 0, n - 1);

    printf("Sorted array in ascending order:\n");
    printArray(data, n);

    return 0;
}
