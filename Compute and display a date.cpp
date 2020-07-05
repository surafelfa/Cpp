/* A program that compute and display a date after n days of a given Gregorian date.
   This program was written by Surafel Fantu   */
#include <iostream>
#include <stdlib.h>
using namespace std;
void displayThedate();
void whenNegativeNumOrZeroIsEntered(){
	cout<<"You entered zero or a negative number";
}
void aboutDay(){
	cout<<"You entered a wrong day";
}
void aboutMonth(){
	cout<<"Error, month can not be grater than twelve";
}
unsigned int day,month,year,n;//global variables
int main() {

	cout<<"Enter the day, the month, and the year respectively.\n";
	cin>>day>>month>>year;
	cout<<"After how many days do you want to know the date.\n";
	cin>>n;
	if(day<=0||month<=0||year<0||n<0)whenNegativeNumOrZeroIsEntered();
	else if((month==4||month==6||month==9||month==11)&&day>30)aboutDay();
	else if((month==2&&((year%4==0&&(year%100!=0))||(year%400==0)))&&day>29)aboutDay();
	else if((month==2&&(!((year%4==0&&(year%100!=0))||(year%400==0))))&&day>28)aboutDay();
	else if(day>31)aboutDay();
	else if(month>12)aboutMonth();
	else displayThedate();

	cout<<endl;

	system("pause");
	return 0;
}
void displayThedate(){

	while(n!=0){
		day++;
		if(day==31&&(month==4||month==6||month==9||month==11)){
			++month;
			day=1;
		}else if(((year%4==0&&(year%100!=0))||(year%400==0))&&(day==30&&month==2)){
			++month;
			day=1;
		}else if(!((year%4==0&&(year%100!=0))||(year%400==0))&&(day==29&&month==2)){
			++month;
			day=1;
		}
		else if(day==32){
			++month;
			day=1;
			if(month==13){
				++year;
				month=1;
			}
		}
		--n;
	}
	cout<<day<<'/'<<month<<'/'<<year<<endl;
}
