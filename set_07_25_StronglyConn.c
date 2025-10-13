#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INIT_CAP 4
typedef struct {
    int *a;
    int size;
    int cap;
} IntVec;
void iv_init(IntVec *v) {
    v->a = malloc(sizeof(int) * INIT_CAP);
    v->size = 0;
    v->cap = INIT_CAP;
}
void iv_push(IntVec *v, int x) {
    if (v->size == v->cap) {
        v->cap *= 2;
        v->a = realloc(v->a, sizeof(int) * v->cap);
    }
    v->a[v->size++] = x;
}
void iv_free(IntVec *v) { free(v->a); v->a = NULL; v->size = v->cap = 0; }
typedef struct { int u, v; } Edge;
typedef struct {
    Edge *a;
    int top;
    int cap;
} EdgeStack;
void estack_init(EdgeStack *s) {
    s->cap = 32;
    s->a = malloc(sizeof(Edge) * s->cap);
    s->top = 0;
}
void estack_push(EdgeStack *s, Edge e) {
    if (s->top == s->cap) {
        s->cap *= 2;
        s->a = realloc(s->a, sizeof(Edge) * s->cap);
    }
    s->a[s->top++] = e;
}
Edge estack_pop(EdgeStack *s) {
    if (s->top == 0) { Edge e = {-1,-1}; return e; }
    return s->a[--s->top];
}
int estack_empty(EdgeStack *s) { return s->top == 0; }
void estack_free(EdgeStack *s) { free(s->a); s->a = NULL; s->top = s->cap = 0; }
int n, m;
IntVec *adj_dir;
IntVec *adj_undir;
int *dfn_scc, *low_scc, scc_time;
int *stack_scc, stack_scc_top;
char *onstack_scc;
int *scc_id; 
int scc_count;
void scc_init() {
    dfn_scc = malloc(sizeof(int)*n);
    low_scc = malloc(sizeof(int)*n);
    scc_id = malloc(sizeof(int)*n);
    onstack_scc = malloc(sizeof(char)*n);
    stack_scc = malloc(sizeof(int)*n);
    for (int i=0;i<n;i++) { dfn_scc[i] = -1; low_scc[i] = 0; scc_id[i] = -1; onstack_scc[i] = 0; }
    stack_scc_top = 0;
    scc_time = 0;
    scc_count = 0;
}
void scc_push_stack(int v) {
    stack_scc[stack_scc_top++] = v;
    onstack_scc[v] = 1;
}
void scc_dfs(int u) {
    dfn_scc[u] = low_scc[u] = scc_time++;
    scc_push_stack(u);
    for (int i=0;i<adj_dir[u].size;i++) {
        int v = adj_dir[u].a[i];
        if (dfn_scc[v] == -1) {
            scc_dfs(v);
            if (low_scc[v] < low_scc[u]) low_scc[u] = low_scc[v];
        } else if (onstack_scc[v]) {
            if (dfn_scc[v] < low_scc[u]) low_scc[u] = dfn_scc[v];
        }
    }
    if (low_scc[u] == dfn_scc[u]) {
        int w;
        do {
            w = stack_scc[--stack_scc_top];
            onstack_scc[w] = 0;
            scc_id[w] = scc_count;
        } while (w != u);
        scc_count++;
    }
}

