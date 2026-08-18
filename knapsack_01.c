#include <stdio.h>
int max(int a, int b)
{
    return (a > b) ? a : b;
}
int main()
{
    int weights[] = {1, 3, 4, 5};
    int values[] = {1, 4, 5, 7};
    int n = sizeof(weights) / sizeof(weights[0]);
    int capacity = 7;
    int dp[n + 1][capacity + 1];
    for (int i = 0; i <= n; i++)
    {
        for (int w = 0; w <= capacity; w++)
        {
            if (i == 0 || w == 0)
            {
                dp[i][w] = 0;
            }
            else if (weights[i - 1] <= w)
            {
                dp[i][w] = max(
                    values[i - 1] + dp[i - 1][w - weights[i - 1]],
                    dp[i - 1][w]
                );
            }
            else
            {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }
    printf("Maximum Value = %d\n", dp[n][capacity]);
    return 0;
}
