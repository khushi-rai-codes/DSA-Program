#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int adj[MAX][MAX];
    int vertices;
} Graph;

int visited[MAX];
int stack[MAX];
int top = -1;

void dfs1(Graph *g, int v) {
    visited[v] = 1;

    for (int i = 0; i < g->vertices; i++) {
        if (g->adj[v][i] && !visited[i]) {
            dfs1(g, i);
        }
    }

    stack[++top] = v;
}

void dfs2(Graph *g, int v) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < g->vertices; i++) {
        if (g->adj[v][i] && !visited[i]) {
            dfs2(g, i);
        }
    }
}

Graph transpose(Graph *g) {
    Graph t;
    t.vertices = g->vertices;

    for (int i = 0; i < g->vertices; i++) {
        for (int j = 0; j < g->vertices; j++) {
            t.adj[i][j] = g->adj[j][i];
        }
    }

    return t;
}

void kosaraju(Graph *g) {
    for (int i = 0; i < g->vertices; i++) {
        visited[i] = 0;
    }

    top = -1;

    for (int i = 0; i < g->vertices; i++) {
        if (!visited[i]) {
            dfs1(g, i);
        }
    }

    Graph t = transpose(g);

    for (int i = 0; i < g->vertices; i++) {
        visited[i] = 0;
    }

    printf("\nStrongly Connected Components:\n");

    while (top >= 0) {
        int v = stack[top--];

        if (!visited[v]) {
            dfs2(&t, v);
            printf("\n");
        }
    }
}

int main() {
    Graph g;

    g.vertices = 5;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            g.adj[i][j] = 0;
        }
    }

    g.adj[0][1] = 1;
    g.adj[1][2] = 1;
    g.adj[2][0] = 1;

    g.adj[1][3] = 1;
    g.adj[3][4] = 1;
    g.adj[4][3] = 1;

    kosaraju(&g);

    return 0;
}
