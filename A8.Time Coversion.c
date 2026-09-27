#include <stdio.h>
#include <string.h>

void timeConversion(char* s) {
    int hh, mm, ss;
    char period[3];

    // Parse hours, minutes, seconds, and AM/PM indicator
    sscanf(s, "%d:%d:%d%s", &hh, &mm, &ss, period);

    // Handle 12-hour logic
    if (strcmp(period, "AM") == 0) {
        if (hh == 12) {
            hh = 0; // 12 AM becomes 00
        }
    } else if (strcmp(period, "PM") == 0) {
        if (hh != 12) {
            hh += 12; // 01 PM - 11 PM becomes 13 - 23
        }
    }

    // Print formatted in 24-hour style (with leading zeros)
    printf("%02d:%02d:%02d\n", hh, mm, ss);
}

int main() {
    char s[11]; // e.g., "07:05:45PM\0"
    if (scanf("%s", s) == 1) {
        timeConversion(s);
    }
    return 0;
}
