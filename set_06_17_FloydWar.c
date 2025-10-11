#include <stdio.h>
#define INF 99999  // Represents infinity (no direct edge)
#define V 4        // Number of vertices (You can change this value)

// Function to print the final distance matrix
void printSolution(int dist[V][V]) {
    printf("The following matrix shows the shortest distances between every pair of vertices:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (dist[i][j] == INF)
                printf("%7s", "INF");
            else
                printf("%7d", dist[i][j]);
        }
        printf("\n");
    }
}

// Function to implement Floyd–Warshall algorithm
void floydWarshall(int graph[V][V]) {
    int dist[V][V];

    // Step 1: Initialize the solution matrix same as input graph matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Step 2: Update distances by considering all vertices one by one
    for (int k = 0; k < V; k++) {             // Pick all vertices as intermediate
        for (int i = 0; i < V; i++) {         // Pick all vertices as source
            for (int j = 0; j < V; j++) {     // Pick all vertices as destination
                // If vertex k is on the shortest path from i to j, update dist[i][j]
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Step 3: Print the shortest distance matrix
    printSolution(dist);
}

// Driver Code
int main() {
    /* Example graph represented as adjacency matrix
       INF means there is no direct edge between the nodes */
    int graph[V][V] = {
        {0,   5,  INF, 10},
        {INF, 0,   3,  INF},
        {INF, INF, 0,   1},
        {INF, INF, INF, 0}
    };

    floydWarshall(graph);
    return 0;
}
