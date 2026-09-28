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
                cout << "Add Book selected.\n";
                break;

            case 2:
                cout << "Display Books selected.\n";
                break;

            case 3:
                cout << "Search Book selected.\n";
                break;

            case 4:
                cout << "Delete Book selected.\n";
                break;

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