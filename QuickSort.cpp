#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvExtractor.h"
#include "sort.h"


using namespace std;
//quick sort sorting algorithm


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

