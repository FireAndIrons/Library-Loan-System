/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Library item manager function definitions

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <iterator>
#include <typeinfo>
#include "libraryitem.h"
#include "dvd.h"
#include "audiocd.h"
#include "book.h"
#include "libraryitemManager.h"

using namespace std;

//Is empty
bool libitemManager::isEmpty() {
    return itemList.empty();
}

//Add item test
void libitemManager::addItemTest(libitem *itemTest) {
    itemList.push_back(itemTest);
    incCount();
}

//Gets item status
char libitemManager::GetItemStatus(int foundItem) {
    return itemList.at(foundItem)->GetItemStatus();
}

//Function to return lost item price
double libitemManager::GetLostPrice(int itemID) {
    int foundItem;

    foundItem = searchLibItem(itemID);

    if(foundItem < 0) {
        return 0;
    }
    else{
        return itemList.at(foundItem)->GetItemCost();
    }

}

//Getting count
int libitemManager::GetCount() {return itemCount;}

//Increment count
void libitemManager::incCount() {itemCount++;}

//Decrement count
void libitemManager::decCount() {itemCount--;}

//Function to search item list: returns the item's index
int libitemManager::searchLibItem(int itemID) {

    libitem *temp;

    for(unsigned int i = 0; i < itemList.size(); ++i) {
        temp = itemList.at(i);

        if(temp->GetLibID() == itemID) {
            return i;
        }
    }

    cout << itemID << " is not a valid ID. Item was not found." << endl;
    return -1;
}

//Function to edit the item's status
void libitemManager::editItemStatus(int foundItem, char newStatus) {
    char currStatus;

    currStatus = itemList.at(foundItem)->GetItemStatus();

    if(newStatus == 'I') {
        currStatus = newStatus;
        itemList.at(foundItem)->SetItemStatus(currStatus);
        cout << endl << "The item is now checked in." << endl;
    }
    else if(newStatus == 'O') {
        currStatus = newStatus;
        itemList.at(foundItem)->SetItemStatus(currStatus);
        cout << endl << "The item is now checked out." << endl;
    }
    else if(newStatus == 'L'){
        currStatus = newStatus;
        itemList.at(foundItem)->SetItemStatus(currStatus);
        cout << endl << "The item has been reported as lost." << endl;
    }
    else if(currStatus == 'X') {
        currStatus = 'I';
        itemList.at(foundItem)->SetItemStatus(currStatus);
        cout << endl << "The item has changed from default 'X' to checked in." << endl;
    }
}

//Function to cleanup add lib item menu: prompts user for info and adds a book to item list
void libitemManager::addBook() {
    unsigned int itemID, ISBN;
    int loanPeriod = 10;
    string userTitle, userCreator, userArtist, releaseDate, userGenre;
    double userCost;
    char currStatus = 'X';
    libitem *temp;

    itemID = rand() % 9000 + 1000;
    ISBN = rand() % 1000000000 + 9999999999;
    cout << "Title: ";
    getline(cin, userTitle);
    cout << "Author ('H.P. Lovecraft'): ";
    getline(cin, userCreator);
    cout << "Genre: ";
    getline(cin, userGenre);
    cout << "Cost: ";
    cin >> userCost; cin.ignore();

    temp = new book(itemID, loanPeriod, userCost, userTitle,
                    userGenre, currStatus, ISBN, userCreator);

    itemList.push_back(temp);
    incCount();
    storeLibItems();
}

//Function to cleanup add lib item menu: prompts user for info and adds a DVD to item list
void libitemManager::addDVD() {
    unsigned int itemID;
    int loanPeriod = 10, runTime;
    string userTitle, userCreator, userArtist, releaseDate, userGenre;
    double userCost;
    char currStatus = 'X';
    libitem *temp;

    itemID = rand() % 9000 + 1000;
    cout << "Title: ";
    getline(cin, userTitle);
    cout << "Studio (Sony, Disney): ";
    getline(cin, userCreator);
    cout << "Genre: ";
    getline(cin, userGenre);
    cout << "Release date (mm/dd/yyyy): ";
    getline(cin, releaseDate);
    cout << "Run time (in minutes): ";
    cin >> runTime; cin.ignore();
    cout << "Cost: ";
    cin >> userCost; cin.ignore();

    temp = new dvd(itemID, loanPeriod, userCost, userTitle, userGenre,
                   currStatus, runTime, userCreator, releaseDate);

    itemList.push_back(temp);
    incCount();
    storeLibItems();
}

//Function to cleanup add lib item menu: prompts user for info and adds an audio CD to item list
void libitemManager::addAudioCD() {
    unsigned int itemID;
    int loanPeriod = 10, numOfTracks;
    string userTitle, userCreator, userArtist, releaseDate, userGenre;
    double userCost;
    char currStatus = 'X';
    libitem *temp;

    itemID = rand() % 9000 + 1000;
    cout << "Title: ";
    getline(cin, userTitle);
    cout << "Artist: ";
    getline(cin, userCreator);
    cout << "Genre: ";
    getline(cin, userGenre);
    cout << "Number of tracks: ";
    cin >> numOfTracks; cin.ignore();
    cout << "Release date (mm/dd/yyyy): ";
    getline(cin, releaseDate);
    cout << "Cost: ";
    cin >> userCost; cin.ignore();

    temp = new audiocd(itemID, loanPeriod, userCost, userTitle, userGenre,
                       currStatus, userCreator, numOfTracks, releaseDate);

    itemList.push_back(temp);
    incCount();
    storeLibItems();
}

