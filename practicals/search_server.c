#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sfd, new_sock, arr[10], item, found = 0;
    struct sockaddr_in addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8090);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sfd, 1);
    new_sock = accept(sfd, NULL, NULL);

    read(new_sock, arr, sizeof(arr));   // Receive array
    read(new_sock, &item, sizeof(item));  // Receive item

    for (int i = 0; i < 10; i++) {
        if (arr[i] == item) {
            found = 1;
            break;
        }
    }

    send(new_sock, &found, sizeof(found), 0);

    close(new_sock);
    close(sfd);
    return 0;
}
