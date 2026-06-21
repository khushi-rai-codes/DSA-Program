#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int key;
    int degree;
    struct Node *parent;
    struct Node *child;
    struct Node *sibling;
};
struct Node* createNode(int key)
{
    struct Node* node =
        (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->degree = 0;
    node->parent = NULL;
    node->child = NULL;
    node->sibling = NULL;
    return node;
}

void display(struct Node* root)
{
    while(root)
    {
        printf("%d ", root->key);
        root = root->sibling;
    }
}
int main()
{
    struct Node* heap = createNode(10);
    heap->sibling = createNode(20);
    heap->sibling->sibling = createNode(30);
    printf("Binomial Heap Elements: ");
    display(heap);
    return 0;
}
