#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// ===============================
// Book Class
// ===============================

class Book
{
private:
    int bookID;
    string title;
    string author;
    string category;
    bool issued;

public:

    Book()
    {
        bookID = 0;
        title = "";
        author = "";
        category = "";
        issued = false;
    }

    // Function to input book details
    void inputBook()
    {
        cout << "\n========== ADD NEW BOOK ==========\n";

        cout << "Enter Book ID : ";
        cin >> bookID;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Book Title : ";
        getline(cin, title);

        cout << "Enter Author Name : ";
        getline(cin, author);

        cout << "Enter Category : ";
        getline(cin, category);

        issued = false;
    }

    // Function to display book details
    void displayBook() const
    {
        cout << "\n----------------------------------------\n";
        cout << "Book ID      : " << bookID << endl;
        cout << "Title        : " << title << endl;
        cout << "Author       : " << author << endl;
        cout << "Category     : " << category << endl;
        cout << "Status       : " << (issued ? "Issued" : "Available") << endl;
        cout << "----------------------------------------\n";
    }

    // Save book to file
void writeToFile(ofstream &file)
{
    file << bookID << "|"
         << title << "|"
         << author << "|"
         << category << "|"
         << issued << endl;
}

// Load book from file
void loadFromString(const string &line)
{
    if (line.empty())
        return;

    stringstream ss(line);
    string temp;

    getline(ss, temp, '|');
    bookID = stoi(temp);

    getline(ss, title, '|');

    getline(ss, author, '|');

    getline(ss, category, '|');

    getline(ss, temp);
    issued = stoi(temp);
}

// Getter
int getBookID() const
{
    return bookID;
}

string getTitle() const
{
    return title;
}

string getAuthor() const
{
    return author;
}

bool isIssued() const
{
    return issued;
}

void setIssued(bool status)
{
    issued = status;
}


};

class Member
{
private:
    int memberID;
    string name;
    string phone;

public:

    Member()
    {
        memberID = 0;
        name = "";
        phone = "";
    }

    void inputMember()
    {
        cout << "\n========== ADD MEMBER ==========\n";

        cout << "Enter Member ID : ";
        cin >> memberID;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Member Name : ";
        getline(cin, name);

        cout << "Enter Phone Number : ";
        getline(cin, phone);
    }

    void displayMember() const
    {
        cout << "\n----------------------------------------\n";
        cout << "Member ID    : " << memberID << endl;
        cout << "Name         : " << name << endl;
        cout << "Phone Number : " << phone << endl;
        cout << "----------------------------------------\n";
    }

    void writeToFile(ofstream &file)
    {
        file << memberID << "|"
             << name << "|"
             << phone << endl;
    }

    void loadFromString(const string &line)
    {
        if (line.empty())
    return;
        stringstream ss(line);
        string temp;

        getline(ss, temp, '|');
        memberID = stoi(temp);

        getline(ss, name, '|');

        getline(ss, phone);
    }

    int getMemberID() const
    {
        return memberID;
    }
};

vector<Book> loadBooks()
{
    vector<Book> books;

    ifstream file("books.txt");

    string line;

   while (getline(file, line))
{
    if (line.empty())
        continue;

    Book book;
    book.loadFromString(line);
    books.push_back(book);
}

    file.close();

    return books;
}

vector<Member> loadMembers()
{
    vector<Member> members;

    ifstream file("members.txt");

    string line;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Member member;

        member.loadFromString(line);

        members.push_back(member);
    }

    file.close();

    return members;
}

bool memberExists(int memberID)
{
    vector<Member> members = loadMembers();

    for (auto &member : members)
    {
        if (member.getMemberID() == memberID)
            return true;
    }

    return false;
}

void addBook()
{
    vector<Book> books = loadBooks();

    Book newBook;

    newBook.inputBook();

    // Check for duplicate Book ID
    for (const auto &book : books)
    {
        if (book.getBookID() == newBook.getBookID())
        {
            cout << "\nBook ID already exists!\n";
            return;
        }
    }

    ofstream file("books.txt", ios::app);

    if (!file)
    {
        cout << "\nError opening books file!\n";
        return;
    }

    newBook.writeToFile(file);

    file.close();

    cout << "\nBook Added Successfully!\n";
}

void addMember()
{
    vector<Member> members = loadMembers();

    Member newMember;

    newMember.inputMember();

    // Check duplicate Member ID
    for (const auto &member : members)
    {
        if (member.getMemberID() == newMember.getMemberID())
        {
            cout << "\nMember ID already exists!\n";
            return;
        }
    }

    ofstream file("members.txt", ios::app);

    if (!file)
    {
        cout << "\nError opening members file!\n";
        return;
    }

    newMember.writeToFile(file);

    file.close();

    cout << "\nMember Added Successfully!\n";
}

void displayBooks()
{
    ifstream file("books.txt");

    if (!file)
    {
        cout << "\nNo books found.\n";
        return;
    }

    string line;

    cout << "\n========== BOOK LIST ==========\n";

    while (getline(file, line))
{
    if (line.empty())
        continue;

    Book book;

    book.loadFromString(line);

    book.displayBook();
}

    file.close();
}

void saveBooks(vector<Book> &books)
{
    ofstream file("books.txt");

    for (auto &book : books)
    {
        book.writeToFile(file);
    }

    file.close();
}

void displayMembers()
{
    ifstream file("members.txt");

    if (!file)
    {
        cout << "\nNo members found.\n";
        return;
    }

    string line;

    cout << "\n========== MEMBER LIST ==========\n";

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Member member;

        member.loadFromString(line);

        member.displayMember();
    }

    file.close();
}

