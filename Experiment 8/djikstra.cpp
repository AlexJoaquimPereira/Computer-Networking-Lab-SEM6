#include <iostream>
#include <climits>
#define MAX 50
using namespace std;

int graph[MAX][MAX]; // graph with costs
int dist[MAX]; // distance vector
bool visited[MAX]; // visited set

int n; // number of routers
int e; // number of edges

void printTable(int itr) {
    cout << "\nIteration " << itr + 2 << "\n";
    cout << "Router\tMinimum dist\tProcessed\n";
    for (int i = 1; i <= n; i++) {
        cout << i << "\t";
        if(dist[i] == INT_MAX)
            cout << "INF\t\t";
        else cout << dist[i] << "\t\t";
        if(visited[i] == true) 
            cout << "True\n";
        else cout << "False\n";
    }
}

void Dijkstra(int src) {
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[src] = 0;

    printTable(1);

    for (int count = 1; count < n; count++) {
        int u = -1, min_dist = INT_MAX;
        for (int v = 1; v <= n; v++) {
            if (!visited[v] && dist[v] < min_dist) {
                u = v;
                min_dist = dist[v];
            }
        }
        if (u == -1)
            break;

        visited[u] = true;

        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != INT_MAX && !visited[v] && 
                dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
        printTable(count + 2);
    }
}

int main() {
    cout << "Enter number of routers: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else graph[i][j] = INT_MAX;
        }
    }

    cout << "Fill the table\n";
    cout << "Router1\tRouter2\tCost\n";
    for (int i = 0; i < e; i++) {
        int u, v, cost;
        cin >> u >> v >> cost;
        graph[u][v] = cost;
        graph[v][u] = cost;
    }

    int src;
    cout << "Enter source router: ";
    cin >> src;
    Dijkstra(src);
}

/*
5
6
1 2 10
1 3 30
1 4 100
2 3 50
3 4 20
2 5 10
*/