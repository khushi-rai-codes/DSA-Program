#include <stdio.h>
#include <stdlib.h>
struct Interval
{
    int low;
    int high;
};
struct Node
{
    struct Interval interval;
    int max;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int low, int high)
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    node->interval.low = low;
    node->interval.high = high;
    node->max = high;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Node* insert(struct Node *root, int low, int high)
{
    if(root == NULL)
        return createNode(low, high);
    if(low < root->interval.low)
        root->left = insert(root->left, low, high);
    else
        root->right = insert(root->right, low, high);
    if(root->max < high)
        root->max = high;
    return root;
}
void inorder(struct Node *root)
{
    if(root)
    {
        inorder(root->left);
        printf("[%d,%d] Max=%d\n",
               root->interval.low,
               root->interval.high,
               root->max);
        inorder(root->right);
    }
}
int main()
{
    struct Node *root = NULL;
    root = insert(root, 15, 20);
    root = insert(root, 10, 30);
    root = insert(root, 17, 19);
    root = insert(root, 5, 20);
    root = insert(root, 12, 15);
    printf("Interval Tree:\n");
    inorder(root);
    return 0;
}
