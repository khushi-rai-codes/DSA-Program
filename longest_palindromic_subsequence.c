#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int longestPalindromicSubsequence(char str[]) {
    int n = strlen(str);
    int dp[n][n];

    for (int i = 0; i < n; i++)
        dp[i][i] = 1;

    for (int length = 2; length <= n; length++) {
        for (int i = 0; i <= n - length; i++) {
            int j = i + length - 1;

            if (str[i] == str[j]) {
                if (length == 2)
                    dp[i][j] = 2;
                else
                    dp[i][j] = dp[i + 1][j - 1] + 2;
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[0][n - 1];
}

int main() {
    char str[100];

    printf("Enter a string: ");
    scanf("%99s", str);

    printf("Length of Longest Palindromic Subsequence: %d\n",
           longestPalindromicSubsequence(str));

    return 0;
}
