#include <stdio.h>
#include <string.h>
int minimum(int a, int b, int c)
{
    int min = a;
    if (b < min)
        min = b;
    if (c < min)
        min = c;
    return min;
}
int editDistance(char str1[], char str2[])
{
    int m = strlen(str1);
    int n = strlen(str2);
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++)
        dp[i][0] = i;
    for (int j = 0; j <= n; j++)
        dp[0][j] = j;
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (str1[i - 1] == str2[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = 1 + minimum(
                    dp[i - 1][j],
                    dp[i][j - 1],
                    dp[i - 1][j - 1]
                );
            }
        }
    }
    return dp[m][n];
}
int main()
{
    char str1[] = "kitten";
    char str2[] = "sitting";
    printf("String 1: %s\n", str1);
    printf("String 2: %s\n", str2);
    printf("Minimum Edit Distance: %d\n",
           editDistance(str1, str2));
    return 0;
}
