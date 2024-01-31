/*A program that demonstrates Max Heap*/
#include <iostream>
#include <queue>
#include <unordered_map>
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

void siftDown(Node* root) {
  Node* largest = root;
  if (root->left != NULL && root->left->data > largest->data) {
    largest = root->left;
  }
  if (root->right != NULL && root->right->data > largest->data) {
    largest = root->right;
  }
  if (largest != root) {
    swap(&(root->data), &(largest->data));
    siftDown(largest);
  }
}

void insert(Node** root, queue<Node*>& q, unordered_map<int, Node*>& m, int data) {
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
  m[data] = node;
  siftUp(node);
}

void deleteNode(Node** root, queue<Node*>& q, unordered_map<int, Node*>& m, int data) {
  if (*root == NULL) {
    cout << "Heap is empty!" << endl;
    return;
  }
  if (m.find(data) == m.end()) {
    cout << "Element not found in the heap" << endl;
    return;
  }
  Node* node = m[data];
  Node* lastNode = q.back();
  swap(&(node->data), &(lastNode->data));
  m[lastNode->data] = node;
  m.erase(data);
  if (lastNode->parent != NULL) {
    if (lastNode->parent->left == lastNode) {
      lastNode->parent->left = NULL;
    } else {
      lastNode->parent->right = NULL;
    }
  }
  delete lastNode;
  q.pop();
  siftDown(*root);
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
  unordered_map<int, Node*> m;
  int choice, x;
  cout << "----------Max Heap Menu----------" << endl;
  cout << "1. Insert" << endl;
  cout << "2. Delete Specific" << endl;
  cout << "3. Display" << endl;
  cout << "57. Exit" << endl;
  cout << "------------------------" << endl;
  while (1) {
    cout << "Enter your choice: ";
    cin >> choice;
    switch (choice) {
    case 1:
      cout << "Enter the value: ";
      cin >> x;
      insert(&root, q, m, x);
      break;
    case 2:
      cout << "Enter the value to delete: ";
      cin >> x;
      deleteNode(&root, q, m, x);
      break;
    case 3:
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