//Function to house main item addition menu
void libitemManager::addLibItemMenu() {

    int userChoice;

    srand(time(0));

    enum addItemList {BOOK = 1, DVD = 2, AUDIOCD = 3};

    cout << "Which item would you like to add to the catalogue?" << endl
         << "1. A book" << endl << "2. A DVD" << endl << "3. An audio CD " << endl;
    cout << "Enter your selection: ";
    cin >> userChoice; cin.ignore();

    switch (userChoice) {
        case BOOK:
            addBook();
            break;
        case DVD:
            addDVD();
            break;
        case AUDIOCD:
            addAudioCD();
            break;
        default:
            break;
    }

}

//Function to delete an item
void libitemManager::deleteLibItem(int itemID) {


    for(auto it = itemList.begin(); it !=itemList.end(); ++it) {

        if((*it)->GetLibID() == itemID) {
            itemList.erase(it);
            cout << "Item was deleted." << endl;
            decCount();
            storeLibItems();
            return;
        }

    }

    cout << "Invalid ID." << endl;

}

//Function to print the item list
void libitemManager::printItemList() {

    cout << endl << "ITEM LIST" << endl;

    for(unsigned int i = 0; i < itemList.size(); ++i) {
        itemList.at(i)->Print(cout);
        cout << endl;
    }
}

//Function to print a single item based on item ID
void libitemManager::printSingleItem(int itemID) {
    libitem *temp;
    int foundItem;

    cout << endl << "SINGLE ITEM" << endl;

    foundItem = searchLibItem(itemID);

    if(foundItem < 0) {
        return;
    }
    else {
        temp = itemList.at(foundItem);

        temp->Print(cout);
    }

}

//Writes items to file
void libitemManager::storeLibItems() {
    ofstream fout;
    fout.open("libItems.txt");
    fout << GetCount() << endl;

    /*
     * Iterates by list's count, checks the item type,
     * casts the pointer to that item, and then prints
     * the specific item data to the file
     * The printToFile functions are defined in each child class
     * They are used to clean up the write to file function
     */
    libitem *temp;
    for(unsigned int i = 0; i < GetCount(); ++i) {
        temp = itemList.at(i);

        if(typeid(*temp) == typeid(book)) {
            book *tempBook = dynamic_cast <book*>(itemList.at(i));

            tempBook->printToFile(fout);
        }

        else if(typeid(*temp) == typeid(dvd)) {
            dvd *tempDVD = dynamic_cast <dvd*>(itemList.at(i));

            tempDVD->printToFile(fout);
        }

        else if(typeid(*temp) == typeid(audiocd)) {
            audiocd *tempCD = dynamic_cast <audiocd*>(itemList.at(i));

            tempCD->printToFile(fout);
        }
    }

    fout.close();
}

//Function to cleanup load item function: reads in book data and stores to vector
void libitemManager::loadFromFileBook(ifstream& fin) {
    unsigned int itemID, ISBN;
    int loanPeriod;
    string loadTitle, loadCreator, loadGenre;
    double loadCost;
    char currStatus;
    char delimiter = ',';

    fin >> itemID >> loanPeriod >> loadCost;
    fin.ignore();
    getline(fin, loadTitle, delimiter);
    getline(fin, loadGenre, delimiter);
    fin >> currStatus >> ISBN;
    fin.ignore();
    getline(fin, loadCreator);

    itemList.push_back(new book(itemID, loanPeriod, loadCost, loadTitle,
                                loadGenre, currStatus, ISBN, loadCreator));
}

//Function to cleanup load item function: reads in DVD data and stores to vector
void libitemManager::loadFromFileDVD(ifstream& fin) {
    unsigned int itemID;
    int loanPeriod, runTime;
    string loadTitle, loadCreator, loadArtist, releaseDate, loadGenre;
    double loadCost;
    char currStatus;
    char delimiter = ',';

    fin >> itemID >> loanPeriod >> loadCost;
    fin.ignore();
    getline(fin, loadTitle, delimiter);
    getline(fin, loadGenre, delimiter);
    fin >> currStatus >> runTime;
    fin.ignore();
    getline(fin, loadCreator, delimiter);
    fin >> releaseDate;

    itemList.push_back(new dvd(itemID, loanPeriod, loadCost, loadTitle,
                               loadGenre, currStatus, runTime, loadCreator, releaseDate));
}

//Function to cleanup load item function: reads in audio CD data and stores to vector
void libitemManager::loadFromFileCD(ifstream& fin) {
    unsigned int itemID;
    int loanPeriod, numOfTracks;
    string loadTitle, loadCreator, loadArtist, releaseDate, loadGenre;
    double loadCost;
    char currStatus;
    char delimiter = ',';

    fin >> itemID >> loanPeriod >> loadCost;
    fin.ignore();
    getline(fin, loadTitle, delimiter);
    getline(fin, loadGenre, delimiter);
    fin >> currStatus;
    fin.ignore();
    getline(fin, loadCreator, delimiter);
    fin >> numOfTracks;
    fin >> releaseDate;

    itemList.push_back(new audiocd(itemID, loanPeriod, loadCost, loadTitle,
                                   loadGenre, currStatus, loadCreator, numOfTracks, releaseDate));
}

//Reads in items from file
void libitemManager::loadLibItems() {
    ifstream fin;
    int itemType;

    fin.open("libItems.txt");

    fin >> itemCount;

    for(unsigned int i = 0; i < itemCount; ++i) {
        fin >> itemType;

        if(itemType == 1) {
            loadFromFileBook(fin);
        }

        else if(itemType == 2) {
            loadFromFileDVD(fin);
        }

        else if(itemType == 3) {
            loadFromFileCD(fin);
        }
    }

    fin.close();
}