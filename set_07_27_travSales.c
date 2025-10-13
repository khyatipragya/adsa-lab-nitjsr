#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#define INF 999999
int min(int a, int b) {
    return (a < b) ? a : b;
}
int tsp_dp(int **graph, int n) {
    int N = 1 << n;
    int **dp = (int **)malloc(N * sizeof(int *));
    for (int i = 0; i < N; i++)
        dp[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = INF;
    dp[1][0] = 0;
    for (int mask = 1; mask < N; mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                int nextMask = mask | (1 << v);
                dp[nextMask][v] = min(dp[nextMask][v], dp[mask][u] + graph[u][v]);
            }
        }
    }
    int ans = INF;
    for (int i = 1; i < n; i++)
        ans = min(ans, dp[N - 1][i] + graph[i][0]);
    for (int i = 0; i < N; i++)
        free(dp[i]);
    free(dp);
    return ans;
}
int tsp_greedy(int **graph, int n) {
    int *visited = (int *)calloc(n, sizeof(int));
    int cost = 0, count = 1, curr = 0;
    visited[curr] = 1;
    while (count < n) {
        int next = -1, min_dist = INF;
        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[curr][i] < min_dist) {
                min_dist = graph[curr][i];
                next = i;
            }
        }
        visited[next] = 1;
        cost += min_dist;
        curr = next;
        count++;
    }
    cost += graph[curr][0];
    free(visited);
    return cost;
}
int **generate_graph(int n) {
    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++)
        graph[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = INF;
            else
                graph[i][j] = rand() % 100 + 1;
        }
    }
    return graph;
}
int main() {
    srand(time(0));
    int sizes[] = {10, 20, 40, 60, 100};
    int num_tests = sizeof(sizes) / sizeof(sizes[0]);
    double times[num_tests];
    printf("TSP Problem Size vs Execution Time\n");
    printf("-----------------------------------\n");
    printf("Nodes\tTime (seconds)\n");
    printf("-----------------------------------\n");
    for (int t = 0; t < num_tests; t++) {
        int n = sizes[t];
        int **graph = generate_graph(n);
        clock_t start = clock();
        int cost;
        if (n <= 15) cost = tsp_dp(graph, n); 
        else cost = tsp_greedy(graph, n); 
        clock_t end = clock();
        double time_taken = (double)(end - start) / CLOCKS_PER_SEC;
        times[t] = time_taken;
        printf("%d\t%.6f\n", n, time_taken);
        for (int i = 0; i < n; i++) free(graph[i]);
        free(graph);
    }
    printf("-----------------------------------\n");
    printf("Execution complete.\n");
    return 0;
}
