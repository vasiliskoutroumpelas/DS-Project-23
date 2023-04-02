#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include "csvExtractor.h"

using namespace std;

void countingSort(vector<Record>& Array, int Range)
{
    int n=Array.size();

    vector<int> Auxiliary(Range, 0); //auxiliary vector that holds count
    vector<Record> Temporary(n); //temporary vector

    for(int i=0; i<n; i++) //the count of each element goes to the vector
    {
        Auxiliary[Array[i].Value]++;
    }

    for(int i=1; i<Range; i++) //the vector now has the right positions
    {
        Auxiliary[i]=Auxiliary[i]+Auxiliary[i-1];
    }

    for(int i=n-1; i>=0; i--) //the elements are now sorted
    {
        Temporary[Auxiliary[Array[i].Value]]=Array[i];
        Auxiliary[Array[i].Value]--;
    }

    for(int i=0; i<n; i++) //the sorted elements go back to the initial vector
    {
        Array[i]=Temporary[i];
    }
}

int range(vector<Record>& Array) //function that finds the maximum element (range)
{
    int greatest=0;

    for(int i=0; i<Array.size(); i++)
    {
        if(Array[i].Value>=greatest)
            greatest=Array[i].Value;
    }
    return greatest;
}

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
    case 8: Data.back().Value=stoll(token); break;
    case 9: Data.back().Cumulative=stoll(token); break;
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

int main()
{
    ifstream file("data.csv");
    if(!file.good()) {
        cout<<"error"<<endl;
        return -1;
    }

    vector<Record> data;
    csvToVector(file, data);
    int Range=range(data);

    countingSort(data, Range);

    //for (Record row : data)
    //    cout << "Date: " << row.Date << endl;

    return 0;
}
