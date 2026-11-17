#include <stdio.h>
#include <string.h>

#define MAX 105
#define INF 1000000000

int capacity[MAX][MAX];
int residual[MAX][MAX];
int parent[MAX];
int n;

int bfs(int source, int sink) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    queue[rear++] = source;
    visited[source] = 1;
    parent[source] = -1;

    while (front < rear) {
        int u = queue[front++];

        for (int v = 0; v < n; v++) {
            if (!visited[v] && residual[u][v] > 0) {
                parent[v] = u;
                visited[v] = 1;

                if (v == sink)
                    return 1;

                queue[rear++] = v;
            }
        }
    }

    return 0;
}

int edmondsKarp(int source, int sink) {
    memcpy(residual, capacity, sizeof(capacity));

    int maxFlow = 0;

    while (bfs(source, sink)) {
        int pathFlow = INF;

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];

            if (residual[u][v] < pathFlow)
                pathFlow = residual[u][v];
        }

        for (int v = sink; v != source; v = parent[v]) {
            int u = parent[v];

            residual[u][v] -= pathFlow;
            residual[v][u] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    return maxFlow;
}

int main(void) {
    int m, source, sink;

    printf("Enter vertices and edges: ");
    scanf("%d %d", &n, &m);

    if (n <= 0 || n >= MAX || m < 0) {
        printf("Invalid graph dimensions.\n");
        return 1;
    }

    printf("Enter edges (from to capacity):\n");

    for (int i = 0; i < m; i++) {
        int u, v, c;
        scanf("%d %d %d", &u, &v, &c);

        if (u < 0 || u >= n || v < 0 || v >= n || c < 0) {
            printf("Invalid edge.\n");
            return 1;
        }

        capacity[u][v] += c;
    }

    printf("Enter source and sink: ");
    scanf("%d %d", &source, &sink);

    if (source < 0 || source >= n ||
        sink < 0 || sink >= n || source == sink) {
        printf("Invalid source or sink.\n");
        return 1;
    }

    int result = edmondsKarp(source, sink);

    printf("\nMaximum Flow: %d\n", result);

    printf("\nResidual Capacity Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%5d", residual[i][j]);

        printf("\n");
    }

    return 0;
}
