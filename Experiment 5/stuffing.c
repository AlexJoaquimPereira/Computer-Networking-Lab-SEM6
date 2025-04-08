#include<stdio.h>
#include<string.h>
#define MAX 100

const char* FLAG = "FLAG";
const char* ESC = "ESC";

void charStuffing() {
    char data[MAX];
    int frame_size, len, i, j, count;

    printf("Enter the data: ");
    fgets(data, MAX, stdin);
    data[strcspn(data, "\n")] = 0;

    printf("Enter the frame size: ");
    scanf("%d", &frame_size);
    getchar(); // consume newline

    len = strlen(data);
    printf("Data after Character count: ");

    for (i = 0; i < len; i += (frame_size - 1)) {
        count = (i + (frame_size - 1) <= len) ? frame_size - 1 : len - i;
        printf("%d", count + 1);
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
    fgets(frame, MAX, stdin);
    frame[strcspn(frame, "\n")] = 0;

    while (i < strlen(frame)) {
        if (frame[i] < '1' || frame[i] > '9') {
            printf("Invalid frame format!\n");
            return;
        }
        count = frame[i] - '0';
        i++;

        for (int k = 1; k < count && frame[i] != '\0'; k++) {
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
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0;

    for (i = 0; input[i] != '\0'; i++) {
        stuffed[j++] = input[i];

        if (input[i] == '1') {
            count++;
            if (count == 5) {
                stuffed[j++] = '0';
                count = 0;
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
    fgets(input, MAX, stdin);
    input[strcspn(input, "\n")] = 0;

    for (i = 0; input[i] != '\0'; i++) {
        destuffed[j++] = input[i];

        if (input[i] == '1') {
            count++;
            if (count == 5 && input[i + 1] == '0') {
                i++;
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

    printf("Enter the number of strings: ");
    scanf("%d", &len);
    getchar();

    printf("Enter the strings (one per line):\n");
    strcat(stuffed, FLAG);
    strcat(stuffed, " ");

    for (i = 0; i < len; i++) {
        fgets(input[i], MAX, stdin);
        input[i][strcspn(input[i], "\n")] = 0;

        if (strcmp(input[i], FLAG) == 0 || strcmp(input[i], ESC) == 0) {
            strcat(stuffed, ESC);
            strcat(stuffed, " ");
        }
        strcat(stuffed, input[i]);
        strcat(stuffed, " ");
    }
    strcat(stuffed, FLAG);

    printf("Data after Byte Stuffing: %s\n", stuffed);
}

void byteDestuffing() {
    char words[MAX][MAX];
    char destuffed[MAX * 2] = "";
    int count = 0, flagCount = 0, escNext = 0;

    printf("Enter the frame values (space-separated):\n");
    while (scanf("%s", words[count]) != EOF && flagCount < 3) {
        if (strcmp(words[count], FLAG) == 0) {
            flagCount++;
            if (flagCount == 3) break;
        }
        count++;
    }
    getchar();

    int flagSeen = 0;
    for (int i = 0; i < count; i++) {
        if (strcmp(words[i], FLAG) == 0) {
            flagSeen++;
            if (flagSeen == 1 || flagSeen == 3) continue;
        }

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
        destuffed[strlen(destuffed) - 1] = '\0';

    printf("Original data: %s\n", destuffed);
}

int main() {
    int choice = 0;
    while (choice != 7) {
        printf("\nCharacter Count:\n");
        printf("1. Transmitter\n");
        printf("2. Receiver\n");
        printf("Bit Stuffing\n");
        printf("3. Transmitter\n");
        printf("4. Receiver\n");
        printf("Byte Stuffing\n");
        printf("5. Transmitter\n");
        printf("6. Receiver\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
        case 1:
            charStuffing();
            break;
        case 2:
            charDestuffing();
            break;
        case 3:
            bitStuffing();
            break;
        case 4:
            bitDestuffing();
            break;
        case 5:
            byteStuffing();
            break;
        case 6:
            byteDestuffing();
            break;
        default:
            printf("Invalid choice\n");
        }
    }
    return 0;
}
