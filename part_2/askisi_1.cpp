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
int search(BstNode *root, string date);
void inOrderRepr(BstNode *node, vector<BstNode *> &nodes);
void inOrder(BstNode *node, vector<BstNode *> &nodes);
BstNode* sortedVectorToBST(vector<BstNode *> &nodes, int first, int last);
BstNode* makeBalancedTree(BstNode *root);
int changeValueByDate(BstNode *root, string date, int new_value);
BstNode* deleteByDate(BstNode *root, string date);

BstNode* printInOrder(BstNode *root);
BstNode* printSearch(BstNode *root);
BstNode* printChangeValue(BstNode *root);
BstNode* printDelete(BstNode *root);

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
        cout << "2. Search value by date." << endl;
        cout << "3. Change value that matches a date." << endl;
        cout << "4. Delete a record that matches a date." << endl;
        cout << "5. Exit program." << endl;
        cout << "Enter your choice (1-5)" << endl;
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
                root = printSearch(root);
                cout << "Press Enter to return to menu..." << endl;
                cin.ignore();
                cin.get();
                break;
            case 3:
                root = printChangeValue(root); 
                cout << "Press Enter to return to menu..." << endl;
                cin.ignore();
                cin.get();
                break;
            case 4:
                root = printDelete(root);
                cout << "Press Enter to return to menu..." << endl;
                cin.ignore();
                cin.get();
                break;
            case 5:
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

void inOrderRepr(BstNode *node, vector<BstNode *> &nodes)
{
    if (node == NULL)
    {
        return;
    }
    inOrderRepr(node->left, nodes);
    nodes.push_back(node);
    cout << node->element.date << " | " << node->element.value << endl; // code for inorder traversal representation
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

            min_right_subtree->count = 0; // set counter equal to 0

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
    inOrderRepr(root, sortednodes);
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
        inOrderRepr(root, nodes1); // for the user to see the actual change
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
    inOrderRepr(root, nodes2);
    return root;
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
