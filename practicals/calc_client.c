#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock, nums[3], result;
    struct sockaddr_in serv;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8089);
    serv.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr*)&serv, sizeof(serv));

    printf("Enter num1, num2, operation (1=+, 2=-, 3=*, 4=/): ");
    scanf("%d%d%d", &nums[0], &nums[1], &nums[2]);

    send(sock, nums, sizeof(nums), 0);
    read(sock, &result, sizeof(result));

    if (result == -999)
        printf("Division by zero error\n");
    else
        printf("Result: %d\n", result);

    close(sock);
    return 0;
}
