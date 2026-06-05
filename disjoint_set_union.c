#include<stdio.h>
#define MAX 10
int parent[MAX];
void makeSet(int n)
{
    for(int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
}
int find(int x)
{
    if(parent[x] != x)
    {
        parent[x] = find(parent[x]);
    }
    return parent[x];
}
void unionSets(int a, int b)
{
    int rootA = find(a);
    int rootB = find(b);
    if(rootA != rootB)
    {
        parent[rootB] = rootA;
    }
}
int main()
{
    int n = 5;
    makeSet(n);
    unionSets(0, 1);
    unionSets(1, 2);
    unionSets(3, 4);
    printf("Find(2) = %d\n", find(2));
    printf("Find(4) = %d\n", find(4));
    if(find(0) == find(2))
        printf("0 and 2 belong to same set\n");
    return 0;
}
