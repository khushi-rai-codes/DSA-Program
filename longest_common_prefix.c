#include <stdio.h>
#include <string.h>
void longestCommonPrefix(char str[][100], int n)
{
    char prefix[100];
    strcpy(prefix, str[0]);
    for (int i = 1; i < n; i++)
    {
        while (strncmp(prefix, str[i], strlen(prefix)) != 0)
        {
            prefix[strlen(prefix) - 1] = '\0';
            if (strlen(prefix) == 0)
            {
                printf("No Common Prefix\n");
                return;
            }
        }
    }
    printf("Longest Common Prefix: %s\n", prefix);
}
int main()
{
    char str[4][100] = {
        "flower",
        "flow",
        "flight",
        "flask"
    };
    longestCommonPrefix(str, 4);
    return 0;
}
