#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int path[MAX];
int n;

/* Check if vertex v can be added to position pos in Hamiltonian Cycle */
int isSafe(int v, int pos) {
    /* Check adjacency from previous vertex */
    if (graph[path[pos - 1]][v] == 0)
        return 0;

    /* Check if already included */
    for (int i = 0; i < pos; i++)
        if (path[i] == v)
            return 0;

    return 1;
}

/* Recursive utility function */
int hamCycleUtil(int pos) {
    if (pos == n) {
        /* Check if last vertex connects to first */
        if (graph[path[pos - 1]][path[0]] == 1)
            return 1;
        else
            return 0;
    }

    for (int v = 1; v < n; v++) {
        if (isSafe(v, pos)) {
            path[pos] = v;

            if (hamCycleUtil(pos + 1))
                return 1;

            path[pos] = -1;  // backtrack
        }
    }
    return 0;
}

/* Main Hamiltonian cycle function */
int hamCycle() {
    for (int i = 0; i < n; i++)
        path[i] = -1;

    path[0] = 0; // start from vertex 0

    if (hamCycleUtil(1) == 0) {
        printf("\nNo Hamiltonian Cycle exists\n");
        return 0;
    }

    printf("\nHamiltonian Cycle found: ");
    for (int i = 0; i < n; i++)
        printf("%d ", path[i]);
    printf("%d\n", path[0]); // to show the cycle

    return 1;
}

int main() {
    int e;
    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    // Initialize graph
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter %d edges (u v):\n", e);
    for (int i = 0; i < e; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = graph[v][u] = 1;  // undirected graph
    }

    hamCycle();

    return 0;
}
