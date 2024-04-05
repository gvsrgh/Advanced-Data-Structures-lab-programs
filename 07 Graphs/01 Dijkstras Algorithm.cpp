#include <iostream>
#include <climits>
#include <vector>

using namespace std;

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the constructed distance array and paths
void printSolution(int dist[], vector<int> parent, int V, int src) {
    cout << "Vertex\tDistance\tPath" << endl;
    for (int i = 0; i < V; i++) {
        cout << src << " -> " << i << "\t" << dist[i] << "\t\t";
        vector<int> path;
        int j = i;
        while (j != -1) {
            path.push_back(j);
            j = parent[j];
        }
        for (int k = path.size() - 1; k > 0; k--)
            cout << path[k] << " -> ";
        cout << path[0]; // Print the source vertex without an arrow
        cout << endl;
    }
}

// Dijkstra's algorithm implementation for directed graphs
void dijkstra(int graph[][100], int src, int V) {
    int dist[V];     // Output array to hold the shortest distance from src to i
    bool visited[V];  // Array to keep track of visited vertices
    vector<int> parent(V, -1); // Parent array to store the shortest path

    // Initialize all distances as INFINITE and visited[] as false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = false;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, visited, V);

        // Mark the picked vertex as visited
        visited[u] = true;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // Update dist[v] only if it's not visited, there's an edge from u to v,
            // and the total weight of path from src to v through u is smaller than current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    // Print the constructed distance array and paths
    printSolution(dist, parent, V, src);
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    int graph[100][100]; // Assuming a maximum of 100 vertices

    cout << "Enter the adjacency matrix:" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
        }
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    dijkstra(graph, src, V); // Source vertex is src
    return 0;
}


/*
9
0 4 0 0 8 0 0 0 0
4 0 8 0 11 0 0 0 0
0 8 0 7 0 0 4 0 2
0 0 7 0 0 0 14 9 0
8 11 0 0 0 1 0 0 7
0 0 0 0 1 0 2 0 6
0 0 4 14 0 2 0 10 0
0 0 0 9 0 0 10 0 0
0 0 2 0 7 5 0 0 0
*/
