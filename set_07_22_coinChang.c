#include <stdio.h>
void coinChange(int coins[], int n, int amount) {
    int count[10] = {0}; 
    int i;
    printf("Coins used to make amount %d:\n", amount);
    for (i = 0; i < n; i++) {
        if (amount >= coins[i]) {
            count[i] = amount / coins[i];
            amount = amount % coins[i];
        }
    }

    for (i = 0; i < n; i++) {
        if (count[i] != 0)
            printf("%d coin(s) of denomination %d\n", count[i], coins[i]);
    }

    if (amount != 0)
        printf("Remaining amount that cannot be changed: %d\n", amount);
}

int main() {
    int coins[10];
    int n, amount, i;

    printf("Enter the number of coin denominations: ");
    scanf("%d", &n);

    printf("Enter the coin denominations (in descending order): ");
    for (i = 0; i < n; i++)
        scanf("%d", &coins[i]);

    printf("Enter the amount to make change for: ");
    scanf("%d", &amount);

    coinChange(coins, n, amount);

    return 0;
}
