#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// ====================================
// Book Class
// ====================================

class Book
{
private:
    int bookID;
    string title;
    string author;
    string publisher;
    bool isIssued;

public:

    Book()
    {
        bookID = 0;
        title = "";
        author = "";
        publisher = "";
        isIssued = false;
    }

};

// ====================================
// Member Class
// ====================================

class Member
{
private:
    int memberID;
    string memberName;
    string phone;

public:

    Member()
    {
        memberID = 0;
        memberName = "";
        phone = "";
    }

};

// ====================================
// Book Functions
// ====================================



// ====================================
// Member Functions
// ====================================



// ====================================
// Issue / Return Functions
// ====================================



// ====================================
// Main
// ====================================

int main()
{
    cout << "Library Management System\n";

    return 0;
}