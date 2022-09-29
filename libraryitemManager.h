/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Library item manager class definition

#include <vector>

using namespace std;

class libitemManager {
private:
    int itemCount;
    vector<libitem*> itemList;

public:
    int GetCount();
    double GetLostPrice(int itemID);
    char GetItemStatus(int foundItem);

    void incCount();
    void decCount();
    bool isEmpty();

    void addItemTest(libitem *itemTest);
    void addLibItemMenu();
    void deleteLibItem(int itemID);
    int searchLibItem(int itemID);
    void editItemStatus(int foundItem, char newStatus);

    void printItemList();
    void printSingleItem(int itemID);

    void storeLibItems();
    void loadLibItems();

    void loadFromFileBook(ifstream& fin);
    void loadFromFileDVD(ifstream& fin);
    void loadFromFileCD(ifstream& fin);

    void addBook();
    void addDVD();
    void addAudioCD();
};