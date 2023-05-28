#include <bits/stdc++.h>

using namespace std;

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

typedef struct BstNode
{
    Record element;
    BstNode *left;
    BstNode *right;
} BstNode;

typedef struct node
{
   node* next=NULL;
   node* head;
   Record data;
} Node;

// ASKISI A
BstNode* getNewNode(Record element);
BstNode* insert(BstNode *root, Record element);
int search(BstNode *root, string date);
void inOrderRepr(BstNode *node);
void inOrder(BstNode *node, vector<BstNode *> &nodes);
BstNode* sortedVectorToBST(vector<BstNode *> &nodes, int first, int last);
BstNode* makeBalancedTree(BstNode *root);
int changeValueByDate(BstNode *root, string date, int new_value);
BstNode* deleteByDate(BstNode *root, string date);

BstNode* printInOrder(BstNode *root);
BstNode* printSearch(BstNode *root);
BstNode* printChangeValue(BstNode *root);
BstNode* printDelete(BstNode *root);

// ASKISI C
void printRecord(Record rec);
void pushHash(vector<Node*> &table, int hashValue, Record data);
void printHash(vector<Node*> hashTable);
void searchHash(vector<Node*> hashTable, string inputDate);
vector<Node*> hashing(vector<Record> &data);
void deleteHashNode(vector<Node*> &hashTable, string inputDate);
void editHashNode(vector<Node*> &hashTable, string inputDate, long int newValue);
void hashMenu(vector<Node*> &hashTable);
void printRecord(Record rec);

// COMMON
int date_to_int(string date);

void csvToVector(ifstream &file, vector<Record> &Data);
void splitStringToRecordFields(stringstream &ss, Record &record);
void insertDataToField(int fieldCounter, string token, Record &record);

int main()
{
   // system("clear");
    
    ifstream file("data.csv");
    if (!file.good())
    {
        cout << "error" << endl;
        return -1;
    }

    vector<Record> data;
    csvToVector(file, data);


    
    return 0;
}

BstNode* getNewNode(Record element)
{

    BstNode *newNode = new BstNode();
    newNode->element = element;
    newNode->left = newNode->right = NULL;
    return newNode;
}

BstNode* insert(BstNode *root, Record element)
{

    if (root == NULL)
    {

        // empty tree
        root = getNewNode(element);
    }
    if (date_to_int(element.date) == date_to_int(root->element.date))
    {

        return root;
    }
    if (date_to_int(element.date) < date_to_int(root->element.date))
    {

        root->left = insert(root->left, element);
    }
    else
    {

        root->right = insert(root->right, element);
    }
    return root;
}

int search(BstNode *root, string date)
{
    if (root == NULL)
        return -1;

    else if (date_to_int(root->element.date) == date_to_int(date))
        return root->element.value;
        
    else if (date_to_int(date) <= date_to_int(root->element.date))
        return search(root->left, date);

    else
        return search(root->right, date);
}

/* Function to traverse the skewed binary tree in-order and
   store its node pointers in vector nodes[] */

void inOrderRepr(BstNode *node)
{
    if (node == NULL)
    {
        return;
    }
    inOrderRepr(node->left);
    cout << node->element.date << " | " << node->element.value << endl; // code for inorder traversal representation
    inOrderRepr(node->right);
}

/* Function to traverse the skewed binary tree in-order and
   store its node pointers in vector nodes[] AND ALSO PRINT THE ELEMENTS OF THAT VECTOR  */

void inOrder(BstNode *node, vector<BstNode *> &nodes)
{
    if (node == NULL)
    {
        return;
    }
    inOrder(node->left, nodes);
    nodes.push_back(node);
    inOrder(node->right, nodes);
}

/* A function that constructs Balanced
Binary search Tree from a sorted vector */
BstNode* sortedVectorToBST(vector<BstNode *> &nodes, int first, int last)
{
    // Base Case
    if (first > last)
        return NULL;

    // Get the middle element and make it root
    int mid = (first + last) / 2;
    BstNode *root = nodes[mid];

    /* Recursively construct the left subtree
    and make it left child of root */
    root->left = sortedVectorToBST(nodes, first, mid - 1);

    /* Recursively construct the right subtree
    and make it right child of root */
    root->right = sortedVectorToBST(nodes, mid + 1, last);

    return root;
}

BstNode* makeBalancedTree(BstNode *root)
{
    // Store nodes of given BST in sorted order
    vector<BstNode *> nodes;
    inOrder(root, nodes);

    // Constructs BST from nodes[] vector
    int n = nodes.size();
    return sortedVectorToBST(nodes, 0, n - 1);
}

