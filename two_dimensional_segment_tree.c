#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 4

int tree[2 * N][2 * M];

void build(int matrix[N][M]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            tree[N + i][M + j] = matrix[i][j];
        }
    }

    // Build column trees for leaf rows.
    for (int i = N; i < 2 * N; i++) {
        for (int j = M - 1; j > 0; j--) {
            tree[i][j] =
                tree[i][2 * j] + tree[i][2 * j + 1];
        }
    }

    // Build row trees.
    for (int i = N - 1; i > 0; i--) {
        for (int j = 1; j < 2 * M; j++) {
            tree[i][j] =
                tree[2 * i][j] + tree[2 * i + 1][j];
        }
    }
}

void update(int row, int col, int value) {
    int x = row + N;
    int y = col + M;

    for (int i = x; i > 0; i /= 2) {
        for (int j = y; j > 0; j /= 2) {
            if (i >= N) {
                if (j >= M) {
                    tree[i][j] = value;
                } else {
                    tree[i][j] =
                        tree[i][2 * j] +
                        tree[i][2 * j + 1];
                }
            } else {
                tree[i][j] =
                    tree[2 * i][j] +
                    tree[2 * i + 1][j];
            }
        }
    }
}

int queryRow(int row, int left, int right) {
    int result = 0;

    left += M;
    right += M;

    while (left < right) {
        if (left & 1)
            result += tree[row][left++];

        if (right & 1)
            result += tree[row][--right];

        left /= 2;
        right /= 2;
    }

    return result;
}

// Queries rectangle [r1, r2) x [c1, c2).
int rectangleSum(int r1, int c1, int r2, int c2) {
    int result = 0;

    r1 += N;
    r2 += N;

    while (r1 < r2) {
        if (r1 & 1)
            result += queryRow(r1++, c1, c2);

        if (r2 & 1)
            result += queryRow(--r2, c1, c2);

        r1 /= 2;
        r2 /= 2;
    }

    return result;
}

int main() {
    int matrix[N][M] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 16}
    };

    build(matrix);

    printf("Initial rectangle sum: %d\n",
           rectangleSum(0, 0, 2, 2));

    update(1, 1, 20);

    printf("After updating (1,1) to 20: %d\n",
           rectangleSum(0, 0, 2, 2));

    printf("Full matrix sum: %d\n",
           rectangleSum(0, 0, 4, 4));

    return 0;
}
