#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ALPHABET_SIZE 26
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};
struct TrieNode* createNode()
{
    struct TrieNode *node =
        (struct TrieNode*)malloc(sizeof(struct TrieNode));
    node->isEndOfWord = 0;
    for(int i = 0; i < ALPHABET_SIZE; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}
void insert(struct TrieNode *root, char *key)
{
    struct TrieNode *current = root;

    for(int i = 0; key[i] != '\0'; i++)
    {
        int index = key[i] - 'a';

        if(current->children[index] == NULL)
        {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = 1;
}
int search(struct TrieNode *root, char *key)
{
    struct TrieNode *current = root;
    for(int i = 0; key[i] != '\0'; i++)
    {
        int index = key[i] - 'a';
        if(current->children[index] == NULL)
            return 0;
        current = current->children[index];
    }
    return current != NULL && current->isEndOfWord;
}
int main()
{
    struct TrieNode *root = createNode();
    insert(root, "cat");
    insert(root, "dog");
    insert(root, "apple");
    printf("cat: %s\n",
           search(root, "cat") ? "Found" : "Not Found");
    printf("bat: %s\n",
           search(root, "bat") ? "Found" : "Not Found");
    return 0;
}
