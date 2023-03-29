#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvExtractor.h"
#include "sort.h"

using namespace std;

int main() {
    ifstream file("data.csv");
    if(!file.good()) {
        cout<<"error"<<endl;
        return -1;
    }

    vector<Record> data;
    csvToVector(file, data);

    mergeSort(data, 0, data.size()-1);


    //! SIKE , WHAT ARE YOU DOING HERE


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