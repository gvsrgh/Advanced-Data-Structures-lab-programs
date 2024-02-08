#include<iostream>
using namespace std;

// Node structure
struct Node {
    int *keys;
    int t;  // Minimum degree (defines the range for number of keys)
    Node **C; // An array of child pointers
    int n;  // Current number of keys
    bool leaf; // Is true when node is leaf. Otherwise false
};

// A BTree
struct BTree {
    Node *root; // Pointer to root node
    int t;  // Minimum degree
};

// Function to create a new node
Node* newNode(int t, bool leaf) {
    // Allocate memory for new node
    Node *new_node = new Node;

    // Copy the given minimum degree and leaf property
    new_node->t = t;
    new_node->leaf = leaf;

    // Allocate memory for maximum number of possible keys and child pointers
    new_node->keys = new int[2*t-1];
    new_node->C = new Node *[2*t];

    // Initialize the number of keys as 0
    new_node->n = 0;

    return new_node;
}

// Function to create a new BTree
BTree* newBTree(int t) {
    BTree *new_tree = new BTree;
    new_tree->root = newNode(t, true);
    new_tree->t = t;
    return new_tree;
}

// Function to insert a key in the BTree
void insert(BTree *T, int k) {
    // TODO: Implement the insert function
}

// Function to delete a key in the BTree
void deleteKey(BTree *T, int k) {
    // TODO: Implement the delete function
}

// Function to search a key in the BTree
Node* search(BTree *T, int k) {
    // TODO: Implement the search function
    return NULL;
}

// Function to display the BTree
void display(BTree *T) {
    // TODO: Implement the display function
}

int main() {
    cout << "\nOPERATIONS ON 2-3 B TREE" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Search" << endl;
    cout << "4. Display (Level Order)" << endl;
    cout << "5. Exit" << endl;

    // TODO: Implement the menu operations

    return 0;
}
