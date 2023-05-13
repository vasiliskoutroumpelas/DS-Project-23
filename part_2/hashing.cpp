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

// sioutas slides
void mergeValues(vector<Record> &data, int left, int middle, int right);
void mergeSortValues(vector<Record> &data, int left, int right);

// tsakalidis and internet
int findMaxValue(vector<Record> &array);
void countingSortValues(vector<Record> &array, int range);

bool areSortedValues(vector<Record> &vector);

// original
void csvToVector(ifstream &file, vector<Record> &Data);
void splitStringToRecordFields(stringstream &ss, Record& record);
void insertDataToField(int fieldCounter, string token, Record& record);


typedef struct node
{
   node* next=NULL;
   node* previous=NULL;
   node* head;
   int data;
} Node;

void pushHash(vector<Node*> &table, int hashValue, int initValue){
   Node* firstNode=table.at(hashValue);
   Node* currentNode;
   
   

//first element knows the last

   

    if(!firstNode){
        table.at(hashValue)=new Node;
        firstNode=table.at(hashValue);
       // firstNode=new Node;
        currentNode=firstNode;
    }
    else{
         currentNode= (*firstNode).head;
        (*currentNode).next=new Node;
        currentNode=(*currentNode).next;
    }
        (*firstNode).head=currentNode;
    

    (*currentNode).data=initValue;
   
}

void hashing(vector<Record> &data)
{
    
    int m_hashTableSize =data.size()*0.75;
    int Hx;
    vector<Node*> T(m_hashTableSize);
    
   
    cout<<T.size()<<endl;
    
    cout<<data.size()<<endl<<m_hashTableSize<<endl;

   


    for (int i = 0; i < data.size(); i++)
    {
        Hx=data[i].date[0]+data[i].date[1]+data[i].date[2]+data[i].date[3]+data[i].date[4]+data[i].date[5]+data[i].date[6]+data[i].date[7]+data[i].date[8]+data[i].date[9];
        cout<<Hx<<endl;
    }
    

}


int main()
{
   // system("clear");
    
    // ifstream file("data.csv");
    // if (!file.good())
    // {
    //     cout << "error" << endl;
    //     return -1;
    // }

    // vector<Record> data1, data2;
    // csvToVector(file, data1);
    // data2 = data1;

    // hashing(data2);

    vector<Node*>table(3);
    int S[]={1, 3, 4, 7, 10, 17, 21};
    int hx[]={1,0,1,1,1,2,0};


    for (int i = 0; i < 7; i++)
   {
        cout<<S[i]<<"\t";
   }
   cout<<endl;
   for (int i = 0; i < 7; i++)
   {
     cout<<hx[i]<<"\t";
   }
   cout<<endl;


    for (int i = 0; i < 7; i++)
    {
        pushHash(table, hx[i], S[i]);
    }
    
Node* temp;

cout<<"FINAL"<<endl;
    for (int i = 0; i < table.size(); i++)
    {
        cout<<"i="<<i<<endl;
        temp=table[i];


        cout<<(*temp).data<<"\t";
        do{
            temp=(*temp).next;
            cout<<(*temp).data<<"\t";
            
        }while((*temp).next);
        cout<<endl;
    }
    


    return 0;
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
