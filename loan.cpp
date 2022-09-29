/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Loan function definitions

#include <ctime>
#include "loan.h"

using namespace std;

//Default Loan constructor - isOverdue and isRenewed set to false
loan::loan() {loanID = 0; itemID = 0; patID = 0; dueDateTime = 0; isOverdue = 0; isRenewed = 0;}

//Initialized Loan constructor
loan::loan(int loanid, int itemid, int patid, time_t duedatetime, bool status, bool renewed) {
    loanID = loanid;
    itemID = itemid;
    patID = patid;
    dueDateTime = duedatetime;
    isOverdue = status;
    isRenewed = renewed;
}

//****Mutators for Loan****
void loan::SetLoanID(int loanid) {loanID = loanid;}

void loan::SetBookID(int itemid) {itemID = itemid;}

void loan::SetPatID(int patid) {patID = patid;}

//10 days in secs is added onto the loan creation time to create the exact due date
void loan::SetDueDateTime(time_t duedatetime) {dueDateTime = duedatetime + 864000;}

void loan::SetLoanStatus(bool status) {isOverdue = status;}

void loan::SetLoanRenewalStatus(bool renewed) {isRenewed = renewed;}

//****Accessors for Loan****
int loan::GetLoanID() {return loanID;}

int loan::GetBookID() {return itemID;}

int loan::GetPatID() {return patID;}

time_t loan::GetDueDateTime() {return dueDateTime;}

bool loan::GetLoanStatus() {return isOverdue;}

bool loan::GetLoanRenewalStatus() {return isRenewed;}