#include <iostream>
using namespace std;

#define MAX 1000 // Max size of Heap

int n = 0; // Global variable to track the size of the heap
int minHeap[MAX]; // Global array to store the heap elements

// Function to heapify ith node in a Heap
void heapify(int arr[], int n, int i) {
    int smallest = i; // Initialize smallest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is smaller than root
    if (l < n && arr[l] < arr[smallest])
        smallest = l;

    // If right child is smaller than smallest so far
    if (r < n && arr[r] < arr[smallest])
        smallest = r;

    // If smallest is not root
    if (smallest != i) {
        swap(arr[i], arr[smallest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, smallest);
    }
}

// Function to insert a new node to the Heap
void insertNode(int arr[], int& n, int Key) {
    // Increase the size of Heap by 1
    n++;

    // Insert the element at end of Heap
    arr[n - 1] = Key;

    // Heapify the new node following a Bottom-up approach
    int i = n - 1;
    int parent = (i - 1) / 2;
    while (i > 0 && arr[parent] > arr[i]) {
        swap(arr[i], arr[parent]);
        i = parent;
        parent = (i - 1) / 2;
    }
}

// Function to delete the root from Heap
void deleteRoot(int arr[], int& n) {
    if (n <= 0) {
        cout << "Heap is empty!" << endl;
        return;
    }

    // Get the last element
    int lastElement = arr[n - 1];

    // Replace root with last element
    arr[0] = lastElement;

    // Decrease size of heap by 1
    n--;

    // heapify the root node
    heapify(arr, n, 0);
}

// A utility function to print array of size n
void printArray(int arr[], int n) {
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

// Main function
int main() {
    int choice, x;
    cout << "----------Min Heap Menu----------" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Delete Root" << endl;
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
            insertNode(minHeap, n, x);
            break;
        case 2:
            cout << "Deleting root..." << endl;
            deleteRoot(minHeap, n);
            break;
        case 3:
            cout << "Current Min Heap: ";
            printArray(minHeap, n);
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
