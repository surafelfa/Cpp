#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <iomanip>
using namespace std;
const int ESC=27;

int t_convert(int ,char &);
void t_input(int&,int&);
void t_desplay(int,int,char);

int main(){
int h,m,covHr;
int key;
char me;
do {
    t_input(h,m);
    covHr=t_convert(h,me);
    if (covHr==0)cout<<"invalid input";
    else t_desplay(covHr,m,me);
    cout<<("\npress Any key to  continue or ESC to Exit")<<endl;
    key=getche();

 } while (key != ESC);

return 0;
}


int t_convert(int hh,char &merd){
    if( hh==0){
        merd='A';
        return 12;
      }
    else if (hh>0&&hh<=12){
        merd='A';
        return hh;
      }
    else if (hh<=23&&hh>12){
        merd='P';
        return hh-12;
    }
    else return 0;

}


void t_input(int &hh,int &mm){

cout<<"Enter the hour and minute to be converted separated by space >> ";
cin>>hh>>mm;

}

void t_desplay(int hr,int mn, char merd){
  if (merd=='A')
    cout<<setw(2)<<setfill('0')<<hr<<":"<<setfill('0')<<setw(2)<<mn<<" AM";
  else cout<<hr<<" : "<<mn <<" PM";
 }




