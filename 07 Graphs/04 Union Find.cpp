#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent;

public:
    UnionFind(int n) {
        parent.resize(n);
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void Union(int x, int y) {
        parent[x] = y;
    }
};

bool hasCycle(const vector<pair<int, int>>& edges, int n) {
    UnionFind uf(n);

    for (const auto& edge : edges) {
        int x = uf.find(edge.first);
        int y = uf.find(edge.second);

        if (x == y)
            return true;

        uf.Union(x, y);
    }
    return false;
}

int main() {
    int n, m;
    cout << "Enter the number of vertices and edges: ";
    cin >> n >> m;

    vector<pair<int, int>> edges(m);
    cout << "Enter the edges (Source, Destination):" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> edges[i].first >> edges[i].second;
    }

    if (hasCycle(edges, n))
        cout << "Graph contains cycle." << endl;
    else
        cout << "Graph does not contain cycle." << endl;

    return 0;
}
