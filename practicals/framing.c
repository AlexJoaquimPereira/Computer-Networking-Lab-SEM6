// file: framing_methods.c
#include <stdio.h>
#include <string.h>

#define MAX 100

// Character Count Framing
void char_count_framing(char *input) {
    int len = strlen(input);
    printf("Character Count Framed: [%d]%s\n", len, input);
}

// Character Stuffing (flag = $, escape = /)
void char_stuffing(char *input) {
    char stuffed[MAX] = "$";
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] == '$' || input[i] == '/')
            strncat(stuffed, "/", 1);  // Escape special chars
        strncat(stuffed, &input[i], 1);
    }
    strcat(stuffed, "$");
    printf("Character Stuffed: %s\n", stuffed);
}

// Bit Stuffing (flag = 01111110)
void bit_stuffing(char *input) {
    char stuffed[MAX] = "";
    int count = 0;
    for (int i = 0; i < strlen(input); i++) {
        strncat(stuffed, &input[i], 1);
        if (input[i] == '1') {
            count++;
            if (count == 5) {
                strcat(stuffed, "0"); // Stuff a 0
                count = 0;
            }
        } else count = 0;
    }
    printf("Bit Stuffed: 01111110%s01111110\n", stuffed);
}

int main() {
    char input[MAX];
    printf("Enter input for framing (binary for bit stuffing): ");
    scanf("%s", input);
    char_count_framing(input);
    char_stuffing(input);
    bit_stuffing(input);
    return 0;
}
