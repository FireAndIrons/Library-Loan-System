/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Book function definitions

#include <iostream>
#include <fstream>
#include <string>
#include "libraryitem.h"
#include "book.h"

using namespace std;

//Initialized constructor
book::book(int id, int loanperiod, double cost, string title, string genre, char status,
           int isbn, string author):libitem(id, loanperiod, cost, title, genre, status) {
    ISBN = isbn;
    bookAuthor = author;
}

//****Mutators for book****
void book::SetISBN(int isbn) {ISBN = isbn;}
void book::SetAuthor(string author) {bookAuthor = author;}

//****Accessors for book****
int book::GetISBN() {return ISBN;}
string book::GetAuthor() {return bookAuthor;}

//Overridden print function
void book::Print(ostream& out) {
    libitem::Print(out);
    out << "Author: " << GetAuthor() << endl
        << "ISBN: " << GetISBN() << endl;
}

//Print function to write formatted data to file
void book::printToFile(ofstream& fout) {

    fout << "1 " << GetLibID() << " " <<  GetItemLoanPeriod() << " " << GetItemCost()
         << " " << GetItemTitle() << "," << GetItemGenre() << "," << GetItemStatus()
         << " " << GetISBN() << " " << GetAuthor() << endl;
}
