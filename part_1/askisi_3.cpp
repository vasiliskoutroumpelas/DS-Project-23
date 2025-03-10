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
    long long value;
    long long cumulative;
} Record;

int binarySearch(vector<Record> &array, int key, int indexMin, int indexMax);
int interpolationSearch(vector<Record> &data, int key, int low, int high);
int date_to_int(string date);
bool isValidDate(string date);
void printResultsOfSearch(vector<Record> &data, int index);

void quickSortDates(vector<Record> &data, int left, int right);
bool areSortedDates(vector<Record> &vector);

void csvToVector(ifstream &file, vector<Record> &data);
void splitStringToRecordFields(stringstream &ss, Record &record);
void insertDataToField(int fieldCounter, string token, Record &record);

int main()
{
    system("clear");

    ifstream file("data.csv");
    if (!file.good())
    {
        cout << "error" << endl;
        return -1;
    }

    vector<Record> data;
    csvToVector(file, data);

    quickSortDates(data, 0, data.size() - 1);
    cout << areSortedDates(data) << endl;

    string date;
    cout << "Enter valid date in DD/MM/YYYY format, between 2015 and 2021: " << endl;
    cin >> date;
    
    while (!isValidDate(date)) {
        cout << "Invalid date or not between specified bounds" << endl;
        cout << "Enter valid date in DD/MM/YYYY format, between 2015 and 2021: " << endl;
        cin >> date;
    }

    cout << endl;

    auto start1 = high_resolution_clock::now();

    int index1 = binarySearch(data, date_to_int(date), 0, data.size() - 1);

    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);

    cout << "Binary Search:" << endl;
    cout << "Took " << duration1.count() << " microseconds" << endl
         << endl;
    ;
    printResultsOfSearch(data, index1);

    cout << endl;

    auto start2 = high_resolution_clock::now();

    int index2 = interpolationSearch(data, date_to_int(date), 0, data.size() - 1);

    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout << "Interpolation Search:" << endl;
    cout << "Took " << duration2.count() << " microseconds" << endl
         << endl;
    printResultsOfSearch(data, index2);

    return 0;
}

int binarySearch(vector<Record> &array, int key, int indexMin, int indexMax)
{
    int indexMid = (indexMax + indexMin) / 2;
    if (indexMin <= indexMax)
    {
        if (date_to_int(array[indexMid].date) == key)
        {
            cout << "Date found at index " << indexMid << " of sorted dates." << endl;
            return indexMid;
        }

        else if (date_to_int(array[indexMid].date) > key)
            return binarySearch(array, key, indexMin, indexMid - 1);

        else
            return binarySearch(array, key, indexMid + 1, indexMax);
    }
    cout << "Date not found." << endl;
    return -1;
}

int interpolationSearch(vector<Record> &data, int key, int low, int high)
{
    int next;
    while (key > date_to_int(data[low].date) && key <= date_to_int(data[high].date))
    {
        next = low + ((key - date_to_int(data[low].date)) / (date_to_int(data[high].date) - date_to_int(data[low].date))) * (high - low);

        if (date_to_int(data[next].date) < key)
            low = next + 1;

        else if (date_to_int(data[next].date) > key)
            high = next - 1;

        else
            low = next;
    }
    if (key == date_to_int(data[low].date))
    {
        cout << "Date found at index " << low << " of sorted dates." << endl;
        return low;
    }

    cout << "Date not found." << endl;
    return -1;
}

// function that takes the dates as string and outputs the "reversed" int (helps with comparisons later)
int date_to_int(string date)
{
    stringstream ss(date);
    string str;
    int day, month, year;
    char delimiter = '/';

    getline(ss, str, delimiter);
    day = stoi(str);

    getline(ss, str, delimiter);
    month = stoi(str);

    getline(ss, str, delimiter);
    year = stoi(str);

    // here the date is output as a "reversed" integer.
    return (10000 * year + 100 * month + day);
}

bool isValidDate(string date)
{
    stringstream ss(date);
    string str;
    int day, month, year;
    char delimiter = '/';

    getline(ss, str, delimiter);
    day = stoi(str);

    getline(ss, str, delimiter);
    month = stoi(str);

    getline(ss, str, delimiter);
    year = stoi(str);

    // If year, month and day 
    // are not in given range
    if (year > 2021 || 
        year < 2015)
    return false;
    if (month < 1 || month > 12)
    return false;
    if (day < 1 || day > 31)
    return false;
  
    // Handle February month 
    // with leap year
    if (month == 2)
    {
        if ((((year % 4 == 0) && 
         (year % 100 != 0)) ||
         (year % 400 == 0)))
        return (day <= 29);
        else
        return (day <= 28);
    }
  
    // Months of April, June, 
    // Sept and Nov must have 
    // number of days less than
    // or equal to 30.
    if (month == 4 || month == 6 ||
        month == 9 || month == 11)
        return (day <= 30);
  
    return true;
}

void printResultsOfSearch(vector<Record> &data, int index)
{
    if (index >= 0)
    {
        int i = index;
        while (i >= 0 && date_to_int(data[index].date) == date_to_int(data[i].date))
        {
            cout << "For date " << data[i].date << " in index " << i << " of sorted dates:" << endl; 
            cout << "Value is equal to: " << data[i].value << endl;
            cout << "Cumulative is equal to: " << data[i].cumulative << endl;
            cout << endl;
            i--;
        }

        i = index;
        while (i < data.size() && date_to_int(data[index].date) == date_to_int(data[i].date))
        {
            cout << "For date " << data[i].date << " in index " << i << " of sorted dates:" << endl; 
            cout << "Value is equal to: " << data[i].value << endl;
            cout << "Cumulative is equal to: " << data[i].cumulative << endl;
            cout << endl;
            i++;
        }
    }
    else
    {
        cout << "No results to be printed." << endl;
    }
}

void quickSortDates(vector<Record> &data, int left, int right)
{
    int pivot;
    int leftArrow, rightArrow;
    leftArrow = left;
    rightArrow = right;
    pivot = date_to_int(data[(left + right) / 2].date);

    while (rightArrow >= leftArrow)
    {
        while (date_to_int(data[rightArrow].date) > pivot)
            --rightArrow;
        while (date_to_int(data[leftArrow].date) < pivot)
            ++leftArrow;
        if (leftArrow <= rightArrow)
        {
            swap(data[leftArrow], data[rightArrow]);
            ++leftArrow;
            --rightArrow;
        }
    }

    if (left < rightArrow)
        quickSortDates(data, left, rightArrow);
    if (leftArrow < right)
        quickSortDates(data, leftArrow, right);
}

bool areSortedDates(vector<Record> &vector)
{
    for (int i = 1; i < vector.size(); i++)
    {
        if (date_to_int(vector[i].date) < date_to_int(vector[i - 1].date))
        {
            cout << "Dates are not sorted." << endl;
            return false;
        }
    }
    cout << "Dates are sorted." << endl;
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

void insertDataToField(int fieldCounter, string token, Record &record)
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
        record.value = stoll(token);
        break;
    case 9:
        record.cumulative = stoll(token);
        break;
    default:
        break;
    }
}
