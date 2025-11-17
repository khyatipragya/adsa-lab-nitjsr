#include <stdio.h>
#include <stdbool.h>

#define MAX 20   // Safe upper limit for backtracking

int n, e;
int graph[MAX][MAX];
int path[MAX];
bool visited[MAX];

// Check if vertex v can be added at position pos in the Hamiltonian path
bool isSafe(int v, int pos) {
    // Must be adjacent to previous vertex in the path
    if (graph[path[pos - 1]][v] == 0)
        return false;

    // Must not already be in the path
    if (visited[v])
        return false;

    return true;
}

bool hamiltonianCycleUtil(int pos) {
    if (pos == n) {
        // Check if last vertex connects back to first
        return graph[path[pos - 1]][path[0]] == 1;
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;
            visited[v] = true;

            if (hamiltonianCycleUtil(pos + 1))
                return true;

            visited[v] = false;
        }
    }
    return false;
}

bool hamiltonianCycle() {
    // Start from vertex 0
    path[0] = 0;
    visited[0] = true;

    if (hamiltonianCycleUtil(1)) {
        return true;
    }

    return false;
}

int main() {
    printf("Enter number of vertices (n): ");
    scanf("%d", &n);

    printf("Enter number of edges (e): ");
    scanf("%d", &e);

    // Initialize graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v): \n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;
    }

    for (int i = 0; i < n; i++)
        visited[i] = false;

    if (hamiltonianCycle()) {
        printf("\nHamiltonian Cycle exists!\nCycle: ");
        for (int i = 0; i < n; i++)
            printf("%d ", path[i]);
        printf("%d\n", path[0]); // Return to start
    } else {
        printf("\nNo Hamiltonian Cycle exists in the graph.\n");
    }

    return 0;
}
