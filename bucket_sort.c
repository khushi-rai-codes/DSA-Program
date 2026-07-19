#include <stdio.h>
void bucketSort(float arr[], int n)
{
    float bucket[10][10];
    int count[10] = {0};
    for (int i = 0; i < n; i++)
    {
        int index = arr[i] * 10;
        bucket[index][count[index]++] = arr[i];
    }
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < count[i] - 1; j++)
        {
            for (int k = j + 1; k < count[i]; k++)
            {
                if (bucket[i][j] > bucket[i][k])
                {
                    float temp = bucket[i][j];
                    bucket[i][j] = bucket[i][k];
                    bucket[i][k] = temp;
                }
            }
        }
    }
    int index = 0;
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < count[i]; j++)
        {
            arr[index++] = bucket[i][j];
        }
    }
}
int main()
{
    float arr[] = {0.42, 0.32, 0.23, 0.52, 0.25, 0.47, 0.51};
    int n = sizeof(arr) / sizeof(arr[0]);
    bucketSort(arr, n);
    printf("Sorted Array:\n");
    for (int i = 0; i < n; i++)
        printf("%.2f ", arr[i]);
    return 0;
}
