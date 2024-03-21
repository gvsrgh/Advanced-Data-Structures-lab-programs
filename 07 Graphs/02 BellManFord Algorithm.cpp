#include <iostream>
#include <climits>

using namespace std;

// Structure to represent a weighted edge
struct Edge {
    int src, dest, weight;
};

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    cout << "Vertex \t Distance from Source\n";
    for (int i = 0; i < V; i++)
        cout << i << " \t " << dist[i] << endl;
}

// Bellman-Ford algorithm implementation
void BellmanFord(Edge edge[], int V, int E, int src) {
    int dist[V]; // Output array to hold the shortest distance from src to i

    // Initialize distances from src to all other vertices as INFINITE
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX;
    dist[src] = 0;

    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        // Traverse through all edges
        for (int j = 0; j < E; j++) {
            int u = edge[j].src;    // Source vertex of current edge
            int v = edge[j].dest;   // Destination vertex of current edge
            int weight = edge[j].weight; // Weight of current edge

            // Relax the edge if a shorter path is found
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }

    // Check for negative-weight cycles
    for (int i = 0; i < E; i++) {
        int u = edge[i].src;    // Source vertex of current edge
        int v = edge[i].dest;   // Destination vertex of current edge
        int weight = edge[i].weight; // Weight of current edge

        // If a shorter path is found, graph contains negative-weight cycle
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
            cout << "Graph contains negative-weight cycle\n";
            return;
        }
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;

    Edge edge[E]; // Array to store edges

    cout << "Enter the source, destination, and weight of each edge:\n";
    for (int i = 0; i < E; i++)
        cin >> edge[i].src >> edge[i].dest >> edge[i].weight;

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    // Call Bellman-Ford algorithm
    BellmanFord(edge, V, E, src);
    return 0;
}

/*
6 9
0 1 6
0 3 5
0 2 4
1 4 -1
2 1 -2
3 2 -2
3 5 -1
2 4 3
4 5 3
*/
