#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int data)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));

    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Node* buildTree(int arr[], int start, int end)
{
    if(start > end)
        return NULL;
    int maxIndex = start;
    for(int i = start + 1; i <= end; i++)
    {
        if(arr[i] > arr[maxIndex])
            maxIndex = i;
    }
    struct Node *root = createNode(arr[maxIndex]);
    root->left = buildTree(arr, start, maxIndex - 1);
    root->right = buildTree(arr, maxIndex + 1, end);
    return root;
}
void inorder(struct Node *root)
{
    if(root)
    {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}
int main()
{
    int arr[] = {3, 2, 6, 1, 9, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node *root = buildTree(arr, 0, n - 1);
    printf("Cartesian Tree (Inorder): ");
    inorder(root);
    return 0;
}
