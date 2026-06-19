#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int data;
    struct Node *left;
    struct Node *right;
    int rightThread;
};
struct Node* createNode(int data)
{
    struct Node* node =
        (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->rightThread = 0;
    return node;
}
void inorder(struct Node* root)
{
    if(root == NULL)
        return;
    inorder(root->left);
    printf("%d ", root->data);
    if(!root->rightThread)
        inorder(root->right);
}
int main()
{
    struct Node* root = createNode(20);
    root->left = createNode(10);
    root->right = createNode(30);
    root->left->right = root;
    root->left->rightThread = 1;
    printf("Inorder Traversal: ");
    inorder(root);
    return 0;
}
