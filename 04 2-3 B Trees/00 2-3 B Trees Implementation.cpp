#include <iostream>
#include <queue>
using namespace std;

const int t = 2;

struct Node {
    int *keys;
    int t;
    Node **C;
    int n;
    bool leaf;
};

struct BTree {
    Node *root;
    int t;
};

Node* newNode(int t, bool leaf);
BTree* newBTree(int t);
void insert(BTree *T, int k);
void display(BTree *T);

int main() {
    cout << "\nOPERATIONS ON 2-3 B TREE" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Display (Level Order)" << endl;
    cout << "3. Exit" << endl;

    BTree *T = newBTree(2);

    int choice, key;
    do {
        cout << "Enter your choice: "; 
        cin >> choice;
        switch(choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                insert(T, key);
                break;
            case 2:
                cout << "BTree:" << endl;
                display(T);
                break;
            case 3:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}

Node* newNode(int t, bool leaf) {
    Node *new_node = new Node;
    new_node->t = t;
    new_node->leaf = leaf;
    new_node->keys = new int[2*t-1];
    new_node->C = new Node *[2*t];
    new_node->n = 0;
    return new_node;
}

BTree* newBTree(int t) {
    BTree *new_tree = new BTree;
    new_tree->root = newNode(t, true);
    new_tree->t = t;
    return new_tree;
}

void splitChild(Node *x, int i, Node *y) {
    Node *z = newNode(y->t, y->leaf);
    z->n = x->t - 1;
    for (int j = 0; j < x->t - 1; j++) {
        z->keys[j] = y->keys[j+x->t];
    }
    if (!y->leaf) {
        for (int j = 0; j < x->t; j++) {
            z->C[j] = y->C[j+x->t];
        }
    }
    y->n = x->t - 1;
    for (int j = x->n; j >= i+1; j--) {
        x->C[j+1] = x->C[j];
    }
    x->C[i+1] = z;
    for (int j = x->n-1; j >= i; j--) {
        x->keys[j+1] = x->keys[j];
    }
    x->keys[i] = y->keys[x->t-1];
    x->n++;
}

void insertNonFull(Node *x, int k) {
    int i = x->n - 1;
    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i+1] = x->keys[i];
            i--;
        }
        x->keys[i+1] = k;
        x->n++;
    } else {
        while (i >= 0 && k < x->keys[i]) {
            i--;
        }
        i++;
        if (x->C[i]->n == 2*x->t - 1) {
            splitChild(x, i, x->C[i]);
            if (k > x->keys[i]) {
                i++;
            }
        }
        insertNonFull(x->C[i], k);
    }
}

void insert(BTree *T, int k) {
    Node *r = T->root;
    if (r->n == 2*T->t - 1) {
        Node *s = newNode(T->t, false);
        s->C[0] = r;
        T->root = s;
        splitChild(s, 0, r);
        insertNonFull(s, k);
    } else {
        insertNonFull(r, k);
    }
}

void display(BTree *T) {
    if (T == NULL || T->root == NULL) {
        cout << "Empty BTree" << endl;
        return;
    }

    queue<Node *> q;
    q.push(T->root);
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            Node *curr = q.front();
            q.pop();
            for (int j = 0; j < curr->n; j++) {
                cout << curr->keys[j] << " ";
            }
            if (!curr->leaf) {
                for (int j = 0; j <= curr->n; j++) {
                    if (curr->C[j] != NULL)
                        q.push(curr->C[j]);
                }
            }
            if (i < n - 1) {
                cout << "| ";
            }
        }
        cout << endl;
    }
}
