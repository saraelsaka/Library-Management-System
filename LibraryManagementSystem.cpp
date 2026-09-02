#include <iostream>
using namespace std;

//--------------------Book class-----------------------
class Book{
    public:
        int BookId;
        string title;
        string author;
        bool isAvailable;
        static int TotalBooks;

        Book(): BookId(0), title(""), author(""), isAvailable(true){ 
        TotalBooks++;
        }

//--------------Display Book Data--------------------------
    void display() const{
        cout<<"Book ID: "<<BookId<<endl;
        cout<<"Book Title: "<<title<<endl;
        cout<<"Author: "<<author<<endl;
        cout<<((isAvailable)?"Available ":"Not Available ")<<endl;
        cout<<"____________________________________________"<<endl;
    }

    bool operator==(const Book &other) const{
        return BookId == other.BookId;
    }
};

int Book::TotalBooks = 0;

class Person{
    protected:
        string name;
        int id;

    public:
        Person(): name(""), id(0){}
        Person(string n,int i): name(n), id(i){}

    virtual void showMenu(Book books[], int &bookCount) = 0;
};

//-------------------Member class---------------------
class Member: public Person{
    private:
        Book BorrowedBooks[5];
        int BorrowedCount;

    public:
        Member(): BorrowedCount(0){}
        Member(string n,int i): Person(n,i), BorrowedCount(0){}

//-----------------Borrowing Book method---------------
    void BorrowBook(Book books[], int bookCount){
        int bid;
        cout<<"Enter Book ID to borrow: ";
        cin>>bid;

        for(int i = 0; i < bookCount; i++){
            if(books[i].BookId == bid && books[i].isAvailable){

                if(BorrowedCount==5){ 
                    cout<<"you reached Limit books "<<endl;
                    return; 
                }
                BorrowedBooks[BorrowedCount++] = books[i];
                books[i].isAvailable = false;
                cout<<"Book Borrowed Successfully!"<<endl;
                return;
            }
        }
        cout<<"Book not available!"<<endl;
    }

//----------------Returning Book method-------------------
    void returnBook(Book books[], int bookCount){
        int bid;
        cout<<"Enter Book ID to return: ";
        cin>>bid;

        for(int i = 0;i < BorrowedCount ;i++){
            if(BorrowedBooks[i].BookId == bid){
                for(int j = 0 ; j < bookCount;j++)
                    if(books[j].BookId == bid){ 
                        books[j].isAvailable=true; 
                        break; 
                    }

                for(int k = i ;k < BorrowedCount-1 ;k++) {
                    BorrowedBooks[k]=BorrowedBooks[k+1];
                }
                BorrowedCount--;
                cout<<"Book Returned Successfully!"<<endl;
                return;
            }
        }
        cout<<"You didn't borrow this book!"<<endl;
    }
//---------------View Borrowed Book method-----------------
    void ViewMyBooks() {
        if(BorrowedCount == 0){ 
            cout<<"No borrowed books"<<endl; 
            return; 
        }
        cout<<"My borrowed books:"<<endl;
        for(int i = 0; i< BorrowedCount; i++)
            cout<<BorrowedBooks[i].BookId
            <<". "<<BorrowedBooks[i].title<<" - "
            <<BorrowedBooks[i].author<<endl;
    }


//-----------------Menu method----------------------------
    void showMenu(Book books[], int &bookCount) override{
        int choice = 0;
        while(choice!= 5){
            cout<<"\nMember Menu\n1. View Available Books\n2. Borrow Book\n3. Return Book\n4. View My Books\n5. Logout"<<endl;
            cout<<"Enter your choice: ";
            cin>>choice;
            switch(choice){
                case 1:
                    for(int i=0;i<bookCount;i++)
                        if(books[i].isAvailable){
                            books[i].display();}
                            break;
                case 2: 
                    BorrowBook(books,bookCount); 
                    break;
                case 3: 
                    returnBook(books,bookCount); 
                    break;
                case 4:     
                    ViewMyBooks(); 
                    break;
                case 5: 
                    cout<<"Logging out..."<<endl; 
                    break;
                default: 
                    cout<<"Invalid choice!"<<endl;
            }
        }
    }
};


