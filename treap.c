#include <stdio.h>
#include <stdlib.h>
#include <time.h>
struct Node
{
    int key;
    int priority;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->priority = rand() % 100;
    node->left = NULL;
    node->right = NULL;
    return node;
}
void inorder(struct Node* root)
{
    if(root)
    {
        inorder(root->left);
        printf("(%d,%d) ", root->key, root->priority);
        inorder(root->right);
    }
}
struct Node* insert(struct Node* root, int key)
{
    if(root == NULL)
        return createNode(key);
    if(key < root->key)
        root->left = insert(root->left, key);
    else if(key > root->key)
        root->right = insert(root->right, key);
    return root;
}
int main()
{
    srand(time(NULL));
    struct Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    printf("Treap (Simplified): ");
    inorder(root);
    return 0;
}
