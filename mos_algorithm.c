#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int left, right, index, block;
} Query;

int *arr, *compressed, *frequency;
int distinct = 0;
int blockSize;

int compareInt(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int compareQuery(const void *a, const void *b) {
    const Query *x = a;
    const Query *y = b;

    if (x->block != y->block)
        return x->block - y->block;

    if (x->block % 2 == 0)
        return x->right - y->right;

    return y->right - x->right;
}

void add(int position) {
    int value = compressed[position];

    if (frequency[value] == 0)
        distinct++;

    frequency[value]++;
}

void removeElement(int position) {
    int value = compressed[position];

    frequency[value]--;

    if (frequency[value] == 0)
        distinct--;
}

int main(void) {
    int n, q;

    printf("Enter array size: ");

    if (scanf("%d", &n) != 1 || n <= 0 || n > 100000) {
        printf("Invalid array size.\n");
        return 1;
    }

    arr = malloc(n * sizeof(int));
    compressed = malloc(n * sizeof(int));

    if (!arr || !compressed) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    for (int i = 0; i < n; i++)
        compressed[i] = arr[i];

    qsort(compressed, n, sizeof(int), compareInt);

    int uniqueCount = 0;

    for (int i = 0; i < n; i++) {
        if (i == 0 || compressed[i] != compressed[i - 1])
            compressed[uniqueCount++] = compressed[i];
    }

    for (int i = 0; i < n; i++) {
        int low = 0, high = uniqueCount - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (compressed[mid] == arr[i]) {
                arr[i] = mid;
                break;
            }

            if (compressed[mid] < arr[i])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    frequency = calloc(uniqueCount, sizeof(int));

    if (!frequency) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter number of queries: ");

    if (scanf("%d", &q) != 1 || q < 0 || q > 100000) {
        printf("Invalid query count.\n");
        return 1;
    }

    Query *queries = malloc(q * sizeof(Query));
    int *answers = malloc(q * sizeof(int));

    if (q > 0 && (!queries || !answers)) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    blockSize = (int)sqrt(n);
    if (blockSize < 1)
        blockSize = 1;

    printf("Enter queries (left right), using 0-based indexing:\n");

    for (int i = 0; i < q; i++) {
        int l, r;

        if (scanf("%d %d", &l, &r) != 2 ||
            l < 0 || r >= n || l > r) {
            printf("Invalid query.\n");
            return 1;
        }

        queries[i] = (Query){l, r, i, l / blockSize};
    }

    qsort(queries, q, sizeof(Query), compareQuery);

    int currentL = 0;
    int currentR = -1;

    for (int i = 0; i < q; i++) {
        int L = queries[i].left;
        int R = queries[i].right;

        while (currentL > L)
            add(--currentL);

        while (currentR < R)
            add(++currentR);

        while (currentL < L)
            removeElement(currentL++);

        while (currentR > R)
            removeElement(currentR--);

        answers[queries[i].index] = distinct;
    }

    printf("\nDistinct elements in each range:\n");

    for (int i = 0; i < q; i++)
        printf("Query %d: %d\n", i + 1, answers[i]);

    free(arr);
    free(compressed);
    free(frequency);
    free(queries);
    free(answers);

    return 0;
}
