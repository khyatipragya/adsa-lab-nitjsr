#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX 50
int n, adj[MAX][MAX];
int visited[MAX], stack[MAX], stackSize;
int minCycle = INT_MAX, maxCycle = 0;
int inStack(int v) {
    for (int i = 0; i < stackSize; i++) { if (stack[i] == v) return 1; }
    return 0;
}
void DFS(int start, int u) {
    visited[u] = 1;
    stack[stackSize++] = u;
    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            if (v == start && stackSize > 2) {
                if (stackSize < minCycle) minCycle = stackSize;
                if (stackSize > maxCycle) maxCycle = stackSize;
            } else if (!inStack(v)) { DFS(start, v); }
        }
    }
    stackSize--;
    visited[u] = 0;
}
int main() {
    int edges, u, v, directed;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
    printf("Is the graph directed? (1=Yes, 0=No): ");
    scanf("%d", &directed);
    printf("Enter number of edges: ");
    scanf("%d", &edges);A
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        adj[u][v] = 1;
        if (!directed) adj[v][u] = 1;
    }
    for (int i = 0; i < n; i++) {
        stackSize = 0;
        DFS(i, i);
    }
    if (minCycle == INT_MAX) { printf("No cycles found in the graph.\n"); } 
    else {
        printf("Smallest cycle length = %d\n", minCycle);
        printf("Largest cycle length = %d\n", maxCycle);
    }
    return 0;
}
