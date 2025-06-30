#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock, arr[10];
    struct sockaddr_in server;

    // Read 10 integers
    printf("Enter 10 integers: ");
    for (int i = 0; i < 10; i++) scanf("%d", &arr[i]);

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8083);
    server.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    // Send array
    send(sock, arr, sizeof(arr), 0);

    // Receive sorted array
    read(sock, arr, sizeof(arr));

    printf("Sorted array: ");
    for (int i = 0; i < 10; i++) printf("%d ", arr[i]);
    printf("\n");

    close(sock);
    return 0;
}
