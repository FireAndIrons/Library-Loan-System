/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Loan Manager class definition, this will store/manipulate loans

#include <vector>

using namespace std;

class loanManager {
private:
    vector<loan> loanList;
    int loanCount;
public:
    int GetLoanCount();

    void incCount();
    void decCount();

    bool isEmpty();
    void addLoanTest(loan loanTest);
    void checkoutItem(int userPatID);
    void checkinItem(double& amtDue, int foundLoan);
    bool hasOverdueItems(int currPatID);
    void printOverdueLoans();
    void printPatronLoans(int currPatID, string patName);
    bool itemIsRenewed(int index);
    int searchLoan(int loanID);
    void itemIsOverdue();
    void itemToRenew();
    double calcLoanRate(int index);

    void storeLoan();
    void loadLoan();

};