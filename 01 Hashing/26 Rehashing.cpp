/*A program to implement rehashing*/
#include <iostream>
#include <map>
using namespace std;

map<int,int> ht;
int tableSize = 0;
double rehashThreshold = 0.8; // Default rehash threshold

int isPrime(int n)
{
    for(int i = 2;i<n;i++)
    {
        if(n%i==0)
            return 0;
    }
    return 1;
}

int getPrime(int n)
{
    int i;
    if(isPrime(n))
        return n;
    for(i=n;!isPrime(i);i++);
    return i;
}

int calculateIndex(int t,int n)
{
    int index = t%n;
    return index;
}

void rehashIfNeeded() {
    if (ht.size() >= rehashThreshold * tableSize) {
        int oldSize = tableSize;
        tableSize *= 2; // Double the table size
        tableSize = getPrime(tableSize); // Get the nearest prime number
        map<int, int> new_ht;

        // Rehash elements into the new hashtable
        for (auto& element : ht) {
            int newIndex = calculateIndex(element.first, tableSize);
            new_ht[newIndex] = element.second;
        }

        // Update global hashtable
        ht = new_ht;

        cout << "Rehashing done. Table size increased to " << tableSize << endl;
    }
}

void insertion(int n)
{
    int key;
    cout<<"Enter the value to be inserted: ";
    cin>>key;
    rehashIfNeeded(); // Check if rehashing is needed
    int index = calculateIndex(key,n);
    if(ht.find(index)!=ht.end())
    {
        cout<<"Collision occurred!!!"<<endl;
        return;
    }
    ht[index] = key;
    cout<<"Insertion Successful!!"<<endl;
}

void display()
{
    map<int,int>::iterator it;
    for(it = ht.begin();it!=ht.end();it++)
    {
        cout<<it->first<<" : "<<it->second<<endl;
    }
}

int main()
{
    int t,choice;
    double threshold;
    cout<<"Enter the table size: ";
    cin>>t;
    tableSize = getPrime(t);
    cout<<"Rounding of the table size to nearest prime number: "<<tableSize<<endl;
    cout<<"Enter the rehash threshold (percentage): ";
    cin>>threshold;
    if (threshold <= 0 || threshold >= 1) {
        cout << "Invalid threshold value. Using default threshold: " << rehashThreshold << endl;
    } else {
        rehashThreshold = threshold;
    }
    while(1)
    {
        cout<<"----------Menu----------"<<endl;
        cout<<"1. Insert"<<endl;
        cout<<"2. TableSize"<<endl;
        cout<<"3. Display"<<endl;
        cout<<"4. Change Rehash Threshold"<<endl;
        cout<<"57. Exit"<<endl;
        cout<<"------------------------"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                insertion(tableSize);
                break;
            case 2:
                cout<<"Initial table size is: "<<t<<endl;
                cout<<"Final table size is: "<<tableSize<<endl;
                break;
            case 3:
                display();
                break;
            case 4:
                cout<<"Enter the new rehash threshold (percentage): ";
                cin>>threshold;
                if (threshold <= 0 || threshold >= 1) {
                    cout << "Invalid threshold value. Using default threshold: " << rehashThreshold << endl;
                } else {
                    rehashThreshold = threshold;
                }
                break;
            case 57:
                exit(0);
                break;
            default:
                cout<<"Please enter a valid choice!!!"<<endl;
        }
    }
    return 0;
}
