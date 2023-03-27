#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvExtractor.h"

using namespace std;

vector<Record> csvToVector(string filename) {
    vector<Record> data;
    
    ifstream file(filename);
    if(!file.good())
        cout << "error" << endl;

    string line;
    getline(file, line);

    while (getline(file, line)) {
        Record record;
        stringstream ss(line);
        string cell;

        getline(ss, cell, ',');
        record.Direction = cell;

        getline(ss, cell, ',');
        record.Year = stoi(cell);

        getline(ss, cell, ',');
        record.Date = cell;

        getline(ss, cell, ',');
        record.Weekday = cell;

        getline(ss, cell, ',');
        record.Country = cell;

        getline(ss, cell, ',');
        if (cell[0] == '\"') {
            string temp = cell.substr(1,cell.size())+',';
            getline(ss, cell, '"');
            cell = temp + cell.substr(0, cell.size()-1);
            getline(ss, cell, ',');
        }
        record.Commodity = cell;

        getline(ss, cell, ',');
        record.Transport_Mode = cell;
    
        getline(ss, cell, ',');
        record.Measure = cell;
        
        getline(ss, cell, ',');
        record.Value = stol(cell);

        getline(ss, cell, ',');
        record.Cumulative = stol(cell);
        
        data.push_back(record);
    }
    return data;
}

int main() {
    vector<Record> data = csvToVector("data.csv");
    
    for (Record row : data) {
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
