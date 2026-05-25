#include<stdio.h>
#include<stdlib.h>
struct Node
{
    int data;
    struct Node *next;
};
struct Node *top = NULL;
void push(int value)
{
    struct Node *newNode;
    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    top = newNode;
    printf("%d pushed into stack\n", value);
}
void pop()
{
    if(top == NULL)
    {
        printf("Stack Underflow\n");
        return;
    }
    struct Node *temp = top;
    printf("%d popped from stack\n", top->data);
    top = top->next;
    free(temp);
}
void display()
{
    struct Node *temp = top;
    if(temp == NULL)
    {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements:\n");
    while(temp != NULL)
    {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}
int main()
{
    push(10);
    push(20);
    push(30);
    display();
    pop();
    display();
    return 0;
}
