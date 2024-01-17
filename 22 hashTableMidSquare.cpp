/*A Program to insert elements into hash table using mid-square method*/
#include <iostream>
#include <map>
using namespace std;

map<int,int> ht;

int getCount(int key)
{
    int n = key;
    int c = 0;
    while(n>0)
    {
        c++;
        n/=10;
    }
    return c;
}

int calculateIndex(int k, int s) {
    int counti = 0;
    int key = k*k;
    counti = getCount(key);
    for(int i = 0;i<counti/2;i++)
        key/=10;
    return key%s;
}

void insertion(int n)
{
    int key;
    cout<<"Enter the value to be inserted: ";
    cin>>key;
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
    int n,choice;
    cout<<"Enter the table size: ";
    cin>>n;
    while(1)
    {
        cout<<"----------Menu----------"<<endl;
        cout<<"1. Insert"<<endl;
        cout<<"2. TableSize"<<endl;
        cout<<"3. Display"<<endl;
        cout<<"57. exit"<<endl;
        cout<<"------------------------"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                insertion(n);
                break;
            case 2:
                cout<<"The table size is: "<<n<<endl;
                break;
            case 3:
                display();
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
