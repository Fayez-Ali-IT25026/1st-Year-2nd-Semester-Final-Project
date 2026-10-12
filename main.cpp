#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cctype>
using namespace std;
 
// ==================== SETTINGS ====================
 
const int    MAX_BOOKS_PER_STUDENT = 3;
const int    LOAN_DAYS             = 14;
const double FINE_PER_DAY          = 5.0;
 
// ==================== DATA CLASSES ====================
 
class Book {
public:
    int id;
    string title;
    string author;
    double price;
    bool available;
    int timesIssued;
};
 
class Student {
public:
    int id;
    string name;
    string department;
    string phone;
};
 
class IssueRecord {
public:
    int studentId;
    int bookId;
    time_t issueDate;
};
 
// ==================== HELPERS ====================
 
string toLower(string s) {
    for (char &c : s) c = tolower((unsigned char)c);
    return s;
}
 
// '|' is our file separator, so remove it from user text
string clean(string s) {
    replace(s.begin(), s.end(), '|', '/');
    return s;
}
 
vector<string> split(const string &line, char sep) {
    vector<string> parts;
    string item;
    stringstream ss(line);
    while (getline(ss, item, sep)) parts.push_back(item);
    return parts;
}
 
string readLine(const string &prompt) {
    string s;
    cout << prompt;
    getline(cin, s);
    return s;
}
 
string readNonEmpty(const string &prompt) {
    string s;
    do {
        s = clean(readLine(prompt));
        if (s.empty()) cout << "Cannot be empty.\n";
    } while (s.empty());
    return s;
}
 
int readInt(const string &prompt) {
    while (true) {
        string s = readLine(prompt);
        try {
            size_t pos;
            int v = stoi(s, &pos);
            if (pos == s.size()) return v;
        } catch (...) {}
        cout << "Please enter a valid number.\n";
    }
}
 
double readDouble(const string &prompt) {
    while (true) {
        string s = readLine(prompt);
        try {
            size_t pos;
            double v = stod(s, &pos);
            if (pos == s.size() && v >= 0) return v;
        } catch (...) {}
        cout << "Please enter a valid price.\n";
    }
}
 
string dateStr(time_t t) {
    char buf[20];
    strftime(buf, sizeof(buf), "%d-%m-%Y", localtime(&t));
    return string(buf);
}
 
int daysSince(time_t t) {
    return (int)(difftime(time(nullptr), t) / 86400);
}
 
// ==================== LIBRARY CLASS ====================
 
class Library {
    vector<Book> books;
    vector<Student> students;
    vector<IssueRecord> issues;
 
public:
    // ---------- File handling ----------
 
    void saveBooks() {
        ofstream f("books.txt");
        for (auto &b : books)
            f << b.id << "|" << b.title << "|" << b.author << "|"
              << b.price << "|" << b.available << "|" << b.timesIssued << "\n";
    }
 
    void saveStudents() {
        ofstream f("students.txt");
        for (auto &s : students)
            f << s.id << "|" << s.name << "|" << s.department << "|" << s.phone << "\n";
    }
 
    void saveIssues() {
        ofstream f("issues.txt");
        for (auto &r : issues)
            f << r.studentId << "|" << r.bookId << "|" << (long long)r.issueDate << "\n";
    }
 
    void loadAll() {
        string line;
 
        ifstream fb("books.txt");
        while (getline(fb, line)) {
            auto p = split(line, '|');
            if (p.size() < 5) continue;
            try {
                Book b;
                b.id = stoi(p[0]);
                b.title = p[1];
                b.author = p[2];
                b.price = stod(p[3]);
                b.available = (p[4] == "1");
                b.timesIssued = (p.size() >= 6) ? stoi(p[5]) : 0;
                books.push_back(b);
            } catch (...) {}
        }
 
        ifstream fs("students.txt");
        while (getline(fs, line)) {
            auto p = split(line, '|');
            if (p.size() < 4) continue;
            try {
                Student s;
                s.id = stoi(p[0]);
                s.name = p[1];
                s.department = p[2];
                s.phone = p[3];
                students.push_back(s);
            } catch (...) {}
        }
        
 
        ifstream fi("issues.txt");
        while (getline(fi, line)) {
            auto p = split(line, '|');
            if (p.size() < 3) continue;
            try {
                IssueRecord r;
                r.studentId = stoi(p[0]);
                r.bookId = stoi(p[1]);
                r.issueDate = (time_t)stoll(p[2]);
                issues.push_back(r);
            } catch (...) {}
        }
    }
 
