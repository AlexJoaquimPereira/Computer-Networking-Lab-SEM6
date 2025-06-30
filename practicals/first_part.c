/*
1. Framing methods: Character count, Character stuffing, Bit stuffing
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>

void character_count_framing(char *data) {
    int len = strlen(data);
    printf("Character Count Framing:\n");
    printf("[%d]%s\n", len, data);
}

void character_stuffing(char *data) {
    char flag = '#';
    char esc = '/';
    char stuffed[100] = "";
    strcat(stuffed, "#");

    for (int i = 0; i < strlen(data); i++) {
        if (data[i] == flag || data[i] == esc) {
            strncat(stuffed, &esc, 1);
        }
        strncat(stuffed, &data[i], 1);
    }
    strcat(stuffed, "#");
    printf("Character Stuffing:\n%s\n", stuffed);
}

void bit_stuffing(char *data) {
    char stuffed[200] = "";
    int count = 0;
    for (int i = 0; i < strlen(data); i++) {
        strncat(stuffed, &data[i], 1);
        if (data[i] == '1') {
            count++;
            if (count == 5) {
                strcat(stuffed, "0"); // Stuff '0' after five '1's
                count = 0;
            }
        } else {
            count = 0;
        }
    }
    printf("Bit Stuffing:\n%s\n", stuffed);
}

int main() {
    char data1[] = "HELLO";
    char data2[] = "HE#L/LO";
    char bit_data[] = "011111101111110";

    character_count_framing(data1);
    character_stuffing(data2);
    bit_stuffing(bit_data);
    return 0;
} 

/*
2. CRC computation for CRC-12 and CRC-16
*/
void xor(char *crc, char *poly, int len) {
    for (int i = 1; i < len; i++)
        crc[i] = crc[i] == poly[i] ? '0' : '1';
}

void compute_crc(char *input, char *poly) {
    int data_len = strlen(input);
    int poly_len = strlen(poly);

    char appended[128];
    strcpy(appended, input);
    for (int i = 0; i < poly_len - 1; i++) strcat(appended, "0");

    char crc[32];
    strncpy(crc, appended, poly_len);
    crc[poly_len] = '\0';

    for (int i = poly_len; i <= strlen(appended); i++) {
        if (crc[0] == '1') xor(crc, poly, poly_len);
        memmove(crc, crc + 1, poly_len);
        crc[poly_len - 1] = appended[i];
    }

    printf("CRC: %s\n", crc);
}

int main_crc() {
    char data[] = "11010011101100";
    char poly12[] = "1100000001111"; // CRC-12
    char poly16[] = "11000000000000101"; // CRC-16

    printf("CRC-12: ");
    compute_crc(data, poly12);

    printf("CRC-16: ");
    compute_crc(data, poly16);
    return 0;
}

/*
3. Go-Back-N with Sliding Window Protocol
*/
#define MAX 8
int window_size = 4;

void send_frames(int total_frames) {
    int sent = 0;
    while (sent < total_frames) {
        int frames = (sent + window_size > total_frames) ? total_frames - sent : window_size;
        printf("\nSending frames: ");
        for (int i = 0; i < frames; i++) printf("%d ", sent + i);

        printf("\nEnter ACK for last frame (or -1 to simulate loss): ");
        int ack;
        scanf("%d", &ack);

        if (ack == -1) {
            printf("ACK lost. Resending from frame %d\n", sent);
        } else if (ack >= sent + frames) {
            sent = ack + 1;
        } else {
            printf("Partial ACK. Resending from frame %d\n", ack + 1);
            sent = ack + 1;
        }
    }
}

int main_gbn() {
    int total;
    printf("Enter total number of frames: ");
    scanf("%d", &total);
    send_frames(total);
    return 0;
}

/*
4. Dijkstra's Algorithm for shortest path
*/
#define V 5

int min_distance(int dist[], int visited[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

void dijkstra(int graph[V][V], int src) {
    int dist[V], visited[V];

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = 0;
    }
    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = min_distance(dist, visited);
        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("\nDijkstra shortest distances from source %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("To %d: %d\n", i, dist[i]);
}

/*
5. Bellman-Ford Algorithm
*/
struct Edge {
    int src, dest, weight;
};

void bellman_ford(struct Edge edges[], int V, int E, int src) {
    int dist[V];
    for (int i = 0; i < V; i++) dist[i] = INT_MAX;
    dist[src] = 0;

    for (int i = 1; i <= V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int j = 0; j < E; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            printf("Graph contains negative weight cycle\n");
            return;
        }
    }

    printf("\nBellman-Ford shortest distances from source %d:\n", src);
    for (int i = 0; i < V; i++)
        printf("To %d: %d\n", i, dist[i]);
}

int main_sp() {
    int graph[V][V] = {
        {0, 6, 0, 1, 0},
        {6, 0, 5, 2, 2},
        {0, 5, 0, 0, 5},
        {1, 2, 0, 0, 1},
        {0, 2, 5, 1, 0}};

    dijkstra(graph, 0);

    struct Edge edges[] = {
        {0, 1, 6}, {0, 3, 1},
        {1, 2, 5}, {1, 3, 2}, {1, 4, 2},
        {2, 4, 5},
        {3, 4, 1}};

    int E = sizeof(edges) / sizeof(edges[0]);
    bellman_ford(edges, V, E, 0);
    return 0;
}

/*
6. Hamming Code Generator for n-bit data
*/
void generate_hamming_code(char data[]) {
    int m = strlen(data); // Number of data bits
    int r = 0;            // Number of parity bits

    // Calculate number of redundant bits needed (2^r >= m + r + 1)
    while ((1 << r) < (m + r + 1)) r++;

    int total = m + r;
    char hamming[32];
    int j = 0, k = 0;

    // Insert placeholders for parity bits
    for (int i = 1; i <= total; i++) {
        if ((i & (i - 1)) == 0) {
            hamming[i - 1] = 'P'; // Placeholder for parity
        } else {
            hamming[i - 1] = data[k++];
        }
    }

    // Calculate parity bits
    for (int i = 0; i < r; i++) {
        int pos = 1 << i;
        int parity = 0;
        for (int j = 1; j <= total; j++) {
            if (j & pos) {
                if (hamming[j - 1] != 'P') {
                    parity ^= (hamming[j - 1] - '0');
                }
            }
        }
        hamming[pos - 1] = parity + '0'; // Replace P with computed bit
    }

    // Print final Hamming code
    printf("\nHamming Code: ");
    for (int i = 0; i < total; i++) printf("%c", hamming[i]);
    printf("\n");
}

int main_hamming() {
    char data[] = "1011"; // Example data bits
    generate_hamming_code(data);
    return 0;
}
