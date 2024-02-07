/*A Program that performs Quick Sort in the given element*/
#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& a, int low, int high)
{
    int pivot = a[low], i = low + 1, j = high;
    while (i <= j)
    {
        while (i <= high && a[i] <= pivot)
            i++;
        while (j >= low && a[j] > pivot)
            j--;
        if (i < j)
        {
            swap(a[i], a[j]);
        }
    }
    swap(a[low], a[j]);
    return j;
}

void quickSort(vector<int>& a, int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, low, high);
        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int main()
{
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    vector<int> a(n);
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++)
        cin >> a[i];
    cout << "Elements before sorting: " << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    quickSort(a, 0, n - 1);
    cout << "\nElements after Quick sort: " << endl;
    for (int i = 0; i < n; i++)
        cout << a[i] << " ";
    return 0;
}
