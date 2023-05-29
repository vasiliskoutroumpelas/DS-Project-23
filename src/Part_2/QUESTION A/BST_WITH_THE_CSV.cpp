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



typedef struct BstNode{
    string date;
    long int value;
    BstNode* left;
    BstNode* right;
}BstNode;


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

void inOrderRepr(BstNode* node, vector<BstNode*> &nodes)
{
    if (node == NULL){
        return;
    }
    inOrderRepr(node->left, nodes);
    nodes.push_back(node);
    inOrderRepr(node->right, nodes);


    for(int i=0; i<nodes.size(); i++){                                     //Code For Inorder Traversal Representation (start)

        cout << nodes.at(i)->date << " | " << nodes.at(i)->value <<endl;

    }                                                                     //Code For Inorder Traversal Representation (end)
}



/* Function to traverse the skewed binary tree in-order and
   store its node pointers in vector nodes[] AND ALSO PRINT THE ELEMENTS OF THAT VECTOR  */

void inOrder(BstNode* node, vector<BstNode*> &nodes)
{
    if (node == NULL){
        return;
    }
    inOrder(node->left, nodes);
    nodes.push_back(node);
    inOrder(node->right, nodes);
}



/* A function that constructs Balanced
Binary Search Tree from a sorted vector */
BstNode* sortedVectorToBST(vector<BstNode*> &nodes, int first, int last)
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
    return root->value;                       //to check if the change was successful or not

  }
  else if(date_to_int(date) <= date_to_int(root->date)) return changeValueByDate(root->left, date, new_value);
  else return changeValueByDate(root->right, date, new_value);

}



BstNode* deleteByDate(BstNode* root, string date){

    // Base Case
    if(root == NULL) return root;

    if(date_to_int(date) < date_to_int(root->date)) return deleteByDate(root->left, date);

    else if(date_to_int(date) > date_to_int(root->date)) return deleteByDate(root->right, date);

    else if (date_to_int(root->date) == date_to_int(date)){

          // case 1: node to be deleted has no children (aka is a leaf node)
          if (root->left == NULL && root->right == NULL){
            return NULL;
          }
          // case 2: node to be deleted has one right child (or no child)
          else if(root->left == NULL){
            BstNode* temp = root->right;
            delete root;
            return temp;
          }

          // case 3: node to be deleted has one left child (or no child)
          else if (root->right == NULL){
            BstNode * temp = root->left;
            delete root;
            return temp;
          }


          // case 4:  node to be deleted has two children
          else {

            // find the minimum value in the right subtree
            BstNode* min_right_subtree ;
            BstNode* current = root->right;
            while (current->left != NULL)
            {
              current = current->left;
            }
            min_right_subtree = current;

            // switch the values
            root->date = min_right_subtree->date;
            root->value = min_right_subtree->value;

            // Delete the node, with the corresponding date the user entered, now as a leaf node
            root->right = deleteByDate(root->right, min_right_subtree->date);
          }


    }
    return root;
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

    int n = data1.size()
    for(int i=0; i<n; i++){                                                            //  for(Record element: data1){

        root = Insert(root, data1.at(i).date, data1.at(i).value);                      //          root = Insert(root, element.date, element.value);
                                                                                        
    }                                                                                  //  }
   


//Code For Inorder Traversal Representation

  cout << "Inorder Traversal Represantation is: " << endl;
  cout<< "Date       |     Value" << endl << endl;
  root = makeBalancedTree(root);
  vector<BstNode*> sortednodes;
  inOrderRepr(root, sortednodes);

//Code For Searching by Date

  string date;
  cout << "Enter date to be searched\n";
  cin >> date;
  if (Search(root,date) == -1) cout << "Empty tree or Date Not Found." << endl;
  else cout << "Corresponding Value is: " << Search(root,date) << endl;



//Code For Changing Value by Date

  string Date;
  cout << "Enter the Date whose Value you want to change: " << endl;
  cin >> Date;
  int new_value;
  cout << "Enter the new Value: "<< endl;
  cin >> new_value;
  int result1 = changeValueByDate(root, date, new_value);

  if(result1 == -1) cout << "Empty tree or Date Not Found." << endl;
  else cout << "Value " << result1 << " is now the new Value for Date " << Date << endl;


//Code For Deleting struct of corresponding date

string Date2;          // i name it that way to be different from 'date' and 'Date' string variables above
cout << "Enter the Date of the entry you want to delete: " << endl;
cin >> Date2;
root = deleteByDate(root, Date2);

// rebalancing the BST after deletion
root = makeBalancedTree(root);
cout << "Entry with Date " << Date2 << " has been successfully deleted." << endl << endl;

// Doing Inorder Traversal to see the resulted balanced BST after deletion
cout << "InOrder Traversal After Deletion: " << endl;
vector<BstNode*> nodes;
inOrderRepr(root, nodes);




return 0;
}
