#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 100 // Maximum number of vertices in the graph

// Adjacency matrix representation of the graph
int graph[MAX_VERTICES][MAX_VERTICES];
// Array to store the color of each vertex (-1: uncolored, 0: color 0, 1: color 1)
int color[MAX_VERTICES];
int num_vertices;

// Function to perform BFS and check for bipartiteness from a given source vertex
bool isBipartiteBFS(int src) {
    // Initialize a queue for BFS
    int queue[MAX_VERTICES];
    int front = 0, rear = 0;

    queue[rear++] = src; // Enqueue the source vertex
    color[src] = 0;      // Assign color 0 to the source vertex

    while (front < rear) {
        int u = queue[front++]; // Dequeue a vertex

        // Traverse all adjacent vertices of u
        for (int v = 0; v < num_vertices; v++) {
            if (graph[u][v]) { // If there is an edge between u and v
                if (color[v] == -1) { // If v is uncolored
                    color[v] = 1 - color[u]; // Assign the opposite color to v
                    queue[rear++] = v;       // Enqueue v
                } else if (color[v] == color[u]) { // If v has the same color as u
                    return false; // Not bipartite (odd cycle found)
                }
            }
        }
    }
    return true; // Bipartite from this component
}

// Function to check if the entire graph is bipartite
bool checkBipartite() {
    // Initialize all vertices as uncolored
    for (int i = 0; i < num_vertices; i++) {
        color[i] = -1;
    }

    // Iterate through all vertices to handle disconnected graphs
    for (int i = 0; i < num_vertices; i++) {
        if (color[i] == -1) { // If vertex i is uncolored, start BFS from it
            if (!isBipartiteBFS(i)) {
                return false; // Not bipartite
            }
        }
    }
    return true; // Graph is bipartite
}

int main() {
    printf("Enter the number of vertices: ");
    scanf("%d", &num_vertices);

    printf("Enter the adjacency matrix (0 or 1 for no edge/edge):\n");
    for (int i = 0; i < num_vertices; i++) {
        for (int j = 0; j < num_vertices; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    if (checkBipartite()) {
        printf("The graph is Bipartite.\n");
    } else {
        printf("The graph is NOT Bipartite.\n");
    }

    return 0;
}