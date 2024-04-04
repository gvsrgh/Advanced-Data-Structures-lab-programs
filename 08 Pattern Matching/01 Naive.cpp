/* A program to demonstrate Naive's Algorithm*/
#include <iostream>
#include <vector>

using namespace std;

vector<int> naive(int n,string txt,int m,string pt){
    int i,j;
    vector<int> res;
    for(i = 0;i<=n-m;i++)
    {
        for(j=0;j<m;j++)
            if(txt[i+j]!=pt[j])
                break;
        if(j==m)
            res.push_back(i);
    }
    return res;
}

int main(){
    string txt;
    string pt;
    cout<<"\nEnter the text: ";
    cin >> txt;
    cout<<"\nEnter the pattern: ";
    cin>>pt;
    vector<int> res;
    res = naive(txt.size(),txt,pt.size(),pt);
    cout<<"\nThe patter found at the indices: "<<endl;
    for(int i = 0;i<res.size();i++)
        cout<<res[i]<<" ";
    cout<<endl;
    return 0;
}
