#include <stdio.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int left, int right, int bit) {
    int i = left, j = right;
    while (i <= j) {
        while (i <= j && ((arr[i] >> bit) & 1) == 0)
            i++;
        while (i <= j && ((arr[j] >> bit) & 1) == 1)
            j--;
        if (i < j) {
            swap(&arr[i], &arr[j]);
            i++;
            j--;
        }
    }
    return i;
}
void radixExchangeSort(int arr[], int left, int right, int bit) {
    if (left >= right || bit < 0)
        return;
    int mid = partition(arr, left, right, bit);
    radixExchangeSort(arr, left, mid - 1, bit - 1);
    radixExchangeSort(arr, mid, right, bit - 1);
}
int highestBit(int x) {
    int bit = 0;
    while (x >> bit)
        bit++;
    return bit - 1;
}
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main() {
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Original array:\n");
    printArray(arr, n);
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    int bit = highestBit(max);
    radixExchangeSort(arr, 0, n - 1, bit);
    printf("Sorted array:\n");
    printArray(arr, n);
    return 0;
}
