/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//LibItem (base class) function definitions

#include <iostream>
#include <string>
#include "libraryitem.h"

using namespace std;

/*
 * A note: I decided to put title and genre in the base class because all derived classes
 * have a title and a genre. This only seemed logical when I considered how inheritance
 * works for the derived classes. Please understand that I chose this not to be
 * contrarian towards Dr. Keathly's instructions, but instead to utilize the power of inheritance.
 */
libitem::libitem(int id, int loanperiod, double cost, string title, string genre, char status) {
    libItemID = id;
    libItemLoanPeriod = loanperiod;
    libItemCost = cost;
    libItemTitle = title;
    libItemStatus = status;
    libItemGenre = genre;

}

//****Mutators for Lib Item****
void libitem::SetLibID(int id) {libItemID = id;}
void libitem::SetItemCost(double cost) {libItemCost = cost;}
void libitem::SetItemStatus(char status) {libItemStatus = status;}
void libitem::SetItemLoanPeriod(int period) {libItemLoanPeriod = period;}
void libitem::SetItemTitle(string title) {libItemTitle = title;}
void libitem::SetItemGenre(string genre) {libItemGenre = genre;}

//****Accessors for Lib Item****
int libitem::GetLibID() {return libItemID;}
double libitem::GetItemCost() {return libItemCost;}
char libitem::GetItemStatus() {return libItemStatus;}
int libitem::GetItemLoanPeriod() {return libItemLoanPeriod;}
string libitem::GetItemTitle() {return libItemTitle;}
string libitem::GetItemGenre() {return libItemGenre;}

//Virtual print function to be overridden by children classes
void libitem::Print(ostream& out) {
    out << *this;
}

//Overloaded operator function to utilize polymorphism
ostream& operator<<(ostream& out, libitem& libit) {
    out << "Lib ID: " << libit.libItemID << endl
        << "Loan Period: " << libit.libItemLoanPeriod << " days" << endl
        << "Status: " << libit.libItemStatus << endl
        << "Cost: " << libit.libItemCost << endl
        << "Genre: " << libit.libItemGenre << endl
        << "Title: " << libit.libItemTitle << endl;

    return out;
}
