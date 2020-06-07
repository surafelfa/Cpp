#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main() {
	const int NB_STD=50;
	double md_mrk[NB_STD], mean,median,mode,stdDev,range,total=0.0,x[NB_STD],temp;
	int count[NB_STD],cpy_count[NB_STD];
	for(int i=0;i<NB_STD;i++){
		cout<<"Enter mark for student "<<i+1<<" : ";
		cin>>md_mrk[i];
		total+=md_mrk[i];
	}
	mean=total/NB_STD;
	cout<<"Mean is: "<<mean<<endl;
	double cpy_mark[NB_STD];
	for(int i=0;i<NB_STD;i++){
		cpy_mark[i]=md_mrk[i];
	}
	for(int i=0;i<NB_STD-1;i++){
		for(int j=NB_STD-1;j>i;j--){
			if(md_mrk[j]<md_mrk[j-1]){
				temp=md_mrk[j];
				md_mrk[j]=md_mrk[j-1];
				md_mrk[j-1]=temp;
			}
		}
	}
	
	median=(md_mrk[24]+md_mrk[25])/2;
	cout<<"Median is: "<<median<<endl;
	
	for(int i=0;i<NB_STD;i++){
		count[i]=0;
		cout<<md_mrk[i]<<"  ";
	}
	for(int i=0;i<NB_STD;i++){
		for(int j=0;j<NB_STD;j++){
			if(md_mrk[i]==md_mrk[j])count[i]++;	
		}	
	}
	for(int i=0;i<NB_STD;i++){
		cpy_count[i]=count[i];
	}
	for(int i=0;i<NB_STD-1;i++){
		for(int j=NB_STD-1;j>i;j--){
			if(count[j]<count[j-1]){
				temp=count[j];
				count[j]=count[j-1];
				count[j-1]=temp;
			}
		}
	}
	int count1=0;
	for(int i=0;i<NB_STD;i++){
		if(count[NB_STD-1]==cpy_count[i]){
			++count1;
			cout<<endl<<"Mode is: "<<cpy_mark[i]<<endl;
		}
	}
	range=md_mrk[49]-md_mrk[0];
	cout<<"Range is: "<<range<<endl;
	for(int i=0;i<NB_STD;i++){
		x[i]=cpy_mark[i]-mean;
	}
	total=0.0;
	for(int i=0;i<NB_STD;i++){
		x[i]=x[i]*x[i];
		total +=x[i];
	}
	mean=total/NB_STD;
	stdDev=sqrt(mean);
	cout<<"Standard Deviation: "<<stdDev<<endl;
	return 0;	
}
	
