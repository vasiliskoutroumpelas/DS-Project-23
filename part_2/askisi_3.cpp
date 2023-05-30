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

typedef struct node
{
    node *next = NULL;
    node *head;
    Record data;
} Node;

// original
void csvToVector(ifstream &file, vector<Record> &Data);
void splitStringToRecordFields(stringstream &ss, Record &record);
void insertDataToField(int fieldCounter, string token, Record &record);

void printRecord(Record rec);
void pushHash(vector<Node *> &table, int hashValue, Record data);
void printHash(vector<Node *> hashTable);
void searchHash(vector<Node *> hashTable, string inputDate);
vector<Node *> hashing(vector<Record> &data);
void deleteHashNode(vector<Node *> &hashTable, string inputDate);
void editHashNode(vector<Node *> &hashTable, string inputDate, long long newValue);
void menu(vector<Node *> &hashTable);
void printRecord(Record rec);

int main()
{
    // system("clear");

    ifstream file("data.csv");
    if (!file.good())
    {
        cout << "error" << endl;
        return -1;
    }

    vector<Record> data1, data2;
    csvToVector(file, data1);
    data2 = data1;

    vector<Node *> hashTable;
    hashTable = hashing(data2);

    menu(hashTable);

    return 0;
}

//** Adds a new Node(Record) to the hashtable in its respective position
void pushHash(vector<Node *> &table, int hashValue, Record data)
{
    Node *firstNode = table.at(hashValue);
    Node *currentNode;

    // first element knows the last

    if (!firstNode)
    {
        table.at(hashValue) = new Node;
        firstNode = table.at(hashValue);
        currentNode = firstNode;
    }
    else
    {
        currentNode = (*firstNode).head;
        (*currentNode).next = new Node;
        currentNode = (*currentNode).next;
    }
    (*firstNode).head = currentNode;

    (*currentNode).data = data;
}

//** Prints the whole hashtable (currently not in use because of the impracticality of the large input file)
void printHash(vector<Node *> hashTable)
{

    Node *temp;

    cout << "FINAL" << endl;
    for (int i = 0; i < hashTable.size(); i++)
    {

        temp = hashTable[i];

        if (temp)
        {
            cout << "i=" << i << endl;
            while (temp)
            {

                cout << (*temp).data.date << "-->";
                temp = (*temp).next;
            }
            cout << endl;
        }
    }
}

// ** Searches for a record's value on the hash table based on an input date
void searchHash(vector<Node *> hashTable, string inputDate)
{
    int hx = (inputDate[0] + inputDate[1] + inputDate[2] + inputDate[3] + inputDate[4] + inputDate[5] + inputDate[6] + inputDate[7] + inputDate[8] + inputDate[9]) % 11;
    Node *temp;
    int recordCounter = 0;
    if (hx <= hashTable.size())
    {

        temp = hashTable.at(hx);

        while (temp)
        {
            if ((*temp).data.date == inputDate)
            {
                cout << (recordCounter + 1) << "-->" << (*temp).data.value << endl;
                recordCounter++;
            }
            temp = (*temp).next;
        }
        if (recordCounter != 0)
            cout << "Date Found in Table " << recordCounter << " time(s)!" << endl;
        else
            cout << "Error 404: Date not Found" << endl;
    }
}

// ** Generates the hash table with the input data vector
vector<Node *> hashing(vector<Record> &data)
{

    int m_hashTableSize = data.size() * 0.75;
    int hx;
    vector<Node *> hashTable(m_hashTableSize);

    for (int i = 0; i < data.size(); i++)
    {
        hx = (data[i].date[0] + data[i].date[1] + data[i].date[2] + data[i].date[3] + data[i].date[4] + data[i].date[5] + data[i].date[6] + data[i].date[7] + data[i].date[8] + data[i].date[9]) % 11;

        pushHash(hashTable, hx, data[i]);
    }

    return hashTable;
}

// ** Deletes a record (Node) from the hastable based on an input date
void deleteHashNode(vector<Node *> &hashTable, string inputDate)
{
    int hx = (inputDate[0] + inputDate[1] + inputDate[2] + inputDate[3] + inputDate[4] + inputDate[5] + inputDate[6] + inputDate[7] + inputDate[8] + inputDate[9]) % 11;
    Node *temp;
    Node *prev;

    if (hx <= hashTable.size())
    {

        temp = prev = hashTable.at(hx);
        if (temp)
        {

            // search element is also the first element
            if ((*temp).data.date == inputDate)
            {
                // in case this list has more than one elements
                if ((*hashTable.at(hx)).next)
                    hashTable.at(hx) = (*hashTable.at(hx)).next;
                free(temp);
            }

            // search element is not the first element
            else
            {
                while ((*temp).data.date != inputDate)
                {
                    prev = temp;
                    temp = (*temp).next;
                }

                // if temp is out of the list
                if (!temp)
                {
                    (*prev).next = NULL;
                    free(temp);
                }
                // delete element in the middle of the list
                else
                {
                    (*prev).next = (*temp).next;
                    free(temp);
                }
            }
        }
    }
}

