#include <iostream>
using namespace std;
#include <conio.h>
#include<stdlib.h>
void list_of_primes(int x , int y);
int main (){
int i,f;
	cout<<"enter the first: ";
	cin>>i;
	cout<<"enter the last: ";
	cin>>f;
	list_of_primes(i , f);
//	getch();
	return 0;
}
void list_of_primes(int x , int y){
	int isPrime,j;
	for (x=x+1;x<y;++x){
		isPrime=1;
		for(j=2;j<=x/2 && isPrime;++j){
			if(x%j==0){
				isPrime=0;}
				}
	if(isPrime) cout<<x<<" ";		}
}

