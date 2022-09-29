/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Patron function definitions

#include <string>
#include "patron.h"
using namespace std;

//Default Patron constructor
patron::patron() {patID = 0; patName = "none"; patFineBalance = 0; currCntBooks = 0;}

//Initialized Patron constructor
patron::patron(int patid, string patname, double patfinebalance, int currcntbooks) {
    patID = patid;
    patName = patname;
    patFineBalance = patfinebalance;
    currCntBooks = currcntbooks;
}

//****Mutators for Patron****
void patron::SetID(int patid) {patID = patid;}

void patron::SetName(string patname) {patName = patname;}

void patron::SetBalance(double patfinebalance) {patFineBalance = patfinebalance;}

void patron::SetCountBooks(int currcntbooks) {currCntBooks = currcntbooks;}

//****Accessors for Patron****
int patron::GetID() {return patID;}

string patron::GetName() {return patName;}

double patron::GetBalance() {return patFineBalance;}

int patron::GetCountBooks() {return currCntBooks;}

