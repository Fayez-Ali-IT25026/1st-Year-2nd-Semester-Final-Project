#include <iostream>
#include <fstream>
using namespace std;


// ==================== BOOK CLASS ====================

class Book {
public:
    int id;
    string title;
    string author;
    double price;
    bool available;
};


// ==================== SAVE BOOKS ====================

void saveBooks(Book books[], int bookCount) {

    ofstream file("books.txt");

    for (int i = 0; i < bookCount; i++) {

        file << books[i].id << "|"
             << books[i].title << "|"
             << books[i].author << "|"
             << books[i].price << "|"
             << books[i].available << "\n";
    }

    file.close();
}


// ==================== LOAD BOOKS ====================

void loadBooks(Book books[], int &bookCount) {

    ifstream file("books.txt");

    if (!file) {
        return;
    }

    bookCount = 0;

    while (file >> books[bookCount].id) {

        file.ignore();

        getline(file, books[bookCount].title, '|');

        getline(file, books[bookCount].author, '|');

        file >> books[bookCount].price;

        file.ignore();

        file >> books[bookCount].available;

        bookCount++;

        if (bookCount >= 100) {
            break;
        }
    }

    file.close();
}


// ==================== STUDENT CLASS ====================

class Student {
public:
    int id;
    string name;
    string department;
    string phone;
};

// ==================== SAVE STUDENTS ====================

void saveStudents(Student students[], int studentCount) {

    ofstream file("students.txt");

    for (int i = 0; i < studentCount; i++) {

        file << students[i].id << "|"
             << students[i].name << "|"
             << students[i].department << "|"
             << students[i].phone << "\n";
    }

    file.close();
}

// ==================== LOAD STUDENTS ====================

void loadStudents(Student students[], int &studentCount) {

    ifstream file("students.txt");

    if (!file) {
        return;
    }

    studentCount = 0;

    while (file >> students[studentCount].id) {

        file.ignore();

        getline(file, students[studentCount].name, '|');

        getline(file, students[studentCount].department, '|');

        getline(file, students[studentCount].phone);

        studentCount++;

        if (studentCount >= 100) {
            break;
        }
    }

    file.close();
}

// ==================== MAIN FUNCTION ====================

