// file: hamming_code.c
#include <stdio.h>
#include <math.h>

int is_power_of_two(int x) {
    return x && !(x & (x - 1));
}

void generate_hamming(int data[], int n) {
    int r = 0, i, j, k = 0;

    // Calculate parity bits needed
    while ((1 << r) < (n + r + 1)) r++;

    int total = n + r;
    int hamming[total + 1]; // 1-based index

    // Insert data and placeholder for parity bits
    for (i = 1; i <= total; i++) {
        if (is_power_of_two(i)) hamming[i] = 0;  // parity
        else hamming[i] = data[k++];
    }

    // Calculate parity bits
    for (i = 0; i < r; i++) {
        int pos = 1 << i;
        int xor_sum = 0;
        for (j = 1; j <= total; j++) {
            if (j & pos) xor_sum ^= hamming[j];
        }
        hamming[pos] = xor_sum;
    }

    printf("Hamming Code: ");
    for (i = total; i >= 1; i--) printf("%d", hamming[i]);
    printf("\n");
}

int main() {
    int data[32], n, i;
    printf("Enter number of data bits: ");
    scanf("%d", &n);
    printf("Enter data bits (LSB first): ");
    for (i = 0; i < n; i++) scanf("%d", &data[i]);

    generate_hamming(data, n);
    return 0;
}
