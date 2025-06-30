#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock, arr[10], item, found;
    struct sockaddr_in serv;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8090);
    serv.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr*)&serv, sizeof(serv));

    printf("Enter 10 integers: ");
    for (int i = 0; i < 10; i++) scanf("%d", &arr[i]);
    printf("Enter number to search: ");
    scanf("%d", &item);

    send(sock, arr, sizeof(arr), 0);
    send(sock, &item, sizeof(item), 0);

    read(sock, &found, sizeof(found));
    if (found)
        printf("Item found!\n");
    else
        printf("Item not found.\n");

    close(sock);
    return 0;
}
