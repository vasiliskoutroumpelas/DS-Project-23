#ifndef SORT
#define SORT

#include <vector>
#include <string>
#include "csvExtractor.h"
using namespace std;

void merge(vector<Record> &data, int left, int middle, int right);
void mergeSort(vector<Record> &data, int left, int right);
#endif
