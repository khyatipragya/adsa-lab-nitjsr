#include <stdio.h>
#include <string.h>

#define d 256        // number of characters in input alphabet
#define q 101        // a prime number for modulo hashing

void rabinKarp(char text[], char pattern[]) {
    int n = strlen(text);
    int m = strlen(pattern);
    int h = 1;            // h = (d^(m-1)) % q
    int p = 0;            // hash value for pattern
    int t = 0;            // hash value for text
    int i, j;

    // Calculate h = pow(d, m-1) % q
    for (i = 0; i < m - 1; i++)
        h = (h * d) % q;

    // Calculate initial hash values of pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide pattern over text
    for (i = 0; i <= n - m; i++) {
        // Check hash values
        if (p == t) {
            // Check characters one by one
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j])
                    break;
            }
            if (j == m)
                printf("Pattern found at index %d\n", i);
        }

        // Compute hash for next window
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + 1]) % q;

            // Make sure hash is positive
            if (t < 0)
                t = t + q;
        }
    }
}

int main() {
    char text[100], pattern[50];

    printf("Enter the text: ");
    gets(text);

    printf("Enter the pattern to search: ");
    gets(pattern);

    printf("\nSearching...\n\n");
    rabinKarp(text, pattern);

    return 0;
}
