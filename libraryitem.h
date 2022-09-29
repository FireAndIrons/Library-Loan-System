/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//LibItem (base class) definitions

using namespace std;

class libitem {
private:
    unsigned int libItemID;
    double libItemCost;
    char libItemStatus; //I - In, O - Out, L - Lost
    int libItemLoanPeriod;
    string libItemTitle;
    string libItemGenre;

public:
    libitem(int, int, double, string, string, char);

    void SetLibID(int id);
    void SetItemCost(double cost);
    void SetItemStatus(char status);
    void SetItemLoanPeriod(int loanperiod);
    void SetItemTitle(string title);
    void SetItemGenre(string genre);

    int GetLibID();
    double GetItemCost();
    char GetItemStatus();
    int GetItemLoanPeriod();
    string GetItemTitle();
    string GetItemGenre();

    virtual void Print(ostream& out);

    friend ostream& operator<<(ostream& st, libitem& libit);
};