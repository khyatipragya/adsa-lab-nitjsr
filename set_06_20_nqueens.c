#include <stdio.h>
#include <stdbool.h>

#define MAX 20  // Maximum board size

int board[MAX];
int n;

// Function to print the board
void printSolution() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i] == j)
                printf("Q ");
            else
                printf(". ");
        }
        printf("\n");
    }
    printf("\n");
}

// Function to check if a queen can be placed at row and column
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i++) {
        // Check column and diagonals
        if (board[i] == col || 
            board[i] - i == col - row || 
            board[i] + i == col + row)
            return false;
    }
    return true;
}

// Recursive function to solve N-Queens using backtracking
void solveNQueens(int row) {
    if (row == n) {
        printSolution();
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isSafe(row, col)) {
            board[row] = col;      // Place queen
            solveNQueens(row + 1); // Recurse for next row
        }
    }
}

int main() {
    printf("Enter the number of queens: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of queens. Please use a value between 1 and %d.\n", MAX);
        return 1;
    }

    printf("\nAll possible solutions:\n\n");
    solveNQueens(0);

    return 0;
}
