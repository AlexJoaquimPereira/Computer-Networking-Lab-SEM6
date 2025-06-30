#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock;
    struct sockaddr_in server;
    char filename[100], buffer[1024];
    FILE *fp;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8085);
    server.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    printf("Enter filename to upload: ");
    scanf("%s", filename);

    // Send file name to server
    send(sock, filename, strlen(filename), 0);

    fp = fopen(filename, "r");
    if (!fp) {
        printf("File not found\n");
        return 1;
    }

    // Send file contents
    while (fgets(buffer, 1024, fp)) {
        send(sock, buffer, strlen(buffer), 0);
        usleep(100000);  // Optional delay
    }

    fclose(fp);
    close(sock);
    return 0;
}
