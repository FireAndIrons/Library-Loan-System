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
#include "dvd.h"

using namespace std;

//Initialized constructor
dvd::dvd(int id, int loanperiod, double cost, string title, string genre, char status,
         int runtime, string studio, string dvdreleasedate):libitem(id, loanperiod, cost, title, genre, status) {
    runTime = runtime;
    dvdStudio = studio;
    dvdReleaseDate = dvdreleasedate;
}

//****Mutators for DVD****
void dvd::SetRunTime(int runtime) {runTime = runtime;}
void dvd::SetStudio(string studio) {dvdStudio = studio;}
void dvd::SetDVDReleaseDate(string dvdreleasedate) {dvdReleaseDate = dvdreleasedate;}

//****Accessors for DVD****
int dvd::GetRunTime() {return runTime;}
string dvd::GetStudio() {return dvdStudio;}
string dvd::GetDVDReleaseDate() {return dvdReleaseDate;}


//Overridden print function
void dvd::Print(ostream& out) {
    libitem::Print(out);
    out << "Studio: " << GetStudio() << endl
        << "DVD Release Date: " << GetDVDReleaseDate() << endl
        << "DVD Run Time: " << GetRunTime() << " minutes" << endl;
}

//Print function to write formatted data to file
void dvd::printToFile(ofstream& fout) {

    fout << "2 " << GetLibID() << " " <<  GetItemLoanPeriod() << " " << GetItemCost()
         << " " << GetItemTitle() << "," << GetItemGenre() << "," << GetItemStatus()
         << " " << GetRunTime() << " " << GetStudio() << "," << GetDVDReleaseDate()
         << endl;
}
