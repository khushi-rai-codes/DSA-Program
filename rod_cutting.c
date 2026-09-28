#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;

    printf("Enter rod length: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid rod length.\n");
        return 0;
    }

    int price[n];

    printf("Enter prices for lengths 1 to %d:\n", n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &price[i]);
    }

    int dp[n + 1];
    dp[0] = 0;

    for (int length = 1; length <= n; length++) {
        int best = price[length - 1];

        for (int cut = 1; cut < length; cut++) {
            best = max(best, price[cut - 1] + dp[length - cut]);
        }

        dp[length] = best;
    }

    printf("Maximum obtainable value: %d\n", dp[n]);

    return 0;
}
