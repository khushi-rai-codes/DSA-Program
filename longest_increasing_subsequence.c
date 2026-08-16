#include <stdio.h>
int main()
{
    int arr[] = {10, 22, 9, 33, 21, 50, 41, 60};
    int n = sizeof(arr) / sizeof(arr[0]);
    int dp[n];
    int maxLength = 1;
    for (int i = 0; i < n; i++)
        dp[i] = 1;
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (arr[i] > arr[j] && dp[i] < dp[j] + 1)
            {
                dp[i] = dp[j] + 1;
            }
        }
        if (dp[i] > maxLength)
           maxLength = dp[i];
    }
    printf("Length of Longest Increasing Subsequence = %d\n",
           maxLength);
    return 0;
}
