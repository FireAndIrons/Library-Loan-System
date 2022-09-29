/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Loan Manager function definitions

#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include "loan.h"
#include "loanManager.h"

using namespace std;

//Getting count
int loanManager::GetLoanCount() {return loanCount;}

//Increment count
void loanManager::incCount() {loanCount++;}

//Decrement count
void loanManager::decCount() {loanCount--;}

//Is empty
bool loanManager::isEmpty() {
    return loanList.empty();
}

//Add loan test
void loanManager::addLoanTest(loan loanTest) {
    loanList.push_back(loanTest);
    incCount();
}

//Add or "Checkout" loan
void loanManager::checkoutItem(int userPatID) {
    loan currLoan;
    int userItemID;
    unsigned int newLoanID;

    cout << endl << "ITEM CHECKOUT" << endl;

    for(unsigned int i = 0; i < 1; ++i) {
        cout << "Enter an item ID: ";
        cin >> userItemID;

        //Generating random 4 digit book ID
        srand(time(0));
        newLoanID = rand() % 9000 + 1000;
        cout << "Your loan has been assigned this ID: "  << newLoanID << endl;

        currLoan.SetPatID(userPatID);
        currLoan.SetBookID(userItemID);
        currLoan.SetLoanID(newLoanID);

        //Getting time at loan creation
        time_t timeAtLoan = time(NULL);

        currLoan.SetDueDateTime(timeAtLoan);
        currLoan.SetLoanStatus(false);
        loanList.push_back(currLoan);

        cout << newLoanID << " has been added to the loan list." << endl;

        incCount();
    }

    storeLoan();
}

//Delete or "Checkin" loan
void loanManager::checkinItem(double& amtDue, int foundLoan) {

    cout << endl << "CHECKIN ITEM";

    cout << endl << "To start, we will check for any fines.";

    //If not found, notify user
    if(foundLoan < 0) {
        cout << endl << "No loan exists." << endl;
    }
    //Else if loan is overdue, calculate late fees and delete loan
    else {
        if(loanList.at(foundLoan).GetLoanStatus()) {
            amtDue = calcLoanRate(foundLoan);
        }

        loanList.erase(loanList.begin() + foundLoan);

        decCount();

        cout << endl << "Your loan has been removed from the Loan list." << endl;
    }

    storeLoan();
}

//Calculating the loan rate - returns the new charge
double loanManager::calcLoanRate(int index) {
    time_t timeStart;
    timeStart = time(NULL);

    //Subtracts time at the start of program from loan's creation time
    double timeDifference = difftime(timeStart, loanList.at(index).GetDueDateTime());

    //How many days the book is overdue
    int daysOverdue = timeDifference / 86400;

    //Loan rate per day
    double newCharge = daysOverdue * 0.25;

    return newCharge;
}

//Edit or "Renew" loan
void loanManager::itemToRenew() {
    int foundLoan;
    int currLoanID;

    cout << endl << "RENEW LOAN" << endl;
    cout << "Please enter your loan ID:";
    cin >> currLoanID; cin.ignore();
    foundLoan = searchLoan(currLoanID);

    //Checking to see if 1. Loan is the correct loan 2. If the patron has overdue books
    //3. If the book has been once renewed already
    if(loanList.at(foundLoan).GetLoanID() == currLoanID
       && hasOverdueItems(loanList.at(foundLoan).GetPatID())
       && itemIsRenewed(foundLoan)) {

        //Adds 10 more days to due date
        loanList.at(foundLoan).SetDueDateTime(loanList.at(foundLoan).GetDueDateTime());

        //Sets renewal status to true
        loanList.at(foundLoan).SetLoanRenewalStatus(true);

        cout << currLoanID << " has been renewed." << endl;
    }
    else {
        cout << "Your loan could not be found." << endl;
    }

    storeLoan();
}

//Get loan renewal status of found loan
bool loanManager::itemIsRenewed(int index) {
    return loanList.at(index).GetLoanRenewalStatus();
}

