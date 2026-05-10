#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node* next;
};
struct Node* head = NULL;
void insert(int value)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if(head == NULL)
    {
        head = newNode;
    }
    else
    {
        struct Node* temp = head;
        while(temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}
void search(int key)
{
    struct Node* temp = head;
    int position = 1;
    while(temp != NULL)
    {
        if(temp->data == key)
        {
            printf("Element found at position %d\n", position);
            return;
        }
        temp = temp->next;
        position++;
    }
    printf("Element not found\n");
}
void display()
{
    struct Node* temp = head;
    printf("Linked List: ");
    while(temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
int main()
{
    insert(10);
    insert(20);
    insert(30);
    insert(40);
    display();
    search(30);
    return 0;
}
