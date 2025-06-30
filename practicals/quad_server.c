#include <stdio.h>
#include <math.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int sfd, new_sock;
    float coeffs[3], a, b, c, d, root1, root2;
    struct sockaddr_in addr;

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(8088);
    addr.sin_addr.s_addr = INADDR_ANY;
    bind(sfd, (struct sockaddr*)&addr, sizeof(addr));
    listen(sfd, 1);

    new_sock = accept(sfd, NULL, NULL);

    read(new_sock, coeffs, sizeof(coeffs));  // Receive a, b, c

    a = coeffs[0]; b = coeffs[1]; c = coeffs[2];
    d = b * b - 4 * a * c;

    float result[2] = {0};
    if (d >= 0) {
        root1 = (-b + sqrt(d)) / (2 * a);
        root2 = (-b - sqrt(d)) / (2 * a);
        result[0] = root1;
        result[1] = root2;
    } else {
        result[0] = result[1] = -999;  // Indicator for imaginary roots
    }

    send(new_sock, result, sizeof(result), 0);

    close(new_sock);
    close(sfd);
    return 0;
}
