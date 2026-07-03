#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_CHAR 26
struct Node
{
    struct Node *children[MAX_CHAR];
    int isEnd;
};
struct Node* createNode()
{
    struct Node *node = (struct Node*)malloc(sizeof(struct Node));
    for(int i = 0; i < MAX_CHAR; i++)
        node->children[i] = NULL;
    node->isEnd = 0;
    return node;
}
void insertSuffix(struct Node *root, char *suffix)
{
    struct Node *current = root;
    while(*suffix)
    {
        int index = *suffix - 'a';
        if(current->children[index] == NULL)
            current->children[index] = createNode();
        current = current->children[index];
        suffix++;
    }
    current->isEnd = 1;
}
void buildSuffixTrie(struct Node *root, char *text)
{
    int n = strlen(text);
    for(int i = 0; i < n; i++)
        insertSuffix(root, text + i);
}
int search(struct Node *root, char *pattern)
{
    struct Node *current = root;
    while(*pattern)
    {
        int index = *pattern - 'a';
        if(current->children[index] == NULL)
            return 0;      
      current = current->children[index];
        pattern++;
    }
    return 1;
}
int main()
{
    char text[] = "banana";
    struct Node *root = createNode();
    buildSuffixTrie(root, text);
    if(search(root, "ana"))
        printf("Pattern Found\n");
    else
        printf("Pattern Not Found\n");
    return 0;
}
