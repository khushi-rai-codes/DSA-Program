#include <stdio.h>
#include <math.h>
int jumpSearch(int arr[], int n, int key)
{
    int step = sqrt(n);
    int prev = 0;
    while (arr[(step < n ? step : n) - 1] < key)
    {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }
    while (arr[prev] < key)
    {
        prev++;

        if (prev == (step < n ? step : n))
            return -1;
    }
    if (arr[prev] == key)
        return prev;
    return -1;
}
int main()
{
    int arr[] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key;
    printf("Enter element to search: ");
    scanf("%d", &key);
    int index = jumpSearch(arr, n, key);
    if (index != -1)
        printf("Element found at index %d\n", index);
    else
        printf("Element not found\n");
    return 0;
}
