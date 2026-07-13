#include <stdio.h>
int ternarySearch(int arr[], int left, int right, int key)
{
    while (left <= right)
    {
        int mid1 = left + (right - left) / 3;
        int mid2 = right - (right - left) / 3;
        if (arr[mid1] == key)
            return mid1;
        if (arr[mid2] == key)
            return mid2;
        if (key < arr[mid1])
            right = mid1 - 1;
        else if (key > arr[mid2])
            left = mid2 + 1;
        else
        {
            left = mid1 + 1;
            right = mid2 - 1;
        }
    }
    return -1;
}
int main()
{
    int arr[] = {5, 10, 15, 20, 25, 30, 35, 40, 45, 50};
    int n = sizeof(arr) / sizeof(arr[0]);
    int key;
    printf("Enter element to search: ");
    scanf("%d", &key);
    int result = ternarySearch(arr, 0, n - 1, key);
    if (result != -1)
        printf("Element found at index %d\n", result);
    else
        printf("Element not found\n");
    return 0;
}
