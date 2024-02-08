/*A Program that performs Merge Sort in the given element*/
#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& a, int low, int mid, int high)
{
    int i = low, h = low, j = mid + 1;
    vector<int> b(high - low + 1);
    while (h <= mid && j <= high)
    {
        if (a[h] <= a[j])
        {
            b[i - low] = a[h];
            h++;
        }
        else
        {
            b[i - low] = a[j];
            j++;
        }
        i++;
    }
    while (h <= mid)
    {
        b[i - low] = a[h];
        i++;
        h++;
    }
    while (j <= high)
    {
        b[i - low] = a[j];
        i++;
        j++;
    }
    for (int k = low; k <= high; k++)
    {
        a[k] = b[k - low];
    }
}

void mergeSort(vector<int>& a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

int main()
{
    int n;
    cout << "Enter Number of elements: ";
    cin >> n;
    cout << endl;
    vector<int> a(n);
    cout << "Enter the elements: " << endl;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Elements before sorting: " << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    mergeSort(a, 0, n - 1);
    cout << "\nElements after Merge Sort: " << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    return 0;
}
