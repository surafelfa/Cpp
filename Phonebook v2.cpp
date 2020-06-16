
// This program is written by Surafel Fantu
#include<iostream>
#include<cstring>
#include<stdlib.h>
#include<iomanip>
#include <conio.h>
#include <windows.h>
struct PERSON {
    char name[1000][80];
    char phone[1000][15];
    char email[1000][80];
};
const int ESC=27;
using namespace std;
void Welcome();
void Menu(PERSON& persenalInfo, int & idx);
void edits(PERSON& persenalInfo, int &n);
void views(PERSON& persenalInfo, int n);
void EditSubMenu(PERSON& persenalInfo,int & n);
void ViewSubMenu(PERSON& persenalInfo,int n);
void AddContact(PERSON& persenalInfo, int &n);
void GetContactInfo(char prompt[], char input[],int size);
void Add(PERSON& persenalInfo,int & n , const char newName[], const char newPhone[], const char newEmail[]);
void Sort(PERSON& persenalInfo,int  n);
void SortByName(PERSON& persenalInfo,int  n);
void SortByPhone(PERSON& persenalInfo,int  n);
void EditContact(PERSON& persenalInfo,int  n);
void Search(PERSON persenalInfo,int  n, int byWhat, char input[], int searchResultIdx[], int & noResults);
void SearchByName(PERSON persenalInfo,int  n, char input[], int searchResultIdx[], int & noResults);
void SearchByPhone(PERSON persenalInfo,int  n,  char input[],int searchResultIdx[], int & noResults);
void Edit(PERSON &persenalInfo,int contactToEditIdx);
void RemoveContact(PERSON &persenalInfo,int & n);
void Remove(PERSON &persenalInfo,int & n, int contactToRemoveIdx);
void viewAll(PERSON& persenalInfo,int  n);
void viewBySearch(PERSON &persenalInfo,int n);
void Display(PERSON persenalInfo,const int resultToDisplay[], int noResult);
void Display(PERSON persenalInfo,int n);
void fareWall();
HANDLE hConsole= GetStdHandle(STD_OUTPUT_HANDLE);
int main(){
    PERSON persenalInfo;
    char key;
    int i=0;
    Menu(persenalInfo,i);
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
    cout<<"\n         tThank you for using our contact book application! Goodbye.\n";
}
void Menu(PERSON& persenalInfo,int & idx){
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
                edits(persenalInfo,idx);
                break;
            case 2:
                views(persenalInfo,idx);
                break;
            default:
                cout<<"Invalid choice!";
                cout<<endl<<endl<<("press Any key to  continue or ESC to Exit")<<endl;
                //getch();
                key=getche();
                system("cls");
                Welcome();
                Menu(persenalInfo,idx);
                break;
        }
        SetConsoleTextAttribute(hConsole, 8);
        cout<<endl<<endl<<("press Any key to  continue or ESC to Exit")<<endl;
   	 	key=getche();
   	 	system ("cls");
    }while (key != ESC);
}
void edits(PERSON & persenalInfo,int &n){
    system ("cls");
    EditSubMenu(persenalInfo,n);
}
void EditSubMenu(PERSON & persenalInfo,int & n){
    int choice;
    SetConsoleTextAttribute(hConsole, 8);
    cout<<"1: Add\n2: Edit\n3: Remove\n4: Back to main menu items\n";
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
            AddContact(persenalInfo,n);
            break;
        case 2:
            if(n!=0)
                EditContact(persenalInfo,n);
            else
                cout<<"You have not added any contact yet!!!\n";
            break;
        case 3:
            if(n!=0)
                RemoveContact(persenalInfo,n);
             else
                cout<<"You have not added any contact yet!!!\n";
            break;
        case 4:
            system ("cls");
            Menu(persenalInfo,n);
            break;
        default:
            cout<<"invalid choice!";
    }
}
void GetContactInfo(char prompt[], char input[],int size=80){

    cout<<prompt;
    cin.getline(input,size);
}
void AddContact(PERSON &personalInfo,int &n){
    system ("cls");
    SetConsoleTextAttribute(hConsole, 8);
    char newName[80],newEmail[80],newPhone[15];
    GetContactInfo("Enter a full name: ",newName);
    GetContactInfo("Enter a phone number: ",newPhone,15);
    GetContactInfo("Enter a email address: ",newEmail);
    Add(personalInfo,n,newName,newPhone,newEmail);
}
void Add(PERSON &personalInfo,int & n , const char newName[], const char newPhone[], const char newEmail[]){
    strcpy(personalInfo.name[n],newName);
    strcpy(personalInfo.phone[n],newPhone);
    strcpy(personalInfo.email[n],newEmail);
    n++;
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout<<"The contact has been added";
}
void EditContact(PERSON &personalInfo,int  n){
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
    Search(personalInfo,n,byWhat,searchedchar,searchResultIdx,noResults);
    if(noResults!=0){
        SetConsoleTextAttribute(hConsole, 8);
        cout<<"\nPlease enter the contact's roll number that you want to edit: ";
        cin>>contactToEditIdx;
        cin.ignore();
        if(contactToEditIdx<noResults)
            Edit(personalInfo,contactToEditIdx);
        else
            cout<<"Error!!!, Wrong index";
    }
}
void Search(PERSON personalInfo,int  n, int byWhat, char input[], int searchResultIdx[], int & noResults){
    switch(byWhat){
        case 0:
            SearchByPhone(personalInfo,n,input,searchResultIdx,noResults);
            break;
        case 1:
            SearchByName(personalInfo,n,input,searchResultIdx,noResults);
            break;
        default:
            cout<<"invalid choice!";

    }
}
void SearchByPhone(PERSON personalInfo, int  n,  char input[],int searchResultIdx[], int & noResults){
    int idx=0;
    for(int i=0;i<n;i++){
		if(strcmp(personalInfo.phone[i],input)==0){
            searchResultIdx[idx]=i;
            idx++;
			noResults++;
		}
	}
	SetConsoleTextAttribute(hConsole, 6);
	cout<<noResults<<"result(s) is(are) found.\n";
	Display(personalInfo,searchResultIdx,noResults);
}
void SearchByName(PERSON personalInfo,int  n, char input[], int searchResultIdx[], int & noResults){
    int idx=0;
    for(int i=0;i<n;i++){
		if(strcmp(personalInfo.name[i],input)==0){
            searchResultIdx[idx]=i;
            idx++;
			noResults++;
		}
    }
    SetConsoleTextAttribute(hConsole, 6);
    cout<<noResults<<" result(s) is(are) found.\n";
    if(noResults!=0)
        Display(personalInfo,searchResultIdx,noResults);
}
void Edit(PERSON& personalInfo,int contactToEditIdx){
    SetConsoleTextAttribute(hConsole, 8);
    char newName[80],newPhone[15],newEmail[80];
    GetContactInfo("Enter a new full name: ",newName);
    GetContactInfo("Enter a phone number: ",newPhone);
    GetContactInfo("Enter an email address: ",newEmail,15);
    strcpy(personalInfo.name[contactToEditIdx],newName);
    strcpy(personalInfo.phone[contactToEditIdx],newPhone);
    strcpy(personalInfo.email[contactToEditIdx],newEmail);
    system("cls");
    SetConsoleTextAttribute(hConsole, 6);
    cout<<"The contact has been edited.";
}
void RemoveContact(PERSON& personalInfo, int & n){
    system ("cls");
    SetConsoleTextAttribute(hConsole, 8);
    char searchedchar[80],confirmation;
    int noResults=0,choice,searchResultIdx[1000];
    GetContactInfo("which contact do you to be removed? Enter a full name: ",searchedchar);
    SearchByName(personalInfo,n,searchedchar,searchResultIdx,noResults);
    if(noResults!=0){
        SetConsoleTextAttribute(hConsole, 8);
        cout<<"\nEnter the contact's index that you to be removed: ";
        cin>>choice;
        if(choice<noResults){
        cout<<"Are you sure you want to remove "<<personalInfo.name[choice]<<" ? if your answer is yes enter y, if not enter any key: ";
        cin>>confirmation;
        if(confirmation=='y'||confirmation=='Y')
            Remove(personalInfo,n,choice);
        }
        else
            cout<<"Error!!!, Wrong index";
    }
}
void Remove(PERSON& personalInfo, int & n, int contactToRemoveIdx){
		strcpy(personalInfo.name[contactToRemoveIdx],personalInfo.name[n-1]);
		strcpy(personalInfo.phone[contactToRemoveIdx],personalInfo.phone[n-1]);
		strcpy(personalInfo.email[contactToRemoveIdx],personalInfo.email[n-1]);
		n--;
		system("cls");
		SetConsoleTextAttribute(hConsole, 6);
		cout<<"The contact has been removed";
}
void views(PERSON &personalInfo, int n){
    system ("cls");
    ViewSubMenu(personalInfo,n);
}
void ViewSubMenu(PERSON& personalInfo,int n){
    int choice;
    SetConsoleTextAttribute(hConsole, 8);
    cout<<"1: View by search\n2: View all\n";
    cin>>choice;
    cin.ignore();
    switch(choice){
        case 1:
            viewBySearch(personalInfo,n);
            break;
        case 2:
            viewAll(personalInfo,n);
            break;
        default:
            cout<<"invalid choice!";
    }
}
void viewBySearch(PERSON &personalInfo,int n){
    system ("cls");
    SetConsoleTextAttribute(hConsole, 8);
    char fullName[80];
    int searchResultIdx[1000],noResults=0;
    GetContactInfo("Enter a contact's full name: ",fullName);
    if(n>1)
        Sort(personalInfo,n);
    SearchByName(personalInfo,n,fullName,searchResultIdx,noResults);
}
void viewAll(PERSON &personalInfo, int  n){
    system ("cls");
    if(n>1)
        Sort(personalInfo,n);
    Display(personalInfo,n);
}
void Display(PERSON personalInfo,const int resultToDisplay[], int noResult){
    //system ("cls");
    SetConsoleTextAttribute(hConsole, 3);
    cout<<setw(25)<<left<<setfill(' ')<<"# Full Name"<<setw(25)<<left<<setfill(' ')<<"Phone Number"<<setw(25)<<left<<setfill(' ')<<"Email"<<setw(25)<<setfill(' ');
    cout<<setw(100)<<setfill('-')<<"\n";
    for(int i=0;i<noResult;i++){
        cout<<endl<<i<<") "<<setw(25)<<left<<setfill(' ')<<personalInfo.name[resultToDisplay[i]]<<setw(25)<<left<<setfill(' ')<<personalInfo.phone[i]<<setw(25)<<left<<setfill(' ')<<personalInfo.email[i];
        cout<<setw(100)<<setfill('-')<<"\n";
    }
}
void Display(PERSON personalInfo, int n){
    //system ("cls");
    SetConsoleTextAttribute(hConsole, 3);
    cout<<setw(25)<<left<<setfill(' ')<<"# Full Name"<<setw(25)<<left<<setfill(' ')<<"Phone Number"<<setw(25)<<left<<setfill(' ')<<"Email"<<setw(25)<<setfill(' ');
    cout<<setw(100)<<setfill('-')<<"\n";
    for(int i=0;i<n;i++){
        cout<<endl<<i<<") "<<setw(25)<<left<<setfill(' ')<<personalInfo.name[i]<<setw(25)<<left<<setfill(' ')<<personalInfo.phone[i]<<setw(25)<<left<<setfill(' ')<<personalInfo.email[i];
        cout<<setw(100)<<setfill('-')<<"\n";
    }
}
void Sort(PERSON & personalInfo, int  n) {
	int byWhat;
	SetConsoleTextAttribute(hConsole, 8);
	cout<<"sort by what: 0 means by 'name' 1 means by 'phone': ";
	cin>>byWhat;
	switch(byWhat){
		case 0:
			SortByName(personalInfo,n);
			cout<<"The contact book has been sorted by name!\n";
			break;
		case 1:
			SortByPhone(personalInfo,n);
			cout<<"The contact book has been sorted by phone!\n";
			break;
		default:
            cout<<"invalid choice!";
	}
}
void SortByName(PERSON & personalInfo, int  n){
	char tempName[80],temPhone[15],tempEmail[80];
	for(int i=0;i<n-1;i++){
		for(int j=n-1;j>i;j--){
			if(strcmp(personalInfo.name[j],personalInfo.name[j-1])==-1){
				strcpy(tempName,personalInfo.name[j]);
				strcpy(personalInfo.name[j],personalInfo.name[j-1]);
				strcpy(personalInfo.name[j-1],tempName);
				strcpy(temPhone,personalInfo.phone[j]);
				strcpy(personalInfo.phone[j],personalInfo.phone[j-1]);
				strcpy(personalInfo.phone[j-1],temPhone);
				strcpy(tempEmail,personalInfo.email[j]);
				strcpy(personalInfo.email[j],personalInfo.email[j-1]);
				strcpy(personalInfo.email[j-1],tempEmail);
			}
		}
	}
}
void SortByPhone(PERSON &personalInfo,int  n){
	char tempName[80],temPhone[15],tempEmail[80];
	for(int i=0;i<n-1;i++){
		for(int j=n-1;j>i;j--){
			if(strcmp(personalInfo.phone[j],personalInfo.phone[j-1])==-1){
				strcpy(temPhone,personalInfo.phone[j]);
				strcpy(personalInfo.phone[j],personalInfo.phone[j-1]);
				strcpy(personalInfo.phone[j-1],temPhone);
				strcpy(tempName,personalInfo.name[j]);
				strcpy(personalInfo.name[j],personalInfo.name[j-1]);
				strcpy(personalInfo.name[j-1],tempName);
				strcpy(tempEmail,personalInfo.email[j]);
				strcpy(personalInfo.email[j],personalInfo.email[j-1]);
				strcpy(personalInfo.email[j-1],tempEmail);
			}
		}
	}
}
