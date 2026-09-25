#include <stdio.h>

#define MAX 10

int main() {
    int matrix[MAX][MAX];
    int rows, cols;
    int nonZero = 0;

    printf("Enter rows and columns: ");
    scanf("%d %d", &rows, &cols);

    printf("Enter matrix elements:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);

            if (matrix[i][j] != 0) {
                nonZero++;
            }
        }
    }

    printf("\nOriginal Matrix:\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    printf("\nSparse Matrix Representation:\n");
    printf("Row\tColumn\tValue\n");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                printf("%d\t%d\t%d\n", i, j, matrix[i][j]);
            }
        }
    }

    printf("\nTotal non-zero elements: %d\n", nonZero);

    if (nonZero < (rows * cols) / 2) {
        printf("The matrix is sparse.\n");
    } else {
        printf("The matrix is not sparse.\n");
    }

    return 0;
}
