#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int point[2];
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int x, int y)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->point[0] = x;
    node->point[1] = y;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Node* insert(struct Node* root, int x, int y, int depth)
{
    if(root == NULL)
        return createNode(x, y);
    int cd = depth % 2;
    if((cd == 0 && x < root->point[0]) ||
       (cd == 1 && y < root->point[1]))
    {
        root->left = insert(root->left, x, y, depth + 1);
    }
    else
    {
        root->right = insert(root->right, x, y, depth + 1);
    }
    return root;
}
void preorder(struct Node* root)
{
    if(root)
    {
        printf("(%d,%d) ", root->point[0], root->point[1]);
        preorder(root->left);
        preorder(root->right);
    }
}
int main()
{
    struct Node* root = NULL;
    root = insert(root, 3, 6, 0);
    root = insert(root, 17, 15, 0);
    root = insert(root, 13, 15, 0);
    root = insert(root, 6, 12, 0);
    root = insert(root, 9, 1, 0);
    printf("KD Tree (Preorder): ");
    preorder(root);
    return 0;
}
