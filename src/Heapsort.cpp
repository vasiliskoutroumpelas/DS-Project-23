#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "csvExtractor.h"

using namespace std;

void heapifyDown(vector<Record>& heap, int size, int i) { //function that step by step gives the vector heap property
    int greatest = i; //father node
    int leftNode = 2 * i + 1; //left child node
    int rightNode = 2 * i + 2;  //right child node

    if (leftNode < size && heap[leftNode].Cumulative > heap[greatest].Cumulative) //father index moves to the greatest element
        greatest = leftNode;

    if (rightNode < size && heap[rightNode].Cumulative > heap[greatest].Cumulative)  //father index moves to the greatest element
        greatest = rightNode;

    if (greatest != i) {  //function that swaps the greatest with the least element to partially sort the heap
        swap(heap[i], heap[greatest]);
        heapifyDown(heap, size, greatest);
    }
}

void createMaxHeap(vector<Record>& heap, int size) { //function to create a heap that satisfies the heap property
    for (int i = size / 2 - 1; i >= 0; i--)
        heapifyDown(heap, size, i);
}

void heapSort(vector<Record>& heap) { //the main sorting algorithm
    int size = heap.size();

    createMaxHeap(heap, size); //creation of the heap

    for (int i = size - 1; i >= 0; i--) { //consecutive swaps of the last with the root element and heapification of the vector.
        swap(heap[0], heap[i]);
        heapifyDown(heap, i, 0);
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
    ifstream file("testset.csv");
    if(!file.good()) {
        cout<<"error"<<endl;
        return -1;
    }

    vector<Record> data;
    csvToVector(file, data);

    heapSort(data);

    for (Record row : data) {
        cout << "Date: " << row.Date << endl;
    }
    return 0;
}
