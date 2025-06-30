#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char filename[100], buffer[1024];
    FILE *fp;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(8084);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    new_socket = accept(server_fd, NULL, NULL);

    // Get filename from client
    read(new_socket, filename, sizeof(filename));

    fp = fopen(filename, "r");
    if (!fp) {
        strcpy(buffer, "File not found");
        send(new_socket, buffer, strlen(buffer), 0);
    } else {
        while (fgets(buffer, 1024, fp)) {
            send(new_socket, buffer, strlen(buffer), 0);
            usleep(100000);  // Small delay
        }
        fclose(fp);
    }

    close(new_socket);
    close(server_fd);
    return 0;
}
