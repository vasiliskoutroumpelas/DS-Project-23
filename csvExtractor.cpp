#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

typedef struct record{
    string Direction;
    string Date;
    string Weekday;
    string Country;
    string Commodity;
    string Transport_Mode;
    string Measure;
    long int Value;
    long int Cumulative;
    int Year;
    
}Record;

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

int main() {
    ifstream file("data.csv");
    if(!file.good()) {
        cout<<"error"<<endl;
        return -1;
    }

    vector<Record> Data;
    csvToVector(file, Data);

    for (Record row : Data) {
        cout << "Direction: " << row.Direction << endl;
        cout << "Year: " << row.Year << endl;
        cout << "Date: " << row.Date << endl;
        cout << "Weekday: " << row.Weekday << endl;
        cout << "Country: " << row.Country << endl;
        cout << "Commodity: " << row.Commodity << endl;
        cout << "Transport Mode: " << row.Transport_Mode << endl;
        cout << "Measure: " << row.Measure << endl;
        cout << "Value: " << row.Value << endl;
        cout << "Cumulative: " << row.Cumulative << endl;
        cout << endl;
    }        
    return 0;
}