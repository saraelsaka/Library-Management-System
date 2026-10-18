# Library Management System

A console-based Library Management System developed using C++ to practice Object-Oriented Programming (OOP) concepts.

The system allows librarians to manage books and members to borrow, return, and view their borrowed books.

## Features

- Add new books to the library.
- Remove books that are not currently borrowed.
- View all books and their availability.
- Prevent duplicate book IDs.
- Borrow and return books.
- View borrowed books.
- Limit each member to five borrowed books.
- Display the total number of books.
- Provide separate menus for librarians and members.
- Validate numeric input in menus and book operations.

## Technologies Used

- C++
- Object-Oriented Programming
- Arrays and Loops
- Functions and Constructors

## OOP Concepts Applied

### 1. Encapsulation
Using access specifiers such as `private`, `protected`, and `public` to control access to class members.

### 2. Inheritance
Using the `Person` base class for the `Member` and `Librarian` classes.

### 3. Polymorphism
Using virtual functions and function overriding to implement separate menus for members and librarians.

### 4. Abstraction
Using `Person` as an abstract class with a pure virtual function.

### 5. Static Members
Using a static member to track the total number of books in the library.

### 6. Operator Overloading
Overloading the equality operator (`==`) to compare books by their IDs.

## Project Structure

```text
Library-Management-System/
│
├── main.cpp
├── README.md
└── .gitignore
```

## How to Run

### Requirements

- A C++ compiler such as GCC or MinGW.
- A code editor or IDE such as Visual Studio Code.

### Compile the Program

Open a terminal in the project directory and run:

```bash
g++ -std=c++11 main.cpp -o library
```

### Run the Program

On Windows:

```bash
library.exe
```

On Linux or macOS:

```bash
./library
```

## Current Limitations

- Book and borrowing data are stored in memory and are lost when the program closes.
- The system does not use a database.
- The system does not include persistent user accounts or authentication.
- Each member's borrowing records are maintained only during that member's session.

## Future Improvements

- Store book and member data in files or a database.
- Add a search feature for books.
- Introduce persistent member accounts.
- Separate class declarations and implementations into header and source files.
- Add automated tests for library operations.

## Author

Sara Elsaka
