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


// original
void csvToVector(ifstream &file, vector<Record> &Data);
void splitStringToRecordFields(stringstream &ss, Record& record);
void insertDataToField(int fieldCounter, string token, Record& record);


typedef struct node
{
   node* next=NULL;
   node* previous=NULL;
   node* head;
   Record data;
} Node;

void pushHash(vector<Node*> &table, int hashValue, Record data){
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
    

    (*currentNode).data=data;
   
}

void printHash(vector<Node*> hashTable){
       
Node* temp;

cout<<"FINAL"<<endl;
    for (int i = 0; i < hashTable.size(); i++)
    {
       
        temp=hashTable[i];

        if(temp) 
        {   
            cout<<"i="<<i<<endl;
            while(temp) {
                
                cout<<(*temp).data.date<<"-->";
                temp=(*temp).next;
                
            }
        cout<<endl;
        }
          
        
    }
    

}

void searchHash(vector<Node*> hashTable, string inputDate){
    int hx=(inputDate[0]+inputDate[1]+inputDate[2]+inputDate[3]+inputDate[4]+inputDate[5]+inputDate[6]+inputDate[7]+inputDate[8]+inputDate[9])%11;
    Node* temp;
    int recordCounter=0;
    if(hx<=hashTable.size()){

        temp=hashTable.at(hx);

         while(temp) {
                if((*temp).data.date==inputDate){
                    cout<<(recordCounter+1)<<"-->"<<(*temp).data.value<<endl;
                    recordCounter++;
                    
                }
                temp=(*temp).next;
                
            }
        if(recordCounter!=0 )cout<<"Date Found in Table "<<recordCounter<<" time(s)!"<<endl;
        else cout<<"Error 404: Date not Found"<<endl;
    }



}

vector<Node*> hashing(vector<Record> &data)
{
    
    int m_hashTableSize =data.size()*0.75;
    int hx;
    vector<Node*> hashTable(m_hashTableSize);
    
   
    cout<<hashTable.size()<<endl;
    
    cout<<data.size()<<endl<<m_hashTableSize<<endl;

   


    for (int i = 0; i < data.size(); i++)
    {
        //cout<<data[i].date<<endl;
        
        hx=(data[i].date[0]+data[i].date[1]+data[i].date[2]+data[i].date[3]+data[i].date[4]+data[i].date[5]+data[i].date[6]+data[i].date[7]+data[i].date[8]+data[i].date[9])%11;
        
       // cout<<i<<"\t"<<Hx<<"\t"<<data[i].date<<endl;
        pushHash(hashTable, hx, data[i]);
       //cout<<Hx<<endl;
    }
    
     return hashTable;
}



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


    vector<Node*> T;
    T=hashing(data2);

    cout<<"Search Date: 14/12/2021"<<endl;
    searchHash(T, "14/12/2021");

    cout<<"Search Date: 14/12/2023"<<endl;
    searchHash(T, "14/12/2023");
   // printHash(T);
    

   
 

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
