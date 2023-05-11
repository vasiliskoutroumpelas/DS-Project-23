/*леходос дглиоуяциас BALANCED BST:


1) дглиоуяциа емос (SKEWD/UNBALANCED) BST ле диадовийа INSERT().
2) ежаялоцг акцояихлоу емдодиатангс (INORDER) сто паяапамы демтяо йаи апохгйеусг тым (ПКщОМ sorted) тилым се ема диамусла VECTOR[]
3) ауто то SORTED VECTOR еисацетаи ыс паяалетяос се лиа сумаятгсг г опоиа то вягсилопоиеи циа ма йатасйеуасеи ема BALANCED BST TREE.


  кептолеяеиа укопоигсгс лоу:  ╪МТЫР ТЯщВЕИ ТщКЕИА ЙАИ ЙАТСЙЕУэФЕТАИ щМА balanced BST, ТО ОПОъО ЕъМАИ RIGHT !!! balanced. аУТЭ СГЛАъМЕИ ЭТИ
  ТА ЖЩККА ДИАТэССОМТАИ ЛЕ ПЯОТЕЯАИЭТГТА ПЯОР ТГ ДЕНИэ ЛЕЯИэ.


*/


#include <iostream>
#include <vector>

using namespace std;


struct BstNode{

    int data;
    BstNode* left;
    BstNode* right;


};


BstNode* GetNewNode(int data){

    BstNode* newNode = new BstNode();
    newNode->data = data;
    newNode->left = newNode -> right = NULL;
    return newNode;

}


BstNode* Insert(BstNode* root, int data){

    if(root == NULL){

        //empty tree
        root = GetNewNode(data);
    }
    else if(data <= root->data){

        root->left = Insert(root->left, data);
    }
    else{

        root->right = Insert(root->right, data);
    }
    return root;
}


bool Search(BstNode* root, int data){

    if(root == NULL) return false;
    else if(root->data == data) return true;
    else if(data <= root->data) return Search(root->left,data);
    else return Search(root->right,data);


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



/* Function to do preorder traversal of tree */
void preOrder(BstNode* node)
{
    if (node == NULL)
        return;
    printf("%d ", node->data);
    preOrder(node->left);
    preOrder(node->right);
}


int main(){
BstNode* root = NULL;   //Creating an empty tree
root = Insert(root,10);
root = Insert(root,9);
root = Insert(root,8);
root = Insert(root,7);
root = Insert(root,6);
root = Insert(root,5);



int number;
cout << "Enter number to be searched\n";
cin >> number;
if(Search(root,number) == true) cout << "Number Found\n";
else cout << "Number Not Found\n";



root = makeBalancedTree(root);


//printing the BALANCED BST TO TEST IF ALGORITHM WORKS
printf("%d ", root->data);
printf("%d ", root->left->data);
printf("%d ", root->right->data);
printf("%d ", root->left->right->data);
printf("%d ", root->right->left->data);
printf("%d ", root->right->right->data);





return 0;

}










