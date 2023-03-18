#include<iostream>
#include<fstream>
#include<ctime>
#include<string.h>
using namespace std;

class book{
    private:
    int bookId;
    char date[15];
    char time[15];
    char title[25];
    int price;
    
    public:
    book(){
        bookId = 0;
        strcpy(title,"no title");
        price = 0;
    }
    void getBookData();
    void showBookData();
    int storeBook();
    void viewAllBooks();
    void searchBook(char *);
    void deleteBook(char *);
};

void book::deleteBook(char * t){
    ifstream fin;
    ofstream fout;
    bool flag = false;
    fin.open("Book.dat",ios::in|ios::binary);
    fout.open("temp.dat",ios::out|ios::binary);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof()){
        if(strcmp(t,title)){
            fout.write((char*)this,sizeof(*this));
            fin.read((char*)this,sizeof(*this));
        }else{
             flag = true;
              fin.read((char*)this,sizeof(*this));
        } 
    }
    fout.close();
    fin.close();
    if(!flag){
        cout<<"\t\tBook Not Found\n";
    }
    remove("Book.dat");
    rename("temp.dat","Book.dat");
}

void book :: searchBook(char *str){
    ifstream fin;
    system("clear");
     cout<<"\t\t$---Welcome to the Radhe Rani Book Store---$\n";
    bool flag = false;
    fin.open("Book.dat",ios::in|ios::binary);
    if(!fin)cout<<"\t\tFile Not Found\n";
    else{
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
           if(!strcmp(str,title)){
               showBookData();
               flag = true;
               return;
            }
               fin.read((char*)this,sizeof(*this));
        }
        if(!flag == true)cout<<"\t\tNot Found\n";
        return;
    }
}

void book :: viewAllBooks(){
    ifstream fin;
    system("clear");
     cout<<"\t\t$---Welcome to the Radha Rani Book Store---$\n";
    fin.open("Book.dat",ios::in|ios::binary);
    if(!fin)
         cout<<"\t\tFile Not Found\n";
    else{   
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof()){
        showBookData();
       fin.read((char*)this,sizeof(*this));
       }
       fin.close();
    }
}

void book :: showBookData(){
    cout<<"\t\t---------------------------------\n";
    cout<<"\t\tDate  : "<<date<<endl;
    cout<<"\t\tTime  : "<<time<<endl;
    cout<<"\t\tId    : "<<bookId<<endl;
    cout<<"\t\tName  : "<<title<<endl;
    cout<<"\t\tPrice : "<<price<<endl;
    cout<<"\t\t---------------------------------\n";
    return;
}

int book::storeBook(){
    getBookData();
    if(bookId == 0 or price == 0){
        cout<<"\t\tBook Detail not Enteredn\n";
        return 0;
    }
    else{
    ofstream fout;
    fout.open("Book.dat",ios::app|ios::binary);
    fout.write((char*)this,sizeof(*this));
    fout.close();
    cout<<"\t\tAdded Record\n";
    return 1;
    }
}

void book :: getBookData(){
    system("clear");
    cout<<"\t\t$---Welcome to the Radha Rani Book Store---$\n";
    strcpy(date,__DATE__);
    strcpy(time,__TIME__);
    cout<<"\n\t\tEnter the Book Id : ";
    cin>>bookId;
    cout<<"\t\tEnter the Book Title : ";
    cin.ignore();
    cin.getline(title,20);
    cout<<"\t\tEnter the Book Price : ";
    cin>>price;
}

int main(){
   book b1;
   system("clear");
    cout<<"\t\t$---Welcome to the Radha Rani Book Store---$\n";
   while(1){
    char str[10];
    int ch;
    cout<<"\n\n\t\tPress\n";
    cout<<"\t\t1. StoreBook\n";
    cout<<"\t\t2. View_All_Books\n";
    cout<<"\t\t3. Search_A_Book\n";
    cout<<"\t\t4. Delete_Book_Record\n";
    cout<<"\t\t5. Exit\n";
    cout<<"\t\tEnter your Choice.";
    cin>>ch;

    switch(ch){
        case 1:
          b1.storeBook();
          break;
        case 2:
          b1.viewAllBooks();
          break;
        case 3:
           cout<<"\t\tEnter Name : ";
           cin.ignore();cin.getline(str,10);
           b1.searchBook(str);
           break;
        case 4:
           cout<<"\t\tEnter Name : ";
           cin.ignore();cin.getline(str,10);
           b1.deleteBook(str);      
           break;
        case 5:
           exit(0);
           break;
        default:
           cout<<"\t\tWrong Choice\n";       
    }
   }
   return 0;
}
