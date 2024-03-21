#include <iostream>
#include <climits>

using namespace std;

// Function to print the solution matrix
void printSolution(int dist[][100], int V) {
    cout << "The following matrix shows the shortest distances between every pair of vertices:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if(dist[i][j] == INT_MAX)
                cout << "INF" << "\t";
            else
                cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

// Function to solve the all-pairs shortest path problem using Floyd Warshall algorithm
void floydWarshall(int graph[][100], int V) {
    int dist[100][100];

    // Initialize the solution matrix same as input graph matrix
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            dist[i][j] = graph[i][j];

    // Update distance values by considering all vertices as intermediate vertices
    for (int k = 0; k < V; k++) {
        // Pick all vertices as source one by one
        for (int i = 0; i < V; i++) {
            // Pick all vertices as destination for the above picked source
            for (int j = 0; j < V; j++) {
                // If vertex k is on the shortest path from i to j, then update the value of dist[i][j]
                if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Print the shortest distance matrix
    printSolution(dist, V);
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    int graph[100][100];

    // Take input for the adjacency matrix
    cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cin >> graph[i][j];
            // Set INF values to INT_MAX except for diagonal elements (self-loops)
            if (graph[i][j] == -1234567890) {
                if (i == j) {
                    graph[i][j] = 0; // Set diagonal elements to 0
                } else {
                    graph[i][j] = INT_MAX; // Set non-diagonal elements to INT_MAX
                }
            }
        }
    }

    // Solve the shortest paths using Floyd Warshall algorithm
    floydWarshall(graph, V);
    
    return 0;
}


/*
4
0 8 -1234567890 1
-1234567890 0 1 -1234567890
4 -1234567890 0 -1234567890
-1234567890 2 9 0
*/
