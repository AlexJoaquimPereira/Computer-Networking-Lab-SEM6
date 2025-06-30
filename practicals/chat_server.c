#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in addr;
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(8086);
    addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    new_socket = accept(server_fd, NULL, NULL);

    // Fork to handle send/recv in parallel
    if (fork() == 0) {
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            read(new_socket, buffer, sizeof(buffer));
            printf("Client: %s", buffer);
        }
    } else {
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            fgets(buffer, sizeof(buffer), stdin);
            send(new_socket, buffer, strlen(buffer), 0);
        }
    }

    return 0;
}
