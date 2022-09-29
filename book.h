/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Book class definition

using namespace std;

class book: public libitem {
private:
    unsigned int ISBN;
    string bookAuthor;

public:
    book(int, int, double, string, string, char, int, string);

    void SetISBN(int isbn);
    void SetAuthor(string author);

    int GetISBN();
    string GetAuthor();

    void Print(ostream &out);

    void printToFile(ofstream& fout);

};