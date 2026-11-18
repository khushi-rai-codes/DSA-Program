#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 1005
#define MAXE 10005

typedef struct {
    int to;
    int edgeId;
    int next;
} Edge;

Edge edges[2 * MAXE];

int head[MAXV];
int degree[MAXV];
int inDegree[MAXV], outDegree[MAXV];
int edgeUsed[MAXE];

int edgeCount = 0;
int directed;
int vertices, m;

int adjacencyCount = 0;

void addEdge(int u, int v, int id) {
    edges[adjacencyCount].to = v;
    edges[adjacencyCount].edgeId = id;
    edges[adjacencyCount].next = head[u];

    head[u] = adjacencyCount++;
    degree[u]++;

    if (directed) {
        outDegree[u]++;
        inDegree[v]++;
    } else {
        edges[adjacencyCount].to = u;
        edges[adjacencyCount].edgeId = id;
        edges[adjacencyCount].next = head[v];

        head[v] = adjacencyCount++;
        degree[v]++;
    }
}

int findStartVertex(void) {
    int start = -1;

    if (directed) {
        int startNodes = 0;
        int endNodes = 0;

        for (int i = 0; i < vertices; i++) {
            int difference = outDegree[i] - inDegree[i];

            if (difference == 1) {
                start = i;
                startNodes++;
            } else if (difference == -1) {
                endNodes++;
            } else if (difference != 0) {
                return -1;
            }
        }

        if (!((startNodes == 1 && endNodes == 1) ||
              (startNodes == 0 && endNodes == 0))) {
            return -1;
        }

        if (start == -1) {
            for (int i = 0; i < vertices; i++) {
                if (outDegree[i] > 0) {
                    start = i;
                    break;
                }
            }
        }
    } else {
        int oddCount = 0;

        for (int i = 0; i < vertices; i++) {
            if (degree[i] % 2 != 0) {
                oddCount++;
                start = i;
            }
        }

        if (oddCount != 0 && oddCount != 2)
            return -1;

        if (oddCount == 0) {
            start = -1;

            for (int i = 0; i < vertices; i++) {
                if (degree[i] > 0) {
                    start = i;
                    break;
                }
            }
        }
    }

    return start;
}

int findEulerianPath(int start, int path[]) {
    int stack[MAXE + 5];
    int top = 0;
    int pathSize = 0;

    int current[MAXV];

    for (int i = 0; i < vertices; i++)
        current[i] = head[i];

    stack[top++] = start;

    while (top > 0) {
        int u = stack[top - 1];

        while (current[u] != -1 &&
               edgeUsed[edges[current[u]].edgeId]) {
            current[u] = edges[current[u]].next;
        }

        if (current[u] == -1) {
            path[pathSize++] = u;
            top--;
        } else {
            int edgeIndex = current[u];
            current[u] = edges[edgeIndex].next;

            int v = edges[edgeIndex].to;
            int id = edges[edgeIndex].edgeId;

            if (!edgeUsed[id]) {
                edgeUsed[id] = 1;
                stack[top++] = v;
            }
        }
    }

    return pathSize;
}

int main(void) {
    printf("EULERIAN PATH AND CIRCUIT\n");
    printf("------------------------\n");

    printf("Enter number of vertices and edges: ");

    if (scanf("%d %d", &vertices, &m) != 2 ||
        vertices <= 0 || vertices >= MAXV ||
        m < 0 || m >= MAXE) {
        printf("Invalid graph dimensions.\n");
        return 1;
    }

    printf("Enter graph type (1 = Directed, 0 = Undirected): ");

    if (scanf("%d", &directed) != 1 ||
        (directed != 0 && directed != 1)) {
        printf("Invalid graph type.\n");
        return 1;
    }

    for (int i = 0; i < vertices; i++)
        head[i] = -1;

    printf("Enter edges (u v), using vertices 0 to %d:\n",
           vertices - 1);

    for (int i = 0; i < m; i++) {
        int u, v;

        if (scanf("%d %d", &u, &v) != 2 ||
            u < 0 || u >= vertices ||
            v < 0 || v >= vertices) {
            printf("Invalid edge.\n");
            return 1;
        }

        addEdge(u, v, i);
    }

    if (m == 0) {
        printf("\nGraph has no edges.\n");
        return 0;
    }

    int start = findStartVertex();

    if (start == -1) {
        printf("\nNo Eulerian path exists.\n");
        return 0;
    }

    int path[MAXE + 5];

    int pathSize = findEulerianPath(start, path);

    if (pathSize != m + 1) {
        printf("\nNo Eulerian path exists.\n");
        return 0;
    }

    printf("\nEulerian Path:\n");

    for (int i = pathSize - 1; i >= 0; i--) {
        printf("%d", path[i]);

        if (i > 0)
            printf(" -> ");
    }

    printf("\n");

    if (path[0] == path[pathSize - 1])
        printf("\nThe graph has an Eulerian Circuit.\n");
    else
        printf("\nThe graph has an Eulerian Path but not a Circuit.\n");

    return 0;
}
