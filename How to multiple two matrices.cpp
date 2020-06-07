#include<iostream>
#include<iomanip>
using namespace std;

struct matrix{
    int rowsize=0,colsize=0;
    int **elms='\0';
};
int create(matrix &m){
   m.elms=new(nothrow)int * [m.rowsize] ;
   if(m.elms==NULL)
    return 0;
    for(int i=0;i<m.rowsize;i++){
        m.elms[i]=new(nothrow)int[m.colsize];
        if(m.elms[i]==NULL){
            for(int j=0;j<i;j++)
                delete []m.elms[j];
            delete [] m.elms;
            m.colsize=m.rowsize=0;
            m.elms='\0';
            return 0;
        }
    }
    return 1;
}
void destroy(matrix &m){
    if(m.elms!=NULL){
        for(int i=0;i<m.rowsize;i++)
            delete [] m.elms[i];
        delete [] m.elms;
    }
    m.colsize=m.rowsize=0;
    m.elms='\0';
}
void populate(matrix m){
    cout<<"enter the matrix data: \n";
    for(int i=0;i<m.rowsize;i++){
        for(int j=0;j<m.colsize;j++)
            cin>>m.elms[i][j];
    }
}
void display(matrix m){
    cout<<"Result\n ";
    for(int i=0;i<m.rowsize;i++){
        for(int j=0;j<m.colsize;j++)
            cout<<setw(4)<<m.elms[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}
int getMatrix(matrix &m, string prompt){
    cout<<prompt<<": "<<endl;
    do{
        cout<<"enter row and column size: ";
        cin>>m.rowsize>>m.colsize;
        if(m.rowsize<=0||m.colsize<=0)
            cout<<"wrong size!!!"<<endl;
    }while(m.rowsize<=0||m.colsize<=0);
    if(create(m)){
        populate(m);
        return 1;
    }
    else
        return 0;
}
int multiply(matrix a, matrix b, matrix &r){
    if(a.colsize!=b.rowsize)
        return 0;
    r.rowsize=a.rowsize;
    r.colsize=b.colsize;
    if(create(r)){
        for(int i=0;i<a.rowsize;i++){
            for(int j=0;j<b.colsize;j++){
                r.elms[i][j]=0;
                for(int k=0;k<a.colsize;k++)
                    r.elms[i][j]+=a.elms[i][k]*b.elms[k][j];
            }
        }
        return 1;
    }else
        return 2;
}
int main(){
    matrix a,b,r;
    int states;
    if(getMatrix(a,"Enter first matrix")&&getMatrix(b,"Enter second matrix")){
        states=multiply(a,b,r);
        if(states==1)
            display(r);
        else if(states==2)
            cout<<"Insufficient memory!!!"<<endl;
        else
            cout<<"Matrix can not be mult\n";
    }
    destroy(a);destroy(b);destroy(r);
    return 0;
}

