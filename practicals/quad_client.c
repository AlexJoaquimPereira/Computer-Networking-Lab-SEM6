#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sock;
    struct sockaddr_in serv;
    float coeffs[3], roots[2];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv.sin_family = AF_INET;
    serv.sin_port = htons(8088);
    serv.sin_addr.s_addr = INADDR_ANY;

    connect(sock, (struct sockaddr*)&serv, sizeof(serv));

    printf("Enter a b c: ");
    for (int i = 0; i < 3; i++) scanf("%f", &coeffs[i]);

    send(sock, coeffs, sizeof(coeffs), 0);
    read(sock, roots, sizeof(roots));

    if (roots[0] == -999)
        printf("Imaginary roots.\n");
    else
        printf("Roots: %.2f, %.2f\n", roots[0], roots[1]);

    close(sock);
    return 0;
}
