/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */

#include <iostream>
#include <iomanip>
#include <ctime>
#include "libraryitem.h"
#include "patron.h"
#include "loan.h"
#include "dvd.h"
#include "audiocd.h"
#include "book.h"
#include "patronManager.h"
#include "loanManager.h"
#include "libraryitemManager.h"

//Main function declarations
void displayGreeting();
void printGenMenu();
void patronMenu();
void itemMenu();
void loanMenu();
void loadDataBases();
void storeDataBases();
void makeOverdueTest();


//Globally declaring databases
patronManager patrons;
libitemManager libItems;
loanManager loans;

int main() {

    loadDataBases();

    //Creates overdue loan at start of program
    //The entry 1234 "Bad Person" can be used to test overdue functionality
    if(patrons.isEmpty() && libItems.isEmpty() && loans.isEmpty()) {
        makeOverdueTest();
    }

    //Updates all loans to overdue depending on time difference at start of program
    loans.itemIsOverdue();

    char userChoice = 'x';

    displayGreeting();

    do {
        printGenMenu();
        enum genMenuItems {PATRON = 'p', ITEM = 'i', LOAN = 'l', QUIT = 'q'};

        cout << endl << "Enter your selection: ";
        cin >> userChoice;
        switch (userChoice) {
            case PATRON:
                patronMenu();
                break;
            case ITEM:
                itemMenu();
                break;
            case LOAN:
                loanMenu();
                break;
            case QUIT:
                cout << "Thank you for visiting the Library!" << endl;
                break;
            default:
                break;
        }
    } while (userChoice != 'q');

    storeDataBases();

    return 0;
}

//Calls store functions
void storeDataBases() {
    patrons.storePatron();
    libItems.storeLibItems();
    loans.storeLoan();
}

//Calls load functions
void loadDataBases() {
    patrons.loadPatron();
    libItems.loadLibItems();
    loans.loadLoan();
}

//Print function displaying greeting
void displayGreeting() {
    cout << setfill('*') << setw(31)
         << " Welcome to the Library! ";
    cout << setfill('*') << setw(6) << "*";
    cout << endl;
    cout << setfill('/') << setw(37) << "/";
    cout << endl;
}

//Print function for general menu
void printGenMenu() {
    cout << endl << "GENERAL MENU" << endl
         << "p - Patron Menu" << endl
         << "i - Library Item Menu" << endl
         << "l - Loan Menu" << endl
         << "q - Quit" << endl;
}

//Patron menu - this function prints and houses the patron functionalities
void patronMenu() {
    int userChoice;
    int userPatID;
    enum menuItems {ADDPATRON = 1, DELETEPATRON = 2, PRINTPATRONS = 3, SINGLEPATRON = 4, QUIT = 5};

    do {
        cout << endl << "PATRON MENU" << endl
             << "1. Add Patron" << endl << "2. Delete Patron" << endl << "3. Print Patron List"<< endl
             << "4. Print Single Patron" << endl << "5. Quit" << endl;

        cout << endl << "Enter your selection: "; cin >> userChoice;
        switch (userChoice) {
            case ADDPATRON:
                patrons.addPatron();
                break;
            case DELETEPATRON:
                cout << "Please enter a patron ID: ";
                cin >> userPatID; cin.ignore();
                patrons.deletePatron(userPatID);
                break;
            case PRINTPATRONS:
                patrons.printPatronList();
                break;
            case SINGLEPATRON:
                cout << "Please enter a patron ID: ";
                cin >> userPatID; cin.ignore();
                patrons.printSinglePatron(userPatID);
                break;
            case QUIT:
                break;
            default:
                cout << "Invalid selection (" << userChoice << "). Enter option 1-5." << endl;
        }
    } while(userChoice < 5 || userChoice > 5);
}

//Item menu - this function prints and houses the item functionalities
void itemMenu() {
    int userChoice;
    int userItemID;

    enum menuItems {ADDITEM = 1, DELETEITEM = 2, PRINTITEMS = 3, SINGLEITEM = 4, QUIT = 5};

    do {
        cout << endl << "ITEM MENU" << endl
             << "1. Add Item" << endl << "2. Delete Item" << endl << "3. Print Item List"<< endl
             << "4. Print Single Item" << endl << "5. Quit" << endl;

        cout << endl << "Enter your selection: "; cin >> userChoice;
        switch (userChoice) {
            case ADDITEM:
                libItems.addLibItemMenu();
                break;
            case DELETEITEM:
                cout << "Please enter an item ID: ";
                cin >> userItemID; cin.ignore();
                libItems.deleteLibItem(userItemID);
                break;
            case PRINTITEMS:
                libItems.printItemList();
                break;
            case SINGLEITEM:
                cout << "Please enter an item ID: ";
                cin >> userItemID; cin.ignore();
                libItems.printSingleItem(userItemID);
                break;
            case QUIT:
                break;
            default:
                cout << "Invalid selection (" << userChoice << "). Enter option 1-5." << endl;
        }
    } while(userChoice < 5 || userChoice > 5);
}

