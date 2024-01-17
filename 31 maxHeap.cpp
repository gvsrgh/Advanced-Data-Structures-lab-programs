#include <iostream>
#include <queue>
using namespace std;

struct Node {
  int data;
  Node* left;
  Node* right;
  Node* parent;
};


Node* newNode(int data) {
  Node* node = new Node;
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

void swap(int *a, int *b) {
  int temp = *b;
  *b = *a;
  *a = temp;
}

void siftUp(Node* node) {
  queue<Node*> q;
  while (node->parent != NULL && node->data > node->parent->data) {
    q.push(node->parent);
    swap(&(node->data), &(node->parent->data));
    node = q.front();
    q.pop();
  }
}


void insert(Node** root, queue<Node*>& q, int data) {
  Node* node = newNode(data);
  if (*root == NULL) {
    *root = node;
  } else if (q.front()->left == NULL) {
    q.front()->left = node;
    node->parent = q.front();
  } else {
    q.front()->right = node;
    node->parent = q.front();
    q.pop();
  }
  q.push(node);
  siftUp(node);
}


void levelOrder(Node* root) {
  if (root == NULL)
    return;
  queue<Node*> q;
  q.push(root);
  while (!q.empty()) {
    Node* node = q.front();
    cout << node->data << " ";
    if (node->left != NULL)
      q.push(node->left);
    if (node->right != NULL)
      q.push(node->right);
    q.pop();
  }
  cout << "\n";
}

int main() {
  Node* root = NULL;
  queue<Node*> q;
  int choice, x;
  while (1) {
    cout << "----------Max Heap Menu----------" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Display" << endl;
    cout << "57. Exit" << endl;
    cout << "------------------------" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "Enter the value: ";
      cin >> x;
      insert(&root, q, x);
      break;
    case 2:
      levelOrder(root);
      break;
    case 57:
      exit(0);
      break;
    default:
      cout << "Please enter a valid choice!!!" << endl;
    }
  }
  return 0;
}
