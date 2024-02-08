/*A Program that performs Linear Search in the given element*/
#include <iostream>
using namespace std;

int linearSearch(int n,int a[],int target)
{
    for(int i=0;i<n;i++)
        if(a[i]==target)
            return i;
    return -1;
}

int main()
{
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    int a[n];
    cout<<"Enter "<<n<<" elements: ";
    for(int i=0;i<n;i++)
        cin>>a[i];
    int target;
    cout<<"Enter the element to be searched: ";
    cin>>target;
    int index = linearSearch(n,a,target);
    if(index==-1)
        cout<<"Element "<<target<<" not found in the array";
    else
        cout<<"Element "<<target<<" found at the index: "<<index;
    return 0;
}
