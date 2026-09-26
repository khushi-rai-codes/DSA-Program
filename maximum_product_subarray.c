#include <stdio.h>

int max(int a, int b) {
    return (a > b) ? a : b;
}

int min(int a, int b) {
    return (a < b) ? a : b;
}

int main() {
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid array size.\n");
        return 0;
    }

    int arr[n];

    printf("Enter array elements:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    int currentMax = arr[0];
    int currentMin = arr[0];
    int maximumProduct = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < 0) {
            int temp = currentMax;
            currentMax = currentMin;
            currentMin = temp;
        }

        currentMax = max(arr[i], currentMax * arr[i]);
        currentMin = min(arr[i], currentMin * arr[i]);

        maximumProduct = max(maximumProduct, currentMax);
    }

    printf("Maximum Product Subarray: %d\n", maximumProduct);

    return 0;
}
