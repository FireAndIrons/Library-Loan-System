/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//DVD class definition

using namespace std;

class dvd: public libitem {
private:
    int runTime;
    string dvdStudio;
    string dvdReleaseDate;

public:
    dvd(int, int, double, string, string, char, int, string, string);

    void SetRunTime(int runtime);
    void SetStudio(string studio);
    void SetDVDReleaseDate(string dvdreleasedate);

    int GetRunTime();
    string GetStudio();
    string GetDVDReleaseDate();

    void Print(ostream& out);

    void printToFile(ofstream& fout);
};