/*
 * Samantha Fisher - sjc0208
 * CSCE 1040
 * HW4 Library Management System
 */
//Audio CD class definition

using namespace std;

class audiocd : public libitem {
private:
    string CDArtist;
    int numTracks;
    string CDReleaseDate;

public:
    audiocd(int, int, double, string, string, char, string, int, string);

    void SetCDArtist(string artist);
    void SetNumOfTracks(int numtracks);
    void SetCDReleaseDate(string cdreleasedate);

    string GetCDArtist();
    int GetNumOfTracks();
    string GetCDReleaseDate();

    void Print(ostream &out);

    void printToFile(ofstream& fout);
};