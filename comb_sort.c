#include <stdio.h>
void combSort(int arr[], int n)
{
    int gap = n;
    int swapped = 1;
    while (gap != 1 || swapped)
    {
        gap = (gap * 10) / 13;
        if (gap < 1)
            gap = 1;
        swapped = 0;
        for (int i = 0; i < n - gap; i++)
        {
            if (arr[i] > arr[i + gap])
            {
                int temp = arr[i];
                arr[i] = arr[i + gap];
                arr[i + gap] = temp;
                swapped = 1;
            }
        }
    }
}
int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    combSort(arr, n);
    printf("Sorted Array:\n");
    for(int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}
