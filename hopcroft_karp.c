#include <stdio.h>
#include <string.h>

#define MAX 505

int nLeft, nRight;
int adj[MAX][MAX], degree[MAX];
int pairU[MAX], pairV[MAX], dist[MAX];

int bfs(void) {
    int queue[MAX], front = 0, rear = 0;
    int found = 0;

    for (int u = 1; u <= nLeft; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            queue[rear++] = u;
        } else {
            dist[u] = -1;
        }
    }

    while (front < rear) {
        int u = queue[front++];

        for (int i = 0; i < degree[u]; i++) {
            int v = adj[u][i];

            if (pairV[v] == 0) {
                found = 1;
            } else if (dist[pairV[v]] == -1) {
                dist[pairV[v]] = dist[u] + 1;
                queue[rear++] = pairV[v];
            }
        }
    }

    return found;
}

int dfs(int u) {
    for (int i = 0; i < degree[u]; i++) {
        int v = adj[u][i];

        if (pairV[v] == 0 ||
            (dist[pairV[v]] == dist[u] + 1 &&
             dfs(pairV[v]))) {

            pairU[u] = v;
            pairV[v] = u;
            return 1;
        }
    }

    dist[u] = -1;
    return 0;
}

int hopcroftKarp(void) {
    int matching = 0;

    while (bfs()) {
        for (int u = 1; u <= nLeft; u++) {
            if (pairU[u] == 0 && dfs(u))
                matching++;
        }
    }

    return matching;
}

int main(void) {
    int edges;

    printf("Enter left vertices, right vertices and edges: ");

    if (scanf("%d %d %d", &nLeft, &nRight, &edges) != 3 ||
        nLeft < 1 || nLeft >= MAX ||
        nRight < 1 || nRight >= MAX ||
        edges < 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter edges (left_vertex right_vertex):\n");

    for (int i = 0; i < edges; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 1 || u > nLeft ||
            v < 1 || v > nRight) {
            printf("Invalid edge.\n");
            return 1;
        }

        if (degree[u] >= MAX) {
            printf("Too many edges for a vertex.\n");
            return 1;
        }

        adj[u][degree[u]++] = v;
    }

    int result = hopcroftKarp();

    printf("\nMaximum matching: %d\n", result);

    for (int u = 1; u <= nLeft; u++) {
        if (pairU[u] != 0)
            printf("%d -> %d\n", u, pairU[u]);
    }

    return 0;
}
