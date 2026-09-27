#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char str[500];

    printf("Enter a string: ");
    scanf("%499s", str);

    int n = strlen(str);

    if (n == 0) {
        printf("Longest Palindromic Substring: \n");
        return 0;
    }

    /*
       Transform:
       "abba" -> "^#a#b#b#a#$"
       This allows even and odd length palindromes
       to be handled uniformly.
    */
    int size = 2 * n + 3;
    char *t = (char *)malloc(size * sizeof(char));

    t[0] = '^';
    int index = 1;

    for (int i = 0; i < n; i++) {
        t[index++] = '#';
        t[index++] = str[i];
    }

    t[index++] = '#';
    t[index++] = '$';
    t[index] = '\0';

    int *p = (int *)calloc(size, sizeof(int));

    int center = 0;
    int right = 0;
    int maxLength = 0;
    int maxCenter = 0;

    for (int i = 1; i < index - 1; i++) {
        int mirror = 2 * center - i;

        if (i < right) {
            p[i] = (right - i < p[mirror])
                    ? right - i
                    : p[mirror];
        }

        while (t[i + (1 + p[i])] == t[i - (1 + p[i])]) {
            p[i]++;
        }

        if (i + p[i] > right) {
            center = i;
            right = i + p[i];
        }

        if (p[i] > maxLength) {
            maxLength = p[i];
            maxCenter = i;
        }
    }

    int start = (maxCenter - maxLength) / 2;

    printf("Longest Palindromic Substring: ");

    for (int i = start; i < start + maxLength; i++) {
        printf("%c", str[i]);
    }

    printf("\n");
    printf("Length: %d\n", maxLength);

    free(t);
    free(p);

    return 0;
}
