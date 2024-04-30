#include <iostream>
#include <map>
using namespace std;

map<int, int> ht;

int isPrime(int n) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

int getPrime(int n) {
    int i;
    if (isPrime(n))
        return n;
    for (i = n; !isPrime(i); i++);
    return i;
}

int calculateIndex(int t, int n) {
    int index = t % n;
    return index;
}

void insertion(int n) {
    int key;
    cout << "Enter the value to be inserted: ";
    cin >> key;
    int index = calculateIndex(key, n);
    if (ht.find(index) != ht.end()) {
        cout << "Collision occurred!!!" << endl;
        return;
    }
    ht[index] = key;
    cout << "Insertion Successful!!" << endl;
}

void deletion(int n) {
    int key;
    cout << "Enter the value to be deleted: ";
    cin >> key;
    int index = calculateIndex(key, n);
    if (ht.find(index) != ht.end()) {
        ht.erase(index);
        cout << "Deletion Successful!!" << endl;
    } else {
        cout << "Element not found in the hashtable!" << endl;
    }
}

void display() {
    map<int, int>::iterator it;
    for (it = ht.begin(); it != ht.end(); it++) {
        cout << it->first << " : " << it->second << endl;
    }
}

int main() {
    int t, choice;
    cout << "Enter the table size: ";
    cin >> t;
    int n = getPrime(t);
    cout << "Rounding of the table size to nearest prime number: " << n << endl;
    while (1) {
        cout << "----------Menu----------" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Delete" << endl;
        cout << "3. TableSize" << endl;
        cout << "4. Display" << endl;
        cout << "57. Exit" << endl;
        cout << "------------------------" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                insertion(n);
                break;
            case 2:
                deletion(n);
                break;
            case 3:
                cout << "Initial table size is: " << t << endl;
                cout << "Final table size is: " << n << endl;
                break;
            case 4:
                display();
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
