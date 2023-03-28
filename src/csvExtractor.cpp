#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "csvExtractor.h"

using namespace std;

void insertData(int counter, string token, vector<Record>& Data){
    switch (counter)
    {
    case 0: Data.back().Direction=token; break;
    case 1: Data.back().Year=stoi(token); break;
    case 2: Data.back().Date=token; break;
    case 3: Data.back().Weekday=token; break;
    case 4: Data.back().Country=token; break;
    case 5: Data.back().Commodity=token; break;        
    case 6: Data.back().Transport_Mode=token; break;
    case 7: Data.back().Measure=token; break;
    case 8: Data.back().Value=stol(token); break;
    case 9: Data.back().Cumulative=stol(token); break;
    default:
        break;
    }
}


void splitstring(stringstream& ss, vector<Record>& Data){
    string token;
    int counter=0;
    
    while(getline(ss, token, ',')){
        insertData(counter, token, Data);
        counter++;
        
        if(ss.peek()=='"'){
            ss.get();
            getline(ss, token, '"');
            insertData(counter, token, Data);

            //! next comma after ",
            ss.get();
            counter++;
        }
    }
    
}


void csvToVector(ifstream& file, vector<Record>& Data){
string line;
stringstream ss(line);
Record* record;

// Remove the first line of the file
getline(file, line);
    while(getline(file, line)) {
        
        record = new Record;
        Data.push_back(*record);
        ss<<line;
        
        splitstring(ss, Data);
        
        //reset stringstream
        ss.str("");
        ss.clear();       
    }
}
