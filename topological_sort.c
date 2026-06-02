#include<stdio.h>
#define V 6
void topologicalSortUtil(int v, int visited[], int stack[], int *top, int graph[V][V])
{
    visited[v] = 1;
    for(int i = 0; i < V; i++)
    {
        if(graph[v][i] && !visited[i])
        {
            topologicalSortUtil(i, visited, stack, top, graph);
        }
    }
    stack[++(*top)] = v;
}
void topologicalSort(int graph[V][V])
{
    int visited[V] = {0};
    int stack[V];
    int top = -1;
    for(int i = 0; i < V; i++)
    {
        if(!visited[i])
        {
            topologicalSortUtil(i, visited, stack, &top, graph);
        }
    }
    printf("Topological Sort:\n");
    while(top >= 0)
    {
        printf("%d ", stack[top--]);
    }
}
int main()
{
    int graph[V][V] =
    {
        {0,0,1,0,0,0},
        {0,0,1,1,0,0},
        {0,0,0,0,1,0},
        {0,0,0,0,1,1},
        {0,0,0,0,0,1},
        {0,0,0,0,0,0}
    };
    topologicalSort(graph);
    return 0;
}
