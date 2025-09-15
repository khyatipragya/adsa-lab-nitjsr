#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;
Node* adj[MAX];
int visited[MAX], parent[MAX], d[MAX], f[MAX];
int timeCounter = 0;
int n;
void addEdge(int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adj[u];
    adj[u] = newNode;
}
void DFSVisit(int u) {
    visited[u] = 1;
    d[u] = ++timeCounter;
    Node* temp = adj[u];
    while (temp != NULL) {
        int v = temp->vertex;
        if (visited[v] == 0) {
            printf("Tree Edge: %d -> %d\n", u, v);
            parent[v] = u;
            DFSVisit(v);
        } else if (f[v] == 0) { printf("Back Edge: %d -> %d\n", u, v); } 
        else {
            if (d[u] < d[v]) printf("Forward Edge: %d -> %d\n", u, v);
            else printf("Cross Edge: %d -> %d\n", u, v);
        }
        temp = temp->next;
    }
    f[u] = ++timeCounter;
}
void DFS() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
        parent[i] = -1;
        d[i] = f[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            DFSVisit(i);
        }
    }
}
int main() {
    int edges, u, v;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) adj[i] = NULL;
    printf("Enter number of edges: ");
    scanf("%d", &edges);
    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d%d", &u, &v);
        addEdge(u, v);  
    }
    printf("\nClassifying edges during DFS:\n");
    DFS();
    return 0;
}
