/*A program to perform operatiohns on Queue*/
#include <iostream>
#include <queue>
using namespace std;

queue<int> qu;

void insertion()
{
    int val;
    cout<<"Enter the value to be enqueued: "<<endl;
    cin>>val;
    qu.push(val);
}

void deletion()
{
    if(qu.empty())
    {
        cout<<"Queue Underflow"<<endl;
        return;
    }
    int val = qu.front();
    qu.pop();
    cout<<"Top most element "<<val<<" is dequed"<<endl;
}

void frontElement()
{
    if(qu.empty())
    {
        cout<<"Queue is empty"<<endl;
        return;
    }
    cout<<"Front element is "<<qu.front()<<endl;
}

void rearElement()
{
    if(qu.empty())
    {
        cout<<"Queue is empty"<<endl;
        return;
    }
    cout<<"Rear element is "<<qu.back()<<endl;
}

void queueSize()
{
    cout<<"Stack size: "<<qu.size()<<endl;
}

void isEmpty()
{
    if(qu.empty())
        cout<<"Stack is empty"<<endl;
    else
        cout<<"Stack is not empty"<<endl;
}

void display()
{
    queue<int> temp;
    temp = qu;
    while(!temp.empty())
    {
        int val = temp.front();
        temp.pop();
        cout<<val<<" ";
    }
    cout<<endl;
}

int main()
{
    int choice;
    while(1)
    {
        cout<<"--------------Menu--------------"<<endl;
        cout<<"1. Enqueue"<<endl;
        cout<<"2. Dequeue"<<endl;
        cout<<"3. front"<<endl;
        cout<<"4. rear"<<endl;
        cout<<"5. Size"<<endl;
        cout<<"6. isEmpty"<<endl;
        cout<<"7. Display"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                insertion();
                break;
            case 2:
                deletion();
                break;
            case 3:
                frontElement();
                break;
            case 4:
                rearElement();
                break;
            case 5:
                queueSize();
                break;
            case 6:
                isEmpty();
                break;
            case 7:
                display();
                break;
            default:
                cout<<"Please select a valid choice"<<endl;
        }
    }
}
