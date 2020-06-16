#include<iostream>
#include<cstring>
#include<fstream>
#include<cstdlib>
#include<iomanip>
///The contact Index will be updated as the application killed!!!
///written by Surafel Fantu...
using namespace std;
struct contact {
    char name[80];
    char phone[15];
    char email[80];
};
struct conIdex{
    char name[80];
    char phone[15];
    long  position;
};
const contact BLANK_CONTACT={"","",""};
inline void Welcome(){
    cout<<"                 Welcome to this contact book application!\nWith the help of this" ;
    cout<<" application you are able to add, edit,or remove any contact.";
}
inline void fareWall(){
    system("cls");
    cout<<"\n           Thank you for using our contact book application! Goodbye.\n";
}
int openFile(fstream & fcon,char *path){
    fcon.open(path,ios::in|ios::out|ios::binary);
    if(fcon)
        return 1;
    else{
        ofstream ofs(path);
        if(ofs){
            ofs.close();
            openFile(fcon,path);
        }else
            return 0;
    }
}
int loadingContactFile(fstream &fcon, conIdex * &idx, long &n, int &fs){
    long m=0;
    contact con;
    fcon.seekg(0,ios::end);
    m=fcon.tellg()/sizeof(con);
    idx=new (nothrow) conIdex[m + 10];
    n=0;
    if(idx){
        fcon.seekg(0,ios::beg);
        for(long i=0; i< m; i++){
            idx[n].position=fcon.tellg();
            fcon.read((char *)&con, sizeof(contact));
            strncpy(idx[n].name,con.name,79);
            strncpy(idx[n].phone,con.phone,14);
            n++;
        }
        fs=m + 10-n;
        return 1;
    }else
        return 0;
}
inline void GetContactInfo(char prompt[], char input[],int Size=80){
    cout<<prompt;
    cin.getline(input,Size);
}
contact Add(){
    system ("cls");
    contact con;
    cin.ignore(INT_MAX,'\n');
    GetContactInfo("Enter a full name: ",con.name);
    GetContactInfo("Enter a phone number: ",con.phone,15);
    GetContactInfo("Enter a email address: ",con.email);
    return con;
}
int AddContact(fstream &fcon,conIdex * &idx,int &fs,long &n){
    system ("cls");
    contact newCon;
    conIdex *temp;
    if(fs==0) {
        temp=new (nothrow) conIdex[n+ 10];
        if(temp){
            for(long i=0;i<n;i++)
                temp[i]=idx[i];
            delete [] idx;
            idx=temp;
            fs=10;
        }else
            return 0;
    }
    newCon=Add();
    fcon.seekp(0,ios::end);
    idx[n].position=fcon.tellp();
    strncpy(idx[n].name,newCon.name,79);
    strncpy(idx[n].phone,newCon.phone,14);
    fcon.write((char *)&newCon,sizeof(newCon));
    n++;fs--;
    return 1;
}
long SearchByPhone(conIdex *idx,char input[],long n){
    bool found= false;
    for(long i=0;(i<n)&&(!found);i++){
		if(strcmp(idx[i].phone,input)==0){
            found=true;
            return idx[i].position;
		}
	}
	if(!found)
        return -1;

}
long *SearchByName(conIdex *idx,char input[],long n,long &noResult){
    long *p, m = 10;noResult=0;
    unsigned int fs=10;
    p=new (nothrow)long[m];
    for(long i=0;i<n;i++){
		if(strcmp(idx[i].name,input)==0){
            p[noResult]=idx[i].position;
            noResult++;fs--;
            if(fs==0){
                long oldM=m;
                long *temp;m=m+10;
                temp=new (nothrow) long[m];
                for(long k=0;k<oldM;k++)
                    temp[k]=p[k];
                delete [] p;
                p=temp;
                fs=10;
                }
            }
		}
    return p;
}
void Display(fstream &fcon,long * pos, long noResult){
    system ("cls");
    contact con;
    cout<<setw(25)<<left<<setfill(' ')<<"# Full Name"<<setw(25)<<left<<setfill(' ');
    cout<<"Phone Number"<<setw(25)<<left<<setfill(' ')<<"Email"<<setw(25)<<setfill(' ');
    cout<<setw(100)<<setfill('-')<<"\n";
    for(long i=0;i<noResult;i++){
        fcon.seekg(pos[i]);
        fcon.read((char *)&con,sizeof(con));
        cout<<endl<<i<<") "<<setw(25)<<left<<setfill(' ')<<con.name<<setw(25)<<left<<setfill(' ');
        cout<<con.phone<<setw(25)<<left<<setfill(' ')<<con.email;
        cout<<setw(100)<<setfill('-')<<"\n";
    }
}
void Display(fstream &fcon,long pos){
    system ("cls");
    contact con;
    cout<<setw(25)<<left<<setfill(' ')<<"# Full Name"<<setw(25)<<left<<setfill(' ');
    cout<<"Phone Number"<<setw(25)<<left<<setfill(' ')<<"Email"<<setw(25)<<setfill(' ');
    cout<<setw(100)<<setfill('-')<<"\n";
    fcon.seekg(pos);
    fcon.read((char *)&con,sizeof(con));
    cout<<endl<<'#'<<"  "<<setw(25)<<left<<setfill(' ')<<con.name<<setw(25)<<left<<setfill(' ');
    cout<<con.phone<<setw(25)<<left<<setfill(' ')<<con.email;
    cout<<setw(100)<<setfill('-')<<"\n";
}
void DisplayAll(fstream & fcon,long n){
    system ("cls");
    contact con;
    cout<<setw(25)<<left<<setfill(' ')<<"# Full Name"<<setw(25)<<left<<setfill(' ');
    cout<<"Phone Number"<<setw(25)<<left<<setfill(' ')<<"Email"<<setw(25)<<setfill(' ');
    cout<<setw(100)<<setfill('-')<<"\n";
    fcon.seekg(0,ios::beg);
    for(long i=0;i<n;i++){
        fcon.read((char *)&con,sizeof(con));
        cout<<endl<<i<<") "<<setw(25)<<left<<setfill(' ')<<con.name<<setw(25)<<left;
        cout<<setfill(' ')<<con.phone<<setw(25)<<left<<setfill(' ')<<con.email;
        cout<<setw(100)<<setfill('-')<<"\n";
    }
}
void Edit(fstream &fcon,long pos){
    contact con;
    cin.ignore(INT_MAX,'\n');
    GetContactInfo("Enter a new full name: ",con.name);
    GetContactInfo("Enter a phone number: ",con.phone,14);
    GetContactInfo("Enter an email address: ",con.email);
    fcon.seekp(pos);
    fcon.write((char *)&con,sizeof(con));
    system("cls");
    cout<<"The contact has been edited.";
}
void EditContact(fstream &fcon,conIdex *idx,long n){
    system ("cls");
    char searchedchar[80];
    long position,*p,contactToEditIdx,noResult;
    GetContactInfo("which contact do you to be edited? Enter a full name or a phone number: ",searchedchar);
    if(searchedchar[0]=='0'||searchedchar[0]=='1'||searchedchar[0]=='2'||searchedchar[0]=='3'||searchedchar[0]=='4'||
       searchedchar[0]=='5'||searchedchar[0]=='6'||searchedchar[0]=='7'||searchedchar[0]=='8'||searchedchar[0]=='9'){
       position=SearchByPhone(idx,searchedchar,n);
        if(position==-1)
            cout<<"Not found!!!";
        else {
            Display(fcon,position);
            Edit(fcon,position);
        }
    }
    else{
        p=SearchByName(idx,searchedchar,n,noResult);
        if(noResult==0)
            cout<<"Not found!!!";
        else {
            Display(fcon,p,noResult);
            cout<<"\nPlease enter the contact's roll number that you want to edit: ";
            cin>>contactToEditIdx;
            if(contactToEditIdx<noResult)
                Edit(fcon,p[contactToEditIdx]);
            else
                cout<<"Error!!!, Wrong index";
        }
    }
}
void RemoveContact(fstream &fcon,conIdex *idx,long n){
    system ("cls");
    char searchedchar[80],confirmation;
    long noResult=0,*position,choice;
    contact con;
    GetContactInfo("which contact do you to be removed? Enter a full name: ",searchedchar);
    position=SearchByName(idx,searchedchar,n,noResult);
    if(noResult!=0){
        Display(fcon,position,noResult);
        cout<<"\nEnter the contact's index that you to be removed: ";
        cin>>choice;
        if(choice<noResult){
        fcon.seekg(position[choice]);
        fcon.read((char *)&con,sizeof(con));
        cout<<"Are you sure you want to remove "<<con.name<<" ? if your answer is yes enter y, if not enter any key: ";
        cin>>confirmation;
            if(confirmation=='y'||confirmation=='Y'){
                fcon.seekp(position[choice]);
                fcon.write((char *)&BLANK_CONTACT,sizeof(contact));
                system("cls");
                cout<<"Removed!!!\n";
                }
        }
        else cout<<"Error!!!, Wrong index";
    }else
        cout<<"Not found!!!";
}
void removeDeleted(fstream &fcon, char *path){
    contact con;
    ofstream ofs("temp.bin",ios::in|ios::out|ios::binary);
    fcon.seekg(0,ios::beg);
    while(!fcon.eof()){
        fcon.read((char *)&con, sizeof(con));
        if(con.name!="")
            ofs.write((char *)&con,sizeof(con));
        }
    fcon.close();
    remove(path);
    ofs.close();
    rename("temp.bin",path);
    fcon.open(path);
}
int Menu(){
    fstream fcon;int fs,status,ans,Exit,backToMenu;long n,noResult;
    char *path="contact.bin";
    conIdex *idx;
    status=openFile(fcon,path);
    if(!status){
        cout << "Disk is corrupted or malfunctioning!!!";
        return 0;
    }
    status=loadingContactFile(fcon,idx,n,fs);
    if(!status){
         cout << "Not enough memory!!!";
        return 0;
    }
    do{
        backToMenu=0,Exit=0;
        cout<<"\n1: Edit\n2: View\n3: Exit\n";
        cin>>ans;
        switch(ans){
    case 1:
        do{

        cout<<"\n1: Add\n2: Edit\n3: Remove\n4: Back to main menu items\n5: Exit\n";
        cin>>ans;
        if(ans==1){
            system("cls");
            ans=AddContact(fcon,idx,fs,n);
            if(ans)
                cout<<"New contact has been added!!!";
            }
        else if(ans==2){
            cin.ignore(INT_MAX,'\n');
            EditContact(fcon,idx,n);
        }
        else if(ans==3){
            cin.ignore(INT_MAX,'\n');
            RemoveContact(fcon,idx,n);
        }
        else if(ans==4){
            system("cls");
            backToMenu=4;
        }
        else if(ans==5){
            system("cls");
            backToMenu=4;
            Exit=3;
            }
        else {
            system("cls");
            cout<<"Wrong choice!!!";
        }
        }while(backToMenu!=4);
        break;
    case 2:
        do{
        cout<<"\n1: View by search\n2: View all\n3: Back to main menu\n4: Exit\n";
        cin>>ans;
        if(ans==1){
            system("cls");
            long *pos;char name[80];
            cin.ignore(INT_MAX,'\n');
            cout<<"Enter the full name: ";
            cin.getline(name,79);
            pos=SearchByName(idx,name,n,noResult);
            if(noResult==0)
                cout<<"Not found!!!";
            else Display(fcon,pos,noResult);
            }
        else if(ans==2)
            DisplayAll(fcon,n);
        else if(ans==3){
            system("cls");
            backToMenu=3;
        }
        else if(ans==4){
            system("cls");
            backToMenu=3;
            Exit=3;
            }
        else {
            system("cls");
            cout<<"Wrong choice!!!";
            }
        }while(backToMenu!=3);
         break;
    case 3:
        Exit=3; break;
    default:
        system("cls");
        cout<<"Wrong  choice!!!";
        }
    }while(Exit!=3);
    //removeDeleted(fcon,path);
    fcon.close();
}
int main(){
    Welcome();
    Menu();
    fareWall();
    cout<<"\n\t\t\t. . .";
    system("pause");
    return 0;
}


