#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvExtractor.h"
#include "sort.h"


using namespace std;
//quick sort sorting algorithm



int Partition(vector <Record> &data, int start, int end)
{

    long int pivot = data.back().Cumulative;
    int pIndex = end;

    for(int i=pIndex; i>start; i--)
    {
        if(data.at(i).Cumulative>pivot)
        {

            swap(data.at(i), data.at(pIndex));
            pIndex--;
        }
    }


    swap(data.at(start), data.at(pIndex));


    return pIndex;

}


void QuickSort(vector <Record> &data, int start, int end)
{

    if(start<end)
    {
        int p = Partition(data, start, end);
        QuickSort(data, start, (p-1)); //recursive QuickSort call for left partition
        QuickSort(data, (p+1), end); //recursive QuickSort call for right partition

    }

}

