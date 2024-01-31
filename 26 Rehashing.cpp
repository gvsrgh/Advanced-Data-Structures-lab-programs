/*A program to implement rehashing*/
#include <iostream>
#include <vector>
using namespace std;

class Lprobing {
private:
    vector<int*> h;
    int M, nv = 0;
    double u;

public:
    Lprobing(int M, double u) : M(M), u(u) {
        h.resize(M, nullptr);
    }

    void insert1();
    void delete1();
    void display();
    void search1();
    void rehashing();
    void Lprobe(int ele);
};

void Lprobing::Lprobe(int ele) {
    int idx = ele % M;
    if (h[idx] == nullptr) {
        h[idx] = new int(ele);
    } else {
        for (int i = 0; i < M; i++) {
            int hkey = (idx + i) % M;
            if (h[hkey] == nullptr) {
                h[hkey] = new int(ele);
                return;
            }
        }
        cout << "No space for Extra element" << endl;
    }
}

void Lprobing::insert1() {
    cout << "Enter element to insert: ";
    int ele;
    cin >> ele;
    nv++;
    cout << (double)nv / u << endl;
    if ((double)nv / u < 0.75) {
        Lprobe(ele);
    } else {
        rehashing();
        Lprobe(ele);
    }
}

void Lprobing::rehashing() {
    vector<int*> old_h = h;
    M *= 2;
    h.resize(M, nullptr);
    u *= 2;
    nv = 0;
    for (int* ele : old_h) {
        if (ele != nullptr) {
            Lprobe(*ele);
            delete ele;
        }
    }
}

void Lprobing::display() {
    cout << "\tHASH TABLE\t" << endl;
    cout << "Indices\t\tElements" << endl;
    for (int i = 0; i < M; i++) {
        cout << i << "\t\t";
        if (h[i] != nullptr)
            cout << *h[i];
        else
            cout << "NULL";
        cout << endl;
    }
}

void Lprobing::delete1() {
    cout << "Enter element to delete: ";
    int ele;
    cin >> ele;
    int idx = ele % M;
    if (h[idx] != nullptr && *h[idx] == ele) {
        delete h[idx];
        h[idx] = nullptr;
    } else {
        for (int i = 0; i < M; i++) {
            int hkey = (idx + i) % M;
            if (h[hkey] != nullptr && *h[hkey] == ele) {
                delete h[hkey];
                h[hkey] = nullptr;
                break;
            }
        }
    }
    cout << "After deleting " << ele << endl;
    cout << "Elements are: " << endl;
    display();
}

void Lprobing::search1() {
    cout << "Enter element to search: ";
    int ele;
    cin >> ele;
    int idx = ele % M;
    if (h[idx] != nullptr && *h[idx] == ele)
        cout << "Element " << ele << " found at index " << idx << endl;
    else {
        for (int i = 0; i < M; i++) {
            int hkey = (idx + i) % M;
            if (h[hkey] != nullptr && *h[hkey] == ele) {
                cout << "Element " << ele << " found at index " << hkey << endl;
                return;
            }
        }
        cout << "Element " << ele << " not found" << endl;
    }
}

int main() {
    int ch;
    cout << "Enter table size: ";
    int M;
    cin >> M;
    cout << "Enter load factor value: ";
    double u;
    cin >> u;
    Lprobing L(M, u);
    cout << "MENU \n1.Insert()\n2.Delete()\n3.Search()\n4.Display()\n5.Exit" << endl;
    do {
        cout << "Enter your choice: ";
        cin >> ch;
        switch (ch) {
        case 1:
            L.insert1();
            break;
        case 2:
            L.delete1();
            break;
        case 3:
            L.search1();
            break;
        case 4:
            L.display();
            break;
        case 5:
            return 0;
        default:
            cout << "Choice out of Range!!!" << endl;
        }
    } while (1);
}
