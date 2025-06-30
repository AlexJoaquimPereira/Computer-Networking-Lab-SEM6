#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdlib.h>

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    char buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8086);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Fork to handle send/recv in parallel
    if (fork() == 0) {
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            read(sock, buffer, sizeof(buffer));
            printf("Server: %s", buffer);
        }
    } else {
        while (1) {
            memset(buffer, 0, sizeof(buffer));
            fgets(buffer, sizeof(buffer), stdin);
            send(sock, buffer, strlen(buffer), 0);
        }
    }

    return 0;
}
