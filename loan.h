/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Loan class definition

using namespace std;

class loan {
private:
    int loanID;
    int itemID;
    int patID;
    time_t dueDateTime;
    bool isOverdue; //set to false in default
    bool isRenewed; //set to false in default

public:
    loan();
    loan(int loanid, int itemid, int patid, time_t duedatetime, bool status, bool renewed);

    void SetLoanID(int loanid);
    void SetBookID(int itemid);
    void SetPatID(int patid);
    void SetDueDateTime(time_t duedatetime);
    void SetLoanStatus(bool status);
    void SetLoanRenewalStatus(bool renewed);

    int GetLoanID();
    int GetBookID();
    int GetPatID();
    time_t GetDueDateTime();
    bool GetLoanStatus();
    bool GetLoanRenewalStatus();


};