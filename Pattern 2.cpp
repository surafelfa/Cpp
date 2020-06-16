#include <iostream>
using namespace std;
#include <conio.h>
#define PI 3.14
const int HALF_ANGLE=180;
int main (){

/**	float degree,angleInRadian;
	cout<<"enter an angle in degree that you want to change into radian: ";
	cin>>degree;
	angleInRadian=(degree*PI)/HALF_ANGLE;
	cout<<angleInRadian<<"rad\n\n";

	int second,hours,rsecond,minutes;
	cout<<"enter the number of time elapsed for an event: ";
	cin>>second;
	hours=second/3600;
	minutes=(second%3600)/60;
	rsecond=(second%3600)%60;
	cout<<hours<<":"<<minutes<<":"<<rsecond<<".\n\n";**/

	int y,aNumber,placeHolderFor_aNumber,x,z=1,a=10000;
	cout<<"enter an integer in the range 0 to 32767:"<<endl;
	cin>>aNumber;
	cout<<"\n";
	if (aNumber>0 && aNumber<32767){
		for (int i=5;i>=1;--i){
			placeHolderFor_aNumber=aNumber;
			y=10000/z;
			z=z*10;
			for(int j=1;j<=i;++j){
				x=placeHolderFor_aNumber/y;
				cout<<x<<"\t";
				placeHolderFor_aNumber=placeHolderFor_aNumber%y;
				y=y/10;}
		cout<<endl<<endl;
		aNumber=aNumber%a;
		a=a/10;}}
	else{
	cout<<"you have entered a wrong character.\n";}
	getch();
}
