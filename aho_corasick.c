#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET 26
#define MAX_NODES 100
typedef struct
{
    int child[ALPHABET];
    int fail;
    int output;
} Node;
Node trie[MAX_NODES];
int nodeCount = 1;
void initializeNode(int index)
{
    for (int i = 0; i < ALPHABET; i++)
        trie[index].child[i] = -1;
    trie[index].fail = 0;
    trie[index].output = 0;
}
void insertPattern(const char *pattern)
{
    int current = 0;
    for (int i = 0; pattern[i] != '\0'; i++)
    {
        int index = pattern[i] - 'a';
        if (trie[current].child[index] == -1)
        {
            trie[current].child[index] = nodeCount;
            initializeNode(nodeCount);
            nodeCount++;
        }
        current = trie[current].child[index];
    }
    trie[current].output++;
}
void buildFailureLinks()
{
    int queue[MAX_NODES];
    int front = 0;
    int rear = 0;
    for (int i = 0; i < ALPHABET; i++)
    {
        int child = trie[0].child[i];
        if (child != -1)
        {
            trie[child].fail = 0;
            queue[rear++] = child;
        }
        else
        {
            trie[0].child[i] = 0;
        }
    }
    while (front < rear)
    {
        int current = queue[front++];
        for (int i = 0; i < ALPHABET; i++)
        {
            int child = trie[current].child[i];
            if (child != -1)
            {
                trie[child].fail =
                    trie[trie[current].fail].child[i];
                trie[child].output +=
                    trie[trie[child].fail].output;
                queue[rear++] = child;
            }
            else
            {
                trie[current].child[i] =
                    trie[trie[current].fail].child[i];
            }
        }
    }
}
void searchText(const char *text)
{
    int current = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        int index = text[i] - 'a';
        current = trie[current].child[index];
        if (trie[current].output > 0)
        {
            printf(
                "Pattern found ending at index %d\n",
                i
            );
        }
    }
}
int main()
{
    initializeNode(0);
    const char *patterns[] =
    {
        "he",
        "she",
        "his",
        "hers"
    };
    int patternCount =
        sizeof(patterns) / sizeof(patterns[0]);
    for (int i = 0; i < patternCount; i++)
        insertPattern(patterns[i]);
    buildFailureLinks();
    char text[] = "ahishers";
    printf("Text: %s\n\n", text);
    searchText(text);
    return 0;
}
