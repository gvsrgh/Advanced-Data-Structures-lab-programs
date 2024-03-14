#include <iostream>
#include <queue>
using namespace std;

enum Color { RED, BLACK };

class Node {
public:
    int key;
    Node *left, *right, *parent;
    Color color;
    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), color(RED) {}
};

class RedBlackTree {
private:
    Node *root;

    // Helper functions for rotations
    void leftRotate(Node *&root, Node *&pt) {
        Node *pt_right = pt->right;
        pt->right = pt_right->left;
        if (pt->right != NULL)
            pt->right->parent = pt;
        pt_right->parent = pt->parent;
        if (pt->parent == NULL)
            root = pt_right;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_right;
        else
            pt->parent->right = pt_right;
        pt_right->left = pt;
        pt->parent = pt_right;
    }

    void rightRotate(Node *&root, Node *&pt) {
        Node *pt_left = pt->left;
        pt->left = pt_left->right;
        if (pt->left != NULL)
            pt->left->parent = pt;
        pt_left->parent = pt->parent;
        if (pt->parent == NULL)
            root = pt_left;
        else if (pt == pt->parent->left)
            pt->parent->left = pt_left;
        else
            pt->parent->right = pt_left;
        pt_left->right = pt;
        pt->parent = pt_left;
    }

    // Fix violations after insertion
    void fixViolation(Node *&root, Node *&pt) {
        Node *parent_pt = NULL;
        Node *grand_parent_pt = NULL;
        while ((pt != root) && (pt->color != BLACK) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grand_parent_pt = pt->parent->parent;
            if (parent_pt == grand_parent_pt->left) {
                Node *uncle_pt = grand_parent_pt->right;
                if (uncle_pt != NULL && uncle_pt->color == RED) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->right) {
                        leftRotate(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    rightRotate(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            } else {
                Node *uncle_pt = grand_parent_pt->left;
                if ((uncle_pt != NULL) && (uncle_pt->color == RED)) {
                    grand_parent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grand_parent_pt;
                } else {
                    if (pt == parent_pt->left) {
                        rightRotate(root, parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }
                    leftRotate(root, grand_parent_pt);
                    swap(parent_pt->color, grand_parent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK;
    }

    // Helper function for inorder traversal
    void inorderHelper(Node *root) {
        if (root == NULL)
            return;
        inorderHelper(root->left);
        cout << root->key << "(" << (root->color == RED ? "Red" : "Black") << ") ";
        inorderHelper(root->right);
    }

public:
    RedBlackTree() : root(nullptr) {}

    // Public insert function
    void insert(const int &key) {
        Node *pt = new Node(key);
        Node *parent_pt = NULL;
        Node *temp = root;
        while (temp != NULL) {
            parent_pt = temp;
            if (pt->key < temp->key)
                temp = temp->left;
            else
                temp = temp->right;
        }
        pt->parent = parent_pt;
        if (parent_pt == NULL)
            root = pt;
        else if (pt->key < parent_pt->key)
            parent_pt->left = pt;
        else
            parent_pt->right = pt;
        fixViolation(root, pt);
    }

    // Public search function
    Node *search(int key) {
        Node *current = root;
        while (current != NULL && current->key != key) {
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
        return current;
    }

    // Public display function
    void display() {
        inorderHelper(root);
        cout << endl;
    }

    // Public remove function (not implemented here)
    void remove(const int &key) {
        // To be implemented
    }
};

int main() {
    RedBlackTree tree;
    int choice, x;
    cout << "\nOPERATIONS ON RED-BLACK TREE" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete" << endl;
    cout << "3. Search" << endl;
    cout << "4. Display" << endl;
    cout << "5. Exit" << endl;
    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter the value to insert: ";
                cin >> x;
                tree.insert(x);
                break;
            case 2:
                cout << "Enter the value to delete: ";
                // Implement delete functionality
                break;
            case 3:
                cout << "Enter the value to search: ";
                cin >> x;
                if (tree.search(x) != NULL)
                    cout << x << " is present in the tree" << endl;
                else
                    cout << x << " is not present in the tree" << endl;
                break;
            case 4:
                cout << "Red-Black tree elements in inorder: ";
                tree.display();
                break;
            case 5:
                return 0;
            default:
                cout << "Please enter a valid choice!!!" << endl;
        }
    }
    return 0;
}

