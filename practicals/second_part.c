/*
This file contains multiple networking and data link layer implementations
All C programs include appropriate comments for learning and clarity
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

/* All previous sections retained here... */

/*
8. Socket Program - Client-Server to solve Quadratic Equation
*/
void server_quadratic() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    float a, b, c, root1, root2, discriminant;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 5);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);

    // Receive coefficients from client
    recv(newsockfd, &a, sizeof(a), 0);
    recv(newsockfd, &b, sizeof(b), 0);
    recv(newsockfd, &c, sizeof(c), 0);

    discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        root1 = root2 = 0;
    } else {
        root1 = (-b + sqrt(discriminant)) / (2 * a);
        root2 = (-b - sqrt(discriminant)) / (2 * a);
    }

    // Send results back
    send(newsockfd, &root1, sizeof(root1), 0);
    send(newsockfd, &root2, sizeof(root2), 0);
    close(newsockfd);
    close(sockfd);
}

void client_quadratic() {
    int sockfd;
    struct sockaddr_in server_addr;
    float a, b, c, root1, root2;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    // Enter coefficients
    printf("Enter a, b, c: ");
    scanf("%f%f%f", &a, &b, &c);
    send(sockfd, &a, sizeof(a), 0);
    send(sockfd, &b, sizeof(b), 0);
    send(sockfd, &c, sizeof(c), 0);

    // Receive roots
    recv(sockfd, &root1, sizeof(root1), 0);
    recv(sockfd, &root2, sizeof(root2), 0);

    printf("Roots: %.2f and %.2f\n", root1, root2);
    close(sockfd);
}

/*
9. Socket Program - Arithmetic Calculator
*/
void server_calculator() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    int op, a, b, result;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 5);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);

    recv(newsockfd, &op, sizeof(op), 0);
    recv(newsockfd, &a, sizeof(a), 0);
    recv(newsockfd, &b, sizeof(b), 0);

    switch (op) {
        case 1: result = a + b; break;
        case 2: result = a - b; break;
        case 3: result = a * b; break;
        case 4: result = b != 0 ? a / b : 0; break;
        default: result = 0;
    }

    send(newsockfd, &result, sizeof(result), 0);
    close(newsockfd);
    close(sockfd);
}

void client_calculator() {
    int sockfd;
    struct sockaddr_in server_addr;
    int op, a, b, result;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8081);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Enter operation (1=Add, 2=Sub, 3=Mul, 4=Div): ");
    scanf("%d", &op);
    printf("Enter two integers: ");
    scanf("%d%d", &a, &b);

    send(sockfd, &op, sizeof(op), 0);
    send(sockfd, &a, sizeof(a), 0);
    send(sockfd, &b, sizeof(b), 0);

    recv(sockfd, &result, sizeof(result), 0);
    printf("Result: %d\n", result);
    close(sockfd);
}

/*
10. Socket Program - Search integer in a set
*/
void server_search() {
    int sockfd, newsockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    int arr[5] = {10, 20, 30, 40, 50};
    int item, found = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8082);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    listen(sockfd, 5);
    newsockfd = accept(sockfd, (struct sockaddr *)&client_addr, &len);

    recv(newsockfd, &item, sizeof(item), 0);
    for (int i = 0; i < 5; i++) {
        if (arr[i] == item) {
            found = 1;
            break;
        }
    }
    send(newsockfd, &found, sizeof(found), 0);
    close(newsockfd);
    close(sockfd);
}

void client_search() {
    int sockfd;
    struct sockaddr_in server_addr;
    int item, found;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8082);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    printf("Enter number to search: ");
    scanf("%d", &item);
    send(sockfd, &item, sizeof(item), 0);
    recv(sockfd, &found, sizeof(found), 0);

    if (found) printf("Item found.\n");
    else printf("Item not found.\n");

    close(sockfd);
}
