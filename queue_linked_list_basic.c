#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Queue {
    struct Node *front;
    struct Node *rear;
};

void enqueue(struct Queue *q, int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = value;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }

    printf("%d inserted into queue.\n", value);
}

void dequeue(struct Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node *temp = q->front;

    printf("%d removed from queue.\n", temp->data);

    q->front = q->front->next;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

void display(struct Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty.\n");
        return;
    }

    struct Node *temp = q->front;

    printf("Queue: ");

    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

int main() {
    struct Queue q = {NULL, NULL};

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    display(&q);

    dequeue(&q);

    display(&q);

    return 0;
}
