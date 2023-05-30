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

void mergeValues(vector<Record> &data, int left, int middle, int right);
void mergeSortValues(vector<Record> &data, int left, int right);

int findMaxValue(vector<Record> &array);
void countingSortValues(vector<Record> &array, int range);

bool areSortedValues(vector<Record> &vector);

void csvToVector(ifstream &file, vector<Record> &Data);
void splitStringToRecordFields(stringstream &ss, Record& record);
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
    countingSortValues(data1, findMaxValue(data1));
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(stop1 - start1);

    cout << "Counting Sort:" << endl;
    areSortedValues(data1);
    cout << "Took " << duration1.count() << " milliseconds" << endl;

    cout << endl;
    auto start2 = high_resolution_clock::now();
    mergeSortValues(data2, 0, data2.size() - 1);
    auto stop2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);

    cout << "Merge Sort:" << endl;
    areSortedValues(data2);
    cout << "Took " << duration2.count() << " milliseconds" << endl;

    return 0;
}

void countingSortValues(vector<Record> &array, int range)
{
    int size = array.size();

    vector<int> auxiliary(range, 0); // auxiliary vector that holds count
    vector<Record> temporary(size);

    for (int i = 0; i < size; i++)
    {
        auxiliary[array[i].value]++;
    }

    for (int i = 1; i < range; i++) // the vector now has the right positions
    {
        auxiliary[i] = auxiliary[i] + auxiliary[i - 1];
    }

    for (int i = size - 1; i >= 0; i--) // the elements are now sorted
    {
        temporary[auxiliary[array[i].value]] = array[i];
        auxiliary[array[i].value]--;
    }

    for (int i = 0; i < size; i++) // the sorted elements go back to the initial vector
    {
        array[i] = temporary[i];
    }
}

int findMaxValue(vector<Record> &array) // function that finds the maximum element (range)
{
    int max = 0;

    for (Record element : array)
    {
        if (element.value >= max)
            max = element.value;
    }
    return max;
}

void mergeValues(vector<Record> &data, int left, int middle, int right)
{
    vector<Record> temp;
    int i = left;
    int j = middle + 1;

    while (i <= middle && j <= right)
    {
        if (data[i].value <= data[j].value)
            temp.push_back(data[i++]);
        else
            temp.push_back(data[j++]);
    }

    while (i <= middle)
        temp.push_back(data[i++]);
    while (j <= right)
        temp.push_back(data[j++]);

    for (int i = left; i <= right; i++)
    {
        data[i] = temp[i - left];
    }
}

void mergeSortValues(vector<Record> &data, int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        mergeSortValues(data, left, middle);
        mergeSortValues(data, middle + 1, right);
        mergeValues(data, left, middle, right);
    }
}

bool areSortedValues(vector<Record> &vector)
{
    for (int i = 1; i < vector.size(); i++)
    {
        if (vector[i].value < vector[i - 1].value)
        {
            cout << "Values are not sorted." << endl;
            return false;
        }
    }
    cout << "Values are sorted." << endl;
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
