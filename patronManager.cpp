/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Patron Manager function definitions

#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include "patron.h"
#include "patronManager.h"

using namespace std;

//Is empty
bool patronManager::isEmpty() {
    return patronList.empty();
}

//Getting count
int patronManager::GetPatCount() {return patronCount;}

//Increment count
void patronManager::incCount() {patronCount++;}

//Decrement count
void patronManager::decCount() {patronCount--;}

//Add patron tester
void patronManager::addPatTest(patron patTest) {
    patronList.push_back(patTest);
    incCount();
}
//Add patron
void patronManager::addPatron() {
    patron currPatron;
    string userPatName;
    unsigned int userPatID;
    int userNumPats;

    cout << endl << "ADD PATRON" << endl;
    cout << "Enter the number of patrons you would like to add: ";
    cin >> userNumPats;
    cin.ignore();

    //Adding user entered patrons to patron list
    for(unsigned int i = 0; i < userNumPats; ++i) {
        cout << endl << "Enter patron #" << 1 + i << " name ('Ellen Ripley'): ";
        getline(cin, userPatName);

        //Generating random 4 digit patron ID
        srand(time(0));
        userPatID = rand() % 9000 + 1000;
        cout << "Patron " << userPatName << " has been assigned this ID: "  << userPatID << endl;

        currPatron.SetName(userPatName);
        currPatron.SetID(userPatID);
        patronList.push_back(currPatron);

        //Notifying user of addition
        cout << "Patron " << userPatName << " has been added to the patron list." << endl;

        incCount();
    }

    storePatron();
}

//Edit patron balance
void patronManager::editPatronBalance(int index, double balanceUpdateAmt) {
    double currBalance;

    //Locally storing current patron balance
    currBalance = patronList.at(index).GetBalance();

    cout << "The Patron's balance is currently $" << currBalance << endl;

    //Editing the balance
    currBalance += balanceUpdateAmt;

    //Setting the new balance
    patronList.at(index).SetBalance(currBalance);

    cout << "Patron's balance has been updated to $" << currBalance << endl << endl;

    //Storing the edit
    storePatron();
}

//Edit patron book count
void patronManager::editPatronItemCount(int index, int countUpdateAmt) {
    int currCount;

    //Locally storing current patron book count
    currCount = patronList.at(index).GetCountBooks();

    //Editing the count
    currCount += countUpdateAmt;

    //Setting the new count
    patronList.at(index).SetCountBooks(currCount);

    cout << "Patron's loan count is now " << currCount << endl;

    //Storing the edit
    storePatron();
}

//Checking patron eligibility
bool patronManager::checkEligibility(int index) {

    if(patronList.at(index).GetCountBooks() >= 6) {
        cout << endl << "Sorry, no book for you. Too many books, you have." << endl;
        return false;
    }
    //Otherwise they can check out a book
    else {
        cout << endl << "Yay! You have the proper amount of books still." << endl;
        return true;
    }
}

//Delete patron
void patronManager::deletePatron(int patID) {
    int foundPatron;

    //Calling search function
    foundPatron = searchPatron(patID);

    cout << endl << "DELETE PATRON" << endl;

    //If not found, notify user
    if(foundPatron < 0) {
        cout << "No patron exists." << endl;
    }
    //Else delete patron
    else {
        patronList.erase(patronList.begin() + foundPatron);
        cout << "Patron was deleted." << endl;
        decCount();
    }

    //Storing edit
    storePatron();

    cout << endl;
}

//Search for patron
int patronManager::searchPatron(int patID) {
    patron currPatron;

    //Iterating through list, if found notifies user and returns the index of found patron
    for(unsigned int i = 0; i < patronList.size(); ++i) {
        currPatron = patronList.at(i);
        if(patID == currPatron.GetID()) {
            return i;
        }
    }
    //Otherwise user was not found and returns -1
    cout << patID << " is not a valid ID. Patron was not found." << endl;
    return -1;
}

//Print patron list
void patronManager::printPatronList() {
    patron currPatronList;

    cout << endl << "PATRON LIST";

    for(unsigned int i = 0; i < patronList.size(); ++i) {
        currPatronList = patronList.at(i);
        cout << endl << "ID: " << currPatronList.GetID() << " -- Name: " << currPatronList.GetName()
             << " -- Loaned Items Total: " << currPatronList.GetCountBooks() << " -- Balance: $"
             << fixed << setprecision(2) << currPatronList.GetBalance() << endl;
    }

}

//Print single patron
void patronManager::printSinglePatron(int patID) {
    patron currPatron;
    int foundPatron;

    foundPatron = searchPatron(patID);

    cout << endl << "SINGLE PATRON";

    if(foundPatron < 0) {
        cout << endl << "No patron exists." << endl;
    }

    else {
        currPatron = patronList.at(foundPatron);
        cout << endl << "ID: " << currPatron.GetID() << " -- Name: " << currPatron.GetName()
             << " -- Loaned Books Total: " << currPatron.GetCountBooks() << " -- Balance: $"
             << fixed << setprecision(2) << currPatron.GetBalance() << endl;
    }
}

//Store patron data
void patronManager::storePatron() {
    ofstream fout;
    fout.open("patrons.txt");
    patron currPatronList;

    fout << GetPatCount() << endl;

    for(unsigned int i = 0; i < GetPatCount(); ++i) {
        currPatronList = patronList.at(i);
        fout << currPatronList.GetID() << " " << currPatronList.GetCountBooks() << " "
             << currPatronList.GetBalance() << " " << currPatronList.GetName() << endl;
    }

    fout.close();
}

//Load patron data
void patronManager::loadPatron() {
    ifstream fin;
    fin.open("patrons.txt");
    patron tempPatron;

    int loadID;
    string loadFName;
    string loadLName;
    int loadCountBooks;
    double loadBalance;

    fin >> patronCount; fin.ignore();

    for(unsigned int i = 0; i < patronCount; ++i) {
        fin >> loadID;
        fin >> loadCountBooks;
        fin >> loadBalance;
        fin >> loadFName;
        fin >> loadLName;
        tempPatron = patron(loadID, loadFName + " " + loadLName, loadBalance, loadCountBooks);
        patronList.push_back(tempPatron);
    }

    fin.close();
}
