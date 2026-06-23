#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int key;
    struct Node *child;
    struct Node *sibling;
};
struct Node* createNode(int key)
{
    struct Node* node =
        (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}
struct Node* merge(struct Node* a, struct Node* b)
{
    if(a == NULL) return b;
    if(b == NULL) return a;
    if(a->key > b->key)
    {
        struct Node* temp = a;
        a = b;
        b = temp;
    }
    b->sibling = a->child;
    a->child = b;
    return a;
}
void display(struct Node* root)
{
    if(root == NULL)
        return;
    printf("%d ", root->key);
    display(root->child);
    display(root->sibling);
}
int main()
{
    struct Node* heap = createNode(10);
    heap = merge(heap, createNode(20));
    heap = merge(heap, createNode(5));
    heap = merge(heap, createNode(15));
    printf("Pairing Heap Elements: ");
    display(heap);
    return 0;
}
