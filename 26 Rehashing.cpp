/*A program to demonstrate rehashing*/
#include<iostream>
using namespace std;

int A[100],h[100],M,nv=0;
int ele,idx,hkey,i;
double u;

class Lprobing{
public:
    void insert1(int);
    void delete1(int);
    void display(int);
    void search1(int);
    void rehashing();
    void Lprobe(int x);
};

void Lprobing :: Lprobe(int M){
    idx = ele % M;
    if(h[idx] == NULL)
        h[idx] = ele;
    else{
        for(i=0;i<M;i++){
            hkey = (idx + i) % M;
            if(h[hkey] == NULL){
                h[hkey] = ele;
                break;
            }
        }
        if(i==M)
            cout<<"No space for Extra element";
    }
}

void Lprobing :: insert1(int M){
    cout<<"Enter element to insert: ";
    cin>>ele;
    nv++;
    cout<<nv/u<<endl;
    if((nv/u)<0.75){
        Lprobe(M);
    }else{
        for(i=0;i<M;i++)
            A[i]=h[i];
        rehashing();
    }
}

void Lprobing ::rehashing(){
     int x;
     M = 2*M;
     for(int i=0;i<M;i++)
        h[i]=0;
     for(i=0;i<M;i++){
         x = A[i] % M;
         if(h[x]== NULL)
            h[x] = A[i];
         else{
            for(int j=0;j<M;j++){
                hkey = (x + j) % M;
                if(h[hkey] == NULL){
                    h[hkey] = A[i];
                    break;
                }
            }
         }
     }
    u = 2*u;
    if((nv/u)<0.75)
        Lprobe(M);
}

void Lprobing ::display(int M){
    cout<<"\tHASH TABLE\t"<<endl;
    cout<<"Indices\t\tElements"<<endl;
    for(i=0;i<M;i++)
        cout<<i<<"\t\t"<<h[i]<<endl;
}

void Lprobing ::delete1(int M){
    cout<<"Enter element to delete: ";
    cin>>ele;
    idx = ele % M;
    if(h[idx] == ele)
        h[idx] = NULL;
    else{
        for(i=0;i<M;i++){
            hkey = (idx + i)%M;
            if(h[hkey] == ele){
                h[hkey]=NULL;
                break;
            }
        }
    }
    cout<<"After deleting "<<ele<<endl;
    cout<<"Elements are: "<<endl;
    display(M);
}

void Lprobing :: search1(int M){
    cout<<"Enter element to search: ";
    cin>>ele;
    idx = ele % M;
    if(h[idx] == ele)
        cout<<"Element "<<ele<<" found at index "<<idx<<endl;
    else{
        for(i=0;i<M;i++){
            hkey = (idx + i)%M;
            if(h[hkey] == ele){
                cout<<"Element "<<ele<<" found at index "<<hkey<<endl;
                break;
            }
        }
    }
}

int main(){
    int ch;
    Lprobing L;
    cout<<"Enter table size: ";
    cin>>M;
    cout<<"Enter load factor value: ";
    cin>>u;
    cout<<"MENU \n1.Insert()\n2.Delete()\n3.Search()\n4.Display()\n5.Exit"<<endl;
    do{
        cout<<"Enter your choice: ";
        cin>>ch;
        switch(ch){
            case 1 : L.insert1(M);
                break;
            case 2 : L.delete1(M);
                break;
            case 3 : L.search1(M);
                break;
            case 4 : L.display(M);
                break;
            case 5 :
                return 0;
            default : cout<<"Choice out of Range!!!"<<endl;
        }
    }while(1);
}

