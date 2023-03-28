#ifndef CSV_EXTRACTOR
#define CSV_EXTRACTOR

#include <vector>
#include <string>
using namespace std;

typedef struct record{
    string Direction;
    int Year;
    string Date;
    string Weekday;
    string Country;
    string Commodity;
    string Transport_Mode;
    string Measure;
    long int Value;
    long int Cumulative;    
}Record;

vector<Record> csvToVector(string filename);

#endif