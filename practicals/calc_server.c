#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sfd, new_sock;
    int data[3]; // num1, num2, op
    int result = 0;
    struct sockaddr_in addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8089);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sfd, 1);
    new_sock = accept(sfd, NULL, NULL);

    read(new_sock, data, sizeof(data));  // Receive input
    switch (data[2]) {
        case 1: result = data[0] + data[1]; break;
        case 2: result = data[0] - data[1]; break;
        case 3: result = data[0] * data[1]; break;
        case 4: result = data[1] != 0 ? data[0] / data[1] : -999; break;
        default: result = 0;
    }
    send(new_sock, &result, sizeof(result), 0);

    close(new_sock);
    close(sfd);
    return 0;
}
