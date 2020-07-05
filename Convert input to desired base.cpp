/*A program that changes input number into any desired base.
*/
#include <iostream>
#include <cmath>
#include <cstdlib>
using namespace std;
long long decimalTobinary(int );
int binaryTodecimal(long long );
int octalTodecimal(int );
int decimalTooctal(int );
void inputIsLessThan0(){
	cout<<"Error! you have not entered a positive number at first.";
}
void whenBaseIsNotAsExpected(){
	cout<<"Error! you have not entered 2 or 8 or 10 as an input base.";
}
void forNumber_8_and_9(){
	cout<<"Error! eight and nine can not be expressed in base eight.";
}
int main() {
	long long num,x,inBase,placeHolder;
	cout<<"Please, follow the instructions to get the right answer. If you don't do so you won't get the correct answer."<<endl;
	cout<< "Enter a positive number:   ";
	cin>>num;
	cout<<"What is the base of the number that you have entered? Input 2 or 8 or 10. "<<endl;
	cin>>inBase;
	cout<<"In what base do you want the number? "<<endl;
	cin>>x;
	//system("cls");
	if(num<0)inputIsLessThan0();
	else if(!(inBase==2||inBase==8||inBase==10))whenBaseIsNotAsExpected();
	else if (!((num!=9||inBase!=8)&&(num!=8||inBase!=8)))forNumber_8_and_9();
	else if(inBase==2&&x==2)cout<<num;
	else if(inBase==8&&x==8)cout<<num;
	else if(inBase==10&&x==10)cout<<num;
	else if(inBase==2&&x==10)cout<<binaryTodecimal(num);
	else if(inBase==2&&x==8){
		placeHolder=binaryTodecimal(num);
		cout<<decimalTooctal(placeHolder);}
	else if(inBase==8&&x==2){
		placeHolder=octalTodecimal(num);
		cout<<decimalTobinary(placeHolder);}
	else if(inBase==8&&x==10)
		cout<<octalTodecimal(num);
	else if(inBase==10&&x==2)
			cout<<decimalTobinary(num);
	else
		cout<<decimalTooctal(num);
	cout<<endl;
	system("pause");
	return 0;
}
long long decimalTobinary(int num){
	long long binaryNum=0;
	int i=1, remainder;
	while (num!=0){
		remainder=num%2;
		num/=2;
		binaryNum += remainder*i;
		i *=10;
	}
	return binaryNum;
}
int binaryTodecimal(long long num){
	int remainder, i = 0, decimalNum=0;
	while (num!=0){
		remainder = num%10;
		decimalNum+=remainder*pow(2,i);
		num/=10;
		++i;
	}
	return decimalNum;
}
int octalTodecimal(int num){
	int remainder, decimalNum=0,i=0;
	while(num!=0){
		remainder=num%10;
		decimalNum += remainder*pow(8,i);
		num/=10;
		++i;
	}
	return decimalNum;
}
int decimalTooctal(int num){
	int remainder,octalNum=0,i=1;
	while(num!=0){
		remainder =num%8;
		octalNum += remainder*i;
		num/=8;
		i *=10;
	}
	return octalNum;
}


