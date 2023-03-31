#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "csvExtractor.h"

using namespace std;


int Partition(vector <Record> &Data, int s, int e)
{

    long int pivot = Data.front().Cumulative;
    int pIndex = e;

    for(int i=e; i>s; i--)
    {
        if(Data.at(i).Cumulative>pivot)
        {

            swap(Data.at(i), Data.at(pIndex));
            pIndex--;
        }
    }


    swap(Data.at(s), Data.at(pIndex));


    return pIndex;

}


void QuickSort(vector <Record> &Data, int s, int e)
{

    if(s<e)
    {
        int p = Partition(Data, s, e);
        QuickSort(Data, s, (p-1)); //recursive QuickSort call for left partition
        QuickSort(Data, (p+1), e); //recursive QuickSort call for right partition

    }

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

int main() {
    ifstream file("data.csv");
    if(!file.good()) {
        cout<<"error"<<endl;
        return -1;
    }

    vector<Record> data;
    csvToVector(file, data);

    QuickSort(data, 0, (data.size()-1));


    for (Record row : data) {
        cout << "Cumulative: " << row.Cumulative << endl;
    }

    return 0;
}
