#include <iostream>
#include <vector>

using namespace std;

vector<int> calculateLPS(string pattern) {
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> kmp(int n, string txt, int m, string pt) {
    vector<int> res;
    vector<int> lps = calculateLPS(pt);
    int i = 0; // index for txt
    int j = 0; // index for pt
    while (i < n) {
        if (pt[j] == txt[i]) {
            i++;
            j++;
        }
        if (j == m) {
            res.push_back(i - j);
            j = lps[j - 1];
        } else if (i < n && pt[j] != txt[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }
    return res;
}

int main() {
    string txt;
    string pt;
    cout << "\nEnter the text: ";
    cin >> txt;
    cout << "\nEnter the pattern: ";
    cin >> pt;
    vector<int> res;
    res = kmp(txt.size(), txt, pt.size(), pt);
    cout << "\nThe pattern found at the indices: " << endl;
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    cout << endl;
    return 0;
}

