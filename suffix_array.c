#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Suffix
{
    int index;
    char *suffix;
};
int compare(const void *a, const void *b)
{
    return strcmp(((struct Suffix *)a)->suffix,
                  ((struct Suffix *)b)->suffix);
}
void buildSuffixArray(char text[])
{
    int n = strlen(text);
    struct Suffix suffixes[n];
    for(int i = 0; i < n; i++)
    {
        suffixes[i].index = i;
        suffixes[i].suffix = text + i;
    }
    qsort(suffixes, n, sizeof(struct Suffix), compare);
    printf("Suffix Array:\n");
    for(int i = 0; i < n; i++)
    {
        printf("%d -> %s\n",
               suffixes[i].index,
               suffixes[i].suffix);
    }
}
int main()
{
    char text[] = "banana";
    buildSuffixArray(text);
    return 0;
}
