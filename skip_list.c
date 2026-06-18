#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEVEL 4
struct Node
{
    int data;
    struct Node *forward[MAX_LEVEL + 1];
};
struct Node *header;
struct Node* createNode(int data)
{
    struct Node *node =
        (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    for(int i = 0; i <= MAX_LEVEL; i++)
        node->forward[i] = NULL;
    return node;
}
int randomLevel()
{
    int level = 0;
    while(rand() % 2 && level < MAX_LEVEL)
        level++;
    return level;
}
void insert(int value)
{
    struct Node *update[MAX_LEVEL + 1];
    struct Node *current = header;
    for(int i = MAX_LEVEL; i >= 0; i--)
    {
        while(current->forward[i] &&
              current->forward[i]->data < value)
        {
            current = current->forward[i];
        }

        update[i] = current;
    }
    int level = randomLevel();
    struct Node *newNode = createNode(value);
    for(int i = 0; i <= level; i++)
    {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
}
void display()
{
    struct Node *current = header->forward[0];
    printf("Skip List: ");
    while(current)
    {
        printf("%d ", current->data);
        current = current->forward[0];
    }
    printf("\n");
}
int main()
{
    srand(time(NULL));
    header = createNode(-1);
    insert(10);
    insert(20);
    insert(15);
    insert(30);
    display();
    return 0;
}
