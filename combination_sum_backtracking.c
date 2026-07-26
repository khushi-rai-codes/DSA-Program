#include <stdio.h>
void findCombinations(int arr[], int n, int index, int target)
{
    if (target == 0)
    {
        printf("\n");
        return;
    }
    if (index == n || target < 0)
        return;
    if (arr[index] <= target)
    {
        printf("%d ", arr[index]);
        findCombinations(arr, n, index, target - arr[index]);
    }
    findCombinations(arr, n, index + 1, target);
}
int main()
{
    int arr[] = {2, 3, 6, 7};
    int target = 7;
    int n = sizeof(arr) / sizeof(arr[0]);
    printf("Possible combinations:\n");
    findCombinations(arr, n, 0, target);
    return 0;
}
