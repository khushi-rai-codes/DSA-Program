#include <stdio.h>
#include <limits.h>

#define V 5
#define E 8
#define INF 99999

struct Edge
{
    int source;
    int destination;
    int weight;
};

void bellmanFord(
    struct Edge edges[],
    int vertices,
    int edgeCount,
    int distance[]
)
{
    for (int i = 0; i < vertices; i++)
        distance[i] = 0;

    for (int i = 0; i < vertices - 1; i++)
    {
        for (int j = 0; j < edgeCount; j++)
        {
            int u = edges[j].source;
            int v = edges[j].destination;
            int w = edges[j].weight;

            if (distance[u] + w < distance[v])
                distance[v] = distance[u] + w;
        }
    }
}

void dijkstra(
    int graph[V][V],
    int source,
    int distance[]
)
{
    int visited[V] = {0};

    for (int i = 0; i < V; i++)
        distance[i] = INF;

    distance[source] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int minDistance = INF;
        int current = -1;

        for (int i = 0; i < V; i++)
        {
            if (!visited[i] &&
                distance[i] < minDistance)
            {
                minDistance = distance[i];
                current = i;
            }
        }

        if (current == -1)
            break;

        visited[current] = 1;

        for (int i = 0; i < V; i++)
        {
            if (graph[current][i] != INF &&
                !visited[i] &&
                distance[current] != INF &&
                distance[current] +
                    graph[current][i] <
                    distance[i])
            {
                distance[i] =
                    distance[current] +
                    graph[current][i];
            }
        }
    }
}

int main()
{
    struct Edge edges[E] =
    {
        {0, 1, 3},
        {0, 2, 8},
        {0, 4, -4},
        {1, 3, 1},
        {1, 4, 7},
        {2, 1, 4},
        {3, 0, 2},
        {4, 3, 6}
    };

    int h[V];

    bellmanFord(
        edges,
        V,
        E,
        h
    );

    int graph[V][V];

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            graph[i][j] = INF;
        }
    }

    for (int i = 0; i < E; i++)
    {
        int u = edges[i].source;
        int v = edges[i].destination;

        graph[u][v] =
            edges[i].weight +
            h[u] -
            h[v];
    }

    printf("Johnson's Algorithm\n");
    printf("===================\n\n");

    for (int source = 0; source < V; source++)
    {
        int distance[V];

        dijkstra(
            graph,
            source,
            distance
        );

        printf("Shortest paths from vertex %d:\n",
               source);

        for (int destination = 0;
             destination < V;
             destination++)
        {
            if (distance[destination] == INF)
            {
                printf("To %d: INF\n",
                       destination);
            }
            else
            {
                int originalDistance =
                    distance[destination] -
                    h[source] +
                    h[destination];

                printf(
                    "To %d: %d\n",
                    destination,
                    originalDistance
                );
            }
        }

        printf("\n");
    }

    return 0;
}
