#include <iostream>
using namespace std;
int main() {
	// B
	for (int i=1;i<=9;++i){
		if (i==4 || i== 7)cout<<endl;
		cout <<i<<' ';
	}
	cout<<endl<<endl;
	//c
	int p= 0 ,x=1,y=0;
	for ( int i=5 ;i>=1; --i){
		for (int k= 1; k<=p; ++k){
			cout<<"  ";
		}++p;
		y=i+x;
		for ( int j=x ;j<y; j++){
			cout<<j<<" ";
		}x=x+1;cout<<endl;
	}
	// H
	int z=97,e=1,f=2;
	for(int i=1;i<=7;++i){
		for (int j =1 ;j<=i;++j){
			cout<<char(z)<<" ";
			z=z+1;
		}
		cout<<endl;
		z=97;
	//	e=e+f;
	//	++f;	
	}
	cout<<endl;
	//G
	for (int i=6;i>=1;--i){
		if(i==2)cout<<"* *\n";
		for(int j=1;j<=i;++j){
			cout<<"* ";
		}
		cout<<endl;
	}
	//E
	cout<<endl;
	int rows=5, count=0, count1=0, c=0,d=0,h=5;
	for (int i=5 ; i>=1; --i){
		for (int space =1 ; space<=d; ++space){
			cout<<"  ";
			++count;
		}while(c!=2*i-1){
			if( count<=rows-1){
				cout<<h-c<<" ";
				++count;
			}else {
				++count1;
				cout<<h-c+2*count1<<" ";
			}++c;
		}count = count1=c=0;
		++d;
		cout<<endl;
	}c=0, h=5,count=0,count1=0;
	for(int i=2;i<=rows;++i){
		for(int space=1; space<=rows-i ;++space){
			cout<<"  ";
			++count;
		}while (c!=2*i-1){
			if(count<=rows-1){
				cout<<h-c<<' ';
				++count;
			}else {
				++count1;
				cout<<h-c+2*count1<<" ";
			}++c;
		}count=count1=c=0;
		cout<<endl;
	} 			
	return 0;
}
	