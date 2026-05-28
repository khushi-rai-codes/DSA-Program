#include<stdio.h>
#define SIZE 5
int queue[SIZE];
int front = -1;
int rear = -1;
void enqueue(int value)
{
    if((rear + 1) % SIZE == front)
    {
        printf("Queue Overflow\n");
        return;
    }
    if(front == -1)
        front = 0;
    rear = (rear + 1) % SIZE;
    queue[rear] = value;
    printf("%d inserted into queue\n", value);
}
void dequeue()
{
    if(front == -1)
    {
        printf("Queue Underflow\n");
        return;
    }
    printf("%d removed from queue\n", queue[front]);
    if(front == rear)
    {
        front = rear = -1;
    }
    else
    {
        front = (front + 1) % SIZE;
    }
}
void display()
{
    if(front == -1)
    {
        printf("Queue is empty\n");
        return;
    }
    int i = front;
    printf("Queue elements:\n");
    while(i != rear)
    {
        printf("%d ", queue[i]);
        i = (i + 1) % SIZE;
    }
    printf("%d\n", queue[rear]);
}
int main()
{
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    display();
    enqueue(40);
    enqueue(50);
    display();
    return 0;
}