    // ---------- Lookups ----------
 
    int findBook(int id) {
        for (size_t i = 0; i < books.size(); i++)
            if (books[i].id == id) return (int)i;
        return -1;
    }
 
    int findStudent(int id) {
        for (size_t i = 0; i < students.size(); i++)
            if (students[i].id == id) return (int)i;
        return -1;
    }
 
    int findIssue(int bookId) {
        for (size_t i = 0; i < issues.size(); i++)
            if (issues[i].bookId == bookId) return (int)i;
        return -1;
    }
 
    int loansOf(int studentId) {
        int c = 0;
        for (auto &r : issues) if (r.studentId == studentId) c++;
        return c;
    }
 
    // ---------- Printing ----------
 
    void printBookTable(const vector<Book> &list) {
        cout << "\n" << string(78, '=') << "\n";
        cout << left << setw(6) << "ID" << setw(26) << "TITLE" << setw(20) << "AUTHOR"
             << setw(9) << "PRICE" << setw(10) << "STATUS" << "\n";
        cout << string(78, '-') << "\n";
        for (auto &b : list) {
            cout << left << setw(6) << b.id
                 << setw(26) << b.title.substr(0, 24)
                 << setw(20) << b.author.substr(0, 18)
                 << setw(9) << fixed << setprecision(2) << b.price
                 << setw(10) << (b.available ? "Available" : "Issued") << "\n";
        }
        cout << string(78, '=') << "\n";
    }
 
    // ---------- Book features ----------
 
    void addBook() {
        Book b;
        b.id = readInt("\nEnter Book ID: ");
        if (findBook(b.id) != -1) {
            cout << "A book with this ID already exists!\n";
            return;
        }
        b.title = readNonEmpty("Enter Book Title: ");
        b.author = readNonEmpty("Enter Author: ");
        b.price = readDouble("Enter Price: ");
        b.available = true;
        b.timesIssued = 0;
        books.push_back(b);
        saveBooks();
        cout << "\nBook added successfully!\n";
    }
 
    void displayBooks() {
        if (books.empty()) { cout << "\nNo books available.\n"; return; }
 
        cout << "\nSort by: 1) ID  2) Title  3) Price (low to high)\n";
        int s = readInt("Choice: ");
 
        vector<Book> list = books;
        if (s == 2)
            sort(list.begin(), list.end(), [](const Book &a, const Book &b) {
                return toLower(a.title) < toLower(b.title); });
        else if (s == 3)
            sort(list.begin(), list.end(), [](const Book &a, const Book &b) {
                return a.price < b.price; });
        else
            sort(list.begin(), list.end(), [](const Book &a, const Book &b) {
                return a.id < b.id; });
 
        printBookTable(list);
    }
 
    void searchBook() {
        cout << "\nSearch by: 1) ID  2) Keyword (title or author)\n";
        int mode = readInt("Choice: ");
 
        if (mode == 1) {
            int id = readInt("Enter Book ID: ");
            int i = findBook(id);
            if (i == -1) { cout << "\nBook not found.\n"; return; }
            printBookTable({books[i]});
            int r = findIssue(id);
            if (r != -1) {
                int sIdx = findStudent(issues[r].studentId);
                cout << "Issued to: " << (sIdx != -1 ? students[sIdx].name : "Unknown")
                     << " | Due: " << dateStr(issues[r].issueDate + (time_t)LOAN_DAYS * 86400) << "\n";
            }
        } else {
            string key = toLower(readLine("Enter keyword: "));
            vector<Book> found;
            for (auto &b : books)
                if (toLower(b.title).find(key) != string::npos ||
                    toLower(b.author).find(key) != string::npos)
                    found.push_back(b);
            if (found.empty()) cout << "\nNo matching books.\n";
            else printBookTable(found);
        }
    }
 
    void deleteBook() {
        int id = readInt("\nEnter Book ID to delete: ");
        int i = findBook(id);
        if (i == -1) { cout << "\nBook not found.\n"; return; }
        if (!books[i].available) {
            cout << "\nCannot delete: this book is currently issued!\n";
            return;
        }
        books.erase(books.begin() + i);
        saveBooks();
        cout << "\nBook deleted successfully!\n";
    }
 
