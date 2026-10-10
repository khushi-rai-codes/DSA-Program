#include <stdio.h>
#include <limits.h>

#define MAX_N 1000
#define TREE_SIZE (4 * MAX_N)

int tree[TREE_SIZE];
int arr[MAX_N];
int n;

void build(int node, int start, int end) {
    if (start == end) {
        tree[node] = arr[start];
        return;
    }

    int mid = start + (end - start) / 2;

    build(2 * node, start, mid);
    build(2 * node + 1, mid + 1, end);

    tree[node] =
        tree[2 * node] < tree[2 * node + 1]
        ? tree[2 * node]
        : tree[2 * node + 1];
}

int query(int node, int start, int end,
          int left, int right) {
    if (right < start || end < left) {
        return INT_MAX;
    }

    if (left <= start && end <= right) {
        return tree[node];
    }

    int mid = start + (end - start) / 2;

    int a = query(2 * node, start, mid, left, right);
    int b = query(2 * node + 1, mid + 1, end, left, right);

    return a < b ? a : b;
}

void update(int node, int start, int end,
            int index, int value) {
    if (start == end) {
        arr[index] = value;
        tree[node] = value;
        return;
    }

    int mid = start + (end - start) / 2;

    if (index <= mid) {
        update(2 * node, start, mid, index, value);
    } else {
        update(2 * node + 1, mid + 1, end, index, value);
    }

    tree[node] =
        tree[2 * node] < tree[2 * node + 1]
        ? tree[2 * node]
        : tree[2 * node + 1];
}

int main(void) {
    printf("Enter number of elements (1-%d): ", MAX_N);

    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_N) {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d elements:\n", n);

    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Invalid input.\n");
            return 1;
        }
    }

    build(1, 0, n - 1);

    int choice;

    do {
        printf("\n1. Range minimum query\n");
        printf("2. Update element\n");
        printf("3. Exit\n");
        printf("Choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        if (choice == 1) {
            int left, right;

            printf("Enter range (left right, 0-based): ");

            if (scanf("%d %d", &left, &right) != 2 ||
                left < 0 || right >= n || left > right) {
                printf("Invalid range.\n");
                continue;
            }

            printf("Minimum = %d\n",
                   query(1, 0, n - 1, left, right));

        } else if (choice == 2) {
            int index, value;

            printf("Enter index and new value: ");

            if (scanf("%d %d", &index, &value) != 2 ||
                index < 0 || index >= n) {
                printf("Invalid index or input.\n");
                continue;
            }

            update(1, 0, n - 1, index, value);
            printf("Element updated successfully.\n");

        } else if (choice != 3) {
            printf("Invalid choice.\n");
        }

    } while (choice != 3);

    return 0;
}
