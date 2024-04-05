#include <iostream> 
using namespace std; 

class DisjointSet {
    int *size, *parent, n; 
public:
    DisjointSet(int n) { 
        size = new int[n]; 
        parent = new int[n]; 
        this->n = n; 
        make_set();
    }

    void make_set() {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    int find_set(int x) { 
        if (parent[x] != x) 
            parent[x] = find_set(parent[x]);
        
        return parent[x];
    }

    void Union(int x, int y) { 
        int xset = find_set(x); 
        int yset = find_set(y); 
        if (xset == yset)
            return;
        
        if (size[xset] < size[yset]) {
            parent[xset] = yset;
            size[yset] += size[xset];
        } else {
            parent[yset] = xset;
            size[xset] += size[yset];
        }
    }
};

int main() { 
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    DisjointSet obj(n); 

    int numUnions;
    cout << "Enter the number of unions: ";
    cin >> numUnions;
    for(int i = 0; i < numUnions; i++) {
        int x, y;
        cout << "Enter the elements to perform union on: ";
        cin >> x >> y;
        obj.Union(x, y);
    }

    int numQueries;
    cout << "Enter the number of queries: ";
    cin >> numQueries;
    for(int i = 0; i < numQueries; i++) {
        int a, b;
        cout << "Enter the elements to check if they are in the same set: ";
        cin >> a >> b;
        if (obj.find_set(a) == obj.find_set(b)) 
            cout << "Yes" << endl;
        else
            cout << "No" << endl; 
    }

    return 0; 
}
