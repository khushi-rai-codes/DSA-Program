#include<stdio.h>
#include<stdlib.h>
struct Node
{
    char data;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(char data)
{
    struct Node* node =
        (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void inorder(struct Node* root)
{
    if(root)
    {
        inorder(root->left);
        printf("%c ", root->data);
        inorder(root->right);
    }
}
int main()
{
    struct Node* root = createNode('*');
    root->left = createNode('+');
    root->right = createNode('-');
    root->left->left = createNode('A');
    root->left->right = createNode('B');
    root->right->left = createNode('C');
    root->right->right = createNode('D');
    printf("Inorder Traversal:\n");
    inorder(root);
    return 0;
}
