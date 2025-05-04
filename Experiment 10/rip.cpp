// RIP protocol (Bellman Ford)
#include<iostream>
#include<climits>
#define MAX 15 // with referencce to max hop size allowed 15
using namespace std;

int graph[MAX][MAX]; // graph with costs, no path means inf
// int dist[MAX][MAX]; // routing table for each router:[router][dist. with other router]
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

// Returns true if there's an edge present
// [1 .. n], [2 .. n] etc
int defedges(int u, int v) {
    for (int i = 1; i <= v; i++) {
        if (graph[i][u] != INT_MAX) {
            return 1;
        }
    }
    return 0;
}

void BellmanFord(int src, int dest){
    for (int i = 1; i <= n; i++) 
        dist[i] = graph[src][i];

    dist[src] = 0;
    for(int k = 2; k <= n; k++){ // traverse router - 1 times
        for (int j = 1; j <= e; j++){ // traverse edge times
            for (int u = 1; u <= n; u++) {
                if (u != src && defedges(u, n) == 1) {
                    for (int i = 1; i <= n; i++) {
                        if (graph[i][u] != INT_MAX && dist[u] > dist[i] + graph[i][u]) {
                            dist[u] = dist[i] + graph[i][u];
                        }
                    }
                }
            }
        }
    }
}

int main (){
    cout << "Enter number of routers: ";
    cin >> n;
    cout << "Enter number of edges: ";
    cin >> e;

    for (int i = 1; i <= n; i++) { // prefilling
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

    int src, dest;
    cout << "Enter source router: ";
    cin >> src;
    cout << "Enter destination router: ";
    cin >> dest;
    BellmanFord(src, dest);
}