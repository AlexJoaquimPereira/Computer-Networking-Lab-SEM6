#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    char filename[100], buffer[1024];
    FILE *fp;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_port = htons(8085);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    new_socket = accept(server_fd, NULL, NULL);

    // Read filename to save
    read(new_socket, filename, sizeof(filename));
    fp = fopen(filename, "w");

    // Receive content and write to file
    int n;
    while ((n = read(new_socket, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, n, fp);
    }

    fclose(fp);
    close(new_socket);
    close(server_fd);
    return 0;
}
