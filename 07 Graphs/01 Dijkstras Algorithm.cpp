#include <iostream>
#include <climits>

using namespace std;

// Function to find the vertex with minimum distance value
int minDistance(int dist[], bool visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (!visited[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    cout << "Vertex \t Distance from Source" << endl;
    for (int i = 0; i < V; i++)
        cout << i << "\t" << dist[i] << endl;
}

// Dijkstra's algorithm implementation for directed graphs
void dijkstra(int graph[][100], int src, int V) {
    int dist[V];     // Output array to hold the shortest distance from src to i
    bool visited[V];  // Array to keep track of visited vertices

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
        for (int v = 0; v < V; v++)
            // Update dist[v] only if it's not visited, there's an edge from u to v,
            // and the total weight of path from src to v through u is smaller than current value of dist[v]
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;

    cout << "Enter the number of directed edges: ";
    cin >> E;

    int graph[100][100] = {0}; // Assuming a maximum of 100 vertices

    cout << "Enter the directed edges (source, destination, weight):" << endl;
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph[src][dest] = weight; // Assigning weight to directed edges
    }

    int src;
    cout << "Enter the source vertex: ";
    cin >> src;

    dijkstra(graph, src, V); // Source vertex is src
    return 0;
}


/*
9
14
0 1 4
0 4 8
1 2 8
1 4 11
4 8 7
4 5 1
2 8 2
5 8 6
5 6 2
2 6 4
2 3 7
3 6 14
3 7 9
6 7 10
Initialization:
dist[0] = 0, dist[1] = INT_MAX, dist[2] = INT_MAX
visited[0] = false, visited[1] = false, visited[2] = false

Iteration 1:
i = 0, min = INT_MAX
1) 0 < 2 (T)
V = 0
1.1) (!visited[0] && dist[0] <= min) (T)
min = 0, min_index = 0
u = 0, visited[0] = true
Update dist value of the adjacent vertices of the picked vertex.
dist[1] = min(dist[1], dist[0] + weight[0][1]) = min(INT_MAX, 0 + 10) = 10
dist[2] = min(dist[2], dist[0] + weight[0][2]) = min(INT_MAX, 0 + 4) = 4

Iteration 2:
i = 1, min = INT_MAX
2) 1 < 2 (T)
V = 1
2.1) (!visited[2] && dist[2] <= min) (T)
min = 4, min_index = 2
u = 2, visited[2] = true
Update dist value of the adjacent vertices of the picked vertex.
dist[1] = min(dist[1], dist[2] + weight[2][1]) = min(10, 4 + 1) = 5

Iteration 3:
i = 2, min = INT_MAX
3) 2 < 2 (F)
End of iterations.

Final distances:
dist[0] = 0
dist[1] = 5
dist[2] = 4

*/
