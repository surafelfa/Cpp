#include <iostream>
using namespace std;
void populate();
int gcd(int,int );
void cal(int& , int& , char& , int& , int&,int &, int &);
int main(){
	populate();
	return 0;
}
void populate(){
	int a,b,c,d,denominator, numerator;
	char oper;
	cout<<"Enter a,b an operater, c, and d respectively: ";
	cin>>a>>b>>oper>>c>>d;
	cal(a,b,oper,c,d,numerator,denominator);
	cout<<endl<<a<<'/'<<b<<oper<<c<<'/'<<d<<'='<<numerator<<'/'<<denominator;
}
void cal(int &a,int &b,char &oper,int &c,int &d,int &numerator,int &denominator){
	int g_c_d;
/*	g_c_d=gcd(a,b);a/=g_c_d;b/=g_c_d;
	g_c_d=gcd(c,d);c/=g_c_d;d/=g_c_d;*/
	if(oper=='*'){
		numerator=a*b;
		denominator=c*d;
	}else if (oper=='/'){
		numerator=a*d;
		denominator=c*b;
	}else{
		if(oper=='+'){
		numerator = (a*d)+(c*b);
		denominator= b*d;
		}else{
			numerator=(a*d)-(b*c);
			denominator=b*d;
		}
	}if(numerator!=0){
	g_c_d=gcd(numerator,denominator);
	numerator/=g_c_d;denominator/=g_c_d;
	}
}
int gcd(int x, int y){
	int n=x,m=y;
	while(n!=m){
		if (n>m)n=n-m;
		else m=m-n;
	}
	return n;
}
