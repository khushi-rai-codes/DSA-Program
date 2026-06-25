#include <stdio.h>
#include <stdbool.h>
#define UNIVERSE_SIZE 16
struct VEBTree
{
    bool present[UNIVERSE_SIZE];
};
void initialize(struct VEBTree *tree)
{
    for(int i = 0; i < UNIVERSE_SIZE; i++)
        tree->present[i] = false;
}
void insert(struct VEBTree *tree, int key)
{
    if(key >= 0 && key < UNIVERSE_SIZE)
        tree->present[key] = true;
}
bool search(struct VEBTree *tree, int key)
{
    if(key >= 0 && key < UNIVERSE_SIZE)
        return tree->present[key];
    return false;
}
void display(struct VEBTree *tree)
{
    printf("Elements: ");
    for(int i = 0; i < UNIVERSE_SIZE; i++)
    {
        if(tree->present[i])
            printf("%d ", i);
    }
    printf("\n");
}
int main()
{
    struct VEBTree tree;
    initialize(&tree);
    insert(&tree, 2);
    insert(&tree, 5);
    insert(&tree, 8);
    insert(&tree, 12);
    display(&tree);
    printf("Search 8: %s\n",
           search(&tree, 8) ? "Found" : "Not Found");
    return 0;
}
