/* A program used  to display a diamond.
*/
#include <iostream>
using namespace std;
void displayTriangle();
void displayInvertedTriangle();
int a;
int main() {
	displayTriangle();
	displayInvertedTriangle();
	return 0;
}
void displayTriangle() {
	int h=5,count=0,count1=0,c=0;
	for (int i=1 ; i<=5; ++i){
		for (int space =1 ; space<=5-i; ++space){
			cout<<"  ";
			++count;
		//c!=2*i-1 tells how many times the while loop is going to be executed.
		}while(c!=2*i-1){
			if( count<=4){
				cout<<h+c<<" ";
				++count;
				a=h+c-1;//a number that comes immediately after 5
			}else {
				cout<<a-count1<<" ";
				++count1;
			}++c;
		}count = count1=c=0;//these variables have to be initialized immediately after the while loop.
		--h;
		cout<<endl;
	}
}
void displayInvertedTriangle(){
	int h=2, count=0,count1=0,c=0;
	/*a and c!=2*i-1 have the same meaning as before.
	these nested for loops are used to display an inverted pyramid that has four rows*/
	for (int i=4 ; i>=1; --i){
		for (int space =0 ; space<=4-i; ++space){
			cout<<"  ";
			++count;
		}while(c!=2*i-1){
			if( count<=4){
				cout<<h+c<<" ";
				++count;
				a=h+c-1;
			}else {
				cout<<a-count1<<" ";
				++count1;
			}++c;
		}count = count1=c=0;
		++h;
		cout<<endl;
	}
}

