/*
   This program converts a temperature in degree celsius to degree fahrenheit and kelvin.
   Date written ...
   Written by ...
*/
#include<iostream>
#include<conio.h>
#define CELCIUSFACTOR 1.8
const float ABSOLUTEZERO=273.15;
using namespace std;

int main ()
{
	float celsius, fahrenheit, kelvin;
	system("cls");
	cout << "Please enter the temperature in degree celsius: ";
	cin  >> celsius;
	fahrenheit=CELCIUSFACTOR*celsius + 32.0;
	kelvin=celsius + ABSOLUTEZERO;
	system("cls");
	cout << "celsius: " << celsius <<" \n";
	cout << "Fahrenheit: " << fahrenheit << "\n";
	cout << "Kelvin: " << kelvin;
	getch();
	return 0;
}
