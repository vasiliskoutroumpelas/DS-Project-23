#include <bits/stdc++.h>

using namespace std;
using namespace std::chrono;

typedef struct record
{
    string direction;
    int year;
    string date;
    string weekday;
    string country;
    string commodity;
    string transport_mode;
    string measure;
    long int value;
    long int cumulative;
} Record;

// tsakalidis book + renaming (original)
void heapSortCumulatives(vector<Record> &data, int size);

// sioutas slides
void quickSortCumulatives(vector<Record> &data, int left, int right);

bool areSortedCumulatives(vector<Record> &vector);

// original
void csvToVector(ifstream &file, vector<Record> &data);
void splitStringToRecordFields(stringstream &ss, Record &record);
void insertDataToField(int fieldCounter, string token, Record& record);

int main()
{
    system("clear");
    
    ifstream file("data.csv");
    if (!file.good())
    {
        cout << "error" << endl;
        return -1;
    }

    vector<Record> data1, data2;
    csvToVector(file, data1);
    data2 = data1;

    auto start1 = high_resolution_clock::now();
    
    heapSortCumulatives(data1, data1.size());
    
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);

    cout << "Heap Sort:" << endl;
    areSortedCumulatives(data1);
    cout << "Took " << duration1.count() << " milliseconds" << endl;

    cout << endl;
    auto start2 = high_resolution_clock::now();
    quickSortCumulatives(data2, 0, data2.size() - 1);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);

    cout << "Quick Sort:" << endl;
    areSortedCumulatives(data2);
    cout << "Took " << duration2.count() << " milliseconds" << endl;

    return 0;
}

void heapSortCumulatives(vector<Record> &data, int size)
{
    int heapPointer = ((size - 1) / 2) + 1; // after this position the heap property is true
    int sortedPointer = size - 1;           // after this position the values are sorted
    int currentNode, childNode;
    Record parent;

    while (sortedPointer >= 1)
    {
        if (heapPointer > 0)
        {
            heapPointer--;
            currentNode = heapPointer;
        }
        else
        {
            swap(data.front(), data[sortedPointer]);
            sortedPointer--;
            currentNode = 0;
        }

        parent = data[currentNode];

        while (2 * currentNode + 1 <= sortedPointer)
        {
            childNode = 2 * currentNode + 1;

            // checks which child is larger
            if (childNode < sortedPointer && data[childNode].cumulative < data[childNode + 1].cumulative)
                childNode++;

            // checks if parent is smaller than its largeer child
            if (parent.cumulative < data[childNode].cumulative)
            {
                data[currentNode] = data[childNode];
                currentNode = childNode;
            }

            else
            {
                data[currentNode] = parent;
                break;
            }
        }
    }
}

void quickSortCumulatives(vector<Record> &data, int left, int right)
{
    long int pivot;
    int leftArrow, rightArrow;
    leftArrow = left;
    rightArrow = right;
    pivot = data[(left + right) / 2].cumulative;

    while (rightArrow >= leftArrow)
    {
        while (data[rightArrow].cumulative > pivot)
            --rightArrow;
        while (data[leftArrow].cumulative < pivot)
            ++leftArrow;
        if (leftArrow <= rightArrow)
        {
            swap(data[leftArrow], data[rightArrow]);
            ++leftArrow;
            --rightArrow;
        }
    }

    if (left < rightArrow)
        quickSortCumulatives(data, left, rightArrow);
    if (leftArrow < right)
        quickSortCumulatives(data, leftArrow, right);
}

bool areSortedCumulatives(vector<Record> &vector)
{
    for (int i = 1; i < vector.size(); i++)
    {
        if (vector[i].cumulative < vector[i - 1].cumulative)
        {
            cout << "Cumulatives are not sorted." << endl;
            return false;
        }
    }
    cout << "Cumulatives are sorted." << endl;
    return true;
}

void csvToVector(ifstream &file, vector<Record> &data)
{
    string line;
    stringstream ss(line);
    Record *record;

    // Remove the first line of the file
    getline(file, line);
    while (getline(file, line))
    {
        record = new Record;
        ss << line;

        splitStringToRecordFields(ss, *record);

        data.push_back(*record);

        // reset stringstream
        ss.str("");
        ss.clear();
    }
}

void splitStringToRecordFields(stringstream &ss, Record &record)
{
    string token;
    int fieldCounter = 0;

    while (getline(ss, token, ','))
    {
        insertDataToField(fieldCounter, token, record);
        fieldCounter++;

        if (ss.peek() == '"')
        {
            ss.get();

            getline(ss, token, '"');
            insertDataToField(fieldCounter, token, record);
            fieldCounter++;

            ss.get();
        }
    }
}

void insertDataToField(int fieldCounter, string token, Record& record)
{
    switch (fieldCounter)
    {
    case 0:
        record.direction = token;
        break;
    case 1:
        record.year = stoi(token);
        break;
    case 2:
        record.date = token;
        break;
    case 3:
        record.weekday = token;
        break;
    case 4:
        record.country = token;
        break;
    case 5:
        record.commodity = token;
        break;
    case 6:
        record.transport_mode = token;
        break;
    case 7:
        record.measure = token;
        break;
    case 8:
        record.value = stol(token);
        break;
    case 9:
        record.cumulative = stol(token);
        break;
    default:
        break;
    }
}
