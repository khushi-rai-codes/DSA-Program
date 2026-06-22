#include <stdio.h>
#include <stdlib.h>
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
};
struct Node* createNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node;
    node->right = node;
    return node;
}
void insert(struct Node **min, int key)
{
    struct Node *node = createNode(key);
    if(*min == NULL)
    {
        *min = node;
    }
    else
    {
        node->right = (*min)->right;
        node->left = *min;

        (*min)->right->left = node;
        (*min)->right = node;

        if(node->key < (*min)->key)
            *min = node;
    }
}
void display(struct Node *min)
{
    if(min == NULL)
        return;
    struct Node *temp = min;
    printf("Heap Elements: ");
    do
    {
        printf("%d ", temp->key);
        temp = temp->right;
    }
    while(temp != min);
    printf("\n");
}
int main()
{
    struct Node *min = NULL;
    insert(&min, 20);
    insert(&min, 10);
    insert(&min, 30);
    insert(&min, 5);
    display(min);
    return 0;
}
