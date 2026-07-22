#include <stdio.h>
void cycleSort(int arr[], int n)
{
    int writes = 0;
    for (int cycleStart = 0; cycleStart <= n - 2; cycleStart++)
    {
        int item = arr[cycleStart];
        int pos = cycleStart;
        for (int i = cycleStart + 1; i < n; i++)
            if (arr[i] < item)
                pos++;
        if (pos == cycleStart)
            continue;
        while (item == arr[pos])
            pos++;
        if (pos != cycleStart)
        {
            int temp = item;
            item = arr[pos];
            arr[pos] = temp;
            writes++;
        }
        while (pos != cycleStart)
        {
            pos = cycleStart;
            for (int i = cycleStart + 1; i < n; i++)
                if (arr[i] < item)
                    pos++;
            while (item == arr[pos])
                pos++;
            if (item != arr[pos])
            {
                int temp = item;
                item = arr[pos];
                arr[pos] = temp;
                writes++;
            }
        }
    }
    printf("Sorted Array:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\nTotal Writes: %d\n", writes);
}
int main()
{
    int arr[] = {20, 40, 50, 10, 30};
    int n = sizeof(arr) / sizeof(arr[0]);
    cycleSort(arr, n);
    return 0;
}
