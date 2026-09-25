#include <stdio.h>

int main() {
    int n, target;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];

    printf("Enter elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter target sum: ");
    scanf("%d", &target);

    int dp[target + 1];

    for (int i = 0; i <= target; i++) {
        dp[i] = 0;
    }

    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        for (int sum = target; sum >= arr[i]; sum--) {
            if (dp[sum - arr[i]]) {
                dp[sum] = 1;
            }
        }
    }

    if (dp[target]) {
        printf("A subset with sum %d exists.\n", target);
    } else {
        printf("No subset with sum %d exists.\n", target);
    }

    return 0;
}
