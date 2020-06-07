#include <iostream>
#include <iomanip>
using namespace std;
#include <conio.h>
#include<stdlib.h>
const float REGULAR_RATE= 16.78, OVERTIME_RATE=25.17, SOCIAL_SECURITY_TAX=0.06,FEDERAL_INCOME_TAX=0.14,
STATE_INCOME_TAX=0.05,UNION=10,INSURANCE=35,REGULAR_HOURS=40,HOURS_IN_WEEK=168;
int main (){
	float hour,withholding,grosspay,netpay;
	unsigned short dependent;
	cout<<"how many hours did a worker work in a week: ";
	cin>>hour;
	if (hour>=0 && hour<=HOURS_IN_WEEK) {
		cout<<"\nhow many dependents does a worker have: ";
		cin>>dependent;
			if(dependent>0){
				if(hour<=REGULAR_HOURS){
					grosspay=REGULAR_HOURS*hour;
				}else
				grosspay=REGULAR_HOURS*hour + (hour-REGULAR_HOURS*OVERTIME_RATE);
				withholding=(SOCIAL_SECURITY_TAX+FEDERAL_INCOME_TAX+STATE_INCOME_TAX)*grosspay+UNION;
				if(dependent>=3) withholding+=INSURANCE;
				netpay=grosspay-withholding;
				system("cls");
				cout<<fixed<<setprecision(2)<<endl;
				cout<<"gross pay: "<<grosspay<<endl;
				cout<<"withholding: "<<withholding<<endl;
				cout<<"net pay: "<<netpay<<endl;

			}else
			cout<<"wrong input for number of dependents.";
		}else
		cout<<"wrong input for hours worked.";
	system("pause");
	return 0;

}

