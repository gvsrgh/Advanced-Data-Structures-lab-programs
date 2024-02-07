/*A Program that performs Binary Search in the given element*/
#include <iostream>
using namespace std;

int bianrySearch(int a[],int target,int low,int high)
{
    while(low<=high)
    {
        int mid = (low+high)/2;
        if(a[mid]==target)
            return mid;
        else if(target<a[mid])
            high = mid-1;
        else
            low = mid+1;
    }
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
    int index = bianrySearch(a,target,0,n-1);
    if(index==-1)
        cout<<"Element "<<target<<" not found in the array";
    else
        cout<<"Element "<<target<<" found at the index: "<<index;
    return 0;
}
