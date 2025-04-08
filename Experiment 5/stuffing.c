#include<stdio.h>
#include<string.h>
#define MAX 100
#define FLAG '%'
#define ESC '\\'

// Character count encoding
void charStuffing() {
    char data[MAX];
    int frame_size, len, i, j, count;

    printf("Enter the data: ");
    scanf("%s", data);

    printf("Enter the frame size: ");
    while (scanf("%d", &frame_size) != 1 || frame_size <= 1) {
        printf("Invalid input. Frame size must be greater than 1. Try again: ");
        while (getchar() != '\n'); // Clear buffer
    }

    len = strlen(data);
    printf("Data after Character count: ");

    for (i = 0; i < len; i += (frame_size - 1)) {
        count = (i + (frame_size - 1) <= len) ? frame_size - 1 : len - i;
        printf("%d", count + 1);  // Include count itself in frame size
        for (j = i; j < i + count; j++) {
            printf("%c", data[j]);
        }
    }
    printf("\n");
}

void charDestuffing() {
    char frame[MAX], original[MAX];
    int i = 0, j = 0, count;

    printf("Enter the frame values: ");
    scanf("%s", frame);

    while (i < strlen(frame)) {
        if (frame[i] < '1' || frame[i] > '9') { // Validate numeric count
            printf("Invalid frame format!\n");
            return;
        }
        count = frame[i] - '0';  // Convert char to integer
        i++;

        for (int k = 1; k < count && frame[i] != '\0'; k++) { // k=1 because count itself is part of frame
            original[j++] = frame[i++];
        }
    }
    original[j] = '\0';
    printf("Original data: %s\n", original);
}

void bitStuffing() {
    char input[MAX], stuffed[MAX];
    int i, j = 0, count = 0;
    
    printf("Enter the message: ");
    scanf("%s", input);

    for (i = 0; input[i] != '\0'; i++) {
        stuffed[j++] = input[i];

        if (input[i] == '1') {
            count++;
            if (count == 5) {
                stuffed[j++] = '0';  // Insert bit-stuffing '0'
                count = 0;  // Reset count
            }
        } else {
            count = 0;
        }
    }
    stuffed[j] = '\0';

    printf("Message after performing bit stuffing: %s\n", stuffed);
}

void bitDestuffing() {
    char input[MAX], destuffed[MAX];
    int i, j = 0, count = 0;

    printf("Enter the message: ");
    scanf("%s", input);

    for (i = 0; input[i] != '\0'; i++) {
        destuffed[j++] = input[i];

        if (input[i] == '1') {
            count++;
            if (count == 5 && input[i + 1] == '0') {
                i++; // Skip the stuffed '0'
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    destuffed[j] = '\0';

    printf("Message after bit destuffing: %s\n", destuffed);
}

void byteStuffing() {
    char input[MAX][MAX], stuffed[MAX * 2] = "";
    int len, i;

    printf("Enter the length of String: ");
    scanf("%d", &len);
    getchar();  // Consume newline

    printf("Enter the String:\n");

    // Add first FLAG
    strcat(stuffed, FLAG);
    strcat(stuffed, " ");

    for (i = 0; i < len; i++) {
        scanf("%s", input[i]);

        // If FLAG or ESC appears, prepend ESC
        if (strcmp(input[i], FLAG) == 0 || strcmp(input[i], ESC) == 0) {
            strcat(stuffed, ESC);
            strcat(stuffed, " ");
        }

        strcat(stuffed, input[i]);
        strcat(stuffed, " ");
    }

    // Add third FLAG
    strcat(stuffed, FLAG);

    printf("Data after Byte Stuffing: %s\n", stuffed);
}

void byteDestuffing() {
    char words[MAX][MAX];
    char destuffed[MAX * 2] = "";
    int count = 0, flagCount = 0, escNext = 0;
    int firstFlagFound = 0, lastFlagFound = 0;

    printf("Enter the frame values:\n");

    // Read all words first
    while (scanf("%s", words[count]) != EOF ) {
            if (strcmp(words[count], FLAG) == 0) {
            flagCount++;  // Count FLAG occurrences
            if(flagCount==3)
            break;
        }
        count++;
    }

       int flagSeen = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], FLAG) == 0) {
            flagSeen++;
            if (flagSeen == 1 || flagSeen == 3) {
                continue;  // Ignore first and third FLAG
            }
        }

        // Handle escaping logic
        if (escNext) {
            escNext = 0;
        } else if (strcmp(words[i], ESC) == 0) {
            escNext = 1;
            continue;
        }

        strcat(destuffed, words[i]);
        strcat(destuffed, " ");
    }

    if (strlen(destuffed) > 0)
        destuffed[strlen(destuffed) - 1] = '\0';  // Remove last space

    printf("Original data: %s\n", destuffed);
}

int main(){
    char str[MAX];
    printf("Enter a string: "); // enter a line with spaces included
    
    int choice;
    while (choice != 7){
        printf("Character Count:\n");
        printf("1. Transmitter\n");
        printf("2. Receiver\n");
        printf("Bit Stuffing\n");
        printf("3. Transmitter\n");
        printf("4. Reciever\n");
        printf("Byte Stuffing\n");
        printf("5. Transmitter\n");
        printf("6. Reciever\n");
        printf("7. Exit\n");
        switch (choice){
        case 1:
            charStuffing(str);
            break;
        case 2:
            charDestuffing(str);
            break;
        case 3:
            bitStuffing(str);
            break;
        case 4:
            bitDestuffing(str);
            break;
        case 5:
            byteStuffing(str);
            break;
        case 6:
            byteDestuffing(str);
            break;
        default:
            printf("Invalid choice\n");
        }
    }
}