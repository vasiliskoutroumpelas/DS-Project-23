#include <iostream>
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


// original
void csvToVector(ifstream &file, vector<Record> &Data);
void splitStringToRecordFields(stringstream &ss, Record& record);
void insertDataToField(int fieldCounter, string token, Record& record);



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



struct BstNode{

    string date;
    long int value;
    BstNode* left;
    BstNode* right;


};


BstNode* GetNewNode(string date, long int value){

    BstNode* newNode = new BstNode();
    newNode->date = date;
    newNode->value = value;
    newNode->left = newNode -> right = NULL;
    return newNode;

}


BstNode* Insert(BstNode* root, string date, long int value){

    if(root == NULL){

        //empty tree
        root = GetNewNode(date, value);
    }
    else if(date_to_int(date) <= date_to_int(root->date)){

        root->left = Insert(root->left, date, value);
    }
    else{

        root->right = Insert(root->right, date, value);
    }
    return root;
}


int Search(BstNode* root, string date){

    if(root == NULL) return -1;
    else if(date_to_int(root->date) == date_to_int(date)) return root->value;
    else if(date_to_int(date) <= date_to_int(root->date)) return Search(root->left,date);
    else return Search(root->right,date);


}



/* Function to traverse the skewed binary tree in-order and
   store its node pointers in vector nodes[] */

void inOrder(BstNode* node, vector<BstNode*> &nodes)
{
    if (node == NULL){
        return;
    }
    inOrder(node->left, nodes);
    nodes.push_back(node);
    inOrder(node->right, nodes);


    for(int i=0; i<nodes.size(); i++){                                     //Code For Inorder Traversal Representation (start)

        cout << nodes.at(i)->date << " | " << nodes.at(i)->value <<endl;

    }                                                                     //Code For Inorder Traversal Representation (end)
}


/* A function that constructs Balanced
Binary Search Tree from a sorted vector */
BstNode* sortedVectorToBST(vector<BstNode*> &nodes, int first, int last)
{
    /* Base Case */
    if (first > last)
        return NULL;

    /* Get the middle element and make it root */
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

BstNode* makeBalancedTree(BstNode* root){

    // Store nodes of given BST in sorted order
    vector<BstNode*> nodes;
    inOrder(root, nodes);

    // Constructs BST from nodes[] vector
    int n = nodes.size();
    return sortedVectorToBST(nodes, 0, n-1);
}


int changeValueByDate(BstNode* root, string date, int new_value){

  if(root == NULL) return -1;
  else if(date_to_int(root->date) == date_to_int(date)){
    root->value = new_value;
    return root->value;         //to check if the change was successful or not
  }
  else if(date_to_int(date) <= date_to_int(root->date)) return changeValueByDate(root->left, date, new_value);
  else return changeValueByDate(root->right, date, new_value);

}




int main(){

    //system("clear");
    system("CLS");

    ifstream file("data.csv");
    if (!file.good())
    {
        cout << "error" << endl;
        return -1;
    }

    vector<Record> data1, data2;
    csvToVector(file, data1);
    data2 = data1;




    BstNode* root = NULL;   //Creating an empty tree

    for(int i=0; i<data1.size(); i++){

        root = Insert(root, data1.at(i).date, data1.at(i).value);

    }


//Code For Inorder Traversal Representation

  cout << "Inorder Traversal Represantation is: " << endl;
  cout<< "Date       |     Value" << endl << endl;
  root = makeBalancedTree(root);

//Code For Searching by Date

  string date;
  cout << "Enter date to be searched\n";
  cin >> date;
  if (Search(root,date) == -1) cout << "Empty tree." << endl;
  else cout << "Corresponding Value is: " << Search(root,date) <<endl;



//Code For Changing Value by Date

  string Date;
  cout << "Enter the Date whose Value you want to change: " << endl;
  cin >> Date;
  int new_value;
  cout << "Enter the new Value: "<< endl;
  cin >> new_value;
  int result = changeValueByDate(root, date, new_value);

  if(result == -1) cout << "Empty tree." << endl;
  else cout << "Value " << result << " inserted succesfully." << endl;


//Code For Deleting struct of corresponding date




    return 0;
}
