#include <stdio.h>
#include <limits.h>

// Function to find the vertex with minimum distance value
int minDistance(int dist[], int visited[], int V) {
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
        if (visited[v] == 0 && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Dijkstra's algorithm implementation
void dijkstra(int graph[][100], int src, int V) {
    int dist[V];     // Output array to hold the shortest distance from src to i
    int visited[V];  // Array to keep track of visited vertices

    // Initialize all distances as INFINITE and visited[] as 0
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, visited[i] = 0;

    // Distance of source vertex from itself is always 0
    dist[src] = 0;

    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(dist, visited, V);

        // Mark the picked vertex as visited
        visited[u] = 1;

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
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int graph[100][100] = {0}; // Assuming a maximum of 100 vertices

    printf("Enter the edges (source, destination, weight):\n");
    for (int i = 0; i < E; i++) {
        int src, dest, weight;
        scanf("%d%d%d", &src, &dest, &weight);
        graph[src][dest] = weight;
        graph[dest][src] = weight; // Assuming undirected graph
    }

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    dijkstra(graph, src, V); // Source vertex is src
    return 0;
}

