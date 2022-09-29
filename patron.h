/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Patron class definition

using namespace std;

class patron {
private:
    int patID;
    string patName;
    double patFineBalance;
    int currCntBooks; //total of books patron has loaned out

public:
    patron();
    patron(int patid, string patname, double patfinebalance, int currcntbooks);

    void SetID(int patid);
    void SetName(string patname);
    void SetBalance(double patfinebalance);
    void SetCountBooks(int currcntbooks);

    int GetID();
    string GetName();
    double GetBalance();
    int GetCountBooks();
};