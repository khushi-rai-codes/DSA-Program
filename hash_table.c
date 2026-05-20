#include<stdio.h>
#define SIZE 10
int hashTable[SIZE];
void initialize()
{
    for(int i = 0; i < SIZE; i++)
    {
        hashTable[i] = -1;
    }
}
int hashFunction(int key)
{
    return key % SIZE;
}
void insert(int key)
{
    int index = hashFunction(key);

    while(hashTable[index] != -1)
    {
        index = (index + 1) % SIZE;
    }
    hashTable[index] = key;
    printf("%d inserted at index %d\n", key, index);
}
void search(int key)
{
    int index = hashFunction(key);
    int start = index;
    while(hashTable[index] != -1)
    {
        if(hashTable[index] == key)
        {
            printf("%d found at index %d\n", key, index);
            return;
        }
        index = (index + 1) % SIZE;
        if(index == start)
            break;
    }
    printf("%d not found\n", key);
}
void display()
{
    printf("Hash Table:\n");

    for(int i = 0; i < SIZE; i++)
    {
        printf("Index %d : %d\n", i, hashTable[i]);
    }
}
int main()
{
    initialize();
    insert(15);
    insert(25);
    insert(35);
    insert(20);
    display();
    search(25);
    search(50);
    return 0;
}
