#include <iostream>
using namespace std;

#define MAX 1000 // Max size of Heap

int n = 0; // Global variable to track the size of the heap
int maxHeap[MAX]; // Global array to store the heap elements

// Function to heapify ith node in a Heap
void heapify(int arr[], int n, int i) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
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
    while (i > 0 && arr[parent] < arr[i]) {
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
            insertNode(maxHeap, n, x);
            break;
        case 2:
            cout << "Deleting root..." << endl;
            deleteRoot(maxHeap, n);
            break;
        case 3:
            cout << "Current Max Heap: ";
            printArray(maxHeap, n);
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
