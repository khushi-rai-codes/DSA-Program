#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *createNode(int data) {
    struct Node *newNode =
        (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}

int hasCycle(struct Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return 1;
        }
    }

    return 0;
}

int cycleLength(struct Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            int length = 1;
            struct Node *current = slow->next;

            while (current != slow) {
                length++;
                current = current->next;
            }

            return length;
        }
    }

    return 0;
}

struct Node *findCycleStart(struct Node *head) {
    struct Node *slow = head;
    struct Node *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            slow = head;

            while (slow != fast) {
                slow = slow->next;
                fast = fast->next;
            }

            return slow;
        }
    }

    return NULL;
}

int main() {
    struct Node *head = createNode(10);
    head->next = createNode(20);
    head->next->next = createNode(30);
    head->next->next->next = createNode(40);
    head->next->next->next->next = createNode(50);

    /* Create a cycle:
       50 -> 30
    */
    head->next->next->next->next->next =
        head->next->next;

    if (hasCycle(head)) {
        printf("Cycle detected.\n");

        printf("Cycle length: %d\n", cycleLength(head));

        struct Node *start = findCycleStart(head);

        if (start != NULL) {
            printf("Cycle starts at node: %d\n", start->data);
        }
    } else {
        printf("No cycle detected.\n");
    }

    return 0;
}
