#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAXV 100
#define MAXE 10000

typedef struct {
    int to, capacity, next;
} Edge;

Edge edges[MAXE];
int head[MAXV], level[MAXV], current[MAXV];
int edgeCount = 0, vertices;

void addEdge(int from, int to, int capacity) {
    edges[edgeCount] = (Edge){to, capacity, head[from]};
    head[from] = edgeCount++;

    edges[edgeCount] = (Edge){from, 0, head[to]};
    head[to] = edgeCount++;
}

int bfs(int source, int sink) {
    int queue[MAXV], front = 0, rear = 0;

    memset(level, -1, sizeof(level));
    level[source] = 0;
    queue[rear++] = source;

    while (front < rear) {
        int u = queue[front++];

        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;

            if (edges[e].capacity > 0 && level[v] == -1) {
                level[v] = level[u] + 1;
                queue[rear++] = v;
            }
        }
    }

    return level[sink] != -1;
}

int dfs(int u, int sink, int flow) {
    if (u == sink)
        return flow;

    for (int *e = &current[u]; *e != -1; *e = edges[*e].next) {
        int id = *e;
        int v = edges[id].to;

        if (edges[id].capacity > 0 &&
            level[v] == level[u] + 1) {

            int pushed = dfs(
                v, sink,
                flow < edges[id].capacity
                    ? flow : edges[id].capacity
            );

            if (pushed > 0) {
                edges[id].capacity -= pushed;
                edges[id ^ 1].capacity += pushed;
                return pushed;
            }
        }
    }

    return 0;
}

int dinic(int source, int sink) {
    int maxFlow = 0;

    while (bfs(source, sink)) {
        memcpy(current, head, sizeof(head));

        int flow;
        while ((flow = dfs(source, sink, INT_MAX)) > 0)
            maxFlow += flow;
    }

    return maxFlow;
}

int main(void) {
    int edgeCountInput, source, sink;

    printf("Enter number of vertices and edges: ");
    if (scanf("%d %d", &vertices, &edgeCountInput) != 2 ||
        vertices < 2 || vertices > MAXV ||
        edgeCountInput < 0 ||
        edgeCountInput > MAXE / 2) {
        printf("Invalid graph dimensions.\n");
        return 1;
    }

    for (int i = 0; i < MAXV; i++)
        head[i] = -1;

    printf("Enter edges as: from to capacity\n");

    for (int i = 0; i < edgeCountInput; i++) {
        int u, v, capacity;

        if (scanf("%d %d %d", &u, &v, &capacity) != 3 ||
            u < 0 || u >= vertices ||
            v < 0 || v >= vertices ||
            capacity < 0) {
            printf("Invalid edge.\n");
            return 1;
        }

        addEdge(u, v, capacity);
    }

    printf("Enter source and sink: ");
    if (scanf("%d %d", &source, &sink) != 2 ||
        source < 0 || source >= vertices ||
        sink < 0 || sink >= vertices ||
        source == sink) {
        printf("Invalid source or sink.\n");
        return 1;
    }

    printf("Maximum flow: %d\n", dinic(source, sink));

    return 0;
}
