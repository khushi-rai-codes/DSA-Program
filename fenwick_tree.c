#include <stdio.h>
#define SIZE 10
int BIT[SIZE + 1];
void update(int index, int value, int n)
{
    while(index <= n)
    {
        BIT[index] += value;
        index += index & (-index);
    }
}
int query(int index)
{
    int sum = 0;
    while(index > 0)
    {
        sum += BIT[index];
        index -= index & (-index);
    }
    return sum;
}
int rangeQuery(int left, int right)
{
    return query(right) - query(left - 1);
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;
    for(int i = 0; i < n; i++)
    {
        update(i + 1, arr[i], n);
    }
    printf("Prefix Sum up to index 3: %d\n", query(3));
    printf("Range Sum (2 to 4): %d\n", rangeQuery(2, 4));
    return 0;
}
