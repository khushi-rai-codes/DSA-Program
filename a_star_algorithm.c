#include <stdio.h>
#include <stdlib.h>

#define ROWS 5
#define COLS 5
#define INF 9999

typedef struct
{
    int row;
    int col;
    int g;
    int h;
    int f;
} Node;

int heuristic(int row, int col, int goalRow, int goalCol)
{
    return abs(row - goalRow) + abs(col - goalCol);
}

int isValid(int row, int col, int grid[ROWS][COLS])
{
    return row >= 0 &&
           row < ROWS &&
           col >= 0 &&
           col < COLS &&
           grid[row][col] == 0;
}

void printPath(int parentRow[ROWS][COLS],
               int parentCol[ROWS][COLS],
               int startRow,
               int startCol,
               int goalRow,
               int goalCol)
{
    int pathRow[ROWS * COLS];
    int pathCol[ROWS * COLS];
    int length = 0;

    int row = goalRow;
    int col = goalCol;

    while (!(row == startRow && col == startCol))
    {
        pathRow[length] = row;
        pathCol[length] = col;
        length++;

        int previousRow = parentRow[row][col];
        int previousCol = parentCol[row][col];

        row = previousRow;
        col = previousCol;
    }

    pathRow[length] = startRow;
    pathCol[length] = startCol;
    length++;

    printf("Shortest Path:\n");

    for (int i = length - 1; i >= 0; i--)
    {
        printf("(%d, %d)", pathRow[i], pathCol[i]);

        if (i != 0)
            printf(" -> ");
    }

    printf("\n");
}

void aStar(int grid[ROWS][COLS],
           int startRow,
           int startCol,
           int goalRow,
           int goalCol)
{
    int gScore[ROWS][COLS];
    int closed[ROWS][COLS] = {0};

    int parentRow[ROWS][COLS];
    int parentCol[ROWS][COLS];

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            gScore[i][j] = INF;
            parentRow[i][j] = -1;
            parentCol[i][j] = -1;
        }
    }

    gScore[startRow][startCol] = 0;

    int directions[4][2] =
    {
        {-1, 0},
        {1, 0},
        {0, -1},
        {0, 1}
    };

    while (1)
    {
        int currentRow = -1;
        int currentCol = -1;
        int lowestF = INF;

        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLS; j++)
            {
                if (!closed[i][j] && gScore[i][j] != INF)
                {
                    int h = heuristic(
                        i,
                        j,
                        goalRow,
                        goalCol
                    );

                    int f = gScore[i][j] + h;

                    if (f < lowestF)
                    {
                        lowestF = f;
                        currentRow = i;
                        currentCol = j;
                    }
                }
            }
        }

        if (currentRow == -1)
        {
            printf("No path exists.\n");
            return;
        }

        if (currentRow == goalRow &&
            currentCol == goalCol)
        {
            printPath(
                parentRow,
                parentCol,
                startRow,
                startCol,
                goalRow,
                goalCol
            );

            printf("Path Cost: %d\n",
                   gScore[goalRow][goalCol]);

            return;
        }

        closed[currentRow][currentCol] = 1;

        for (int i = 0; i < 4; i++)
        {
            int newRow =
                currentRow + directions[i][0];

            int newCol =
                currentCol + directions[i][1];

            if (!isValid(newRow, newCol, grid))
                continue;

            if (closed[newRow][newCol])
                continue;

            int newG = gScore[currentRow][currentCol] + 1;

            if (newG < gScore[newRow][newCol])
            {
                gScore[newRow][newCol] = newG;

                parentRow[newRow][newCol] =
                    currentRow;

                parentCol[newRow][newCol] =
                    currentCol;
            }
        }
    }
}

int main()
{
    int grid[ROWS][COLS] =
    {
        {0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0}
    };

    int startRow = 0;
    int startCol = 0;

    int goalRow = 4;
    int goalCol = 4;

    printf("A* Search Algorithm\n");
    printf("Start: (%d, %d)\n",
           startRow, startCol);

    printf("Goal: (%d, %d)\n\n",
           goalRow, goalCol);

    aStar(
        grid,
        startRow,
        startCol,
        goalRow,
        goalCol
    );

    return 0;
}
