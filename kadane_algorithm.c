#include <stdio.h>
int maxSubArraySum(int arr[], int n)
{
    int maxSoFar = arr[0];
    int currentMax = arr[0];
    for (int i = 1; i < n; i++)
    {
        if (currentMax + arr[i] > arr[i])
            currentMax = currentMax + arr[i];
        else
            currentMax = arr[i];

        if (currentMax > maxSoFar)
            maxSoFar = currentMax;
    }
    return maxSoFar;
}
int main()
{
    int arr[] = {-2, -3, 4, -1, -2, 1, 5, -3};
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Maximum Subarray Sum = %d\n", maxSubArraySum(arr, n));
    return 0;
}
