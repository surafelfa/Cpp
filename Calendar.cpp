#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int main()
{
    int year,weekEndGr,weekDay,hab=23,maxED=30,pagume=5,cnt=1,v,ans;
    do{
        cout<<"enter the year for the calnder you want to see: ";
        cin>>year;
        const string mon[12]={"JANUARY","FEBRUARY","MARCH","APRIL","MAY","JUNE","JULY","AUGUST","SEPTEMBER","OCTOBER","NOVEMBER","DECEMBER"};
        const string mon2[12]={"tahsas/tir","tir/yekatit","yekatit/megabit","megabit/miyazya","miyaziya/ginbot","ginbot/sene","sene/hamle","hamle/nehase","nehase/pagume/meskerem","meskerem/tikimt","tikemt/hidar","hidar/tahsas"};
        const string dy[]={"SUN","MON","TUE","WED","THU","FRI","SAT"};
        int gmd[]={31,28,31,30,31,30,31,31,30,31,30,31};
        if (year%4==0&&year%100!=0||year%400==0){
            gmd[1]=29;
            hab=22;
            pagume=6;
        }
        weekDay = (((year - 1) * 365) + ((year - 1) / 4) - ((year - 1) / 100) + ((year) / 400) + 1) % 7;
        weekEndGr=weekDay;
        for(int i=0;i<12;i++){
                cout<<"\n\n";
                if (i<=7)
                    cout<<setw(12)<<" "<<mon[i]<<year<<"-----"<<mon2[i]<<year-8<<endl;
                else if(i==8)
                    cout<<setw(7)<<" "<<mon[i]<<year<<"-----"<<mon2[i]<<year-8<<"/"<<year-7<<endl;
                else
                    cout<<setw(12)<<" "<<mon[i]<<year<<"-----"<<mon2[i]<<year-7<<endl;
                cout<<setfill('-')<<setw(56)<<""<<setfill(' ')<<endl;
            for(int j=0;j<7;j++){
                cout<<setw(4)<<dy[j]<<setw(4)<<'|';
                if (j==6)
                    cout<<endl;
            }
            cout<<setfill('-')<<setw(56)<<""<<setfill(' ')<<endl;
            for(int d=0;d<weekDay;d++){
                cout<<setw(8)<<" ";
            }
            for (int k=1;k<=gmd[i];k++){
                cout<<setw(2)<<k<<"  "<<setw(2)<<hab<<setw(2)<<'|';
                hab++;
                if (hab==31){
                    cnt++;
                    hab=1;}
                if(cnt==10&&hab>pagume){
                        hab=2;cnt++;
                }
                weekEndGr++;
                while(weekEndGr>6){
                    cout<<endl;
                    cout<<setfill('-')<<setw(56)<<""<<setfill(' ')<<endl;
                    weekEndGr=0;
                }
                weekDay=weekEndGr;
            }
            v=weekDay*8;
            cout<<endl;
            cout<<setfill('-')<<setw(v)<<""<<setfill(' ')<<endl;
            if(i==0)
                cout<<"TAHSAS 29 Gena"<<setw(7)<<" "<<"January 7 Ethiopian Chrismas"<<endl<<"TIR 11 Temket"<<setw(7)<<"January 19 Ethiopian Epiphany"<<endl;
            else if(i==2)
                cout<<"YEKATIT 23 Adwa"<<setw(7)<<" "<<"March 2 - Victory of Adwa"<<endl;
            else if (i==3)
                cout<<"MEGABIT 28 Sekelet"<<setw(7)<<" "<<"April 6 Ethiopian Good Friday"<<endl<<"MEGABIT 30 Tensase"<<setw(7)<<"April 8 Ethiopian Easter"<<endl;
            else if (i==4)
                cout<<"MIYAZIA 23 Yelabaderoch Ken"<<setw(7)<<" "<<"May 1 International Labour Day"<<endl<<"MIYAZIYA 27 Yedel Beal"<<setw(7)<<" "<<"May 5 Ethiopian Patriots Day"<<endl<<
                "Ginbot 20 Yederg Aserar Yewedekebet"<<setw(7)<<" "<<"Overthrow of the Deurge Regime"<<endl;
            else if (i==5)
                cout<<"Sene 8 Remedan"<<setw(7)<<" "<<"June 15 Eid Al Fitr"<<endl;
            else if (i==7)
                cout<<"Nehase 15 Arefa"<<setw(7)<<" "<<"August 21 Eid Al Adha"<<endl;
            else if (i==8)
                cout<<"Meskerem 1 Zemen Melewecha"<<setw(7)<<" "<<"September 11 Ethiopian New Year"<<endl<<"Meskerem 17 Meskel"<<setw(7)<<" "<<"September 27 Finding of the True Cross"<<endl;
            else (i==11);
                cout<<"Hidar 11 Mawlid"<<setw(7)<<" "<< "December 20 Mawlid"<<endl;
        }
        cout<<"\n\n enter '0' to quit program"<<endl;
        cout<<"press '1' to Continue? ";
        cin>>ans;
    }
    while(ans!=0);
  return weekDay;
}
