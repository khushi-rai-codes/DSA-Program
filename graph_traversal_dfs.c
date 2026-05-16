#include<stdio.h>
#define MAX 10
int graph[MAX][MAX];
int visited[MAX];
void dfs(int vertex, int vertices)
{
    visited[vertex] = 1;
    printf("%d ", vertex);
    for(int i = 0; i < vertices; i++)
    {
        if(graph[vertex][i] == 1 && !visited[i])
        {
            dfs(i, vertices);
        }
    }
}
int main()
{
    int vertices = 5;
    int sampleGraph[5][5] =
    {
        {0,1,1,0,0},
        {1,0,1,1,0},
        {1,1,0,0,1},
        {0,1,0,0,1},
        {0,0,1,1,0}
    };
    for(int i = 0; i < vertices; i++)
    {
        for(int j = 0; j < vertices; j++)
        {
            graph[i][j] = sampleGraph[i][j];
        }
    }
    printf("DFS Traversal: ");
    dfs(0, vertices);
    return 0;
}
