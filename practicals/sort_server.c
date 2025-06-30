#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

void bubbleSort(int *arr, int n) {
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
}

int main() {
    int server_fd, new_socket, arr[10];
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create TCP socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Bind to port 8083
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8083);
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));

    // Listen for client
    listen(server_fd, 3);
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);

    // Read array from client
    read(new_socket, arr, sizeof(arr));

    bubbleSort(arr, 10);  // Sort array

    // Send sorted array back
    send(new_socket, arr, sizeof(arr), 0);

    close(new_socket);
    close(server_fd);
    return 0;
}