int main() {

    int choice;

    // Book array
    Book books[100];
    int bookCount = 0;

    // Load previously saved books
    loadBooks(books, bookCount);


    // Student array
    Student students[100];
    int studentCount = 0;

    // Load previously saved students
    loadStudents(students, studentCount);


    // ==================== MAIN MENU ====================

    while (true) {

        cout << "\n====================================\n";
        cout << "     SMART LIBRARY MANAGEMENT\n";
        cout << "====================================\n";

        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. Register Student\n";
        cout << "6. Display Students\n";
        cout << "7. Issue Book\n";
        cout << "8. Return Book\n";
        cout << "9. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;


        // ==================== SWITCH ====================

        switch (choice) {


            // ==================== ADD BOOK ====================

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

                    // Save books to file
                    saveBooks(books, bookCount);

                    cout << "\nBook added successfully!\n";
                }
                else {

                    cout << "\nLibrary is full!\n";
                }

                break;


            // ==================== DISPLAY BOOKS ====================

            case 2:

                if (bookCount == 0) {

                    cout << "\nNo books available.\n";
                }
                else {

                    cout << "\n=============================================================\n";
                    cout << "                    ALL BOOKS\n";
                    cout << "=============================================================\n";

                    cout << "ID\tTITLE\t\t\tAUTHOR\t\t\tPRICE\tSTATUS\n";

                    cout << "-------------------------------------------------------------\n";

                    for (int i = 0; i < bookCount; i++) {

                        cout << books[i].id << "\t";
                        cout << books[i].title << "\t\t";
                        cout << books[i].author << "\t\t";
                        cout << books[i].price << "\t";

                        if (books[i].available) {
                            cout << "Available";
                        }
                        else {
                            cout << "Issued";
                        }

                        cout << "\n";
                    }

                    cout << "=============================================================\n";
                }

                break;


            // ==================== SEARCH BOOK ====================

            case 3: {

                int searchId;
                bool found = false;

                cout << "\nEnter Book ID to search: ";
                cin >> searchId;

                for (int i = 0; i < bookCount; i++) {

                    if (books[i].id == searchId) {

                        cout << "\nBook Found!\n";
                        cout << "-----------------------------\n";

                        cout << "Book ID: "
                             << books[i].id << "\n";

                        cout << "Title: "
                             << books[i].title << "\n";

                        cout << "Author: "
                             << books[i].author << "\n";

                        cout << "Price: "
                             << books[i].price << "\n";

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


            // ==================== DELETE BOOK ====================

            case 4: {

                int deleteId;
                bool found = false;

                cout << "\nEnter Book ID to delete: ";
                cin >> deleteId;

                for (int i = 0; i < bookCount; i++) {

                    if (books[i].id == deleteId) {

                        // Shift books to the left
                        for (int j = i; j < bookCount - 1; j++) {

                            books[j] = books[j + 1];
                        }

                        bookCount--;

                        // Update file
                        saveBooks(books, bookCount);

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


            // ==================== REGISTER STUDENT ====================

            case 5:

                if (studentCount < 100) {

                    cout << "\nEnter Student ID: ";
                    cin >> students[studentCount].id;

                    cin.ignore();

                    cout << "Enter Student Name: ";
                    getline(cin, students[studentCount].name);

                    cout << "Enter Department: ";
                    getline(cin, students[studentCount].department);

                    cout << "Enter Phone: ";
                    getline(cin, students[studentCount].phone);

                    studentCount++;

                    // Save students to file
                    saveStudents(students, studentCount);

                    cout << "\nStudent registered successfully!\n";
                }
                else {

                    cout << "\nStudent limit reached!\n";
                }

                break;


            // ==================== DISPLAY STUDENTS ====================

            case 6:

                if (studentCount == 0) {

                    cout << "\nNo students registered.\n";
                }
                else {

                    cout << "\n============================================\n";
                    cout << "           REGISTERED STUDENTS\n";
                    cout << "============================================\n";

                    for (int i = 0; i < studentCount; i++) {

                        cout << "\nStudent " << i + 1 << "\n";

                        cout << "Student ID: "
                             << students[i].id << "\n";

                        cout << "Name: "
                             << students[i].name << "\n";

                        cout << "Department: "
                             << students[i].department << "\n";

                        cout << "Phone: "
                             << students[i].phone << "\n";

                        cout << "--------------------------------------------\n";
                    }
                }

                break;


            // ==================== ISSUE BOOK ====================

            case 7: {

                int studentId;
                int bookId;

                bool studentFound = false;
                bool bookFound = false;


                cout << "\nEnter Student ID: ";
                cin >> studentId;


                // Search student

                for (int i = 0; i < studentCount; i++) {

                    if (students[i].id == studentId) {

                        studentFound = true;

                        break;
                    }
                }


                if (!studentFound) {

                    cout << "\nStudent not found!\n";

                    break;
                }


                cout << "Enter Book ID: ";
                cin >> bookId;


                // Search book

                for (int i = 0; i < bookCount; i++) {

                    if (books[i].id == bookId) {

                        bookFound = true;


                        if (books[i].available) {

                            books[i].available = false;

                            // Save updated book status
                            saveBooks(books, bookCount);


                            cout << "\nBook issued successfully!\n";

                            cout << "Student ID: "
                                 << studentId << "\n";

                            cout << "Book ID: "
                                 << bookId << "\n";
                        }
                        else {

                            cout << "\nBook is already issued!\n";
                        }

                        break;
                    }
                }


                if (!bookFound) {

                    cout << "\nBook not found!\n";
                }

                break;
            }


            // ==================== RETURN BOOK ====================

            case 8: {

                int bookId;
                bool found = false;


                cout << "\nEnter Book ID to return: ";
                cin >> bookId;


                for (int i = 0; i < bookCount; i++) {

                    if (books[i].id == bookId) {

                        found = true;


                        if (!books[i].available) {

                            books[i].available = true;

                            // Save updated status
                            saveBooks(books, bookCount);


                            cout << "\nBook returned successfully!\n";

                            cout << "Book ID: "
                                 << bookId << "\n";
                        }
                        else {

                            cout << "\nThis book is already available!\n";
                        }

                        break;
                    }
                }


                if (!found) {

                    cout << "\nBook not found!\n";
                }

                break;
            }


            // ==================== EXIT ====================

            case 9:

                cout << "\nThank you for using Smart Library!\n";

                return 0;


            // ==================== INVALID CHOICE ====================

            default:

                cout << "\nInvalid choice! Please try again.\n";
        }
    }


    return 0;
}