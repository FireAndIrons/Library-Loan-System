/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//DVD function definitions

#include <iostream>
#include <fstream>
#include <string>
#include "libraryitem.h"
#include "audiocd.h"

using namespace std;

//Initialized constructor
audiocd::audiocd(int id, int loanperiod, double cost, string title, string genre, char status,
         string artist, int numtracks, string cdreleasedate):libitem(id, loanperiod, cost, title, genre, status) {
    CDArtist = artist;
    numTracks = numtracks;
    CDReleaseDate = cdreleasedate;
}

//****Mutators for CD****
void audiocd::SetCDArtist(string artist) {CDArtist = artist;}
void audiocd::SetNumOfTracks(int numtracks) {numTracks = numtracks;}
void audiocd::SetCDReleaseDate(string cdreleasedate) {CDReleaseDate = cdreleasedate;}

//****Accessors for CD****
string audiocd::GetCDArtist() {return CDArtist;}
int audiocd::GetNumOfTracks() {return numTracks;}
string audiocd::GetCDReleaseDate() {return CDReleaseDate;}

//Overridden print function
void audiocd::Print(ostream& out) {
    libitem::Print(out);
    out << "CD Artist: " << GetCDArtist() << endl
        << "Number of Tracks: " << GetNumOfTracks() << endl
        << "CD Release Date: " << GetCDReleaseDate() << endl;

}

//Print function to write formatted data to file
void audiocd::printToFile(ofstream& fout) {
    fout << "3 " << GetLibID() << " " <<  GetItemLoanPeriod() << " " << GetItemCost()
         << " " << GetItemTitle() << "," << GetItemGenre() << "," << GetItemStatus()
         << " " << GetCDArtist() << "," << GetNumOfTracks() << " " << GetCDReleaseDate()
         << endl;
}
