#include<stdio.h>
#include<stdlib.h>
#define MAX 10
struct Edge
{
    int src, dest, weight;
};
int parent[MAX];
int find(int i)
{
    while(parent[i] != i)
        i = parent[i];

    return i;
}
void unionSet(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);

    parent[rootA] = rootB;
}
void sortEdges(struct Edge edges[], int e)
{
    struct Edge temp;
    for(int i = 0; i < e - 1; i++)
    {
        for(int j = 0; j < e - i - 1; j++)
        {
            if(edges[j].weight > edges[j + 1].weight)
            {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}
void kruskal(struct Edge edges[], int vertices, int edgesCount)
{
    sortEdges(edges, edgesCount);
    for(int i = 0; i < vertices; i++)
        parent[i] = i;
    printf("Edges in Minimum Spanning Tree:\n");
    for(int i = 0; i < edgesCount; i++)
    {
        int srcParent = find(edges[i].src);
        int destParent = find(edges[i].dest);
        if(srcParent != destParent)
        {
            printf("%d -- %d == %d\n",
                   edges[i].src,
                   edges[i].dest,
                   edges[i].weight);
            unionSet(srcParent, destParent);
        }
    }
}
int main()
{
    int vertices = 4;
    int edgesCount = 5;
    struct Edge edges[] =
    {
        {0,1,10},
        {0,2,6},
        {0,3,5},
        {1,3,15},
        {2,3,4}
    };
    kruskal(edges, vertices, edgesCount);
    return 0;
}
