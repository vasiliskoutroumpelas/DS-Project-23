#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "csvExtractor.h"

using namespace std;


  int date_to_int(string date, char del)       // function that takes the dates as string and outputs the "reversed" int (helps with comparisons later)
  {
      stringstream ss(date);
      string word;

      vector <int> Date;

      while (!ss.eof()) {
        for(int i=0; i<3; i++)
        {
              getline(ss, word, del);
              Date.push_back(stoi(word));

        }

        return (10000 * Date[2] + 100 * Date[1] + Date[0]);           //here the date is output as a "reversed" integer.


      }
  }



int binary_interpolation(vector <Record> &Data, int left, int right, int key){


    int next;

    int size = right-left+1;
    next = (int)round((double)(size*(key - date_to_int(Data.at(left).Date, '/')) / (date_to_int(Data.at(right).Date, '/') - date_to_int(Data.at(left).Date, '/'))));

    while(key != date_to_int(Data.at(next).Date, '/'))
    {
        int size = right-left+1;
        int i=0;
        if(size<=3)
        {
            cout << "Direct Search." <<endl;

        }
        if(key >= date_to_int(Data.at(next).Date, '/'))
        {
          while(key > date_to_int(Data.at(next + i * (int)round((double)(sqrt(size) - 1))).Date, '/'))
          {
                  i = i+1;
          }
          right = next + i * round((double)sqrt(size));
          left = next + (i-1) * round((double)sqrt(size));

        }
        else if(key < date_to_int(Data.at(next).Date, '/'))
        {

          while(key < date_to_int(Data.at(next - i * (int)round((double)sqrt(size)) + 1).Date, '/'))
          {
            i = i+1;
          }
          right = next - (i-1) * round((double)sqrt(size));
          left = next - i * round((double)sqrt(size));
        }

        next = left + round((double)(((right-left+1) * (key - date_to_int(Data.at(left).Date,'/')  / (date_to_int(Data.at(right).Date,'/') - date_to_int(Data.at(left).Date, '/'))))));

      }
      if(key == date_to_int(Data.at(next).Date, '/'))
          return next;

      else return -1;

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

    string date;
    cout << "Enter date in DD/MM/YYYY format: " <<endl;
    cin >> date;
    int key = date_to_int(date, '/');


    int index = binary_interpolation(data, 0, (data.size() - 1) / sizeof(int)), key);

    // If element was found
    if (index != -1){
        //cout << "Element found at index " << index;
        cout << "Value is equal to: " << data.at(index).Value <<endl;
        cout << "Cumulative is equal to: " << data.at(index).Cumulative << endl;
    }
    else{
        cout << "Element not found.";
    }


    return 0;
}
