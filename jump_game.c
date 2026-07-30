#include <stdio.h>
int canReachEnd(int arr[], int n)
{
    int maxReach = 0;
    for (int i = 0; i < n; i++)
    {
        if (i > maxReach)
            return 0;
        if (i + arr[i] > maxReach)
            maxReach = i + arr[i];
    }
    return 1;
}
int main()
{
    int arr[] = {2, 3, 1, 1, 4};
    int n = sizeof(arr) / sizeof(arr[0]);
    if (canReachEnd(arr, n))
        printf("End is reachable.\n");
    else
        printf("End is not reachable.\n");
    return 0;
}
