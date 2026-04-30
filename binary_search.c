#include<stdio.h>
int main()
{
    int n, key;
    printf("Enter size of array: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter sorted array elements: ");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    printf("Enter element to search: ");
    scanf("%d", &key);
    int low = 0, high = n - 1, found = 0;
    while(low <= high)
    {
        int mid = (low + high) / 2;
        if(arr[mid] == key)
        {
            printf("Element found at position %d", mid + 1);
            found = 1;
            break;
        }
        else if(arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    if(found == 0)
        printf("Element not found");
    return 0;
}
