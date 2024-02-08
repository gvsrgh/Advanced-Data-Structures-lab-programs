#include<iostream>
#include<queue>
using namespace std;

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

Node* search(Node *x, int k) {
    int i = 0;
    while (i < x->n && k > x->keys[i]) {
        i++;
    }
    if (i < x->n && k == x->keys[i]) {
        return x;
    }
    if (x->leaf) {
        return NULL;
    }
    return search(x->C[i], k);
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

void removeFromLeaf(Node *x, int idx) {
    for (int i = idx + 1; i < x->n; ++i) {
        x->keys[i - 1] = x->keys[i];
    }
    x->n--;
}

void removeFromNonLeaf(Node *x, int idx) {
    int k = x->keys[idx];
    if (x->C[idx]->n >= t) {
        int pred = getPred(x, idx);
        x->keys[idx] = pred;
        deleteKey(x->C[idx], pred);
    } else if (x->C[idx + 1]->n >= t) {
        int succ = getSucc(x, idx);
        x->keys[idx] = succ;
        deleteKey(x->C[idx + 1], succ);
    } else {
        merge(x, idx);
        deleteKey(x->C[idx], k);
    }
}

int getPred(Node *x, int idx) {
    Node *cur = x->C[idx];
    while (!cur->leaf) {
        cur = cur->C[cur->n];
    }
    return cur->keys[cur->n - 1];
}

int getSucc(Node *x, int idx) {
    Node *cur = x->C[idx + 1];
    while (!cur->leaf) {
        cur = cur->C[0];
    }
    return cur->keys[0];
}

void fill(Node *x, int idx) {
    if (idx != 0 && x->C[idx - 1]->n >= t) {
        borrowFromPrev(x, idx);
    } else if (idx != x->n && x->C[idx + 1]->n >= t) {
        borrowFromNext(x, idx);
    } else {
        if (idx != x->n) {
            merge(x, idx);
        } else {
            merge(x, idx - 1);
        }
    }
}

void borrowFromPrev(Node *x, int idx) {
    Node *child = x->C[idx];
    Node *sibling = x->C[idx - 1];
    for (int i = child->n - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }
    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i) {
            child->C[i + 1] = child->C[i];
        }
    }
    child->keys[0] = x->keys[idx - 1];
    if (!child->leaf) {
        child->C[0] = sibling->C[sibling->n];
    }
    x->keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n += 1;
    sibling->n -= 1;
}

void borrowFromNext(Node *x, int idx) {
    Node *child = x->C[idx];
    Node *sibling = x->C[idx + 1];
    child->keys[(child->n)] = x->keys[idx];
    if (!(child->leaf)) {
        child->C[(child->n) + 1] = sibling->C[0];
    }
    x->keys[idx] = sibling->keys[0];
    for (int i = 1; i < sibling->n; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i) {
            sibling->C[i - 1] = sibling->C[i];
        }
    }
    child->n += 1;
    sibling->n -= 1;
}

void merge(Node *x, int idx) {
    Node *child = x->C[idx];
    Node *sibling = x->C[idx + 1];
    child->keys[t - 1] = x->keys[idx];
    for (int i = 0; i < sibling->n; ++i) {
        child->keys[i + t] = sibling->keys[i];
    }
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i) {
            child->C[i + t] = sibling->C[i];
        }
    }
    for (int i = idx + 1; i < x->n; ++i) {
        x->keys[i - 1] = x->keys[i];
    }
    for (int i = idx + 2; i <= x->n; ++i) {
        x->C[i - 1] = x->C[i];
    }
    child->n += sibling->n + 1;
    x->n--;
    delete sibling;
}

void deleteKey(BTree *T, int k) {
    if (!T || !T->root) return;
    removeFromNode(T->root, k);
    if (T->root->n == 0) {
        Node *tmp = T->root;
        if (T->root->leaf) T->root = NULL;
        else T->root = T->root->C[0];
        delete tmp;
    }
}

void removeFromNode(Node *x, int k) {
    int idx = findKey(x, k);
    if (idx < x->n && x->keys[idx] == k) {
        if (x->leaf) {
            removeFromLeaf(x, idx);
        } else {
            removeFromNonLeaf(x, idx);
        }
    } else {
        if (x->leaf) {
            cout << "The key " << k << " does not exist in the tree.\n";
            return;
        }
        bool flag = (idx == x->n);
        if (x->C[idx]->n < t) {
            fill(x, idx);
        }
        if (flag && idx > x->n) {
            removeFromNode(x->C[idx - 1], k);
        } else {
            removeFromNode(x->C[idx], k);
        }
    }
}

int findKey(Node *x, int k) {
    int idx = 0;
    while (idx < x->n && x->keys[idx] < k) {
        ++idx;
    }
    return idx;
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
            cout << "| ";
        }
        cout << endl;
    }
}

int main() {
    cout << "\nOPERATIONS ON 2-3 B TREE" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Search" << endl;
    cout << "4. Display (Level Order)" << endl;
    cout << "5. Exit" << endl;

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
                cout << "Enter key to delete: ";
                cin >> key;
                deleteKey(T, key);
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                if (search(T->root, key))
                    cout << "Key found" << endl;
                else
                    cout << "Key not found" << endl;
                break;
            case 4:
                cout << "BTree:" << endl;
                display(T);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
