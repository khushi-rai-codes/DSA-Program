#include<stdio.h>
#define V 5
#define INF 9999
int minDistance(int dist[], int visited[])
{
    int min = INF, minIndex;
    for(int v = 0; v < V; v++)
    {
        if(visited[v] == 0 && dist[v] <= min)
        {
            min = dist[v];
            minIndex = v;
        }
    }
    return minIndex;
}
void dijkstra(int graph[V][V], int source)
{
    int dist[V];
    int visited[V];
    for(int i = 0; i < V; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }
    dist[source] = 0;
    for(int count = 0; count < V - 1; count++)
    {
        int u = minDistance(dist, visited);
        visited[u] = 1;
        for(int v = 0; v < V; v++)
        {
            if(!visited[v] &&
               graph[u][v] &&
               dist[u] != INF &&
               dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    printf("Vertex\tDistance from Source\n");
    for(int i = 0; i < V; i++)
    {
        printf("%d\t%d\n", i, dist[i]);
    }
}
int main()
{
    int graph[V][V] =
    {
        {0,10,0,30,100},
        {10,0,50,0,0},
        {0,50,0,20,10},
        {30,0,20,0,60},
        {100,0,10,60,0}
    };
    dijkstra(graph, 0);
    return 0;
}
