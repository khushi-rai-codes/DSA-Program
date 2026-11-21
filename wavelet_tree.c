#include <stdio.h>
#include <stdlib.h>

#define MAXN 1000

typedef struct {
    int low, high;
    int *prefix;
    struct WaveletNode *left, *right;
} WaveletNode;

struct WaveletNode {
    int low, high;
    int *prefix;
    struct WaveletNode *left, *right;
};

WaveletNode *build(int *arr, int n, int low, int high) {
    WaveletNode *node = malloc(sizeof(WaveletNode));

    node->low = low;
    node->high = high;
    node->left = node->right = NULL;
    node->prefix = calloc(n + 1, sizeof(int));

    if (low == high || n == 0)
        return node;

    int mid = low + (high - low) / 2;
    int *leftArr = malloc(n * sizeof(int));
    int *rightArr = malloc(n * sizeof(int));
    int l = 0, r = 0;

    for (int i = 0; i < n; i++) {
        if (arr[i] <= mid) {
            leftArr[l++] = arr[i];
            node->prefix[i + 1] = node->prefix[i] + 1;
        } else {
            rightArr[r++] = arr[i];
            node->prefix[i + 1] = node->prefix[i];
        }
    }

    node->left = build(leftArr, l, low, mid);
    node->right = build(rightArr, r, mid + 1, high);

    free(leftArr);
    free(rightArr);

    return node;
}

int kthSmallest(WaveletNode *node, int l, int r, int k) {
    if (node->low == node->high)
        return node->low;

    int leftCount =
        node->prefix[r] - node->prefix[l - 1];

    if (k <= leftCount) {
        int newL = node->prefix[l - 1] + 1;
        int newR = node->prefix[r];

        return kthSmallest(node->left, newL, newR, k);
    } else {
        int newL = l - node->prefix[l - 1];
        int newR = r - node->prefix[r];

        return kthSmallest(
            node->right, newL, newR, k - leftCount
        );
    }
}

int countLE(WaveletNode *node, int l, int r, int x) {
    if (l > r || x < node->low)
        return 0;

    if (node->high <= x)
        return r - l + 1;

    int leftL = node->prefix[l - 1] + 1;
    int leftR = node->prefix[r];

    int rightL = l - node->prefix[l - 1];
    int rightR = r - node->prefix[r];

    return countLE(node->left, leftL, leftR, x)
         + countLE(node->right, rightL, rightR, x);
}

void freeTree(WaveletNode *node) {
    if (!node) return;

    freeTree(node->left);
    freeTree(node->right);

    free(node->prefix);
    free(node);
}

int main() {
    int arr[] = {5, 1, 2, 7, 3, 6, 4};
    int n = sizeof(arr) / sizeof(arr[0]);

    WaveletNode *root = build(arr, n, 1, 7);

    printf("Original Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n3rd smallest in range [2, 6]: %d",
           kthSmallest(root, 2, 6, 3));

    printf("\nElements <= 4 in range [1, 7]: %d\n",
           countLE(root, 1, 7, 4));

    freeTree(root);

    return 0;
}
