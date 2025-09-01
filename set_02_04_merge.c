#include <stdio.h>
#include <stdlib.h>

// Structure to represent a stack frame
typedef struct {
    int low, high, mid;
    int stage; // 0 = divide, 1 = conquer (merge)
} Frame;

// Merge function
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];

    free(L);
    free(R);
}

// Iterative merge sort using stack
void mergeSortIterative(int arr[], int n) {
    // Allocate larger stack to avoid overflow
    Frame *stack = (Frame *)malloc(4 * n * sizeof(Frame));
    int top = -1;

    // push the whole array
    stack[++top] = (Frame){0, n - 1, 0, 0};

    while (top >= 0) {
        Frame cur = stack[top--];

        if (cur.low < cur.high) {
            if (cur.stage == 0) {
                // dividing step
                cur.mid = (cur.low + cur.high) / 2;

                // push conquer (merge) step
                stack[++top] = (Frame){cur.low, cur.high, cur.mid, 1};

                // push right subproblem
                stack[++top] = (Frame){cur.mid + 1, cur.high, 0, 0};

                // push left subproblem
                stack[++top] = (Frame){cur.low, cur.mid, 0, 0};
            } else {
                // merging step
                merge(arr, cur.low, cur.mid, cur.high);
            }
        }
    }

    free(stack);
}

// Utility to print array
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

// Driver program
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    mergeSortIterative(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
