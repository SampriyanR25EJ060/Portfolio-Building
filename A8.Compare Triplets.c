#include <stdio.h>

int main() {
    int a[3], b[3];

    // Input Alice's ratings
    for (int i = 0; i < 3; i++) {
        scanf("%d", &a[i]);
    }

    // Input Bob's ratings
    for (int i = 0; i < 3; i++) {
        scanf("%d", &b[i]);
    }

    int alice_points = 0;
    int bob_points = 0;

    // Compare ratings O(1)
    for (int i = 0; i < 3; i++) {
        if (a[i] > b[i]) {
            alice_points++;
        } else if (a[i] < b[i]) {
            bob_points++;
        }
    }

    // Print results: [Alice, Bob]
    printf("%d %d\n", alice_points, bob_points);

    return 0;
}
