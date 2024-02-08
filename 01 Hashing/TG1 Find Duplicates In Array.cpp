#include <bits/stdc++.h> 
using namespace std;

vector < int > findDuplicates(vector < int > & arr, int n) {
    unordered_map<int, int> freq;
    vector<int> duplicates;

    for (int i = 0; i < n; i++) {
        freq[arr[i]]++;
        if (freq[arr[i]] == 2) {
            duplicates.push_back(arr[i]);
        }
    }
    return duplicates;
}