// ** Searches for a record based on a date and allows the user to change value field.
// ** The old and edited data are printed on the terminal.
void editHashNode(vector<Node *> &hashTable, string inputDate, long long newValue)
{
    int hx = (inputDate[0] + inputDate[1] + inputDate[2] + inputDate[3] + inputDate[4] + inputDate[5] + inputDate[6] + inputDate[7] + inputDate[8] + inputDate[9]) % 11;
    Node *temp;

    if (hx <= hashTable.size())
    {

        temp = hashTable.at(hx);
        if (temp)
        {
            while ((*temp).data.date != inputDate)
            {
                temp = (*temp).next;
            }

            cout << "~Old Record: ~" << endl;
            printRecord((*temp).data);

            (*temp).data.value = newValue;

            cout << "~New Record: ~" << endl;
            ;
            printRecord((*temp).data);
        }
        else
        {
            cout << "ERROR: The list you want to search on is empty..." << endl;
        }
    }
}

// ** Provides a user menu that allows only the provided options to be selected.
void menu(vector<Node *> &hashTable)
{
    int option = 0;
    string tempString;
    long long tempVal;

    while (true)
    {

        system("CLS");
        cout << "~MENU~" << endl;
        cout << "(1) Search Date" << endl
             << "(2) Edit Record" << endl
             << "(3) Delete Node" << endl
             << "(4) Exit" << endl;
        cout << "--> ";

        cin >> option;
        // Error in cin means the input isnt of int type
        if (option > 4 || option < 1 || !cin)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }
        else
            break;
    }

    system("CLS");

    switch (option)
    {
    // search
    case 1:
    {
        cout << "--SEARCH--" << endl
             << "Enter Date to Search (DD/MM/YY): ";
        cin >> tempString;
        system("CLS");
        searchHash(hashTable, tempString);
        break;
    }
    // edit
    case 2:
    {
        cout << "--EDIT--" << endl
             << "Enter Date to Edit (DD/MM/YY): ";
        cin >> tempString;
        cout << "Enter the New Value: ";
        cin >> tempVal;
        system("CLS");
        editHashNode(hashTable, tempString, tempVal);
        break;
    }
    // delete
    case 3:
    {
        cout << "--DELETE--" << endl
             << "Enter Date to Delete (DD/MM/YY): ";
        cin >> tempString;
        system("CLS");
        cout << "~BEFORE~" << endl;
        searchHash(hashTable, tempString);
        cout << endl
             << endl;
        deleteHashNode(hashTable, tempString);
        cout << "~AFTER~" << endl;
        searchHash(hashTable, tempString);
        break;
    }
    // exit
    case 4:
    {
        cout << "Exiting..." << endl;
        exit(0);
        break;
    }

    default:
        break;
    }
}

//** Function that prints the data of a record
void printRecord(Record rec)
{
    cout << "|Direction: " << rec.direction << endl;
    cout << "|Year: " << rec.year << endl;
    cout << "|Date: " << rec.date << endl;
    cout << "|Weekday: " << rec.weekday << endl;
    cout << "|Country: " << rec.country << endl;
    cout << "|Commodity: " << rec.commodity << endl;
    cout << "|Transport Mode: " << rec.transport_mode << endl;
    cout << "|Measure: " << rec.measure << endl;
    cout << "|Value: " << rec.value << endl;
    cout << "|Cumulative: " << rec.cumulative << endl
         << endl;
    ;
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

//** Examples and explanations for the hash functions

/*example:
    -searches the specific date
    -find 44 elements
    -deletes the first know elemement that corresponds to the date
    -executes search again and finds 43 elements

        cout<<"Search Date: 14/12/2021"<<endl;
        searchHash(hashTable, "14/12/2021");
        deleteHashNode(hashTable, "14/12/2021");
        searchHash(hashTable, "14/12/2021");
    */

/*example:
-searches the specific date
-date does not exist
-prints error

     cout<<"Search Date: 14/12/2023"<<endl;
     searchHash(T, "14/12/2023");

 */

/*example:
-searches the specific date
-prints the current record
-changes the value of the record
-prints the edited record

    editHashNode(hashTable, "14/12/2021", 123456);

*/

// printHash(T);
