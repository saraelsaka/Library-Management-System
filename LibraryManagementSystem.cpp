#include <iostream>
#include <string>
#include <limits>
using namespace std;

bool readInt(int &value) {
    if (!(cin >> value)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number." << endl;
        return false;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return true;
}

//--------------------Book class-----------------------
class Book {
public:
    int BookId;
    string title;
    string author;
    bool isAvailable;

    static int TotalBooks;

    Book() : BookId(0), title(""), author(""), isAvailable(true) {}

    //----------------Display Book Data----------------
    void display() const {
        cout << "Book ID: " << BookId << endl;
        cout << "Book Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << (isAvailable ? "Available" : "Not Available") << endl;
        cout << "____________________________________________" << endl;
    }

    bool operator==(const Book &other) const {
        return BookId == other.BookId;
    }
};

int Book::TotalBooks = 0;

//--------------------Person class--------------------
class Person {
protected:
    string name;
    int id;

public:
    Person() : name(""), id(0) {}

    Person(string n, int i) : name(n), id(i) {}

    virtual void showMenu(Book books[], int &bookCount) = 0;

    virtual ~Person() {}
};

//--------------------Member class---------------------
class Member : public Person {
private:
    Book BorrowedBooks[5];
    int BorrowedCount;

public:
    Member() : BorrowedCount(0) {}

    Member(string n, int i) : Person(n, i), BorrowedCount(0) {}

    //----------------Borrow Book-----------------------
    void BorrowBook(Book books[], int bookCount) {
        if (BorrowedCount >= 5) {
            cout << "You reached the borrowing limit!" << endl;
            return;
        }

        int bid;

        cout << "Enter Book ID to borrow: ";

        if (!readInt(bid)) {
            return;
        }

        for (int i = 0; i < bookCount; i++) {
            if (books[i].BookId == bid) {
                if (!books[i].isAvailable) {
                    cout << "Book is already borrowed!" << endl;
                    return;
                }

                BorrowedBooks[BorrowedCount++] = books[i];
                books[i].isAvailable = false;

                cout << "Book Borrowed Successfully!" << endl;
                return;
            }
        }

        cout << "Book not found!" << endl;
    }

    //----------------Return Book-----------------------
    void returnBook(Book books[], int bookCount) {
        int bid;

        cout << "Enter Book ID to return: ";

        if (!readInt(bid)) {
            return;
        }

        for (int i = 0; i < BorrowedCount; i++) {
            if (BorrowedBooks[i].BookId == bid) {

                for (int j = 0; j < bookCount; j++) {
                    if (books[j] == BorrowedBooks[i]) {
                        books[j].isAvailable = true;
                        break;
                    }
                }

                for (int k = i; k < BorrowedCount - 1; k++) {
                    BorrowedBooks[k] = BorrowedBooks[k + 1];
                }

                BorrowedCount--;

                cout << "Book Returned Successfully!" << endl;
                return;
            }
        }

        cout << "You didn't borrow this book!" << endl;
    }

    //----------------View Borrowed Books---------------
    void ViewMyBooks() const {
        if (BorrowedCount == 0) {
            cout << "No borrowed books." << endl;
            return;
        }

        cout << "\nMy Borrowed Books:" << endl;

        for (int i = 0; i < BorrowedCount; i++) {
            cout << BorrowedBooks[i].BookId << ". "
                 << BorrowedBooks[i].title << " - "
                 << BorrowedBooks[i].author << endl;
        }
    }

    //----------------Member Menu-----------------------
    void showMenu(Book books[], int &bookCount) override {
        int choice = 0;

        while (choice != 5) {
            cout << "\nMember Menu" << endl;
            cout << "1. View Available Books" << endl;
            cout << "2. Borrow Book" << endl;
            cout << "3. Return Book" << endl;
            cout << "4. View My Books" << endl;
            cout << "5. Logout" << endl;
            cout << "Enter your choice: ";

            if (!readInt(choice)) {
                continue;
            }

            switch (choice) {
                case 1: {
                    bool found = false;

                    for (int i = 0; i < bookCount; i++) {
                        if (books[i].isAvailable) {
                            books[i].display();
                            found = true;
                        }
                    }

                    if (!found) {
                        cout << "No available books." << endl;
                    }

                    break;
                }

                case 2:
                    BorrowBook(books, bookCount);
                    break;

                case 3:
                    returnBook(books, bookCount);
                    break;

                case 4:
                    ViewMyBooks();
                    break;

                case 5:
                    cout << "Logging out..." << endl;
                    break;

                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }
};

//--------------------Librarian class------------------
class Librarian : public Person {
public:
    Librarian() {}

    Librarian(string n, int i) : Person(n, i) {}

    //----------------Add Book--------------------------
    void addBook(Book books[], int &bookCount) {
        if (bookCount >= 100) {
            cout << "Library is full!" << endl;
            return;
        }

        Book b;

        cout << "Enter Book ID: ";

        if (!readInt(b.BookId)) {
            return;
        }

        if (b.BookId <= 0) {
            cout << "Book ID must be positive!" << endl;
            return;
        }

        for (int i = 0; i < bookCount; i++) {
            if (books[i].BookId == b.BookId) {
                cout << "Book ID already exists!" << endl;
                return;
            }
        }

        cout << "Enter Book Title: ";
        getline(cin, b.title);

        cout << "Enter Book Author: ";
        getline(cin, b.author);

        b.isAvailable = true;

        books[bookCount] = b;
        bookCount++;
        Book::TotalBooks = bookCount;

        cout << "Book Added Successfully!" << endl;
    }

    //----------------Remove Book-----------------------
    void removeBook(Book books[], int &bookCount) {
        int bid;

        cout << "Enter Book ID to remove: ";

        if (!readInt(bid)) {
            return;
        }

        for (int i = 0; i < bookCount; i++) {
            if (books[i].BookId == bid) {

                if (!books[i].isAvailable) {
                    cout << "Cannot remove a borrowed book!" << endl;
                    return;
                }

                for (int j = i; j < bookCount - 1; j++) {
                    books[j] = books[j + 1];
                }

                bookCount--;
                Book::TotalBooks = bookCount;

                cout << "Book Removed Successfully!" << endl;
                return;
            }
        }

        cout << "Book not found!" << endl;
    }

    //----------------View All Books--------------------
    void viewAllBooks(Book books[], int bookCount) const {
        if (bookCount == 0) {
            cout << "No books in the library." << endl;
            return;
        }

        cout << "\nAll Books:" << endl;

        for (int i = 0; i < bookCount; i++) {
            books[i].display();
        }
    }

    //----------------Librarian Menu--------------------
    void showMenu(Book books[], int &bookCount) override {
        int choice = 0;

        while (choice != 5) {
            cout << "\nLibrarian Menu" << endl;
            cout << "1. Add Book" << endl;
            cout << "2. Remove Book" << endl;
            cout << "3. View All Books" << endl;
            cout << "4. Show Total Books" << endl;
            cout << "5. Logout" << endl;
            cout << "Enter your choice: ";

            if (!readInt(choice)) {
                continue;
            }

            switch (choice) {
                case 1:
                    addBook(books, bookCount);
                    break;

                case 2:
                    removeBook(books, bookCount);
                    break;

                case 3:
                    viewAllBooks(books, bookCount);
                    break;

                case 4:
                    cout << "Total Books in System: "
                         << Book::TotalBooks << endl;
                    break;

                case 5:
                    cout << "Logging out..." << endl;
                    break;

                default:
                    cout << "Invalid choice!" << endl;
            }
        }
    }
};

//--------------------LibrarySystem class--------------
class LibrarySystem {
public:
    Book books[100];
    int bookCount;

    LibrarySystem() : bookCount(3) {
        //----------------Book 1-----------------------
        books[0].BookId = 1;
        books[0].title = "1984";
        books[0].author = "George Orwell";
        books[0].isAvailable = true;

        //----------------Book 2-----------------------
        books[1].BookId = 2;
        books[1].title = "Harry Potter";
        books[1].author = "J.K. Rowling";
        books[1].isAvailable = true;

        //----------------Book 3-----------------------
        books[2].BookId = 3;
        books[2].title = "C++ Basics";
        books[2].author = "Author X";
        books[2].isAvailable = true;

        Book::TotalBooks = bookCount;
    }

    //----------------Start System----------------------
    void start() {
        int choice = 0;

        while (choice != 3) {
            cout << "\n--- Welcome to the Library ---" << endl;
            cout << "1. Librarian" << endl;
            cout << "2. Member" << endl;
            cout << "3. Exit" << endl;
            cout << "Select Role: ";

            if (!readInt(choice)) {
                continue;
            }

            if (choice == 1) {
                string n;
                int i;

                cout << "Enter your Name: ";
                getline(cin, n);

                cout << "Enter your ID: ";

                if (!readInt(i)) {
                    continue;
                }

                Librarian lib(n, i);
                lib.showMenu(books, bookCount);
            }

            else if (choice == 2) {
                string n;
                int i;

                cout << "Enter your Name: ";
                getline(cin, n);

                cout << "Enter your ID: ";

                if (!readInt(i)) {
                    continue;
                }

                Member mem(n, i);
                mem.showMenu(books, bookCount);
            }

            else if (choice == 3) {
                cout << "Exiting... Bye Bye!" << endl;
            }

            else {
                cout << "Invalid choice!" << endl;
            }
        }
    }
};

//--------------------Main Function--------------------
int main() {
    LibrarySystem lib;
    lib.start();

    return 0;
}