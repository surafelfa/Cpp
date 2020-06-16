// This program is written by Surafel Fantu
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<iomanip>
#include <conio.h>
#include <windows.h>
//#include <graphics.h>
const int ESC=27;
using namespace std;
void Welcome();
void Menu(char name[][80], char phone[][15], char email[][80], int & idx);
void edits(char name[][80], char phone[][15], char email[][80], int &n);
void views(char name[][80], char phone[][15], char email[][80], int n);
void EditSubMenu(char name[][80], char phone[][15], char email[][80],int & n);
void ViewSubMenu(char name[][80], char phone[][15], char email[][80],int n);
void AddContact(char name[][80], char phone[][15], char email[][80], int &n);
void GetContactInfo(char prompt[], char input[],int size);
void Add(char name[][80], char phone[][15], char email[][80], int & n , const char newName[], const char newPhone[], const char newEmail[]);
void Sort(char name[][80], char phone[][15], char email[][80], int  n);
void SortByName(char name[][80], char phone[][15], char email[][80], int  n);
void SortByPhone(char name[][80], char phone[][15], char email[][80], int  n);
void EditContact(char name[][80], char phone[][15], char email[][80], int  n);
void Search(const char name[][80], const char phone[][15],const char email[][80], int  n, int byWhat, char input[], int searchResultIdx[], int & noResults);
void SearchByName(const char name[][80],const char phone[][15],const char email[][80],int  n, char input[], int searchResultIdx[], int & noResults);
void SearchByPhone(const char name[][80],const char phone[][15],const char email[][80], int  n,  char input[],int searchResultIdx[], int & noResults);
void Edit(char name[][80], char phone[][15], char email[][80],int contactToEditIdx);
void RemoveContact(char name[][80], char phone[][15], char email[][80], int & n);
void Remove(char name[][80], char phone[][15], char email[][80], int & n, int contactToRemoveIdx);
void viewAll(char name[][80], char phone[][15], char email[][80], int  n);
void viewBySearch(char name[][80], char phone[][15], char email[][80],int n);
void Display(const char name[][80], const char phone[][15], const char email[][80],const int resultToDisplay[], int noResult);
void Display(const char name[][80], const char phone[][15], const char email[][80], int n);
void fareWall();
//HANDLE console=GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
int main(){
    char name[1000][80],phone[1000][15],email[1000][80],key;
    int i=0;
    Menu(name,phone,email,i);
    fareWall();
    return 0;
}
void Welcome(){
    SetConsoleTextAttribute(hConsole, 3);
    cout<<"                 Welcome to this contact book application!\nWith the help of this application you are able to add, edit,";
    cout<<"or remove any contact.";
}
void fareWall(){
    SetConsoleTextAttribute(hConsole, 3);
    cout<<"\n \t        tThank you for using our contact book application! Goodbye.\n";
}
void Menu(char name[][80], char phone[][15], char email[][80], int & idx){
  // system("cls");
    int key;
    do{
                Welcome();
        SetConsoleTextAttribute(hConsole,8);
        int choice;
        cout<<"\n1: Edit contacts.\n2: View contact.\n";
        cin>>choice;
        cin.ignore();
        switch(choice){
            case 1:
                edits(name,phone,email,idx);
                break;
            case 2:
                views(name,phone,email,idx);
                break;
            default:

                cout<<"Invalid choice!";
                cout<<endl<<endl<<("press Any key to  continue or ESC to Exit")<<endl;
                //getch();
                key=getche();
                system("cls");
                Welcome();
                Menu(name,phone,email,idx);
                break;
        }
        SetConsoleTextAttribute(hConsole, 8);
        cout<<endl<<endl<<("press Any key to  continue or ESC to Exit")<<endl;
   	 	key=getche();
   	 	system ("cls");
    }while (key != ESC);
}
void edits(char name[][80], char phone[][15], char email[][80], int &n){
    system ("cls");
    EditSubMenu(name,phone,email,n);
}
void EditSubMenu(char name[][80], char phone[][15], char email[][80],int & n){
    int choice;
    SetConsoleTextAttribute(hConsole, 8);
    cout<<"1: Add\n2: Edit\n3: Remove\n4: Back to main menu items\n";
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
            AddContact(name,phone,email,n);
            break;
        case 2:
            if(n!=0)
                EditContact(name,phone,email,n);
            else
                cout<<"You have not added any contact yet!!!\n";
            break;
        case 3:
            if(n!=0)
                RemoveContact(name,phone,email,n);
            else
                cout<<"You have not added any contact yet!!!\n";
            break;
        case 4:
            system ("cls");
            Menu(name,phone,email,n);
            break;
        default:
            cout<<"invalid choice!";
    }
}
void GetContactInfo(char prompt[], char input[],int size=80){

    cout<<prompt;
    cin.getline(input,size);
}
void AddContact(char name[][80], char phone[][15], char email[][80], int &n){
    system ("cls");
    SetConsoleTextAttribute(hConsole, 8);
    char newName[80],newEmail[80],newPhone[15];
    GetContactInfo("Enter a full name: ",newName);
    GetContactInfo("Enter a phone number: ",newPhone,15);
    GetContactInfo("Enter a email address: ",newEmail);
    Add(name,phone,email,n,newName,newPhone,newEmail);
}
void Add(char name[][80], char phone[][15], char email[][80], int & n , const char newName[], const char newPhone[], const char newEmail[]){
    strcpy(name[n],newName);
    strcpy(phone[n],newPhone);
    strcpy(email[n],newEmail);
    n++;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout<<"The contact has been added";
}
void EditContact(char name[][80], char phone[][15], char email[][80], int  n){
    system ("cls");
    SetConsoleTextAttribute(hConsole, 8);
    char searchedchar[80];
    int byWhat,onResults=0,searchResultIdx[1000],contactToEditIdx,noResults=0;
    GetContactInfo("which contact do you to be edited? Enter a full name or a phone number: ",searchedchar);
    if(searchedchar[0]=='0'||searchedchar[0]=='1'||searchedchar[0]=='2'||searchedchar[0]=='3'||searchedchar[0]=='4'||
       searchedchar[0]=='5'||searchedchar[0]=='6'||searchedchar[0]=='7'||searchedchar[0]=='8'||searchedchar[0]=='9')
        byWhat=0;
    else
        byWhat=1;
    Search(name,phone,email,n,byWhat,searchedchar,searchResultIdx,noResults);
    if(noResults!=0){
        SetConsoleTextAttribute(hConsole, 8);
        cout<<"\nPlease enter the contact's roll number that you want to edit: ";
        cin>>contactToEditIdx;
        cin.ignore();
        if(contactToEditIdx<noResults)
            Edit(name,phone,email,contactToEditIdx);
        else
            cout<<"Error!!!, Wrong index";
    }
}
void Search(const char name[][80], const char phone[][15],const char email[][80], int  n, int byWhat, char input[], int searchResultIdx[], int & noResults){
    switch(byWhat){
        case 0:
            SearchByPhone(name, phone,email,n,input,searchResultIdx,noResults);
            break;
        case 1:
            SearchByName(name,phone,email,n,input,searchResultIdx,noResults);
            break;
        default:
            cout<<"invalid choice!";

    }
}
void SearchByPhone(const char name[][80],const char phone[][15],const char email[][80], int  n,  char input[],int searchResultIdx[], int & noResults){
    int idx=0;
    for(int i=0;i<n;i++){
		if(strcmp(phone[i],input)==0){
            searchResultIdx[idx]=i;
            idx++;
			noResults++;
		}
	}
	SetConsoleTextAttribute(hConsole, 6);
	cout<<noResults<<"result(s) is(are) found.\n";
	Display(name,phone,email,searchResultIdx,noResults);
}
void SearchByName(const char name[][80],const char phone[][15],const char email[][80],int  n, char input[], int searchResultIdx[], int & noResults){
    int idx=0;
    for(int i=0;i<n;i++){
		if(strcmp(name[i],input)==0){
            searchResultIdx[idx]=i;
            idx++;
			noResults++;
		}
    }
    SetConsoleTextAttribute(hConsole, 6);
    cout<<noResults<<" result(s) is(are) found.\n";
    if(noResults!=0)
        Display(name,phone,email,searchResultIdx,noResults);
}
void Edit(char name[][80], char phone[][15], char email[][80],int contactToEditIdx){
    SetConsoleTextAttribute(hConsole, 8);
    char newName[80],newPhone[15],newEmail[80];
    GetContactInfo("Enter a new full name: ",newName);
    GetContactInfo("Enter a phone number: ",newPhone);
    GetContactInfo("Enter an email address: ",newEmail,15);
    strcpy(name[contactToEditIdx],newName);
    strcpy(phone[contactToEditIdx],newPhone);
    strcpy(email[contactToEditIdx],newEmail);
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout<<"The contact has been edited.";
}
void RemoveContact(char name[][80], char phone[][15], char email[][80], int & n){
    system ("cls");
    SetConsoleTextAttribute(hConsole, 8);
    char searchedchar[80],confirmation;
    int noResults=0,choice,searchResultIdx[1000];
    GetContactInfo("which contact do you to be removed? Enter a full name: ",searchedchar);
    SearchByName(name,phone,email,n,searchedchar,searchResultIdx,noResults);
    if(noResults!=0){
        SetConsoleTextAttribute(hConsole, 8);
        cout<<"\nEnter the contact's index that you to be removed: ";
        cin>>choice;
        if(choice<noResults){
            cout<<"Are you sure you want to remove "<<name[choice]<<" ? if your answer is yes enter y, if not enter any key: ";
            cin>>confirmation;
            if(confirmation=='y'||confirmation=='Y')
                Remove(name,phone,email,n,choice);
                }
        else
            cout<<"Error!!!, Wrong index";
    }
}
void Remove(char name[][80], char phone[][15], char email[][80], int & n, int contactToRemoveIdx){
		strcpy(name[contactToRemoveIdx],name[n-1]);
		strcpy(phone[contactToRemoveIdx],phone[n-1]);
		strcpy(email[contactToRemoveIdx],email[n-1]);
		n--;
		system("cls");
		SetConsoleTextAttribute(hConsole, 6);
		cout<<"The contact has been removed";
}
void views(char name[][80], char phone[][15], char email[][80], int n){
    system ("cls");
    ViewSubMenu(name,phone,email,n);
}
void ViewSubMenu(char name[][80], char phone[][15], char email[][80],int n){
    int choice;
    SetConsoleTextAttribute(hConsole, 8);
    cout<<"1: View by search\n2: View all\n";
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
            viewBySearch(name,phone,email,n);
            break;
        case 2:
            viewAll(name,phone,email,n);
            break;
        default:
            cout<<"invalid choice!";
    }
}
void viewBySearch(char name[][80], char phone[][15], char email[][80],int n){
    system ("cls");
    SetConsoleTextAttribute(hConsole, 8);
    char fullName[80];
    int searchResultIdx[1000],noResults=0;
    GetContactInfo("Enter a contact's full name: ",fullName);
    if(n>1)
        Sort(name,phone,email,n);
    SearchByName(name,phone,email,n,fullName,searchResultIdx,noResults);
}
void viewAll(char name[][80], char phone[][15], char email[][80], int  n){
    system ("cls");
    if(n>1)
        Sort(name,phone,email,n);
    Display(name,phone,email,n);
}
void Display(const char name[][80], const char phone[][15], const char email[][80],const int resultToDisplay[], int noResult){
    //system ("cls");
    SetConsoleTextAttribute(hConsole, 3);
    cout<<setw(25)<<left<<setfill(' ')<<"# Full Name"<<setw(25)<<left<<setfill(' ')<<"Phone Number"<<setw(25)<<left<<setfill(' ')<<"Email"<<setw(25)<<setfill(' ');
    cout<<setw(100)<<setfill('-')<<"\n";
    for(int i=0;i<noResult;i++){
        cout<<endl<<i<<") "<<setw(25)<<left<<setfill(' ')<<name[resultToDisplay[i]]<<setw(25)<<left<<setfill(' ')<<phone[i]<<setw(25)<<left<<setfill(' ')<<email[i];
        cout<<setw(100)<<setfill('-')<<"\n";
    }
}
void Display(const char name[][80], const char phone[][15], const char email[][80], int n){
    //system ("cls");
    SetConsoleTextAttribute(hConsole, 3);
    cout<<setw(25)<<left<<setfill(' ')<<"# Full Name"<<setw(25)<<left<<setfill(' ')<<"Phone Number"<<setw(25)<<left<<setfill(' ')<<"Email"<<setw(25)<<setfill(' ');
    cout<<setw(100)<<setfill('-')<<"\n";
    for(int i=0;i<n;i++){
        cout<<endl<<i<<") "<<setw(25)<<left<<setfill(' ')<<name[i]<<setw(25)<<left<<setfill(' ')<<phone[i]<<setw(25)<<left<<setfill(' ')<<email[i];
        cout<<setw(100)<<setfill('-')<<"\n";
    }
}
void Sort(char name[][80], char phone[][15], char email[][80], int  n) {
	int byWhat;
	SetConsoleTextAttribute(hConsole, 8);
	cout<<"sort by what: 0 means by 'name' 1 means by 'phone': ";
	cin>>byWhat;
	switch(byWhat){
		case 0:
			SortByName(name,phone,email,n);
			cout<<"The contact book has been sorted by name!\n";
			break;
		case 1:
			SortByPhone(name,phone,email,n);
			cout<<"The contact book has been sorted by phone!\n";
			break;
		default:
            cout<<"invalid choice!";
	}
}
void SortByName(char name[][80], char phone[][15], char email[][80], int  n){
	char tempName[80],temPhone[15],tempEmail[80];
	for(int i=0;i<n-1;i++){
		for(int j=n-1;j>i;j--){
			if(strcmp(name[j],name[j-1])==-1){
				strcpy(tempName,name[j]);
				strcpy(name[j],name[j-1]);
				strcpy(name[j-1],tempName);
				strcpy(temPhone,phone[j]);
				strcpy(phone[j],phone[j-1]);
				strcpy(phone[j-1],temPhone);
				strcpy(tempEmail,email[j]);
				strcpy(email[j],email[j-1]);
				strcpy(email[j-1],tempEmail);
			}
		}
	}
}
void SortByPhone(char name[][80], char phone[][15], char email[][80], int  n){
	char tempName[80],temPhone[15],tempEmail[80];
	for(int i=0;i<n-1;i++){
		for(int j=n-1;j>i;j--){
			if(strcmp(phone[j],phone[j-1])==-1){
				strcpy(temPhone,phone[j]);
				strcpy(phone[j],phone[j-1]);
				strcpy(phone[j-1],temPhone);
				strcpy(tempName,name[j]);
				strcpy(name[j],name[j-1]);
				strcpy(name[j-1],tempName);
				strcpy(tempEmail,email[j]);
				strcpy(email[j],email[j-1]);
				strcpy(email[j-1],tempEmail);
			}
		}
	}
}
