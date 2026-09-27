#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    // Dynamically allocate array of pointers for N sequences
    int** arr = (int**)malloc(n * sizeof(int*));
    int* sizes = (int*)calloc(n, sizeof(int));
    int* capacities = (int*)calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        capacities[i] = 2; // Initial capacity per sequence
        arr[i] = (int*)malloc(capacities[i] * sizeof(int));
    }

    int lastAnswer = 0;

    for (int i = 0; i < q; i++) {
        int type, x, y;
        scanf("%d %d %d", &type, &x, &y);

        int idx = (x ^ lastAnswer) % n;

        if (type == 1) {
            // Append y to arr[idx] (resize dynamically if full)
            if (sizes[idx] == capacities[idx]) {
                capacities[idx] *= 2;
                arr[idx] = (int*)realloc(arr[idx], capacities[idx] * sizeof(int));
            }
            arr[idx][sizes[idx]++] = y;
        } else if (type == 2) {
            // Query value from arr[idx]
            int element_idx = y % sizes[idx];
            lastAnswer = arr[idx][element_idx];
            printf("%d\n", lastAnswer);
        }
    }

    // Free memory
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    free(sizes);
    free(capacities);

    return 0;
}