    // ---------- Student features ----------
 
    void registerStudent() {
        Student s;
        s.id = readInt("\nEnter Student ID: ");
        if (findStudent(s.id) != -1) {
            cout << "A student with this ID already exists!\n";
            return;
        }
        s.name = readNonEmpty("Enter Student Name: ");
        s.department = readNonEmpty("Enter Department: ");
        s.phone = readNonEmpty("Enter Phone: ");
        students.push_back(s);
        saveStudents();
        cout << "\nStudent registered successfully!\n";
    }
 
    void displayStudents() {
        if (students.empty()) { cout << "\nNo students registered.\n"; return; }
        cout << "\n" << string(70, '=') << "\n";
        cout << left << setw(8) << "ID" << setw(22) << "NAME" << setw(16) << "DEPARTMENT"
             << setw(14) << "PHONE" << "BOOKS\n";
        cout << string(70, '-') << "\n";
        for (auto &s : students)
            cout << left << setw(8) << s.id << setw(22) << s.name.substr(0, 20)
                 << setw(16) << s.department.substr(0, 14) << setw(14) << s.phone
                 << loansOf(s.id) << "/" << MAX_BOOKS_PER_STUDENT << "\n";
        cout << string(70, '=') << "\n";
    }
 
    void studentBooks() {
        int sid = readInt("\nEnter Student ID: ");
        int si = findStudent(sid);
        if (si == -1) { cout << "\nStudent not found!\n"; return; }
 
        cout << "\nBooks borrowed by " << students[si].name << ":\n";
        bool any = false;
        for (auto &r : issues) {
            if (r.studentId != sid) continue;
            any = true;
            int bi = findBook(r.bookId);
            time_t due = r.issueDate + (time_t)LOAN_DAYS * 86400;
            int late = daysSince(r.issueDate) - LOAN_DAYS;
            cout << "  [" << r.bookId << "] " << (bi != -1 ? books[bi].title : "Unknown")
                 << " | Issued: " << dateStr(r.issueDate)
                 << " | Due: " << dateStr(due);
            if (late > 0) cout << " | OVERDUE by " << late << " day(s)";
            cout << "\n";
        }
        if (!any) cout << "  None.\n";
    }
 
    // ---------- Issue / Return ----------
 
    void issueBook() {
        int sid = readInt("\nEnter Student ID: ");
        int si = findStudent(sid);
        if (si == -1) { cout << "\nStudent not found!\n"; return; }
 
        if (loansOf(sid) >= MAX_BOOKS_PER_STUDENT) {
            cout << "\n" << students[si].name << " already has "
                 << MAX_BOOKS_PER_STUDENT << " books. Return one first.\n";
            return;
        }
 
        // Block students who hold an overdue book
        for (auto &r : issues)
            if (r.studentId == sid && daysSince(r.issueDate) > LOAN_DAYS) {
                cout << "\nThis student has an overdue book. Return it first!\n";
                return;
            }
 
        int bid = readInt("Enter Book ID: ");
        int bi = findBook(bid);
        if (bi == -1) { cout << "\nBook not found!\n"; return; }
        if (!books[bi].available) { cout << "\nBook is already issued!\n"; return; }
 
        IssueRecord r;
        r.studentId = sid;
        r.bookId = bid;
        r.issueDate = time(nullptr);
        issues.push_back(r);
 
        books[bi].available = false;
        books[bi].timesIssued++;
 
        saveBooks();
        saveIssues();
 
        cout << "\nBook issued successfully!\n";
        cout << "Student : " << students[si].name << "\n";
        cout << "Book    : " << books[bi].title << "\n";
        cout << "Due date: " << dateStr(r.issueDate + (time_t)LOAN_DAYS * 86400) << "\n";
    }
 
    void returnBook() {
        int bid = readInt("\nEnter Book ID to return: ");
        int bi = findBook(bid);
        if (bi == -1) { cout << "\nBook not found!\n"; return; }
        if (books[bi].available) { cout << "\nThis book is already available!\n"; return; }
 
        int ri = findIssue(bid);
        double fine = 0;
        if (ri != -1) {
            int late = daysSince(issues[ri].issueDate) - LOAN_DAYS;
            if (late > 0) fine = late * FINE_PER_DAY;
            issues.erase(issues.begin() + ri);
        }
 
        books[bi].available = true;
        saveBooks();
        saveIssues();
 
        cout << "\nBook returned successfully!\n";
        if (fine > 0)
            cout << "Late fine to pay: " << fixed << setprecision(2) << fine << " BDT\n";
        else
            cout << "Returned on time. No fine.\n";
    }
 
