#include <stdio.h>
#include <stdlib.h>

#define MAX_KEYS 3

typedef struct Node {
    int leaf;
    int n;
    int keys[MAX_KEYS + 1];
    struct Node *child[MAX_KEYS + 2];
    struct Node *next;
} Node;

typedef struct {
    int split;
    int key;
    Node *right;
} Result;

Node *createNode(int leaf) {
    Node *node = calloc(1, sizeof(Node));
    if (!node) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    node->leaf = leaf;
    return node;
}

int firstKey(Node *node) {
    while (!node->leaf)
        node = node->child[0];

    return node->keys[0];
}

Result insertRecursive(Node *node, int key) {
    Result result = {0, 0, NULL};

    if (node->leaf) {
        int i = node->n - 1;

        while (i >= 0 && node->keys[i] > key) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = key;
        node->n++;

        if (node->n <= MAX_KEYS)
            return result;

        Node *right = createNode(1);
        right->n = 2;

        right->keys[0] = node->keys[2];
        right->keys[1] = node->keys[3];

        node->n = 2;

        right->next = node->next;
        node->next = right;

        result.split = 1;
        result.key = right->keys[0];
        result.right = right;

        return result;
    }

    int i = 0;

    while (i < node->n && key >= node->keys[i])
        i++;

    Result childResult =
        insertRecursive(node->child[i], key);

    if (!childResult.split)
        return result;

    for (int j = node->n; j > i; j--)
        node->keys[j] = node->keys[j - 1];

    for (int j = node->n + 1; j > i + 1; j--)
        node->child[j] = node->child[j - 1];

    node->keys[i] = childResult.key;
    node->child[i + 1] = childResult.right;
    node->n++;

    if (node->n <= MAX_KEYS)
        return result;

    Node *right = createNode(0);
    int promoted = node->keys[2];

    right->n = 1;
    right->keys[0] = node->keys[3];

    right->child[0] = node->child[3];
    right->child[1] = node->child[4];

    node->n = 2;

    result.split = 1;
    result.key = promoted;
    result.right = right;

    return result;
}

Node *insert(Node *root, int key) {
    if (!root) {
        root = createNode(1);
        root->keys[0] = key;
        root->n = 1;
        return root;
    }

    Result result = insertRecursive(root, key);

    if (result.split) {
        Node *newRoot = createNode(0);

        newRoot->keys[0] = result.key;
        newRoot->child[0] = root;
        newRoot->child[1] = result.right;
        newRoot->n = 1;

        return newRoot;
    }

    return root;
}

int search(Node *root, int key) {
    while (root && !root->leaf) {
        int i = 0;

        while (i < root->n && key >= root->keys[i])
            i++;

        root = root->child[i];
    }

    if (!root)
        return 0;

    for (int i = 0; i < root->n; i++) {
        if (root->keys[i] == key)
            return 1;
    }

    return 0;
}

void displayLeaves(Node *root) {
    if (!root)
        return;

    while (!root->leaf)
        root = root->child[0];

    printf("B+ Tree Leaf Sequence: ");

    while (root) {
        printf("[ ");

        for (int i = 0; i < root->n; i++)
            printf("%d ", root->keys[i]);

        printf("] ");
        root = root->next;
    }

    printf("\n");
}

int main() {
    Node *root = NULL;

    int values[] = {
        15, 5, 25, 35, 10, 20, 30, 40, 45, 50
    };

    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++)
        root = insert(root, values[i]);

    displayLeaves(root);

    int key = 30;

    if (search(root, key))
        printf("%d found in B+ Tree.\n", key);
    else
        printf("%d not found.\n", key);

    return 0;
}
