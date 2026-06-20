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
    struct Node* node =
        (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct Node* rightRotate(struct Node* x)
{
    struct Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}
struct Node* leftRotate(struct Node* x)
{
    struct Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
struct Node* insert(struct Node* root, int key)
{
    if(root == NULL)
        return createNode(key);
    if(key < root->data)
        root->left = insert(root->left, key);
    else if(key > root->data)
        root->right = insert(root->right, key);
    return root;
}
void inorder(struct Node* root)
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
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    printf("Splay Tree (Simplified): ");
    inorder(root);
    return 0;
}