    // ---------- Reports ----------
 
    void overdueReport() {
        cout << "\n=========== OVERDUE REPORT ===========\n";
        bool any = false;
        for (auto &r : issues) {
            int late = daysSince(r.issueDate) - LOAN_DAYS;
            if (late <= 0) continue;
            any = true;
            int si = findStudent(r.studentId);
            int bi = findBook(r.bookId);
            cout << (bi != -1 ? books[bi].title : "Unknown") << " | "
                 << (si != -1 ? students[si].name : "Unknown")
                 << " (" << (si != -1 ? students[si].phone : "-") << ")"
                 << " | " << late << " days late | Fine: "
                 << fixed << setprecision(2) << late * FINE_PER_DAY << " BDT\n";
        }
        if (!any) cout << "No overdue books. Great!\n";
    }
 
    void popularBooks() {
        if (books.empty()) { cout << "\nNo books available.\n"; return; }
        vector<Book> list = books;
        sort(list.begin(), list.end(), [](const Book &a, const Book &b) {
            return a.timesIssued > b.timesIssued; });
 
        cout << "\n=========== TOP 5 POPULAR BOOKS ===========\n";
        for (size_t i = 0; i < list.size() && i < 5; i++)
            cout << i + 1 << ". " << list[i].title << " by " << list[i].author
                 << " - issued " << list[i].timesIssued << " time(s)\n";
    }
 
    void statistics() {
        int issued = 0, overdue = 0, totalIssues = 0;
        double value = 0;
        for (auto &b : books) {
            if (!b.available) issued++;
            value += b.price;
            totalIssues += b.timesIssued;
        }
        for (auto &r : issues)
            if (daysSince(r.issueDate) > LOAN_DAYS) overdue++;
 
        cout << "\n=========== LIBRARY STATISTICS ===========\n";
        cout << "Total books       : " << books.size() << "\n";
        cout << "Available         : " << books.size() - issued << "\n";
        cout << "Currently issued  : " << issued << "\n";
        cout << "Overdue           : " << overdue << "\n";
        cout << "Registered members: " << students.size() << "\n";
        cout << "Total issues ever : " << totalIssues << "\n";
        cout << "Collection value  : " << fixed << setprecision(2) << value << " BDT\n";
    }
};
 
// ==================== MAIN ====================
 
int main() {
    Library lib;
    lib.loadAll();
 
    while (true) {
        cout << "\n====================================\n";
        cout << "     SMART LIBRARY MANAGEMENT\n";
        cout << "====================================\n";
        cout << " 1. Add Book\n";
        cout << " 2. Display Books (sortable)\n";
        cout << " 3. Search Book\n";
        cout << " 4. Delete Book\n";
        cout << " 5. Register Student\n";
        cout << " 6. Display Students\n";
        cout << " 7. Issue Book\n";
        cout << " 8. Return Book\n";
        cout << " 9. Student's Borrowed Books\n";
        cout << "10. Overdue Report\n";
        cout << "11. Popular Books\n";
        cout << "12. Library Statistics\n";
        cout << " 0. Exit\n";
 
        int choice = readInt("\nEnter your choice: ");
 
        switch (choice) {
            case 1:  lib.addBook();        break;
            case 2:  lib.displayBooks();   break;
            case 3:  lib.searchBook();     break;
            case 4:  lib.deleteBook();     break;
            case 5:  lib.registerStudent();break;
            case 6:  lib.displayStudents();break;
            case 7:  lib.issueBook();      break;
            case 8:  lib.returnBook();     break;
            case 9:  lib.studentBooks();   break;
            case 10: lib.overdueReport();  break;
            case 11: lib.popularBooks();   break;
            case 12: lib.statistics();     break;
            case 0:
                cout << "\nThank you for using Smart Library!\n";
                return 0;
            default:
                cout << "\nInvalid choice! Please try again.\n";
        }
    }
}
 