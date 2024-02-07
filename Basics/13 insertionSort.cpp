/*A Program that performs Insertion Sort in the given element*/
#include <iostream>
using namespace std;

int insertionSort(int n,int a[])
{
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
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
    cout<<"Elements before sorting: "<<endl;
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
    insertionSort(n,a);
    cout<<"\nElements after Insertion sort: "<<endl;
    for(int i=0;i<n;i++)
        cout<<a[i]<<" ";
    return 0;
}
