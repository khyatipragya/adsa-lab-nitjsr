#include <stdio.h>

int n;                    // Number of items
int maxWeight;            // Maximum capacity of knapsack
int weights[20];          // Weights of items
int values[20];           // Values of items
int maxValue = 0;         // Stores maximum profit found
int currWeight = 0;       // Current total weight
int currValue = 0;        // Current total value

// Backtracking function
void knapsack(int i) {
    // Base case: all items considered
    if (i == n) {
        if (currValue > maxValue)
            maxValue = currValue;
        return;
    }

    // Include current item if it doesn't exceed capacity
    if (currWeight + weights[i] <= maxWeight) {
        currWeight += weights[i];
        currValue += values[i];

        knapsack(i + 1);  // Move to next item

        // Backtrack
        currWeight -= weights[i];
        currValue -= values[i];
    }

    // Exclude current item
    knapsack(i + 1);
}

int main() {
    printf("Enter number of items: ");
    scanf("%d", &n);

    printf("Enter weights of items: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &weights[i]);

    printf("Enter values of items: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &values[i]);

    printf("Enter maximum capacity of knapsack: ");
    scanf("%d", &maxWeight);

    knapsack(0);

    printf("\nMaximum value that can be obtained = %d\n", maxValue);

    return 0;
}
