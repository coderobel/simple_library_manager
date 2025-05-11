#include <iostream>
#include <cstring> 
#include <fstream>
#include <stdlib.h>
using namespace std;

struct book {
    int ID;
    char Title[30];
    char Author[30];
    char Availability[10];
} bookdata[100];

struct members {
    int memberID;
    char fname[30];
    char lname[30];
    char borrowed_books[10][10];
    char returned_books[10][10];
} librarymembers[100];

void searchbook();
void AddNewBooks();
void issuebooks();
void returnbooks();
void loadBooksFromFile();
void saveBooksToFile();

int totalBooks = 0;

int main() {
    loadBooksFromFile(); // Load existing book data

    int entry;
    while(true) {
        cout << "Choice 1: Add books" << endl;
        cout << "Choice 2: Search for books" << endl;
        cout << "Choice 3: Issue books to library members" << endl;
        cout << "Choice 4: Handle return of books" << endl;
        cout << "Enter any choice from the above (or any other number to exit): ";
        cin >> entry;
        cin.ignore(); // Ignore the newline character left in the buffer

        switch (entry) {
            case 1:
                AddNewBooks();
                break;
            case 2:
                searchbook();
                break;
            case 3:
                issuebooks();
                break;
            case 4:
                returnbooks();
                break;
            default:
                cout << "Exiting the program." << endl;
                saveBooksToFile();
                return 0;
        }
    }
}

void loadBooksFromFile() {
    ifstream fin("books.txt");
    if (fin.fail()) {
        cout << "Error opening file" << endl;
        return;
    }

    while (fin >> bookdata[totalBooks].ID) {
        fin.ignore(); // Ignore newline
        fin.getline(bookdata[totalBooks].Title, 30);
        fin.getline(bookdata[totalBooks].Author, 30);
        fin.getline(bookdata[totalBooks].Availability, 10);
        totalBooks++;
    }

    fin.close();
}

void saveBooksToFile() {
    ofstream fout("books.txt");
    if (fout.fail()) {
        cout << "Error opening file" << endl;
        return;
    }

    for (int i = 0; i < totalBooks; i++) {
        fout << bookdata[i].ID << endl;
        fout << bookdata[i].Title << endl;
        fout << bookdata[i].Author << endl;
        fout << bookdata[i].Availability << endl;
    }

    fout.close();
}

void searchbook() {
    int searchID;
    cout << "Enter book ID to search: ";
    cin >> searchID;

    for (int i = 0; i < totalBooks; i++) {
        if (bookdata[i].ID == searchID) {
            cout << "Book ID: " << bookdata[i].ID << endl;
            cout << "Title: " << bookdata[i].Title << endl;
            cout << "Author: " << bookdata[i].Author << endl;
            cout << "Availability: " << bookdata[i].Availability << endl;
            return;  // Exit the function after finding the book
        }
    }
    cout << "Book with ID " << searchID << " not found." << endl;
}

void AddNewBooks() {
    char answer = 'Y';  // Initialize answer

    while(answer == 'Y' && totalBooks < 100) {  // Ensure we don't exceed the array limit
        cout << "Enter book ID: ";
        cin >> bookdata[totalBooks].ID;
        cin.ignore();

        cout << "Enter book title: ";
        cin.getline(bookdata[totalBooks].Title, 30);

        cout << "Enter book author: ";
        cin.getline(bookdata[totalBooks].Author, 30);

        cout << "Enter book availability (Y/N): ";
        cin.getline(bookdata[totalBooks].Availability, 10);

        cout << "Do you want to add another book (Y/N): ";
        cin >> answer;
        cin.ignore();

        totalBooks++;  // Increment the index
    }
}

void issuebooks() {
    int searchID;
    cout << "Enter book ID to issue: ";
    cin >> searchID;

    for (int i = 0; i < totalBooks; i++) {
        if (bookdata[i].ID == searchID) {
            if (strcmp(bookdata[i].Availability, "Y") == 0) {
                cout << "\nBook issued successfully." << endl;
                strcpy(bookdata[i].Availability, "N");
                saveBooksToFile();
                return;
            } else {
                cout << "\nBook is currently unavailable." << endl;
                return;
            }
        }
    }
    cout << "Book with ID " << searchID << " not found." << endl;
}

void returnbooks() {
    int searchID;
    cout << "\nEnter book ID to return: ";
    cin >> searchID;

    for (int i = 0; i < totalBooks; i++) {
        if (bookdata[i].ID == searchID) {
            if (strcmp(bookdata[i].Availability, "N") == 0) {
                cout << "\nBook returned successfully." << endl;
                strcpy(bookdata[i].Availability, "Y");
                saveBooksToFile();
                return;
            } else {
                cout << "\nBook was not issued." << endl;
                return;
            }
        }
    }
    cout << "Book with ID " << searchID << " not found." << endl;
}