//Loan menu - this function prints and houses the loan functionalities
void loanMenu() {
    int userChoice, userPatID, userItemID, userLoanID,
        foundPatron, foundItem, foundLoan;
    double patBalance = 0;
    char newItemStatus = 'y';
    string fName, lName;

    enum menuItems {CHECKOUT = 1, CHECKIN = 2, RENEW = 3, LOST = 4, PRINTOVERDUE = 5, PRINTPATITEMS = 6, QUIT = 7};

    do {
        cout << endl << "LOAN MENU" << endl
             << "1. Checkout Item" << endl << "2. Checkin Item" << endl << "3. Renew Loan"<< endl
             << "4. Report Lost Item" << endl << "5. Print Overdue Loans" << endl
             << "6. Print a Patron's Loans" << endl << "7. Quit" << endl;

        cout << endl << "Enter your selection: "; cin >> userChoice;
        switch (userChoice) {
            case CHECKOUT:
                //Search patron database
                cout << "Please enter a patron ID: ";
                cin >> userPatID; cin.ignore();

                if(patrons.searchPatron(userPatID) == -1) {break;}
                else{foundPatron = patrons.searchPatron(userPatID);}

                //Search item database
                cout << "Please enter the desired item's ID: ";
                cin >> userItemID; cin.ignore();

                if(libItems.searchLibItem(userItemID) == -1) {break;}
                else {foundItem = libItems.searchLibItem(userItemID);}

                //Checking the item status, if out or lost patron may not checkout item
                if(libItems.GetItemStatus(foundItem) == 'O' || libItems.GetItemStatus(foundItem) == 'L') {
                    cout << "You may not checkout this item at this time." << endl;
                    break;
                }

                //Check patron eligibility and create loan
                if(patrons.checkEligibility(foundPatron)
                  && loans.hasOverdueItems(userPatID)) {loans.checkoutItem(userPatID);}
                else{break;}

                //Otherwise set the item status to checked out
                newItemStatus = 'O';
                libItems.editItemStatus(foundItem, newItemStatus);

                //Increment patron's item count
                patrons.editPatronItemCount(foundPatron, 1);

                break;
            case CHECKIN:
                //Search loan database
                cout << "Please enter a loan ID: ";
                cin >> userLoanID; cin.ignore();

                if(loans.searchLoan(userLoanID) == -1) {break;}
                else{foundLoan = loans.searchLoan(userLoanID);}

                //Search patron database
                cout << "Please enter a patron ID: ";
                cin >> userPatID; cin.ignore();

                if(patrons.searchPatron(userPatID) == -1) {break;}
                else{foundPatron = patrons.searchPatron(userPatID);}

                //Checkin loan
                loans.checkinItem(patBalance, foundLoan);

                //If patron has fines, ask how much they want to pay and update balance
                if(patBalance != 0) {
                    patrons.editPatronBalance(foundPatron, patBalance);
                    double userAmtPay = -1;

                    while(userAmtPay < 0) {
                        cout << "How much would you like to pay?: ";
                        cin >> userAmtPay;
                        userAmtPay *= -1;
                        patrons.editPatronBalance(foundPatron, userAmtPay);
                    }
                }

                //Decrement patron's item count
                patrons.editPatronItemCount(foundPatron, -1);

                //Search item database
                cout << endl << "Please enter the checked in item's ID: ";
                cin >> userItemID; cin.ignore();

                if(libItems.searchLibItem(userItemID) == -1) {break;}
                else {foundItem = libItems.searchLibItem(userItemID);}

                //Update item status to checked in
                newItemStatus = 'I';
                libItems.editItemStatus(foundItem, newItemStatus);

                break;
            case RENEW:
                loans.itemToRenew();
                break;
            case LOST:
                cout << endl << "REPORT LOST" << endl;

                //Search item database
                cout << "Please enter the desired item's ID: ";
                cin >> userItemID; cin.ignore();

                if(libItems.searchLibItem(userItemID) == -1) {break;}
                else {foundItem = libItems.searchLibItem(userItemID);}

                //Update item status to lost
                newItemStatus = 'L';
                libItems.editItemStatus(foundItem, newItemStatus);

                //Search patron database
                cout << "Please enter a patron ID: ";
                cin >> userPatID; cin.ignore();

                if(patrons.searchPatron(userPatID) == -1) {break;}
                else{foundPatron = patrons.searchPatron(userPatID);}

                //Adding the lost item's price to patron's balance
                patrons.editPatronBalance(foundPatron, libItems.GetLostPrice(foundItem));

                //Decrementing the amount of item's the patron has
                patrons.editPatronItemCount(foundPatron, -1);

                break;
            case PRINTOVERDUE:
                loans.printOverdueLoans();
                break;
            case PRINTPATITEMS:
                cout << endl << "Enter the patron's name ('Ellen Ripley'): "; cin >> fName; cin >> lName;
                cout << "Enter the patron's ID: "; cin >> userPatID;

                loans.printPatronLoans(userPatID, fName + " " + lName);

                break;
            case QUIT:
                break;
            default:
                cout << "Invalid selection (" << userChoice << "). Enter option 1-7." << endl;
        }
    } while(userChoice < 7 || userChoice > 7);
}

//Function to create an overdue loan to test overdue functionalities
void makeOverdueTest() {
    libitem *temp;

    time_t testTime = time(NULL) - 864000;

    patron badPerson = patron(1234, "Bad Person", 0.25, 1);
    patrons.addPatTest(badPerson);

    temp = new book(6789, 10, 10.99, "Gone with the Wind", "Drama", 'O', 1234567890, "Margaret Mitchell");
    libItems.addItemTest(temp);

    loan badLoan = loan(8910, 6789, 1234, testTime, 0, 0);
    loans.addLoanTest(badLoan);
}