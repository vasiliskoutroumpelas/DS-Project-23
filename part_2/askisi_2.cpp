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
    int count; // counter for same Dates
    BstNode *left;
    BstNode *right;
} BstNode;


BstNode* getNewNode(Record element);
BstNode* insert(BstNode *root, Record element);
string search(BstNode *root, long int value);
void inOrderRepr(BstNode *node, vector<BstNode *> &nodes);
void inOrder(BstNode *node, vector<BstNode *> &nodes);
BstNode* sortedVectorToBST(vector<BstNode *> &nodes, int first, int last);
BstNode* makeBalancedTree(BstNode *root);

BstNode* printInOrder(BstNode *root);
long int findMin(BstNode *root);
long int findMax(BstNode *root);
BstNode* printSearchMin(BstNode *root);
BstNode* printSearchMax(BstNode *root);

int date_to_int(string date);

void csvToVector(ifstream &file, vector<Record> &Data);
void splitStringToRecordFields(stringstream &ss, Record &record);
void insertDataToField(int fieldCounter, string token, Record &record);

int main()
{
    system("clear");
    // system("CLS");

    ifstream file("data.csv");
    if (!file.good())
    {
        cout << "error" << endl;
        return -1;
    }

    vector<Record> data1;
    csvToVector(file, data1);

    BstNode *root = NULL; // Creating an empty tree


    for(Record element: data1)
    {
        root = insert(root, element);
        root = makeBalancedTree(root);
    }

    int choice=0;
    bool quit = false;
    while (!quit)
    {

        cout << "1. In Order Representaion." << endl;
        cout << "2. Search Date By Minimum Value." << endl;
        cout << "3. Search Date By Maximum Value." << endl;
        cout << "4. Exit program." << endl;
        cout << "Enter your choice (1-2)" << endl;
        cin >> choice;
        switch (choice)
        {

            case 1:
              root = printInOrder(root);
              cout << "Press Enter to return to menu..." << endl;
              cin.ignore();
              cin.get();
              break;

            case 2:
              root = printSearchMin(root);
              cout << "Press Enter to return to menu..." << endl;
              cin.ignore();
              cin.get();
              break;

            case 3:
              root = printSearchMax(root);
              cout << "Press Enter to return to menu..." << endl;
              cin.ignore();
              cin.get();
              break;

            case 4:
                quit = true;
                break;
            default:
                break;
        }
    }
    cout << "Exit...Zzz" << endl;

    return 0;
}


BstNode* getNewNode(Record element)
{

    BstNode *newNode = new BstNode();
    newNode->element = element;
    newNode->left = newNode->right = NULL;
    newNode->count = 1; // set counter for same dates as 1
    return newNode;
}

BstNode* insert(BstNode *root, Record element)
{

    if (root == NULL)
    {

        // empty tree
        root = getNewNode(element);
    }
    if (element.value == root->element.value)
    {

        (root->count)++; // counter for the same Dates!!!
        return root;
    }
    if (element.value < root->element.value)
    {

        root->left = insert(root->left, element);
    }
    else
    {

        root->right = insert(root->right, element);
    }
    return root;
}

string search(BstNode *root, long int value)
{
    if (root == NULL){
        string emptystring = " ";
        return emptystring;
      }

    else if (root->element.value == value)
        return root->element.date;

    else if (value <= root->element.value)
        return search(root->left, value);

    else
        return search(root->right, value);
}

/* Function to traverse the skewed binary tree in-order and
   store its node pointers in vector nodes[] */

void inOrderRepr(BstNode *node, vector<BstNode *> &nodes)
{
    if (node == NULL)
    {
        return;
    }
    inOrderRepr(node->left, nodes);
    nodes.push_back(node);
    cout << node->element.value << " ( " << node->count << " ) "
         << " | " << node->element.date << endl; // code for inorder traversal representation
    inOrderRepr(node->right, nodes);
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



BstNode* printSearchMin(BstNode *root)
{
    // Code For Searching Date by Minimum Value

    long int min = findMin(root);
    cout << "Minimum value is " << min << endl;
    cout << "Corresponding Date is: " << search(root, min) << endl;
    return root;
}


BstNode* printSearchMax(BstNode *root)
{
    // Code For Searching Date by Maximum Value

    long int max = findMax(root);
    cout << "Maximum value is " << max << endl;
    cout << "Corresponding Date is: " << search(root, max) << endl;
    return root;
}

BstNode* printInOrder(BstNode *root)
{
    // Code For Inorder Traversal Representation

    cout << "Inorder Traversal Represantation is: " << endl;
    cout << "Date       |     Value" << endl << endl;
    vector<BstNode *> sortednodes;
    inOrderRepr(root, sortednodes);
    return root;
}

//Function that returns the minimum value of the BST tree
long int findMin(BstNode *root)
{

  vector<BstNode *> sortednodes;    //vector to store sorted values after inorder traversal
  inOrder(root, sortednodes);
  return sortednodes.at(0)->element.value;   //the value at first index of vector is the smallest
}


//Function that returns the maximum value of the BST tree
long int findMax(BstNode *root)
{

  vector<BstNode *> sortednodes;    //vector to store sorted values after inorder traversal
  inOrder(root, sortednodes);
  return sortednodes.at(sortednodes.size()-1)->element.value;         //the value at last index of vector is the largest
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
