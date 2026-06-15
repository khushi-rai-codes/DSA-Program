#include <stdio.h>
#include <stdlib.h>
#define MAX 3
struct BTreeNode
{
    int keys[MAX];
    int numKeys;
    struct BTreeNode *children[MAX + 1];
    int leaf;
};
struct BTreeNode* createNode(int leaf)
{
    struct BTreeNode* node =
        (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
    node->leaf = leaf;
    node->numKeys = 0;
    for(int i = 0; i <= MAX; i++)
        node->children[i] = NULL;
    return node;
}
void insertSimple(struct BTreeNode* root, int key)
{
    root->keys[root->numKeys++] = key;
}
void display(struct BTreeNode* root)
{
    printf("B-Tree Keys: ");
    for(int i = 0; i < root->numKeys; i++)
        printf("%d ", root->keys[i]);
    printf("\n");
}
int main()
{
    struct BTreeNode* root = createNode(1);
    insertSimple(root, 10);
    insertSimple(root, 20);
    insertSimple(root, 30);
    display(root);
    return 0;
}
