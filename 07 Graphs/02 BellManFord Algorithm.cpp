#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Graph {
    int V;
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) : V(V) {
        adjMatrix.resize(V, vector<int>(V, INT_MAX));
        // Initialize diagonal elements to 0
        for (int i = 0; i < V; ++i)
            adjMatrix[i][i] = 0;
    }

    void addEdge(int src, int dest, int weight) {
        adjMatrix[src][dest] = weight;
    }

    void printSolution(vector<int>& dist) {
        cout << "Vertex Distance from Source\n";
        for (int i = 0; i < V; ++i)
            cout << i << "\t\t" << dist[i] << "\n";
    }

    void bellmanFord(int src) {
        vector<int> dist(V, INT_MAX);
        dist[src] = 0;

        for (int i = 0; i < V - 1; ++i) {
            for (int u = 0; u < V; ++u) {
                for (int v = 0; v < V; ++v) {
                    if (adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                        dist[v] = dist[u] + adjMatrix[u][v];
                    }
                }
            }
        }

        for (int u = 0; u < V; ++u) {
            for (int v = 0; v < V; ++v) {
                if (adjMatrix[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + adjMatrix[u][v] < dist[v]) {
                    cout << "Graph contains negative weight cycle\n";
                    return;
                }
            }
        }

        printSolution(dist);
    }
};

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    Graph graph(V);

    cout << "Enter edges in format (src dest weight):\n";
    for (int i = 0; i < E; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    int src;
    cout << "Enter source vertex: ";
    cin >> src;

    graph.bellmanFord(src);

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
