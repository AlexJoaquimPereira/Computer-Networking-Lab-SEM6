#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char filename[100], buffer[1024];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8084);
    server.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    printf("Enter filename to download: ");
    scanf("%s", filename);

    // Send filename
    send(sock, filename, strlen(filename), 0);

    printf("File content:\n");
    while (read(sock, buffer, sizeof(buffer)) > 0) {
        printf("%s", buffer);
        memset(buffer, 0, sizeof(buffer));
    }

    close(sock);
    return 0;
}
