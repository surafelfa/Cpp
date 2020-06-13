#include<iostream>
#include<cstring>
#include<iomanip>
#include<cstdlib>
#include<fstream>
using namespace std;
/*
#Selling Price of an item is determined by the latest purchase.
#Available quantity for an item at supermarket is always Updated when order and purchase is made.
#itemId,invoice Number of an order,purchaseId, and orderId are generated automatically.
*/
struct item{
    long itemId;
    char name[20];
    char location[3];
    double unitPrice;
    double discount;
    long avaQua;
};
struct itemIdex{
    char location[3];
    long itemId;
    char name[20];
    long  position;
};
struct date{
    int day,month,year;
};
struct order{
    int invoiceNo;
    date date_of_sale;
    char cusFullName[40];
};
struct orderDetail{
    int orderId;
    int invoiceNo;
    int itemId;
    int quantity;
    double discount;
};
struct purchase{
    long invoiceNo;
    date date_of_purchase;
    char supplierFullName[40];
};
struct purchaseDetail{
    long purchaseId;
    long invoiceNo;
    long itemId;
    int quantity;
    double unitPrice;
};
struct purchaseIdex{
    long purchaseId;
    long invoiceNo;
    long itemId;
    long position;
};
struct purchaseIdexOne{
    date date_of_purchase;
    long position;
};
//const ESC=27;
//open the files in fstream mode
int openFile(fstream & fitem,fstream &fp,fstream &fpd,char *path1,char *path2,char *path3){
    fitem.open(path1,ios::in|ios::out|ios::binary);
    fp.open(path2,ios::in|ios::out|ios::binary);
    fpd.open(path3,ios::in|ios::out|ios::binary);
    if(fitem&&fp&&fpd)
        return 1;
    else{
        ofstream ofs1(path1),ofs2(path2),ofs3(path3);
        if(ofs1&&ofs2&&ofs3){
            ofs1.close();ofs2.close();ofs3.close();
            openFile(fitem,fp,fpd,path1,path2,path3);
        }else
            return 0;
    }
}
int loadingItemFile(fstream & fitem, itemIdex * & iIdx, long & in, int & ifs, long &lastItemId){
    long position,m=0;
    item itm;
    // Locate the read pointer at the end
    fitem.seekg(0,ios::end);
    // Calculate the total number of students in the file
    m=fitem.tellg()/sizeof(item);
    iIdx=new (nothrow) itemIdex[m + 10];
    lastItemId=10000;
    in=0;
    if(iIdx){
        fitem.seekg(0,ios::beg);
        for(long i=0; i< m; i++){
            position=fitem.tellg();
            //read a row
            fitem.read((char *)&itm, sizeof(itm));
            iIdx[in].itemId=itm.itemId;
            strncpy(iIdx[in].name,itm.name,19);
            strcpy(iIdx[in].location,itm.location);
            iIdx[in].position=position;
            in++;
            if(itm.itemId>lastItemId) lastItemId=itm.itemId;
        }
        ifs=m + 10-in;
        return 1;
    }else
        return 0;
}
int loadingPurchase(fstream & fp, purchaseIdexOne * & pIdx, long  pn, int  pfs){
    long position,m=0;
    purchase p;
    // Locate the read pointer at the end
    fp.seekg(0,ios::end);
    // Calculate the total number of students in the file
    m=fp.tellg()/sizeof(p);
    pIdx=new (nothrow) purchaseIdexOne[m + 10];
    pn=0;
    if(pIdx){
        fp.seekg(0,ios::beg);
        for(long i=0; i< m; i++){
            position=fp.tellg();
            //read a row
            fp.read((char *)&p, sizeof(p));
            pIdx[pn].date_of_purchase.day=p.date_of_purchase.day;
            pIdx[pn].date_of_purchase.month=p.date_of_purchase.month;
            pIdx[pn].date_of_purchase.year=p.date_of_purchase.year;
            pIdx[pn].position=position;
            pn++;
        }
        pfs=m + 10-pn;
        return 1;
    }else
        return 0;
}
int loadingPurchaseD(fstream & fpd, purchaseIdex * & pIdx, long & pn, int & pfs, long &lastPurchaseId){
    long position,m=0;
    purchaseDetail pd;
    // Locate the read pointer at the end
    fpd.seekg(0,ios::end);
    // Calculate the total number of students in the file
    m=fpd.tellg()/sizeof(pd);
    pIdx=new (nothrow) purchaseIdex[m + 10];
    lastPurchaseId=10000;
    pn=0;
    if(pIdx){
        fpd.seekg(0,ios::beg);
        for(long i=0; i< m; i++){
            position=fpd.tellg();
            //read a row
            fpd.read((char *)&pd, sizeof(pd));
            pIdx[pn].itemId=pd.itemId;
            pIdx[pn].invoiceNo=pd.invoiceNo;
            pIdx[pn].purchaseId=pd.purchaseId;
            pIdx[pn].position=position;
            pn++;
            if(pd.purchaseId>lastPurchaseId) lastPurchaseId=pd.purchaseId;
        }
        pfs=m + 10-pn;
        return 1;
    }else
        return 0;
}
item newItem(long lastItemId){//register an item
    item itm;
    cout <<"Enter product info:" <<endl;
    itm.itemId=++lastItemId;
    itm.avaQua=0;
    itm.discount=0.05;
    itm.unitPrice=0.0;
    cout << "Product Name: "; cin.getline(itm.name,19);
    cout << "Location: "; cin>>itm.location;
    system("cls");
    return itm;
}
int getNewItem(fstream &fitem,itemIdex* & iIdx,long &in,int &ifs,long &lastItemId){
    item newItm;
    itemIdex * temp;
    long position;
    if(ifs==0) {
        temp=new (nothrow) itemIdex[in+ 10];
        if(temp){
            for(int i=0; i< in; i++)
                temp[i]=iIdx[i];
            delete [] iIdx;
            iIdx=temp;
            ifs=10;
        }else
            return 0;
    }
    newItm=newItem(lastItemId);
    fitem.seekp(0,ios::end);
    position=fitem.tellp();
    iIdx[in].itemId=newItm.itemId;
    strncpy(iIdx[in].name,newItm.name,19);
    strcpy(iIdx[in].location,newItm.location);
    iIdx[in].position=position;
    fitem.write((char *)&newItm,sizeof(newItm));
    lastItemId++;
    in++;
    ifs--;
    return 1;
}
void editItem(fstream &fitem,purchaseDetail pD,long position){//after purchasing sth
    item itm;
    fitem.seekg(position,ios::beg);
    fitem.read((char *)&itm,sizeof(itm));
    itm.avaQua=itm.avaQua+pD.quantity;
    itm.unitPrice=pD.unitPrice+pD.unitPrice*0.1;
    fitem.seekp(position,ios::beg);
    fitem.write((char *)&itm,sizeof(itm));
}
long searchItemByName(itemIdex *checkItem,char *name,long in,long &idx){
    bool found=false;
    for(long i=0;(i<in)&&(!found);i++){
        if(strcmp(checkItem[i].name,name)==0){
            found=true;
            idx=i;
            return checkItem[i].position;
        }
    }
    if(!found)
        return -1;
}
long searchItemById(itemIdex *checkItem,long id,long in,long &idx){
    bool found=false;
    for(long i=0;(i<in)&&(!found);i++){
        if(checkItem[i].itemId==id){
            found=true;
            idx=i;
            return checkItem[i].position;
        }
    }
    if(!found)
        return -1;
}
long * searchItemByLocation(itemIdex *checkItem,char *loc,long in,long & idx){
    int ifs=10;
    long *p,m=10;
    idx=0;
    p = new (nothrow) long [m];
    for(long i=0;i<in;i++){
        if(strcmp(checkItem[i].location,loc)==0){
            p[idx]=checkItem[i].position;
            idx++;ifs--;
            if(ifs==0){
                long *temp;m=m+10;
                temp=new (nothrow) long[m];
                for(long k=0; k<m;k++)
                    temp[k]=p[k];
                    delete [] p;
                p=temp;
                ifs=10;
            }
        }
    }
    return p;
}
long searchPurchaseBypId(purchaseIdex *checkPurchase,long id,long pdn,long &idx){
    bool found=false;
    for(long i=0;(i<pdn)&&(!found);i++){
        if(checkPurchase[i].purchaseId==id){
            found=true;
            idx=i;
            return checkPurchase[i].position;
        }
    }
    if(!found)
        return -1;
}
long searchPurchaseByiId(purchaseIdex *checkPurchase,long id,long pn,long &idx){
    bool found=false;
    for(long i=0;(i<pn)&&(!found);i++){
        if(checkPurchase[i].itemId==id){
            found=true;
            idx=i;
            return checkPurchase[i].position;
        }
    }
    if(!found)
        return -1;
}
long * searchPurchaseByivoiceNo(purchaseIdex *checkPurchase,long id,long pn,long &idx){
    int pfs=10;
    long *p,m=10;
    idx=0;
    p = new (nothrow) long [m];
    for(long i=0;i<pn;i++){
        if(checkPurchase[i].invoiceNo==id){
            p[idx]=checkPurchase[i].position;
            idx++;pfs--;
            if(pfs==0){
                long *temp;m=m+10;
                temp=new (nothrow) long[m];
                for(long k=0;k<m;k++)
                    temp[k]=p[k];
                    delete [] p;
                p=temp;
                pfs=10;
            }
        }
    }
    return p;
}
long* searchPurchaseByDate(purchaseIdexOne *checkPurchase,date checkdate,long pn,long &idx){
    int pfs=10;
    long *p,m=10;
    idx=0;
    p = new (nothrow) long [m];
    for(long i=0;i<pn;i++){
        if((checkPurchase[i].date_of_purchase.day==checkdate.day)&&
           (checkPurchase[i].date_of_purchase.month==checkdate.month)&&
           (checkPurchase[i].date_of_purchase.year==checkdate.year)){
            p[idx]=checkPurchase[i].position;
            idx++;pfs--;
            if(pfs==0){
                long *temp;m=m+10;
                temp=new (nothrow) long[m];
                for(long k=0;k<m;k++)
                    temp[k]=p[k];
                    delete [] p;
                p=temp;
                pfs=10;
            }
        }
    }
    return p;
}
void displayItem(fstream &fitem, long position){
    item singleItem;
    fitem.seekg(position);
    fitem.read((char *)&singleItem,sizeof(item));
    cout <<left<<setw(10) << "ITEM ID" <<'\t'<< setw(20) << "Name" <<'\t';
    cout<<setw(8) << "Location" <<'\t'<<setw(10) << "UNIT PRICE" <<'\t';
    cout<<setw(6) << "DISCOUNT" <<'\t'<<setw(8) << "QUANTITY"<<endl;
    cout<<left<<setw(10) <<singleItem.itemId <<'\t' << setw(20)<< singleItem.name;
    cout<<'\t'<<setw(8)<<singleItem.location<<'\t'<< setw(10)<<singleItem.unitPrice;
    cout<<'\t'<< setw(10)<<singleItem.discount<<'\t'<< setw(8)<<singleItem.avaQua<<endl;
}
void displayPurchaseD(fstream &fpd, long position){
    purchaseDetail singlepurchase;
    fpd.seekg(position);
    fpd.read((char *)&singlepurchase,sizeof(purchaseDetail));
    cout <<left<<setw(11) << "ITEM ID" <<'\t'<< setw(11) << "Purchase ID" <<'\t';
    cout<<setw(10) << "Invoice No" <<'\t'<<setw(8) << "QUANTITY" <<'\t';
    cout<<setw(10) << "UNIT PRICE"<<endl;
    cout << setw(11) <<singlepurchase.itemId<<'\t'<<setw(11)<<singlepurchase.purchaseId;
    cout<<'\t'<<setw(10)<<singlepurchase.invoiceNo<<'\t'<<setw(8)<<singlepurchase.quantity;
    cout<<'\t'<< setw(10)<<singlepurchase.unitPrice<<endl;
}
void displayPurchase(fstream &fp, long position){
    purchase singlepurchase;
    fp.seekg(position);
    fp.read((char *)&singlepurchase,sizeof(purchase));
    cout <<left<<setw(11) << "Invoice No" <<'\t'<< setw(39) << "Supplier Full Name" <<'\t';
    cout<<setw(10) << "Date of Purchase"<<endl;
    cout << setw(11) <<singlepurchase.invoiceNo<<'\t'<<setw(39)<<singlepurchase.supplierFullName;
    cout<<'\t'<<setw(2)<<singlepurchase.date_of_purchase.day<<'/';
    cout<<setw(2)<<singlepurchase.date_of_purchase.month<<'/';
    cout<<setw(4)<<singlepurchase.date_of_purchase.year<<endl;
}
void getEditItem(item &oldItem){
    cout <<"Enter new item info:" <<endl;
    cout<<"Product Name: ";
    cin.getline(oldItem.name,19);
    cout<<"Product Location: ";
    cin>>oldItem.location;
    cout<<"Unit Price: ";
    cin>>oldItem.unitPrice;
    cout<<"Available Quantity: ";
    cin>>oldItem.avaQua;
    cout<<"Discount: ";
    cin>>oldItem.discount;
}
void editItem(fstream & fitem, itemIdex * iIdx,long in){
     long id,position,idx;
     item itm;
     cout<<"Enter the product's id that you want to be edited: ";
     cin>>id;
     cin.ignore(INT_MAX,'\n');
     position=searchItemById(iIdx,id,in,idx);
     if(position==-1)
        cout<<"Not found!!!";
     else{
        cout<<"Current item info...\n";
        displayItem(fitem,position);
        getEditItem(itm);
        itm.itemId=id;
        strncpy(iIdx[idx].name,itm.name,19);
        fitem.seekp(position,ios::beg);
        fitem.write((char *) &itm,sizeof(item));
        system("cls");
        cout<<"Edited!!!";

     }
}
void getEditPurchase(purchase &oldpurchase){
    char ch;
    cout<<"Date of purchase: ";
    cin>>oldpurchase.date_of_purchase.day>>ch>>oldpurchase.date_of_purchase.month>>ch>>oldpurchase.date_of_purchase.year;
    cin.ignore(INT_MAX,'\n');
    cout<<"Supplier Full Name: ";
    cin.getline(oldpurchase.supplierFullName,39);
    system("cls");
    cout<<"Edited!!!";
}
void getEditPurchaseD(purchaseDetail &oldpurchase){
    cout <<"you can only edit its unit price" <<endl;
    cout<<"Unit Price: ";
    cin>>oldpurchase.unitPrice;
    system("cls");
    cout<<"Edited!!!";
}
void editPurchaseOne(fstream & fp, purchaseIdexOne * pIdx,long pn){
     long * position,idx,num;
     date d;char ch;
     purchase p;
     cout<<"Enter the product's purchasing date that you want to be edited: ";
     cin>>d.day>>ch>>d.month>>ch>>d.year;
     position=searchPurchaseByDate(pIdx,d,pn,idx);
     if(idx==0)
        cout<<"Not found!!!";
     else{
        cout<<"Current purchase detail info...\n";
        long i=0;
        while(i<idx){
            cout<<i<<' ';
            displayPurchase(fp,position[i]);
            i++;
        }
        cout<<"which product do you want to be edited: ";
        cin>>num;
        fp.seekg(position[num],ios::beg);
        fp.read((char *)&p,sizeof(p));
        getEditPurchase(p);
        fp.seekp(position[num],ios::beg);
        fp.write((char *) &p,sizeof(p));
     }
}
void editPurchase(fstream & fpd, purchaseIdex * pIdx,long pn){
     long id,position,idx;
     purchaseDetail pd;
     cout<<"Enter the product's item id that you want to be edited: ";
     cin>>id;
     position=searchPurchaseByiId(pIdx,id,pn,idx);
     if(position==-1)
        cout<<"Not found!!!";
     else{
        cout<<"Current purchase detail info...\n";
        displayPurchaseD(fpd,position);
        fpd.seekg(position,ios::beg);
        fpd.read((char *)&pd,sizeof(pd));
        getEditPurchaseD(pd);
        fpd.seekp(position,ios::beg);
        fpd.write((char *) &pd,sizeof(pd));
     }
}
void newPurchase(purchase & pur, purchaseDetail &purD,itemIdex* iIdx,long lastPurchaseId,long idx){
    char ch;
    cout <<"Enter product info:" <<endl;
    cout<<"Invoice Number: ";
    cin>>pur.invoiceNo;
    cout<<"Date of purchase: ";
    cin>>pur.date_of_purchase.day>>ch>>pur.date_of_purchase.month>>ch>>pur.date_of_purchase.year;
    cin.ignore(INT_MAX,'\n');
    cout<<"Supplier full name: ";
    cin.getline(pur.supplierFullName,39);
    purD.purchaseId=++lastPurchaseId;
    purD.invoiceNo=pur.invoiceNo;
    purD.itemId=iIdx[idx].itemId;
    cout<<"Unit price: ";cin>>purD.unitPrice;
    cout<<"Quantity: ";cin>>purD.quantity;
}
int getNewPurchase(fstream &fp,fstream &fpd,fstream &fitem,purchaseIdex* & pdIdx,purchaseIdexOne * & pIdx,
                  itemIdex* iIdx,long &in,long &pn,int &pfs,int &ifs,long &lastPurchaseId,long &lastItemId){
    purchase pur; purchaseDetail purD; purchaseIdex * temp;purchaseIdexOne *temp1;
    long itemPosition,idx,position; int status;
    if(pfs==0) {
        temp=new (nothrow) purchaseIdex[pn + 10];
        temp1=new (nothrow) purchaseIdexOne[pn + 10];
        if(temp&&temp1){
            for(int i=0; i< pn; i++){
                temp[i]=pdIdx[i];
                temp1[i]=pIdx[i];
                }
            delete [] pIdx;delete [] pdIdx;
            pIdx=temp1;pdIdx=temp;
            pfs=10;
        }else return 0;
    }char name[20];
    cout<<"Enter the product's name: ";
    cin.getline(name,19);
    itemPosition=searchItemByName(iIdx,name,in,idx);
    position=itemPosition;
    if(position==-1){
        cout<<"The product has not been register!!!\n";
        status=getNewItem(fitem,iIdx,in,ifs,lastItemId);
        if(status){
            cout<<"Registered!!!\n";
            fitem.seekp(-sizeof(item),ios::end);
            itemPosition=fitem.tellp();
            idx=in-1;}  //searchItemByName(iIdx,name,in,idx);
    }
    newPurchase(pur,purD,iIdx,lastPurchaseId,idx);
    fp.seekp(0,ios::end); fpd.seekp(0,ios::end);
    position=fpd.tellp();
    pdIdx[pn].invoiceNo=pur.invoiceNo;
    pdIdx[pn].itemId=iIdx[idx].itemId;
    pdIdx[pn].position=position;
    pdIdx[pn].purchaseId=++lastPurchaseId;
    pIdx[pn].date_of_purchase.day=pur.date_of_purchase.day;
    pIdx[pn].date_of_purchase.month=pur.date_of_purchase.month;
    pIdx[pn].date_of_purchase.year=pur.date_of_purchase.year;
    position=fp.tellp();
    pIdx[pn].position=position;
    fp.write((char *)&pur,sizeof(pur));
    fpd.write((char *)&purD,sizeof(purD));
    pn++; pfs--;
    editItem(fitem,purD,itemPosition);
    return 1;
}
int Menu(){
    fstream fp,fpd,fitem;
    long in,pn,lastItemId,lastPurchaseId,idx;
    int status1,status2,status3,ifs,pfs,choice;
    char ans;
    itemIdex * iIdx;purchaseIdex *pdIdx;purchaseIdexOne *pIdx;
    char * path1="item.bin",* path2="purchase.bin",*path3="purchase_detail.bin";
    status1 = openFile(fitem,fp,fpd,path1,path2,path3);
    if(!status1){
        cout << "Disk is corrupted or malfunctioning!!!";
        return 0;
    }
    status1=loadingItemFile(fitem,iIdx,in,ifs,lastItemId);
    status2=loadingPurchase(fp,pIdx,pn,pfs);
    status3=loadingPurchaseD(fpd,pdIdx,pn,pfs,lastPurchaseId);
    if(!status1||!status2||!status3){
        cout << "Not enough memory!!!";
        return 0;
        }
    do{
        system("cls");
        cout<<"1.Item\n2.Purchase\n3.Exit\n";
        cin>>choice;
        switch(choice){
        case 1:
            system("cls");
            do{
            cout<<"\n1.New Item\n2.Search Item\n3.Edit Item\n4.Back to menu\n";
            cin>>choice;
            cin.ignore(INT_MAX,'\n');
            switch(choice){
                case 1:
                    system("cls");
                    status1=getNewItem(fitem,iIdx,in,ifs,lastItemId);
                    if(status1)
                        cout<<"Added!!!";
                    break;
                case 2:
                    system("cls");
                    cout<<"Search by\n1.By item id\n2.By name\n3.By location\n";
                    cin>>choice;
                    switch(choice){
                        char ans;long position;
                    case 1:
                        system("cls");
                        long id;
                        cout<<"Enter the item's id: ";
                        cin>>id;
                        position=searchItemById(iIdx,id,in,idx);
                        if(position!=-1){
                            cout<<"Do you want to see the result? Enter y/Y: ";
                            cin>>ans;
                            if(ans=='y'||ans=='Y')
                            displayItem(fitem,position);
                        }
                        else cout<<"Not found!!!";
                        break;
                    case 2:
                        system("cls");
                        char name[20];
                        cout<<"Enter the item's name: ";
                        cin.ignore(INT_MAX,'\n');
                        cin.getline(name,19);
                        position=searchItemByName(iIdx,name,in,idx);
                        if(position!=-1){
                            cout<<"Do you want to see the result? Enter y/Y: ";
                            cin>>ans;
                            if(ans=='y'||ans=='Y')
                                displayItem(fitem,position);
                        }
                        else cout<<"Not found!!!";
                        break;
                    case 3:
                        system("cls");
                        char loc[3];
                        cout<<"Enter the item's location: ";
                        cin>>loc;
                        long *pos;
                        pos=searchItemByLocation(iIdx,loc,in,idx);
                        if(idx==0)
                            cout<<"Not found!!!";
                        else {
                            cout<<"Do you want to see the result? Enter y/Y: ";
                            cin>>ans;
                            if(ans=='y'||ans=='Y'){
                                int i=0;
                                while(i<idx){
                                    displayItem(fitem,pos[i]);
                                    i++;
                                }
                            }
                        }
                        break;
                    }
                    break;
                case 3:
                    system("cls");
                    editItem(fitem,iIdx,in);
                    break;
                case 4:
                    system("cls");
                    break;
                }
            }while(choice!=4);
            break;
        case 2:
            system("cls");
            do{
            cout<<"\n1.New Purchase\n2.Search Purchase\n3.Edit Purchase\n5.Back to menu\n";
            cin>>choice;
            cin.ignore(INT_MAX,'\n');
            switch(choice){
            case 1:
                system("cls");
                status1=getNewPurchase(fp,fpd,fitem,pdIdx,pIdx,iIdx,in,pn,pfs,ifs,lastPurchaseId,lastItemId);
                system("cls");
                if(status1)
                    cout<<"Purchased!!!";
                break;
            case 2:
                system("cls");
                cout<<"1.By purchase id\n2.By item id\n3.By invoice number\n4.By date\n";
                cin>>choice;
                switch(choice){
                    system("cls");
                    long position;char ans;
                case 1:
                    system("cls");
                     long id;cout<<"Enter the id: ";
                    cin>>id;
                    position=searchPurchaseByiId(pdIdx,id,pn,idx);
                    if(position!=-1){
                        cout<<"Do you want to see the result? Enter y/Y: ";
                        cin>>ans;
                        if(ans=='y'||ans=='Y')
                            displayPurchaseD(fpd,position);
                    }else cout<<"Not found!!!";
                    break;
                case 2:
                    system("cls");
                    cout<<"Enter the item's id: ";
                    cin>>id;
                    position=searchPurchaseByiId(pdIdx,id,pn,idx);
                    if(position!=-1){
                        cout<<"Do you want to see the result? Enter y/Y: ";
                        cin>>ans;
                        if(ans=='y'||ans=='Y')
                        displayPurchaseD(fpd,position);
                    }else cout<<"Not found!!!";
                    break;
                case 3:
                    system("cls");
                    long invoice;cout<<"Enter invoice number: ";
                    cin>>invoice;
                    long *pos;
                    pos=searchPurchaseByivoiceNo(pdIdx,invoice,pn,idx);
                    if(idx==0)
                       cout<<"Not found!!!";
                    else{
                        cout<<"Do you want to see the result? Enter y/Y: ";
                        cin>>ans;
                        if(ans=='y'||ans=='Y'){
                            long i=0;
                            while(i<idx){
                              displayPurchaseD(fpd,pos[i]);
                              i++;
                            }
                        }
                    }
                    break;
                case 4:
                    system("cls");char ch;
                    date d;cout<<"Enter date of purchase: ";
                    cin>>d.day>>ch>>d.month>>ch>>d.year;
                    pos=searchPurchaseByDate(pIdx,d,pn,idx);
                    if(idx==0)
                        cout<<"Not found!!!";
                    else{
                        cout<<"Do you want to see the result? Enter y/Y: ";
                        cin>>ans;
                        if(ans=='y'||ans=='Y'){
                            long i=0;
                            while(i<idx){
                                displayPurchase(fp,pos[i]);
                                i++;
                            }
                        }
                    }
                    break;
                    }
                break;
            case 3:
                system("cls");int your_ans;
                cout<<"which part do you want to edit 1. Purchase 2. Purchase Detail: ";
                cin>>your_ans;
                if(your_ans==1)
                    editPurchaseOne(fp,pIdx,pn);
                else if (your_ans==2)
                    editPurchase(fpd,pdIdx,pn);
                else cout<<"Wrong Choice!!!";
                break;
            case 4:
                system("cls");
                break;
                }
            }while(choice!=5);
            break;
        case 3:
            break;
        }
    }while(choice!=3);
}
int main(){
    int status;
    status=Menu();
    if(status)
        system("cls");
        cout<<"Good bye!!!";
    return 0;
}




