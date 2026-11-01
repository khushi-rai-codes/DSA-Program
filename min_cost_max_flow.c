#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXV 105
#define MAXE 10005
#define INF (LLONG_MAX / 4)

typedef struct {
    int to, capacity, cost, next;
} Edge;

Edge edges[MAXE];
int head[MAXV], edgeCount = 0;
int vertices;

void addEdge(int u, int v, int capacity, int cost) {
    edges[edgeCount] = (Edge){v, capacity, cost, head[u]};
    head[u] = edgeCount++;

    edges[edgeCount] = (Edge){u, 0, -cost, head[v]};
    head[v] = edgeCount++;
}

int minCostMaxFlow(int source, int sink,
                   long long *totalCost) {
    int maxFlow = 0;
    *totalCost = 0;

    while (1) {
        long long dist[MAXV];
        int parent[MAXV];
        int inQueue[MAXV] = {0};
        int queue[MAXV * MAXV];
        int front = 0, rear = 0;

        for (int i = 0; i < vertices; i++) {
            dist[i] = INF;
            parent[i] = -1;
        }

        dist[source] = 0;
        queue[rear++] = source;
        inQueue[source] = 1;

        while (front != rear) {
            int u = queue[front++ % (MAXV * MAXV)];
            inQueue[u] = 0;

            for (int e = head[u]; e != -1; e = edges[e].next) {
                int v = edges[e].to;

                if (edges[e].capacity > 0 &&
                    dist[u] != INF &&
                    dist[v] > dist[u] + edges[e].cost) {

                    dist[v] = dist[u] + edges[e].cost;
                    parent[v] = e;

                    if (!inQueue[v]) {
                        queue[rear++ % (MAXV * MAXV)] = v;
                        inQueue[v] = 1;
                    }
                }
            }
        }

        if (parent[sink] == -1)
            break;

        int flow = INT_MAX;

        for (int v = sink; v != source; ) {
            int e = parent[v];
            if (edges[e].capacity < flow)
                flow = edges[e].capacity;
            v = edges[e ^ 1].to;
        }

        for (int v = sink; v != source; ) {
            int e = parent[v];

            edges[e].capacity -= flow;
            edges[e ^ 1].capacity += flow;

            v = edges[e ^ 1].to;
        }

        maxFlow += flow;
        *totalCost += (long long)flow * dist[sink];
    }

    return maxFlow;
}

int main(void) {
    int edgeCountInput, source, sink;

    printf("Enter vertices and edges: ");

    if (scanf("%d %d", &vertices, &edgeCountInput) != 2 ||
        vertices < 2 || vertices >= MAXV ||
        edgeCountInput < 0 || edgeCountInput > (MAXE / 2)) {
        printf("Invalid input.\n");
        return 1;
    }

    for (int i = 0; i < MAXV; i++)
        head[i] = -1;

    printf("Enter edges: from to capacity cost\n");

    for (int i = 0; i < edgeCountInput; i++) {
        int u, v, capacity, cost;

        if (scanf("%d %d %d %d", &u, &v, &capacity, &cost) != 4 ||
            u < 0 || u >= vertices ||
            v < 0 || v >= vertices ||
            capacity < 0) {
            printf("Invalid edge.\n");
            return 1;
        }

        addEdge(u, v, capacity, cost);
    }

    printf("Enter source and sink: ");

    if (scanf("%d %d", &source, &sink) != 2 ||
        source < 0 || source >= vertices ||
        sink < 0 || sink >= vertices ||
        source == sink) {
        printf("Invalid source or sink.\n");
        return 1;
    }

    long long totalCost;
    int flow = minCostMaxFlow(source, sink, &totalCost);

    printf("\nMaximum Flow: %d\n", flow);
    printf("Minimum Cost: %lld\n", totalCost);

    return 0;
}
