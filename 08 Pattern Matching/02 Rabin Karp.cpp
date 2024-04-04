#include <iostream>
#include <vector>

using namespace std;

const int prime = 101; // Prime number for hashing

vector<int> rabinKarp(int n, string txt, int m, string pt) {
    vector<int> res;
    int pHash = 0; // Hash value for pattern
    int tHash = 0; // Hash value for current window of text
    int h = 1;

    // Calculate h = pow(prime, m-1) % prime
    for (int i = 0; i < m - 1; i++) {
        h = (h * prime) % prime;
    }

    // Calculate hash value for pattern and first window of text
    for (int i = 0; i < m; i++) {
        pHash = (prime * pHash + pt[i]) % prime;
        tHash = (prime * tHash + txt[i]) % prime;
    }

    // Slide the pattern over text one by one
    for (int i = 0; i <= n - m; i++) {
        // Check hash values of current window of text and pattern
        // If hash values match then only check for characters one by one
        if (pHash == tHash) {
            bool match = true;
            for (int j = 0; j < m; j++) {
                if (txt[i + j] != pt[j]) {
                    match = false;
                    break;
                }
            }
            if (match)
                res.push_back(i);
        }

        // Calculate hash value for next window of text
        // Remove leading digit, add trailing digit, and adjust hash value
        if (i < n - m) {
            tHash = (prime * (tHash - txt[i] * h) + txt[i + m]) % prime;
            if (tHash < 0) // In case of negative hash value, make it positive
                tHash += prime;
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
    res = rabinKarp(txt.size(), txt, pt.size(), pt);
    cout << "\nThe pattern found at the indices: " << endl;
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    cout << endl;
    return 0;
}