//----------------Librarian class-----------------------
class Librarian: public Person{
public:
    Librarian(){}
    Librarian(string n , int i): Person(n , i){}

//------------------Adding book to library-------------------------
    void addBook(Book books[], int &bookCount){
        Book b;
        cout<<"Enter Book ID: "; 
        cin>>b.BookId;
        cin.ignore();

        cout<<"Enter Book Title: ";
        getline(cin,b.title);

        cout<<"Enter Book Author: ";
        getline(cin,b.author);

        b.isAvailable = true;
        books[bookCount++] = b;
        cout<<"Book Added Successfully!"<<endl;
    }

//---------------remove Book from library-----------
    void removeBook(Book books[], int &bookCount){
        int bid;
        cout<<"Enter Book ID to remove: "; 
        cin>>bid;
        for(int i = 0; i < bookCount;i++){
            if(books[i].BookId == bid){
                for(int j = i; j < bookCount-1 ;j++) 
                books[j] = books[j+1];
                bookCount--; 
                Book::TotalBooks--;
                cout<<"Book Removed Successfully!"<<endl;
                return;
            }
        }
        cout<<"Book not found!"<<endl;
    }

//--------------View Books--------------------
    void viewAllBooks(Book books[], int bookCount){
        cout<<"All Books: "<<endl;
        for(int i=0; i < bookCount; i++)
            books[i].display();
    }

//-----------------Menu ----------------------------
    void showMenu(Book books[], int &bookCount) override{
        int choice = 0;
        while(choice!=5){
            cout<<"\nLibrarian Menu\n1. Add Book\n2. Remove Book\n3. View All Books\n4. Show Total Books\n5. Logout"<<endl;
            cout<<"Enter your choice: ";
            cin>>choice;

            switch(choice){
                case 1: 
                    addBook(books , bookCount); 
                    break;
                case 2: 
                    removeBook(books , bookCount); 
                    break;
                case 3: 
                    viewAllBooks(books , bookCount); 
                    break;
                case 4: 
                    cout<<"Total Books in System: "<< bookCount<<endl; break;
                case 5: 
                    cout<<"Logging out..."<<endl; break;
                default: 
                    cout<<"Invalid choice!"<<endl;
            }
        }
    }
};

//---------------LibrarySystem class----------------- 
class LibrarySystem{
    public:
        Book books[100];
        int bookCount;

        LibrarySystem(): bookCount(3){
//----------Book 1 ------------
        books[0].BookId=1; 
        books[0].title="1984"; 
        books[0].author="George Orwell"; 
        books[0].isAvailable=true;
//----------Book 2 ------------
        books[1].BookId=2; 
        books[1].title="Harry Potter"; 
        books[1].author="J.K. Rowling"; 
        books[1].isAvailable=true;
//-----------Book 3------------
        books[2].BookId=3; 
        books[2].title="C++ Basics"; 
        books[2].author="Author X"; 
        books[2].isAvailable=true;
    }

    void start(){
        int choice = 0;
        while(choice!= 3){
            cout<<"---Hello in Library---"<<endl;
            cout<<"\nLibrary System Main Menu\n1. Librarian\n2. Member\n3. Exit"<<endl;
            cout<<"Select Role: ";
            cin>>choice;
            cin.ignore(); 

            if(choice == 1){
                string n; 
                int i;
                cout<<"Enter your Name: "; 
                getline(cin , n);
                cout<<"Enter your ID: "; 
                cin>>i; 
                cin.ignore();
                
                Librarian lib(n , i);
                lib.showMenu(books , bookCount);
            }
            else if(choice == 2){
                string n; 
                int i;
                cout<<"Enter your Name: "; 
                getline(cin,n);
                cout<<"Enter your ID: "; 
                cin>>i; 
                cin.ignore();
                Member mem(n,i);
                mem.showMenu(books , bookCount);
            }
            else if(choice == 3){ 
                cout<<"Exiting... Bye Bye!"<<endl; 
            }
            else{
                cout<<"Invalid choice!"<<endl;
            } 
        }
    }
};

int main(){
    LibrarySystem lib;
    lib.start();
    return 0;
}