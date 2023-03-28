#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "csvExtractor.h"
#include "sort.h"

void merge(vector<Record> &data, int left, int middle, int right) {
    vector<Record> temp;
    int i = left;
    int j = middle+1;

    while (i <= middle && j <= right) {
        if (data[i].Value <= data[j].Value)
            temp.push_back(data[i++]);
        else 
            temp.push_back(data[j++]);
    }
    
    while(i <= middle)
        temp.push_back(data[i++]);
    while(j <= right)
        temp.push_back(data[j++]);

    for (int i = left; i <= right; i++) {
        data[i] = temp[i-left];
    }
}

void mergeSort(vector<Record> &data, int left, int right) {    
    if (left < right) {
        int middle = (left+right)/2;
        mergeSort(data, left, middle);
        mergeSort(data, middle+1, right);
        merge(data, left, middle, right);
    }    
}