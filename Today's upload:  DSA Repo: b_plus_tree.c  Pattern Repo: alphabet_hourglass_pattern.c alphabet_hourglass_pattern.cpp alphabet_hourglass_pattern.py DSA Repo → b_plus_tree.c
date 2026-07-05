#include <stdio.h>
#include <stdlib.h>
#define MAX_KEYS 3
struct BPlusNode
{
    int keys[MAX_KEYS];
    int keyCount;
    struct BPlusNode *children[MAX_KEYS + 1];
    int isLeaf;
    struct BPlusNode *next;
};
struct BPlusNode* createNode(int isLeaf)
{
    struct BPlusNode *node =
        (struct BPlusNode*)malloc(sizeof(struct BPlusNode));
    node->keyCount = 0;
    node->isLeaf = isLeaf;
    node->next = NULL;
    for(int i = 0; i <= MAX_KEYS; i++)
        node->children[i] = NULL;
    return node;
}
void insertLeaf(struct BPlusNode *leaf, int key)
{
    leaf->keys[leaf->keyCount++] = key;
}
void display(struct BPlusNode *leaf)
{
    printf("Leaf Node Keys: ");
    for(int i = 0; i < leaf->keyCount; i++)
        printf("%d ", leaf->keys[i]);
    printf("\n");
}
int main()
{
    struct BPlusNode *root = createNode(1);
    insertLeaf(root, 10);
    insertLeaf(root, 20);
    insertLeaf(root, 30);
    display(root);
    return 0;
}
