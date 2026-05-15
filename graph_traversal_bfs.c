#include<stdio.h>
#define MAX 10
int graph[MAX][MAX], visited[MAX], queue[MAX];
int front = -1, rear = -1;
void enqueue(int vertex)
{
    if(rear == MAX - 1)
        return;
    if(front == -1)
        front = 0;
    queue[++rear] = vertex;
}
int dequeue()
{
    if(front == -1 || front > rear)
        return -1;
    return queue[front++];
}
void bfs(int start, int vertices)
{
    enqueue(start);
    visited[start] = 1;
    printf("BFS Traversal: ");
    while(front <= rear)
    {
        int current = dequeue();
        printf("%d ", current);
        for(int i = 0; i < vertices; i++)
        {
            if(graph[current][i] == 1 && !visited[i])
            {
                enqueue(i);
                visited[i] = 1;
            }
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
    bfs(0, vertices);
    return 0;
}
