/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Patron Manager class definition, this will store/manipulate patrons

#include <vector>

using namespace std;

class patronManager {
private:
    vector<patron> patronList;
    int patronCount;

public:
    bool isEmpty();

    int GetPatCount();
    void incCount();
    void decCount();

    void addPatTest(patron patTest);
    void addPatron();
    void editPatronBalance(int index, double balanceUpdateAmt);
    void editPatronItemCount(int index, int countUpdateAmt);
    void deletePatron(int patID);
    int searchPatron(int patID);
    void printPatronList();
    void printSinglePatron(int patID);
    bool checkEligibility(int index);

    void storePatron();
    void loadPatron();
};