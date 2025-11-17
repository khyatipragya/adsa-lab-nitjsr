#include <stdio.h>
#include <string.h>

// Function to create the LPS (Longest Prefix Suffix) array
void computeLPS(char *pattern, int M, int *lps) {
    int len = 0; 
    lps[0] = 0; 
    int i = 1;

    while (i < M) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP Search function
void KMPSearch(char *pattern, char *text) {
    int M = strlen(pattern);
    int N = strlen(text);

    int lps[M];
    computeLPS(pattern, M, lps);

    int i = 0; // index for text
    int j = 0; // index for pattern

    printf("Pattern found at indices: ");

    int found = 0;

    while (i < N) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == M) {
            printf("%d ", i - j);
            found = 1;
            j = lps[j - 1];
        } 
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    if (!found) {
        printf("No match found");
    }
    printf("\n");
}

int main() {
    char text[100], pattern[100];

    printf("Enter the text: ");
    gets(text);

    printf("Enter the pattern to search: ");
    gets(pattern);

    KMPSearch(pattern, text);

    return 0;
}
