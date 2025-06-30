// file: bellman_ford.c
#include <stdio.h>
#define MAX 100
#define INF 9999

typedef struct {
    int u, v, w;
} Edge;

void bellman_ford(Edge edges[], int V, int E, int src) {
    int dist[V], i, j;
    for (i = 0; i < V; i++) dist[i] = INF;
    dist[src] = 0;

    for (i = 0; i < V - 1; i++) {
        for (j = 0; j < E; j++) {
            int u = edges[j].u, v = edges[j].v, w = edges[j].w;
            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    // Check for negative weight cycle
    for (j = 0; j < E; j++) {
        int u = edges[j].u, v = edges[j].v, w = edges[j].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("Negative weight cycle detected!\n");
            return;
        }
    }

    printf("Shortest distances from source %d:\n", src);
    for (i = 0; i < V; i++) printf("%d -> %d = %d\n", src, i, dist[i]);
}

int main() {
    int V, E, i, src;
    Edge edges[MAX];

    printf("Enter number of vertices and edges: ");
    scanf("%d %d", &V, &E);
    printf("Enter edges (u v w):\n");
    for (i = 0; i < E; i++)
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);

    printf("Enter source vertex: ");
    scanf("%d", &src);

    bellman_ford(edges, V, E, src);
    return 0;
}
