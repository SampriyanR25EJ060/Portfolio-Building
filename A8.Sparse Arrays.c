#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 21 // Max string length is 20 + 1 for null terminator

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0;

    // Allocate memory for N input strings
    char strings[n][MAX_STR_LEN];
    for (int i = 0; i < n; i++) {
        scanf("%s", strings[i]);
    }

    int q;
    if (scanf("%d", &q) != 1) return 0;

    // For each query, count occurrences in the input list
    for (int i = 0; i < q; i++) {
        char query[MAX_STR_LEN];
        scanf("%s", query);

        int count = 0;
        for (int j = 0; j < n; j++) {
            if (strcmp(query, strings[j]) == 0) {
                count++;
            }
        }
        printf("%d\n", count);
    }

    return 0;
}
