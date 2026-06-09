#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
struct Node *last = NULL;
void insertEnd(int value)
{
    struct Node *newNode =
        (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    if(last == NULL)
    {
        last = newNode;
        last->next = last;
        return;
    }
    newNode->next = last->next;
    last->next = newNode;
    last = newNode;
}
void display()
{
    if(last == NULL)
    {
        printf("List is Empty\n");
        return;
    }
    struct Node *temp = last->next;
    do
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    while(temp != last->next);
    printf("\n");
}
int main()
{
    insertEnd(10);
    insertEnd(20);
    insertEnd(30);
    insertEnd(40);
    printf("Circular Linked List:\n");
    display();
    return 0;
}
