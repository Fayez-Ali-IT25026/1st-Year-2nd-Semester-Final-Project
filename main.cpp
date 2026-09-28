#include <iostream>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    double price;
    bool available;
};

int main() {

    int choice;

    Book books[100];
    int bookCount = 0;

    

    while (true) {

        cout << "\n====================================\n";
        cout << "     SMART LIBRARY MANAGEMENT\n";
        cout << "====================================\n";

        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Register Student\n";
        cout << "6. Issue Book\n";
        cout << "7. Return Book\n";
        cout << "8. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:

    if (bookCount < 100) {

        cout << "\nEnter Book ID: ";
        cin >> books[bookCount].id;

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, books[bookCount].title);

        cout << "Enter Author: ";
        getline(cin, books[bookCount].author);

        cout << "Enter Price: ";
        cin >> books[bookCount].price;

        books[bookCount].available = true;

        bookCount++;

        cout << "\nBook added successfully!\n";
    }
    else {
        cout << "\nLibrary is full!\n";
    }

    break;

            case 2:

    if (bookCount == 0) {
        cout << "\nNo books available.\n";
    }
    else {

        cout << "\n=============================================================\n";
        cout << "                    ALL BOOKS\n";
        cout << "=============================================================\n";

        cout << "ID\tTITLE\t\t\tAUTHOR\t\t\tPRICE\n";
        cout << "-------------------------------------------------------------\n";

        for (int i = 0; i < bookCount; i++) {

            cout << books[i].id << "\t";
            cout << books[i].title << "\t\t";
            cout << books[i].author << "\t\t";
            cout << books[i].price << "\n";
        }

        cout << "=============================================================\n";
    }

    break;

            case 3: {

    int searchId;
    bool found = false;

    cout << "\nEnter Book ID to search: ";
    cin >> searchId;

    for (int i = 0; i < bookCount; i++) {

        if (books[i].id == searchId) {

            cout << "\nBook Found!\n";
            cout << "-----------------------------\n";
            cout << "Book ID: " << books[i].id << "\n";
            cout << "Title: " << books[i].title << "\n";
            cout << "Author: " << books[i].author << "\n";
            cout << "Price: " << books[i].price << "\n";

            if (books[i].available) {
                cout << "Status: Available\n";
            }
            else {
                cout << "Status: Issued\n";
            }

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nBook not found.\n";
    }

    break;
}

            case 4: {

    int deleteId;
    bool found = false;

    cout << "\nEnter Book ID to delete: ";
    cin >> deleteId;

    for (int i = 0; i < bookCount; i++) {

        if (books[i].id == deleteId) {

            
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }

            bookCount--;
            found = true;

            cout << "\nBook deleted successfully!\n";
            break;
        }
    }

    if (!found) {
        cout << "\nBook not found.\n";
    }

    break;
}

            case 5:
                cout << "Register Student selected.\n";
                break;

            case 6:
                cout << "Issue Book selected.\n";
                break;

            case 7:
                cout << "Return Book selected.\n";
                break;

            case 8:
                cout << "Thank you for using Smart Library!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}