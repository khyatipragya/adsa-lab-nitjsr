#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NO_OF_CHARS 256

void badCharHeuristic(char *str, int size, int badchar[]) {
    int i;

    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    // Fill the actual value of last occurrence
    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

void preprocessStrongSuffix(int *shift, int *bpos, char *pat, int m) {
    int i = m, j = m + 1;
    bpos[i] = j;

    while (i > 0) {
        while (j <= m && pat[i - 1] != pat[j - 1]) {
            if (shift[j] == 0)
                shift[j] = j - i;
            j = bpos[j];
        }
        i--; j--;
        bpos[i] = j;
    }
}

void preprocessCase2(int *shift, int *bpos, char *pat, int m) {
    int i, j;
    j = bpos[0];
    for (i = 0; i <= m; i++) {
        if (shift[i] == 0)
            shift[i] = j;
        if (i == j)
            j = bpos[j];
    }
}

void search(char *text, char *pat) {
    int m = strlen(pat);
    int n = strlen(text);

    int badchar[NO_OF_CHARS];
    int bpos[m + 1], shift[m + 1];

    // Initialize shift array
    for (int i = 0; i < m + 1; i++)
        shift[i] = 0;

    // Preprocess Good Suffix and Bad Character
    badCharHeuristic(pat, m, badchar);
    preprocessStrongSuffix(shift, bpos, pat, m);
    preprocessCase2(shift, bpos, pat, m);

    printf("Pattern occurs at positions: ");

    int s = 0;
    while (s <= n - m) {

        int j = m - 1;

        // Keep reducing j while characters match
        while (j >= 0 && pat[j] == text[s + j])
            j--;

        // If the pattern is found
        if (j < 0) {
            printf("%d ", s);
            s += shift[0];
        } else {
            int badCharShift = j - badchar[(int)text[s + j]];
            int goodSuffixShift = shift[j + 1];
            s += (badCharShift > goodSuffixShift) ? badCharShift : goodSuffixShift;
        }
    }
}

int main() {
    char text[100], pattern[100];

    printf("Enter text: ");
    gets(text);

    printf("Enter pattern: ");
    gets(pattern);

    search(text, pattern);

    return 0;
}
