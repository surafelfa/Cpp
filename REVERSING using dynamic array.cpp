#include<iostream>
#include<cstdlib>
using namespace std;
void populate(int *arr,int n){
    for(int i=0;i<n;i++){
        cout<<"Enter element "<<i+1<<": ";
        cin>>arr[i];
    }
}
void display(int* arr,int n){
    cout<<"The elements of the array\n";
    for(int i=0;i<n;i++)
        cout<<arr[i]<<", ";
}
void displayReverse(int* arr,int n){
    cout<<"\nIn a reverse direction\n";
    for(int i=n-1;i>=0;i--)
        cout<<arr[i]<<", ";
}
int main(){
    int *p,n;
    cout<<"Enter the number of elements ";
    cin>>n;
    p=new(nothrow)int[n];
    if(p!=NULL){
        populate(p,n);
        system("cls");
        display(p,n);
        displayReverse(p,n);
    }
    else
        cout<<"Insufficient memory";
    delete []p;
    return 0;
}
