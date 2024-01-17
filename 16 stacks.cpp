/*A program to perform operatiohns on STACK*/
#include <iostream>
#include <stack>
using namespace std;

stack<int> st;

void insertion()
{
    int val;
    cout<<"Enter the value to be pushed: "<<endl;
    cin>>val;
    st.push(val);
}

void deletion()
{
    if(st.empty())
    {
        cout<<"Stack Underflow"<<endl;
        return;
    }
    int val = st.top();
    st.pop();
    cout<<"Top most element "<<val<<" is popped"<<endl;
}

void topElement()
{
    if(st.empty())
    {
        cout<<"Stack Underflow"<<endl;
        return;
    }
    cout<<"Top most element is "<<st.top()<<endl;
}

void stackSize()
{
    cout<<"Stack size: "<<st.size()<<endl;
}

void isEmpty()
{
    if(st.empty())
        cout<<"Stack is empty"<<endl;
    else
        cout<<"Stack is not empty"<<endl;
}

void display()
{
    stack<int> temp;
    temp = st;
    while(!temp.empty())
    {
        int val = temp.top();
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
        cout<<"1. Push"<<endl;
        cout<<"2. Pop"<<endl;
        cout<<"3. Peek"<<endl;
        cout<<"4. Size"<<endl;
        cout<<"5. isEmpty"<<endl;
        cout<<"6. Display"<<endl;
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
                topElement();
                break;
            case 4:
                stackSize();
                break;
            case 5:
                isEmpty();
                break;
            case 6:
                display();
                break;
            default:
                cout<<"Please select a valid choice"<<endl;
        }
    }
}
