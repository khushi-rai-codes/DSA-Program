#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TREE_HT 100
struct MinHeapNode
{
    char data;
    unsigned frequency;
    struct MinHeapNode *left;
    struct MinHeapNode *right;
};
struct MinHeap
{
    unsigned size;
    unsigned capacity;
    struct MinHeapNode **array;
};
struct MinHeapNode *createNode(char data, unsigned frequency)
{
    struct MinHeapNode *node =
        (struct MinHeapNode *)malloc(sizeof(struct MinHeapNode));
    node->data = data;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct MinHeap *createMinHeap(unsigned capacity)
{
    struct MinHeap *heap =
        (struct MinHeap *)malloc(sizeof(struct MinHeap));
    heap->size = 0;
    heap->capacity = capacity;
    heap->array =
        (struct MinHeapNode **)malloc(
            capacity * sizeof(struct MinHeapNode *)
        );
    return heap;
}
void swapNodes(
    struct MinHeapNode **a,
    struct MinHeapNode **b
)
{
    struct MinHeapNode *temp = *a;
    *a = *b;
    *b = temp;
}
void minHeapify(struct MinHeap *heap, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if (left < (int)heap->size &&
        heap->array[left]->frequency <
        heap->array[smallest]->frequency)
    {
        smallest = left;
    }

    if (right < (int)heap->size &&
        heap->array[right]->frequency <
        heap->array[smallest]->frequency)
    {
        smallest = right;
    }
    if (smallest != index)
    {
        swapNodes(
            &heap->array[smallest],
            &heap->array[index]
        );
        minHeapify(heap, smallest);
    }
}
struct MinHeapNode *extractMin(struct MinHeap *heap)
{
    struct MinHeapNode *temp = heap->array[0];
    heap->array[0] =
        heap->array[heap->size - 1];
    heap->size--;
    minHeapify(heap, 0);
    return temp;
}
void insertMinHeap(
    struct MinHeap *heap,
    struct MinHeapNode *node
)
{
    int i = heap->size;
    heap->size++;
    while (i > 0 &&
           node->frequency <
           heap->array[(i - 1) / 2]->frequency)
    {
        heap->array[i] =
            heap->array[(i - 1) / 2];

        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}
void buildMinHeap(struct MinHeap *heap)
{
    int i;

    for (i = (heap->size - 2) / 2; i >= 0; i--)
        minHeapify(heap, i);
}
struct MinHeap *buildHeap(
    char data[],
    int frequency[],
    int size
)
{
    struct MinHeap *heap = createMinHeap(size);

    for (int i = 0; i < size; i++)
    {
        heap->array[i] =
            createNode(data[i], frequency[i]);
    }
    heap->size = size;
    buildMinHeap(heap);
    return heap;
}
struct MinHeapNode *buildHuffmanTree(
    char data[],
    int frequency[],
    int size
)
{
    struct MinHeap *heap =
        buildHeap(data, frequency, size);
    while (heap->size > 1)
    {
        struct MinHeapNode *left =
            extractMin(heap);
        struct MinHeapNode *right =
            extractMin(heap);
        struct MinHeapNode *parent =
            createNode(
                '$',
                left->frequency +
                right->frequency
            );

        parent->left = left;
        parent->right = right;
        insertMinHeap(heap, parent);
    }
    return extractMin(heap);
}
void printCodes(
    struct MinHeapNode *root,
    int code[],
    int top
)
{
    if (root->left)
    {
        code[top] = 0;
        printCodes(root->left, code, top + 1);
    }
    if (root->right)
    {
        code[top] = 1;
        printCodes(root->right, code, top + 1);
    }
    if (!root->left && !root->right)
    {
        printf("%c: ", root->data);
        for (int i = 0; i < top; i++)
            printf("%d", code[i]);
        printf("\n");
    }
}
int main()
{
    char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequency[] = {
        5, 9, 12, 13, 16, 45
    };
    int size =
        sizeof(data) / sizeof(data[0]);
    struct MinHeapNode *root =
        buildHuffmanTree(
            data,
            frequency,
            size
        );
    int code[MAX_TREE_HT];
    printf("Huffman Codes:\n");
    printCodes(root, code, 0);
    return 0;
}