//Update loan status to overdue
void loanManager::itemIsOverdue() {
    time_t timeAtStart;
    timeAtStart = time(NULL);

    //Update list at the start of program
    for(unsigned int i = 0; i < loanList.size(); ++i) {

        //Subtracts time at the start of program from loan's creation time
        double timeDiff = difftime(timeAtStart, loanList.at(i).GetDueDateTime());

        //If time is positive, loan is overdue
        if(timeDiff > 0) {
            loanList.at(i).SetLoanStatus(true);
        }
    }
}

//Check loan status
bool loanManager::hasOverdueItems(int currPatID) {

    for(unsigned int i = 0; i < loanList.size(); ++i) {
        //If patron ID matches and is overdue is true, they cannot check out book
        if(loanList.at(i).GetPatID() == currPatID && loanList.at(i).GetLoanStatus() == 1) {
            cout << "You have an overdue loan and cannot renew or checkout a book." << endl;
            return false;
        }
    }

    //Otherwise they don't have loans, or all the loans they have are not overdue
    cout << "You have no overdue loans." << endl;
    return true;
}


//Print all overdue loans
void loanManager::printOverdueLoans() {

    cout << endl << "ALL OVERDUE LOANS" << endl;

    for(unsigned int i = 0; i < loanList.size(); ++i) {
        if(loanList.at(i).GetLoanStatus() == 1) {
            cout << "Loan ID: " << loanList.at(i).GetLoanID() << " -- Patron ID: " << loanList.at(i).GetPatID()
                << " -- Item ID: " << loanList.at(i).GetBookID() << " -- Loan Status: Overdue" << endl;
        }
        else{
            cout << "No overdue loans in list." << endl;
        }
    }

}

//Print a patron's loans
void loanManager::printPatronLoans(int currPatID, string patName) {

    cout << endl << "ALL LOANS FOR PATRON " << patName << ":" << endl;

    for(unsigned int i = 0; i < loanList.size(); ++i) {
        time_t loanTime = loanList.at(i).GetDueDateTime();
        char *date = ctime(&loanTime);

        if(loanList.at(i).GetPatID() == currPatID) {
            cout << "Loan ID: " << loanList.at(i).GetLoanID()
                 << " -- Item ID: " << loanList.at(i).GetBookID()
                 << " -- Loan Due Date: " << date;
        }
        else {
            cout << "Patron " << patName << " currently has no loans out." << endl;
        }
    }

}

//Search loan
int loanManager::searchLoan(int loanID) {

    //Iterating through list, if found notifies user and returns the index of found loan
    for(unsigned int i = 0; i < loanList.size(); ++i) {
        if(loanID == loanList.at(i).GetLoanID()) {
            return i;
        }
    }
    //Otherwise loan was not found and returns -1
    cout << loanID << " is not a valid ID. Loan was not found." << endl;
    return -1;
}

//Store loan data
void loanManager::storeLoan() {
    ofstream fout;
    fout.open("loans.txt");
    loan currLoanList;

    fout << GetLoanCount() << endl;

    for(unsigned int i = 0; i < GetLoanCount(); ++i) {
        currLoanList = loanList.at(i);
        fout << currLoanList.GetLoanID() << " " <<  currLoanList.GetBookID()<< " "
             << currLoanList.GetPatID() << " " <<  currLoanList.GetDueDateTime()<< " "
             << currLoanList.GetLoanStatus() << " " << currLoanList.GetLoanRenewalStatus() << endl;
    }

    fout.close();
}

//Load loan data
void loanManager::loadLoan() {
    ifstream fin;
    fin.open("loans.txt");
    loan tempLoan;

    int loadLID;
    int loadBID;
    int loadPID;
    bool loadStatus;
    time_t loadTime;
    bool loadRenewStatus;

    fin >> loanCount; fin.ignore();

    for(unsigned int i = 0; i < loanCount; ++i) {
        fin >> loadLID;
        fin >> loadBID;
        fin >> loadPID;
        fin >> loadTime;
        fin >> loadStatus;
        fin >> loadRenewStatus;
        tempLoan = loan(loadLID, loadBID, loadPID, loadTime, loadStatus, loadRenewStatus);
        loanList.push_back(tempLoan);
    }

    fin.close();
}