int changeValueByDate(BstNode *root, string date, int new_value)
{
    if (root == NULL)
        return -1;

    else if (date_to_int(root->element.date) == date_to_int(date))
    {
        root->element.value = new_value;
        return root->element.value; // to check if the change was successful or not
    }

    else if (date_to_int(date) <= date_to_int(root->element.date))
        return changeValueByDate(root->left, date, new_value);
    
    else
        return changeValueByDate(root->right, date, new_value);
}

BstNode* deleteByDate(BstNode *root, string date)
{
    // Base Case
    if (root == NULL)
        return root;

    if (date_to_int(date) < date_to_int(root->element.date))
        root->left = deleteByDate(root->left, date);

    else if (date_to_int(date) > date_to_int(root->element.date))
        root->right = deleteByDate(root->right, date);

    // Case: Date is same as root's date
    else
    {

        // case 1: node to be deleted has no children (aka is a leaf node)
        if (root->left == NULL && root->right == NULL)
        {
            return NULL;
        }

        // case 2: node to be deleted has one right child (or no child)
        else if (root->left == NULL)
        {
            BstNode *temp = root->right;
            delete root;
            return temp;
        }

        // case 3: node to be deleted has one left child (or no child)
        else if (root->right == NULL)
        {
            BstNode *temp = root->left;
            delete root;
            return temp;
        }

        // case 4:  node to be deleted has two children
        else
        {

            // find the minimum value in the right subtree
            BstNode *min_right_subtree;
            BstNode *current = root->right;
            while (current->left != NULL)
            {
                current = current->left;
            }
            min_right_subtree = current;

            // switch the values
            root->element = min_right_subtree->element;

            // Delete the node, with the corresponding date the user entered, now as a leaf node
            root->right = deleteByDate(root->right, min_right_subtree->element.date);
        }
    }
    return root;
}


BstNode* printInOrder(BstNode *root)
{
    // Code For Inorder Traversal Representation

    cout << "Inorder Traversal Represantation is: " << endl;
    cout << "Date       |     Value" << endl << endl;
    vector<BstNode *> sortednodes;
    inOrderRepr(root);
    return root;
}

BstNode* printSearch(BstNode *root)
{
    // Code For Searching by Date

    string date;
    cout << "Enter date to be searched\n";
    cin >> date;
    if (search(root, date) == -1)
        cout << "Empty tree or Date Not Found." << endl;
    else
        cout << "Corresponding Value is: " << search(root, date) << endl;
    return root;
}

BstNode* printChangeValue(BstNode *root)
{
    // Code For Changing Value by Date

    string date;
    cout << "Enter the Date whose Value you want to change: " << endl;
    cin >> date;
    int new_value;
    cout << "Enter the new Value: " << endl;
    cin >> new_value;
    int result1 = changeValueByDate(root, date, new_value);

    if (result1 == -1)
        cout << "Empty tree or Date Not Found." << endl;
    else
    {
        cout << "Value " << result1 << " is now the new Value for Date " << date << endl;
        vector<BstNode*> nodes1;
        inOrderRepr(root); // for the user to see the actual change
    }
    return root;
}

BstNode* printDelete(BstNode *root)
{
    // Code For Deleting struct of corresponding date

    string date; // i name it that way to be different from 'date' and 'Date' string variables above
    cout << "Enter the Date of the entry you want to delete: " << endl;
    cin >> date;
    root = deleteByDate(root, date);

    // rebalancing the BST after deletion
    root = makeBalancedTree(root);
    cout << "Entry with Date " << date << " has been successfully deleted." << endl
         << endl;

    // Doing Inorder Traversal to see the resulted balanced BST after deletion
    cout << "InOrder Traversal After Deletion: " << endl;
    vector<BstNode *> nodes2;
    inOrderRepr(root);
    return root;
}

