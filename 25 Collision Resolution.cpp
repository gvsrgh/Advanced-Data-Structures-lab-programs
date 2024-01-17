/*A program that demonstrates Collision resolution technique*/
#include <iostream>
#include <map>
#include <cmath>
#include <list>
using namespace std;


map<int, list<int>> ht;

int cr = 0;

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

int linearProbing(int key,int tSize, int index)
{
    while(index<tSize && (ht.find(index)!=ht.end()))
        index++;
    return index;
}

int quadraticProbing(int key,int tSize,int index)
{
    int i = 1;
    while(index<tSize && (ht.find(index)!=ht.end()))
        index = (index+i*i)%tSize,i++;
    return index;
}

int calculateStepSize(int key,int s)
{
    int stepSize = 0;
    int ti = s-1;
    for(int i = ti;i>=0;i--)
        if (isPrime(i))
        {
            ti = i;
            break;
        }
    while(stepSize==0)
        stepSize = ti-key%ti;
    return stepSize;
}

int doubleHashing(int key,int tSize,int index)
{
    int stepSize = calculateStepSize(key,tSize);
    int i = 1;
    while(index<tSize && (ht.find(index)!=ht.end()))
    {
        index = (index+i*stepSize)%tSize;
        i++;
    }
    return index;
}


int chainingT(int key, int tSize, int index)
{
    return index;
}

int calculateIndex(int t,int n)
{
    int index = t%n;
    return index;
}

void insertion(int n)
{
    int key;
    cout<<"Enter the value to be inserted: ";
    cin>>key;
    int index = calculateIndex(key,n);
    if(ht.find(index)!=ht.end())
    {
        switch(cr)
        {
            case 1:
                index = linearProbing(key,n,index);
                break;
            case 2:
                index = quadraticProbing(key,n,index);
                break;
            case 3:
                index = doubleHashing(key,n,index);
                break;
            case 4:
                index = chainingT(key,n,index);
                break;
            default:
                cout<<"Invalid Collision Choice"<<endl;
        }
    }
    if(ht.find(index)!=ht.end() && cr!=4)
    {
        cout<<"Hash Table is Full!!"<<endl;
        return;
    }
    ht[index].push_back(key);
    cout<<"Insertion Successful!!"<<endl;
}

void display(int n)
{
    for(int index=0; index<n; index++)
    {
        if(!ht[index].empty())
        {
            cout << index << " : ";
            if(cr==4){
                for(int val : ht[index])
                    cout << val << "->";
                cout<<"NULL";
            }
            else
                for(int val: ht[index])
                    cout << val <<" ";
            cout<<endl;
        }
        else
            cout << index << " : Empty" << endl;
    }
}


int main()
{
    int t,choice;
    cout<<"Enter the table size: ";
    cin>>t;
    int n = getPrime(t);
    cout<<"Rounding of the table size to nearest prime number: "<<n<<endl;
    cout<<"---Select Collision Resolution method---"<<endl;
    cout<<"1. Linear Probing"<<endl;
    cout<<"2. Quadratic Probing"<<endl;
    cout<<"3. Double Hashing"<<endl;
    cout<<"4. Chaining"<<endl;
    cout<<"----------------------------------------"<<endl;
    cout<<"Enter your choice: ";
    cin>>cr;
    while(1)
    {
        cout<<"----------Hash Table Menu----------"<<endl;
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
                cout<<"Initial table size is: "<<t<<endl;
                cout<<"Final table size is: "<<n<<endl;
                break;
            case 3:
                display(n);
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
