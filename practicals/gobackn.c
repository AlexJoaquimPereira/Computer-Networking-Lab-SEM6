// file: go_back_n.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define MAX_FRAMES 10

void send_frames(int total, int window) {
    int sent = 0;
    while (sent < total) {
        printf("\nSending frames: ");
        for (int i = 0; i < window && sent + i < total; i++)
            printf("[%d] ", sent + i);
        printf("\n");

        int ack_fail = rand() % window;
        printf("Frame [%d] lost, resending window...\n", sent + ack_fail);

        sent += ack_fail; // Go back to unacknowledged
    }
    printf("\nAll frames sent successfully.\n");
}

int main() {
    int n, window;
    srand(time(NULL));
    printf("Enter number of frames: ");
    scanf("%d", &n);
    printf("Enter window size: ");
    scanf("%d", &window);
    send_frames(n, window);
    return 0;
}