void compute_sccs() {
    scc_init();
    for (int i=0;i<n;i++) if (dfn_scc[i] == -1) scc_dfs(i);
    IntVec *groups = malloc(sizeof(IntVec)*scc_count);
    for (int i=0;i<scc_count;i++) iv_init(&groups[i]);
    for (int v=0; v<n; v++) iv_push(&groups[scc_id[v]], v);
    printf("Strongly Connected Components (Tarjan):\n");
    for (int i=0;i<scc_count;i++) {
        printf(" SCC %d: ", i);
        for (int j=0;j<groups[i].size;j++) {
            if (j) printf(", ");
            printf("%d", groups[i].a[j]);
        }
        printf("\n");
    }
    for (int i=0;i<scc_count;i++) iv_free(&groups[i]);
    free(groups);
    free(dfn_scc); free(low_scc); free(onstack_scc); free(stack_scc); free(scc_id);
}
int *disc, *low, *parent;
int time_bcc;
char *is_articulation;
EdgeStack estack;
void bcc_init() {
    disc = malloc(sizeof(int)*n);
    low = malloc(sizeof(int)*n);
    parent = malloc(sizeof(int)*n);
    is_articulation = malloc(sizeof(char)*n);
    for (int i=0;i<n;i++) { disc[i] = -1; low[i] = 0; parent[i] = -1; is_articulation[i] = 0; }
    time_bcc = 0;
    estack_init(&estack);
}
void pop_bcc_until(Edge e) {
    int *present = calloc(n, sizeof(int));
    int *members = malloc(sizeof(int)*n);
    int memcount = 0;
    Edge cur;
    do {
        cur = estack_pop(&estack);
        if (!present[cur.u]) { present[cur.u]=1; members[memcount++]=cur.u; }
        if (!present[cur.v]) { present[cur.v]=1; members[memcount++]=cur.v; }
    } while (!(cur.u == e.u && cur.v == e.v) && estack.top > 0);
    printf("  Biconnected component (vertices): ");
    for (int i=0;i<memcount;i++) {
        if (i) printf(", ");
        printf("%d", members[i]);
    }
    printf("\n");
    free(present);
    free(members);
}

void bcc_dfs(int u) {
    disc[u] = low[u] = time_bcc++;
    int children = 0;
    for (int i=0;i<adj_undir[u].size;i++) {
        int v = adj_undir[u].a[i];
        if (disc[v] == -1) {
            children++;
            parent[v] = u;
            estack_push(&estack, (Edge){u,v});
            bcc_dfs(v);
            if (low[v] < low[u]) low[u] = low[v];
            if ((parent[u] == -1 && children > 1) || (parent[u] != -1 && low[v] >= disc[u])) {
                is_articulation[u] = 1;
                pop_bcc_until((Edge){u,v});
            }
            if (low[v] > disc[u]) {
                printf(" Bridge: %d - %d\n", u, v);
            }
        } else if (v != parent[u] && disc[v] < disc[u]) {
            estack_push(&estack, (Edge){u,v});
            if (disc[v] < low[u]) low[u] = disc[v];
        }
    }
}
void compute_biconnected() {
    bcc_init();
    printf("\nBiconnected components, articulation points and bridges (on underlying undirected graph):\n");
    for (int i=0;i<n;i++) if (disc[i] == -1) {
        bcc_dfs(i);
        if (!estack_empty(&estack)) {
            int *present = calloc(n, sizeof(int));
            int *members = malloc(sizeof(int)*n);
            int memcount = 0;
            while (!estack_empty(&estack)) {
                Edge cur = estack_pop(&estack);
                if (!present[cur.u]) { present[cur.u]=1; members[memcount++]=cur.u; }
                if (!present[cur.v]) { present[cur.v]=1; members[memcount++]=cur.v; }
            }
            printf("  Biconnected component (vertices): ");
            for (int i2=0;i2<memcount;i2++) {
                if (i2) printf(", ");
                printf("%d", members[i2]);
            }
            printf("\n");
            free(present);
            free(members);
        }
    }
    printf("Articulation Points:\n");
    int any = 0;
    for (int i=0;i<n;i++) if (is_articulation[i]) { printf(" %d", i); any = 1; }
    if (!any) printf(" None");
    printf("\n");

    estack_free(&estack);
    free(disc); free(low); free(parent); free(is_articulation);
}
int main() {
    if (scanf("%d %d", &n, &m) != 2) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }
    adj_dir = malloc(sizeof(IntVec)*n);
    adj_undir = malloc(sizeof(IntVec)*n);
    for (int i=0;i<n;i++) { iv_init(&adj_dir[i]); iv_init(&adj_undir[i]); }
    for (int i=0;i<m;i++) {
        int u,v;
        if (scanf("%d %d", &u, &v) != 2) { fprintf(stderr, "Invalid edge input\n"); return 1; }
        if (u<0 || u>=n || v<0 || v>=n) { fprintf(stderr, "Vertex out of range: %d %d\n", u, v); return 1; }
        iv_push(&adj_dir[u], v);
        iv_push(&adj_undir[u], v);
        iv_push(&adj_undir[v], u);
    }
    compute_sccs();
    compute_biconnected();
    for (int i=0;i<n;i++) { iv_free(&adj_dir[i]); iv_free(&adj_undir[i]); }
    free(adj_dir); free(adj_undir);
    return 0;
}
