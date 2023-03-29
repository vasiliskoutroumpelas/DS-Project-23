#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvExtractor.h"
#include "sort.h"


using namespace std;
//quick sort sorting algorithm



int Partition(vector <Record> &data, int s, int e)
{

    long int pivot = data.front().Cumulative;
    int pIndex = e;

    for(int i=e; i>s; i--)
    {
        if(data.at(i).Cumulative>pivot)
        {

            swap(data.at(i), data.at(pIndex));
            pIndex--;
        }
    }


    swap(data.at(s), data.at(pIndex));


    return pIndex;

}


void QuickSort(vector <Record> &data, int s, int e)
{

    if(s<e)
    {
        int p = Partition(data, s, e);
        QuickSort(data, s, (p-1)); //recursive QuickSort call for left partition
        QuickSort(data, (p+1), e); //recursive QuickSort call for right partition

    }

}

