#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define N 4   // For 4x4 puzzle (15-puzzle)

// Structure for a puzzle node
typedef struct Node {
    int mat[N][N];
    int x, y;             // Blank tile coordinates
    int cost;             // Heuristic cost (Manhattan distance)
    int level;            // Depth of the node in the search tree
    struct Node* parent;  // Pointer to parent node
} Node;

// Function to print a puzzle configuration
void printMatrix(int mat[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (mat[i][j] == 0)
                printf("   ");
            else
                printf("%2d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Directions for movement: up, down, left, right
int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};

// Function to check if (x, y) is within the board
int isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

// Function to allocate a new node
Node* newNode(int mat[N][N], int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = (Node*)malloc(sizeof(Node));

    // Copy data from parent matrix
    memcpy(node->mat, mat, sizeof(node->mat));

    // Swap the blank tile
    int temp = node->mat[x][y];
    node->mat[x][y] = node->mat[newX][newY];
    node->mat[newX][newY] = temp;

    node->x = newX;
    node->y = newY;
    node->level = level;
    node->parent = parent;

    return node;
}

// Function to calculate Manhattan distance heuristic
int calculateCost(int initial[N][N], int final[N][N]) {
    int cost = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            if (initial[i][j] && initial[i][j] != final[i][j])
                for (int x = 0; x < N; x++)
                    for (int y = 0; y < N; y++)
                        if (initial[i][j] == final[x][y])
                            cost += abs(i - x) + abs(j - y);
    return cost;
}

// Function to print the path from root to the goal node
void printPath(Node* root) {
    if (root == NULL)
        return;
    printPath(root->parent);
    printMatrix(root->mat);
}

// Comparison function for priority queue sorting
int compareNodes(const void* a, const void* b) {
    Node* nodeA = *(Node**)a;
    Node* nodeB = *(Node**)b;
    return (nodeA->cost + nodeA->level) - (nodeB->cost + nodeB->level);
}

// Branch and Bound algorithm
void solve(int initial[N][N], int x, int y, int final[N][N]) {
    // Priority queue implemented as an array
    Node* pq[10000];
    int size = 0;

    // Create root node
    Node* root = newNode(initial, x, y, x, y, 0, NULL);
    root->cost = calculateCost(initial, final);
    pq[size++] = root;

    // Branch and Bound loop
    while (size > 0) {
        // Sort nodes based on (cost + level)
        qsort(pq, size, sizeof(Node*), compareNodes);

        // Pick the node with minimum cost + level
        Node* min = pq[0];

        // Remove this node from the queue
        for (int i = 1; i < size; i++)
            pq[i - 1] = pq[i];
        size--;

        // If the node is goal
        if (min->cost == 0) {
            printf("Solution found:\n");
            printPath(min);
            printf("Total moves = %d\n", min->level);
            return;
        }

        // Generate all 4 possible moves
        for (int i = 0; i < 4; i++) {
            int newX = min->x + row[i];
            int newY = min->y + col[i];

            if (isSafe(newX, newY)) {
                Node* child = newNode(min->mat, min->x, min->y, newX, newY, min->level + 1, min);
                child->cost = calculateCost(child->mat, final);
                pq[size++] = child;
            }
        }
    }
}

int main() {
    // Example initial configuration (0 denotes blank tile)
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    // Goal configuration
    int final[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}
    };

    // Blank tile coordinates in initial state
    int x = 1, y = 2;

    printf("Initial State:\n");
    printMatrix(initial);
    printf("Solving...\n\n");

    solve(initial, x, y, final);

    return 0;
}