void searchBookByID()
{
    ifstream file("books.txt");

    if (!file)
    {
        cout << "\nNo books found.\n";
        return;
    }

    int id;

    cout << "\nEnter Book ID : ";
    cin >> id;

    string line;

    bool found = false;

    while (getline(file, line))
{
    if (line.empty())
        continue;

    Book book;

        book.loadFromString(line);

        if (book.getBookID() == id)
        {
            cout << "\nBook Found!\n";

            book.displayBook();

            found = true;

            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nBook not found.\n";
    }
}

void issueBook()
{
    vector<Book> books = loadBooks();

    int bookID, memberID;

    cout << "\nEnter Book ID : ";
    cin >> bookID;

    cout << "Enter Member ID : ";
    cin >> memberID;

    if (!memberExists(memberID))
    {
        cout << "\nMember not found!\n";
        return;
    }

    bool found = false;

    for (auto &book : books)
    {
        if (book.getBookID() == bookID)
        {
            found = true;

            if (book.isIssued())
            {
                cout << "\nBook is already issued!\n";
                return;
            }

            book.setIssued(true);

            saveBooks(books);

            cout << "\nBook Issued Successfully!\n";

            return;
        }
    }

    if (!found)
    {
        cout << "\nBook not found!\n";
    }
}

void returnBook()
{
    vector<Book> books = loadBooks();

    int bookID;

    cout << "\nEnter Book ID : ";
    cin >> bookID;

    bool found = false;

    for (auto &book : books)
    {
        if (book.getBookID() == bookID)
        {
            found = true;

            if (!book.isIssued())
            {
                cout << "\nBook is already available!\n";
                return;
            }

            book.setIssued(false);

            saveBooks(books);

            cout << "\nBook Returned Successfully!\n";

            return;
        }
    }

    if (!found)
    {
        cout << "\nBook not found!\n";
    }
}

void deleteBook()
{
    vector<Book> books = loadBooks();

    int id;

    cout << "\nEnter Book ID to Delete : ";
    cin >> id;

    bool found = false;

    vector<Book> updatedBooks;

    for (const auto &book : books)
    {
        if (book.getBookID() == id)
        {
            found = true;
        }
        else
        {
            updatedBooks.push_back(book);
        }
    }

    if (!found)
    {
        cout << "\nBook not found!\n";
        return;
    }

    saveBooks(updatedBooks);

    cout << "\nBook Deleted Successfully!\n";
}

void searchMember()
{
    ifstream file("members.txt");

    if (!file)
    {
        cout << "\nNo members found.\n";
        return;
    }

    int id;

    cout << "\nEnter Member ID : ";
    cin >> id;

    string line;

    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Member member;

        member.loadFromString(line);

        if (member.getMemberID() == id)
        {
            cout << "\nMember Found!\n";

            member.displayMember();

            found = true;

            break;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nMember not found.\n";
    }
}

void searchBookByTitle()
{
    ifstream file("books.txt");

    if (!file)
    {
        cout << "\nNo books found.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string searchTitle;

    cout << "\nEnter Book Title : ";
    getline(cin, searchTitle);

    string line;

    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Book book;

        book.loadFromString(line);

        if (book.getTitle() == searchTitle)
        {
            cout << "\nBook Found!\n";

            book.displayBook();

            found = true;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nBook not found.\n";
    }
}

void searchBookByAuthor()
{
    ifstream file("books.txt");

    if (!file)
    {
        cout << "\nNo books found.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string searchAuthor;

    cout << "\nEnter Author Name : ";
    getline(cin, searchAuthor);

    string line;

    bool found = false;

    while (getline(file, line))
    {
        if (line.empty())
            continue;

        Book book;

        book.loadFromString(line);

        if (book.getAuthor() == searchAuthor)
        {
            book.displayBook();

            found = true;
        }
    }

    file.close();

    if (!found)
    {
        cout << "\nNo books found by that author.\n";
    }
}



int main()
{
    int choice;

    do
    {
        cout << "\n=====================================\n";
        cout << "     LIBRARY MANAGEMENT SYSTEM\n";
        cout << "=====================================\n";

        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book by ID\n";
        cout << "4. Search Book by Title\n";
        cout << "5. Search Book by Author\n";
        cout << "6. Add Member\n";
        cout << "7. Display Members\n";
        cout << "8. Search Member\n";
        cout << "9. issue book\n";
        cout << "10. Return Book\n";
        cout << "11. Delete Book\n";
        cout << "12. Exit\n";
        cout << "\nEnter your choice : ";
        cin >> choice;
        if (cin.fail())
{
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nInvalid input!\n";
    continue;
}

switch(choice)
{
        case 1:
        addBook();
    break;
    
        case 2:
        displayBooks();
    break;
    
        case 3:
        searchBookByID();
    break;
            
        case 4:
        searchBookByTitle();
    break;
    
        case 5:
        searchBookByAuthor();
    break;
    
        case 6:
        addMember();
    break;
    
        case 7:
        displayMembers();
    break;
    
        case 8:
        searchMember();
    break;
    
        case 9:
        issueBook();
    break;

        case 10:
        returnBook();
    break;

        case 11:
        deleteBook();
    break;
     
        case 12:
        cout << "\nExiting the program. Goodbye!\n";    
    break;   

            
        default:
        cout << "\nInvalid choice! Please try again.\n";
    break;
        }
} while(choice != 12);

    return 0;
}
