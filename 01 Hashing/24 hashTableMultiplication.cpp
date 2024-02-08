/*A Program to insert elements into hashtable using mid-square method*/
#include <iostream>
#include <map>
using namespace std;

map<int,int> ht;

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

int calculateIndex(int k, int s,float A) {
     return (int) (s * (k * A - (int)(k * A)));
}


void insertion(int n,float A)
{
    int key;
    cout<<"Enter the value to be inserted: ";
    cin>>key;
    int index = calculateIndex(key,n,A);
    if(ht.find(index)!=ht.end())
    {
        cout<<"Collision occured!!!"<<endl;
        return;
    }
    ht[index] = key;
    cout<<"Insertion Successfull!!"<<endl;
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
    cout<<"Enter the table size: ";
    cin>>t;
    int n = getPrime(t);
    cout<<"Rounding of the table size to nearest prime number: "<<n<<endl;
    float A;
    cout<<"Enter a number between 0 and 1: ";
    cin>>A;
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
                insertion(n,A);
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
