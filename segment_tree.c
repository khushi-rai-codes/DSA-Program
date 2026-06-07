#include<stdio.h>
#define MAX 100
int tree[MAX];
void buildTree(int arr[], int node, int start, int end)
{
    if(start == end)
    {
        tree[node] = arr[start];
    }
    else
    {
        int mid = (start + end) / 2;
        buildTree(arr, 2 * node, start, mid);
        buildTree(arr, 2 * node + 1, mid + 1, end);

        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }
}
int query(int node, int start, int end, int l, int r)
{
    if(r < start || end < l)
        return 0;
    if(l <= start && end <= r)
        return tree[node];
    int mid = (start + end) / 2;
    int leftSum = query(2 * node, start, mid, l, r);
    int rightSum = query(2 * node + 1, mid + 1, end, l, r);
    return leftSum + rightSum;
}
int main()
{
    int arr[] = {1, 3, 5, 7, 9, 11};
    int n = sizeof(arr) / sizeof(arr[0]);
    buildTree(arr, 1, 0, n - 1);
    printf("Sum from index 1 to 3 = %d\n",
           query(1, 0, n - 1, 1, 3));
    return 0;
}
