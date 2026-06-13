#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    char color;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int data)
{
    struct Node* node =
        (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->color = 'R';
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Node* insert(struct Node* root, int data)
{
    if(root == NULL)
        return createNode(data);
    if(data < root->data)
        root->left = insert(root->left, data);
    else if(data > root->data)
        root->right = insert(root->right, data);
    return root;
}
void inorder(struct Node* root)
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("%d(%c) ", root->data, root->color);
        inorder(root->right);
    }
}
int main()
{
    struct Node* root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root->color = 'B';
    printf("Red Black Tree (Simplified):\n");
    inorder(root);
    return 0;
}
