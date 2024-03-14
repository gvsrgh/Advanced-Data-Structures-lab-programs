/*A Program to implement Red Black Trees*/
#include <iostream>
#include <queue>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
    int val;
    COLOR color;
    Node *left, *right, *parent;

    Node(int val) : val(val) {
        parent = left = right = nullptr;
        color = RED;
    }

    Node *uncle() {
        if (parent == nullptr || parent->parent == nullptr)
            return nullptr;
        if (parent->isOnLeft())
            return parent->parent->right;
        else
            return parent->parent->left;
    }

    bool isOnLeft() { return this == parent->left; }

    Node *sibling() {
        if (parent == nullptr)
            return nullptr;
        if (isOnLeft())
            return parent->right;
        else
            return parent->left;
    }

    void moveDown(Node *nParent) {
        if (parent != nullptr) {
            if (isOnLeft())
                parent->left = nParent;
            else
                parent->right = nParent;
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild() {
        return (left != nullptr && left->color == RED) || (right != nullptr && right->color == RED);
    }
};

class RBTree {
    Node *root;

    void leftRotate(Node *x) {
        Node *nParent = x->right;
        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->right = nParent->left;
        if (nParent->left != nullptr)
            nParent->left->parent = x;
        nParent->left = x;
    }

    void rightRotate(Node *x) {
        Node *nParent = x->left;
        if (x == root)
            root = nParent;
        x->moveDown(nParent);
        x->left = nParent->right;
        if (nParent->right != nullptr)
            nParent->right->parent = x;
        nParent->right = x;
    }

    void swapColors(Node *x1, Node *x2) {
        COLOR temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node *u, Node *v) {
        int temp = u->val;
        u->val = v->val;
        v->val = temp;
    }

    void fixRedRed(Node *x) {
        if (x == root) {
            x->color = BLACK;
            return;
        }
        Node *parent = x->parent, *grandparent = parent->parent, *uncle = x->uncle();
        if (parent->color != BLACK) {
            if (uncle != nullptr && uncle->color == RED) {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                fixRedRed(grandparent);
            } else {
                if (parent->isOnLeft()) {
                    if (x->isOnLeft())
                        swapColors(parent, grandparent);
                    else {
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    leftRotate(grandparent);
                } else {
                    if (x->isOnLeft()) {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    } else
                        swapColors(parent, grandparent);
                    rightRotate(grandparent);
                }
            }
        }
    }

    Node *successor(Node *x) {
        Node *temp = x;
        while (temp->left != nullptr)
            temp = temp->left;
        return temp;
    }

    Node *BSTreplace(Node *x) {
        if (x->left != nullptr && x->right != nullptr)
            return successor(x->right);
        if (x->left == nullptr && x->right == nullptr)
            return nullptr;
        if (x->left != nullptr)
            return x->left;
        else
            return x->right;
    }

    void deleteNode(Node *v) {
        Node *u = BSTreplace(v);
        bool uvBlack = ((u == nullptr || u->color == BLACK) && (v->color == BLACK));
        Node *parent = v->parent;
        if (u == nullptr) {
            if (v == root) {
                root = nullptr;
            } else {
                if (uvBlack)
                    fixDoubleBlack(v);
                else if (v->sibling() != nullptr)
                    v->sibling()->color = RED;
                if (v->isOnLeft())
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }
            delete v;
            return;
        }
        if (v->left == nullptr || v->right == nullptr) {
            if (v == root) {
                v->val = u->val;
                v->left = v->right = nullptr;
                delete u;
            } else {
                if (v->isOnLeft())
                    parent->left = u;
                else
                    parent->right = u;
                delete v;
                u->parent = parent;
                if (uvBlack)
                    fixDoubleBlack(u);
                else
                    u->color = BLACK;
            }
            return;
        }
        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node *x) {
        if (x == root)
            return;
        Node *sibling = x->sibling(), *parent = x->parent;
        if (sibling == nullptr) {
            fixDoubleBlack(parent);
        } else {
            if (sibling->color == RED) {
                parent->color = RED;
                sibling->color = BLACK;
                if (sibling->isOnLeft())
                    rightRotate(parent);
                else
                    leftRotate(parent);
                fixDoubleBlack(x);
            } else {
                if (sibling->hasRedChild()) {
                    if (sibling->left != nullptr && sibling->left->color == RED) {
                        if (sibling->isOnLeft()) {
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        } else {
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    } else {
                        if (sibling->isOnLeft()) {
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        } else {
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = BLACK;
                } else {
                    sibling->color = RED;
                    if (parent->color == BLACK)
                        fixDoubleBlack(parent);
                    else
                        parent->color = BLACK;
                }
            }
        }
    }

    void levelOrder(Node *x) {
        if (x == nullptr)
            return;
        queue<Node *> q;
        Node *curr;
        q.push(x);
        while (!q.empty()) {
            curr = q.front();
            q.pop();
            cout << curr->val << " (" << (curr->color == RED ? "RED" : "BLACK") << ") ";
            if (curr->left != nullptr)
                q.push(curr->left);
            if (curr->right != nullptr)
                q.push(curr->right);
        }
    }

public:
    RBTree() { root = nullptr; }

    Node *getRoot() { return root; }

    void insert(int n) {
        Node *newNode = new Node(n);
        if (root == nullptr) {
            newNode->color = BLACK;
            root = newNode;
        } else {
            Node *temp = root;
            while (temp != nullptr) {
                if (n < temp->val) {
                    if (temp->left == nullptr) {
                        temp->left = newNode;
                        newNode->parent = temp;
                        break;
                    } else
                        temp = temp->left;
                } else {
                    if (temp->right == nullptr) {
                        temp->right = newNode;
                        newNode->parent = temp;
                        break;
                    } else
                        temp = temp->right;
                }
            }
            fixRedRed(newNode);
        }
    }

    Node *search(int n) {
        Node *temp = root;
        while (temp != nullptr) {
            if (n == temp->val)
                return temp;
            else if (n < temp->val)
                temp = temp->left;
            else
                temp = temp->right;
        }
        return nullptr;
    }

    void deleteByVal(int n) {
        if (root == nullptr)
            return;
        Node *v = search(n);
        if (v == nullptr) {
            cout << "Value " << n << " not found in the tree." << endl;
            return;
        }
        deleteNode(v);
    }

    void display() { levelOrder(root); }
};

int main() {
    RBTree tree;
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
                cin >> x;
                tree.deleteByVal(x);
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
                cout << "Red-Black tree elements in level order: ";
                tree.display();
                cout << endl;
                break;
            case 5:
                return 0;
            default:
                cout << "Please enter a valid choice!!!" << endl;
        }
    }
    return 0;
}
