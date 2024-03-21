#include <stdio.h>
#include <limits.h>

// Structure to represent a weighted edge
struct Edge {
    int src, dest, weight;
};

// Function to print the constructed distance array
void printSolution(int dist[], int V) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t %d\n", i, dist[i]);
}

// Bellman-Ford algorithm implementation
void BellmanFord(struct Edge edge[], int V, int E, int src) {
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
            printf("Graph contains negative-weight cycle\n");
            return;
        }
    }

    // Print the constructed distance array
    printSolution(dist, V);
}

int main() {
    int V, E;
    printf("Enter the number of vertices and edges: ");
    scanf("%d%d", &V, &E);

    struct Edge edge[E]; // Array to store edges

    printf("Enter the source, destination, and weight of each edge:\n");
    for (int i = 0; i < E; i++)
        scanf("%d%d%d", &edge[i].src, &edge[i].dest, &edge[i].weight);

    int src;
    printf("Enter the source vertex: ");
    scanf("%d", &src);

    // Call Bellman-Ford algorithm
    BellmanFord(edge, V, E, src);
    return 0;
}

/*
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
