#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int left, right, count;
} Node;

Node *tree;
int nodeCount = 0;
int capacity;

int *values, *sorted;
int *roots;

int compare(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);
}

int createNode(void) {
    if (nodeCount >= capacity) {
        fprintf(stderr, "Node capacity exceeded.\n");
        exit(EXIT_FAILURE);
    }

    int id = ++nodeCount;
    tree[id] = (Node){0, 0, 0};
    return id;
}

int update(int previous, int low, int high, int position) {
    int current = createNode();

    tree[current] = tree[previous];
    tree[current].count++;

    if (low == high)
        return current;

    int mid = low + (high - low) / 2;

    if (position <= mid) {
        tree[current].left = update(
            tree[previous].left,
            low, mid, position
        );
    } else {
        tree[current].right = update(
            tree[previous].right,
            mid + 1, high, position
        );
    }

    return current;
}

int kthSmallest(int leftRoot, int rightRoot,
                int low, int high, int k) {
    if (low == high)
        return low;

    int leftCount =
        tree[tree[rightRoot].left].count -
        tree[tree[leftRoot].left].count;

    int mid = low + (high - low) / 2;

    if (k <= leftCount) {
        return kthSmallest(
            tree[leftRoot].left,
            tree[rightRoot].left,
            low, mid, k
        );
    }

    return kthSmallest(
        tree[leftRoot].right,
        tree[rightRoot].right,
        mid + 1, high,
        k - leftCount
    );
}

int main(void) {
    int n, q;

    printf("Enter array size: ");

    if (scanf("%d", &n) != 1 || n <= 0 || n > 100000) {
        printf("Invalid array size.\n");
        return 1;
    }

    values = malloc(n * sizeof(int));
    sorted = malloc(n * sizeof(int));
    roots = calloc(n + 1, sizeof(int));

    if (!values || !sorted || !roots) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    printf("Enter array elements:\n");

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &values[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        sorted[i] = values[i];
    }

    qsort(sorted, n, sizeof(int), compare);

    int unique = 0;

    for (int i = 0; i < n; i++) {
        if (unique == 0 || sorted[i] != sorted[unique - 1])
            sorted[unique++] = sorted[i];
    }

    int levels = 1;

    while ((1LL << levels) < unique)
        levels++;

    capacity = 1 + n * (levels + 1);

    tree = calloc(capacity, sizeof(Node));

    if (!tree) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    for (int i = 1; i <= n; i++) {
        int low = 0, high = unique - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (sorted[mid] == values[i - 1]) {
                roots[i] = update(
                    roots[i - 1], 0, unique - 1, mid
                );
                break;
            }

            if (sorted[mid] < values[i - 1])
                low = mid + 1;
            else
                high = mid - 1;
        }
    }

    printf("Enter number of queries: ");

    if (scanf("%d", &q) != 1 || q < 0) {
        printf("Invalid query count.\n");
        return 1;
    }

    printf("Enter queries: left right k (1-based indexing)\n");

    for (int i = 0; i < q; i++) {
        int l, r, k;

        if (scanf("%d %d %d", &l, &r, &k) != 3 ||
            l < 1 || r > n || l > r ||
            k < 1 || k > r - l + 1) {
            printf("Invalid query.\n");
            continue;
        }

        int index = kthSmallest(
            roots[l - 1],
            roots[r],
            0, unique - 1,
            k
        );

        printf("K-th smallest element: %d\n", sorted[index]);
    }

    free(values);
    free(sorted);
    free(roots);
    free(tree);

    return 0;
}