//** Adds a new Node(Record) to the hashtable in its respective position
void pushHash(vector<Node*> &table, int hashValue, Record data){
   Node* firstNode=table.at(hashValue);
   Node* currentNode;

//first element knows the last

    if(!firstNode){
        table.at(hashValue)=new Node;
        firstNode=table.at(hashValue);
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


//** Prints the whole hashtable (currently not in use because of the impracticality of the large input file)
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


// ** Searches for a record's value on the hash table based on an input date 
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

// ** Generates the hash table with the input data vector
vector<Node*> hashing(vector<Record> &data)
{
    
    int m_hashTableSize =data.size()*0.75;
    int hx;
    vector<Node*> hashTable(m_hashTableSize);

    for (int i = 0; i < data.size(); i++)
    {   
        hx=(data[i].date[0]+data[i].date[1]+data[i].date[2]+data[i].date[3]+data[i].date[4]+data[i].date[5]+data[i].date[6]+data[i].date[7]+data[i].date[8]+data[i].date[9])%11;
        
        pushHash(hashTable, hx, data[i]);
    }
    
     return hashTable;
}

// ** Deletes a record (Node) from the hastable based on an input date
void deleteHashNode(vector<Node*> &hashTable, string inputDate){
       int hx=(inputDate[0]+inputDate[1]+inputDate[2]+inputDate[3]+inputDate[4]+inputDate[5]+inputDate[6]+inputDate[7]+inputDate[8]+inputDate[9])%11;
    Node* temp;
    Node* prev;



    if(hx<=hashTable.size()){

        temp=prev=hashTable.at(hx);
        if(temp){

            //search element is also the first element
            if((*temp).data.date==inputDate) {
                //in case this list has more than one elements
                if((*hashTable.at(hx)).next) hashTable.at(hx)=(*hashTable.at(hx)).next;
                free(temp);
            }

            //search element is not the first element
            else{
                while((*temp).data.date!=inputDate) { 
                        prev=temp;
                        temp=(*temp).next;
                    }

                //if temp is out of the list
                if(!temp){
                    (*prev).next=NULL;
                    free(temp);
                }
                //delete element in the middle of the list
                else{
                    (*prev).next=(*temp).next;
                    free(temp);
                }
            }
        }
    }
}

// ** Searches for a record based on a date and allows the user to change value field.
// ** The old and edited data are printed on the terminal.
void editHashNode(vector<Node*> &hashTable, string inputDate, long int newValue){
       int hx=(inputDate[0]+inputDate[1]+inputDate[2]+inputDate[3]+inputDate[4]+inputDate[5]+inputDate[6]+inputDate[7]+inputDate[8]+inputDate[9])%11;
    Node* temp;
    
    if(hx<=hashTable.size()){

        temp=hashTable.at(hx);
        if(temp){
            while((*temp).data.date!=inputDate){
                temp=(*temp).next;
            }

            cout<<"~Old Record: ~"<<endl;
            printRecord((*temp).data);

            (*temp).data.value=newValue;

             cout<<"~New Record: ~"<<endl;;
            printRecord((*temp).data);
        }else{
            cout<<"ERROR: The list you want to search on is empty..."<<endl;
        }
    }
}

// ** Provides a user hashMenu that allows only the provided options to be selected.
void hashMenu(vector<Node*> &hashTable){
    int option=0;
    string tempString;
    long int tempVal;

    while(true){
        
            system("CLS");
            cout<<"~MENU~"<<endl;
            cout<<"(1) Search Date"<<endl<<"(2) Edit Record"<<endl<<"(3) Delete Node"<<endl<<"(4) Exit"<<endl;
            cout<<"--> ";

        cin>>option;
        //Error in cin means the input isnt of int type
        if(option>4 || option<1 || !cin){      
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
           
            continue;
        }else break;
    }


    system("CLS");

    switch (option)
    {
    //search
    case 1:{ cout<<"--SEARCH--"<<endl<<"Enter Date to Search (DD/MM/YY): "; cin>>tempString; system("CLS"); searchHash(hashTable, tempString); break;}
    //edit
    case 2:{ cout<<"--EDIT--"<<endl<<"Enter Date to Edit (DD/MM/YY): "; cin>>tempString; cout<<"Enter the New Value: "; cin>>tempVal; system("CLS"); editHashNode(hashTable, tempString, tempVal); break;}
    //delete
    case 3:{cout<<"--DELETE--"<<endl<<"Enter Date to Delete (DD/MM/YY): "; cin>>tempString;  system("CLS"); cout<<"~BEFORE~"<<endl; searchHash(hashTable, tempString); cout<<endl<<endl; deleteHashNode(hashTable, tempString); cout<<"~AFTER~"<<endl; searchHash(hashTable, tempString); break;}
    //exit
    case 4:{ cout<<"Exiting..."<<endl; exit(0); break;}
    
    default:
        break;
    }

}

//** Function that prints the data of a record
void printRecord(Record rec){
    cout<<"|Direction: "<<rec.direction<<endl;
    cout<<"|Year: "<<rec.year<<endl;
    cout<<"|Date: "<<rec.date<<endl;
    cout<<"|Weekday: "<<rec.weekday<<endl;
    cout<<"|Country: "<<rec.country<<endl;
    cout<<"|Commodity: "<<rec.commodity<<endl;
    cout<<"|Transport Mode: "<<rec.transport_mode<<endl;
    cout<<"|Measure: "<<rec.measure<<endl;
    cout<<"|Value: "<<rec.value<<endl;
    cout<<"|Cumulative: "<<rec.cumulative<<endl<<endl;;
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
