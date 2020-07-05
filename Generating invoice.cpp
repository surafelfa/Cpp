/** designed by Surafel Fantu and Tsega Yilma on Saturday/01 Dec/2018 G.C.
		**/
#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<iomanip>

using namespace std;

const float UnitPriceOfTV=400,UnitPriceOfVCR=220,UnitPriceOfREMOTECTRLR=35.20,UnitPriceOfCDPLYR=300,UnitPriceOfTAPEREC=150;
int main(){
    int QuantityOfTV,QuantityOfVCR,QuantityOfREMOTECTRLR,QuantityOfCDPLYR,QuantityOfTAPEREC;
    float TotalPriceOfTV,TotalPriceOfVCR,TotalPriceOfREMOTECTRLR,TotalPriceOfCDPLYR,TotalPriceOfTAPEREC,SUBTOTAL,TAX,TOTAL;
do{cout << "enter the quantity of TV: ";
    cin >> QuantityOfTV;}
while(QuantityOfTV<0);{
	
	cout <<endl;
}

do{cout << "enter the quantity of VCR: ";
    cin >> QuantityOfVCR;}
while(QuantityOfVCR<0);{
	cout <<endl;
}

do{cout << "enter the quantity of REMOTE CTRLR: ";
    cin >> QuantityOfREMOTECTRLR;}
while(QuantityOfREMOTECTRLR<0);{
	cout <<endl;
}

do{cout << "enter the quantity of CD PLAYER: ";
    cin >>QuantityOfCDPLYR;}
while(QuantityOfCDPLYR<0);{
	cout <<endl;
}

do{cout << "enter the quantity of TAPE RECORDER: ";
    cin >> QuantityOfTAPEREC;}
while(QuantityOfTAPEREC<0);{
	cout<<endl;
}

TotalPriceOfTV = QuantityOfTV*UnitPriceOfTV;
TotalPriceOfVCR = QuantityOfVCR*UnitPriceOfVCR;
TotalPriceOfREMOTECTRLR = QuantityOfREMOTECTRLR*UnitPriceOfREMOTECTRLR;
TotalPriceOfCDPLYR =QuantityOfCDPLYR*UnitPriceOfCDPLYR;
TotalPriceOfTAPEREC =QuantityOfTAPEREC*UnitPriceOfTAPEREC;

SUBTOTAL = TotalPriceOfTV + TotalPriceOfVCR + TotalPriceOfREMOTECTRLR + TotalPriceOfCDPLYR + TotalPriceOfTAPEREC;
TAX = (SUBTOTAL*8.25)/100;
TOTAL = TAX + SUBTOTAL;

system("cls");cout << endl;

cout<<fixed<<setprecision(2);
cout<<setw(3)<<left<<"QTY"<<"\t"<<setw(15)<<left<<"DESCRIPTION"<<"\t"<<setw(10)<<left<<"UNIT PRICE"<<"\t"<<setw(11)<<left<<"TOTAL PRICE"<<"\t"<<endl<<endl;

cout<<setw(3)<<left<<QuantityOfTV<<"\t"<<setw(15)<<left<<"TV"<<"\t"<<setw(10)<<right<<UnitPriceOfTV<<"\t"<<setw(11)<<right<<TotalPriceOfTV<<"\t"<<endl;

cout<<setw(3)<<left<<QuantityOfVCR<<"\t"<<setw(15)<<left<<"VCR"<<"\t"<<setw(10)<<right<<UnitPriceOfVCR<<"\t"<<setw(11)<<right<<TotalPriceOfVCR<<"\t"<<endl;

cout<<setw(3)<<left<<QuantityOfREMOTECTRLR<<"\t"<<setw(15)<<left<<"REMOTE CTRLR"<<"\t"<<setw(10)<<right<<UnitPriceOfREMOTECTRLR<<"\t"<<setw(11)<<right<<TotalPriceOfREMOTECTRLR<<"\t"<<endl;

cout<<setw(3)<<left<<QuantityOfCDPLYR<<"\t"<<setw(15)<<left<<"CD PLAYER"<<"\t"<<setw(10)<<right<<UnitPriceOfCDPLYR<<"\t"<<setw(11)<<right<<TotalPriceOfCDPLYR<<"\t"<<endl;

cout<<setw(3)<<left<<QuantityOfTAPEREC<<"\t"<<setw(15)<<left<<"TAPE RECORDER"<<"\t"<<setw(10)<<right<<UnitPriceOfTAPEREC<<"\t"<<setw(11)<<right<<TotalPriceOfTAPEREC<<"\t"<<endl<<endl;


cout<<setw(16)<<"\t"<<setw(10)<<left<<"SUBTOTAL"<<"\t"<<setw(19)<<right<<SUBTOTAL<<"\t"<<endl;

cout<<setw(16)<<"\t"<<setw(10)<<left<<"TAX"<<"\t"<<setw(19)<<right<<TAX<<"\t"<<endl;

cout<<setw(16)<<"\t"<<setw(10)<<left<<"TOTAL"<<"\t"<<setw(19)<<right<<TOTAL<<"\t"<<endl;

getch();

return 0;
}
