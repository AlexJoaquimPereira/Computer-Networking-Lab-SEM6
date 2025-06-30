// file: dijkstra.c
#include <stdio.h>
#define V 10
#define INF 9999

void dijkstra(int graph[V][V], int n, int start) {
    int dist[V], visited[V] = {0}, i, j, min, u;

    for (i = 0; i < n; i++) dist[i] = INF;
    dist[start] = 0;

    for (i = 0; i < n - 1; i++) {
        min = INF;
        for (j = 0; j < n; j++)
            if (!visited[j] && dist[j] < min)
                min = dist[j], u = j;

        visited[u] = 1;
        for (j = 0; j < n; j++)
            if (!visited[j] && graph[u][j] && dist[u] + graph[u][j] < dist[j])
                dist[j] = dist[u] + graph[u][j];
    }

    printf("Shortest distances from node %d:\n", start);
    for (i = 0; i < n; i++) printf("%d -> %d = %d\n", start, i, dist[i]);
}

int main() {
    int graph[V][V], n, i, j, src;
    printf("Enter number of nodes: ");
    scanf("%d", &n);
    printf("Enter cost matrix (%d x %d):\n", n, n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            scanf("%d", &graph[i][j]);

    printf("Enter source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, n, src);
    return 0;
}
