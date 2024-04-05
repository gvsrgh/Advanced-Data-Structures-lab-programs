#include <bits/stdc++.h>
using namespace std;

class Edge {
public:
    int src, dest;
};

class Graph {
public:
    int V, E;
    Edge* edge;
};

Graph* createGraph(int V, int E) {
    Graph* graph = new Graph();
    graph->V = V;
    graph->E = E;
    graph->edge = new Edge[graph->E * sizeof(Edge)];
    return graph;
}

int find(int parent[], int i) {
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int x, int y) {
    parent[x] = y;
}

int isCycle(Graph* graph) {
    int* parent = new int[graph->V];
    for(int i = 0; i < graph->V; i++)
        parent[i] = i;
    for(int i = 0; i < graph->E; ++i) {
        int x = find(parent, graph->edge[i].src);
        int y = find(parent, graph->edge[i].dest);
        if (x == y)
            return 1;
        Union(parent, x, y);
    }
    return 0;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices and edges: ";
    cin >> V >> E;
    Graph* graph = createGraph(V, E);
    cout << "Enter " << E << " edges (Source, Destination): " << endl;
    for(int i = 0; i < E; i++) {
        int src, dest;
        cin >> src >> dest;
        graph->edge[i].src = src;
        graph->edge[i].dest = dest;
    }
    if (isCycle(graph))
        cout << "Graph contains cycle"<<endl;
    else
        cout << "Graph does not contain cycle"<<endl;
    return 0;
}
