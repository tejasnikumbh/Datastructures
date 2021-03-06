/*
 * File : question4.cpp (AVL Binary Search Tree with Lazy Deletion)
 * ------------------------------------------------------------------------------
 * The file implements the balanced version of the binary search tree which uses
 * the AVL algorithm for balancing. The paradigm is procedures and there are various
 * procedures for insertion , finding ,deletion etc.For deletion, this implementation
 * uses a lazy delete strategy.
 * Programming Paradigm : Procedural.
 */

/* Including standard libraries */
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <deque>
using namespace std;

/* Type definitions */
  struct BSTNode{
    int key;
    int bf;
    bool isDeleted;
    BSTNode* parent;
    BSTNode* left;
    BSTNode* right;
  };

/* Global variables and constants*/

  //Maximum no of elements that can be marked for lazy deletion
  const int LAZY_DEL_CAPACITY = 5;
  //Queue to hold the variables marked as delete for lazy deletion.
  deque<BSTNode* > deleteDeque;

/* Function prototypes */
void insertNode(BSTNode* &tree,const int &key);
int insertAVL(BSTNode* parent,BSTNode* &tree, const int &key);
  void fixLeftImbalance(BSTNode* &tree);
  void fixRightImbalance(BSTNode* &tree);
  void rotateLeft(BSTNode* &tree);
  void rotateRight(BSTNode* &tree);

int height(BSTNode *tree);
bool isBalanced(BSTNode *tree);
bool isBST(BSTNode *tree);
BSTNode *findNode(BSTNode* &tree, const int &key);
void displayTree(BSTNode* tree);
void displayDeleteDeque();
void drawLine();

void removeNode(BSTNode* &tree,const int &key);
void removeAVL(BSTNode* &tree,BSTNode* nodeToDelete);
void removeAVLLazy(BSTNode* &tree,BSTNode* nodeToDelete);
  void copyNode(BSTNode* nodeToCopyInto,BSTNode* nodeToDelete);
  BSTNode* findSuccessorInLeftSubtree(BSTNode* tree);
  void fixImbalance(BSTNode* &tree,BSTNode* start);

/* The main program */
int main(){

  //Introduction
  cout<<"****Program to test procedures on Balanced AVL Binary Search tree with Lazy Deletion****"<<endl;

  //Initializing the AVL BST.
  cout<<"Initializing tree with numbers from 1 to 20..."<<endl;
  BSTNode* root = NULL;
  for(int i=1;i<=20;i++){
    insertNode(root,i);
  }

  drawLine();
  cout<<"Tree structure in memory after - initialization"<<endl;
  // Displaying the in-order traversal of the tree
  displayDeleteDeque();
  displayTree(root);


  drawLine();
  cout<<"Tree structure in memory after - Deleting 3,4,8,9"<<endl;
  //Deleting 3,4,8,9
  removeNode(root,3);
  removeNode(root,4);
  removeNode(root,8);
  removeNode(root,9);

  //Displaying in order traversal of the tree.
  displayDeleteDeque();
  displayTree(root);

  drawLine();
  cout<<"Tree structure in memory after -Inserting 21,22,8"<<endl;
  //Inserting 21,22,8
  insertNode(root,21);
  insertNode(root,22);
  insertNode(root,8);

  //Displaying in order traversal of the tree.
  displayDeleteDeque();
  displayTree(root);

  drawLine();
  cout<<"Tree structure in memory after -Deleting 10,12,14"<<endl;
  //Deleting 10,12,14
  removeNode(root,10);
  removeNode(root,12);
  removeNode(root,14);

  //Displaying in order traversal of the tree.
  displayDeleteDeque();
  displayTree(root);

  drawLine();
  cout<<"Tree structure in memory after -Inserting 23,24"<<endl;
  //Inserting 23,24
  insertNode(root,23);
  insertNode(root,24);

  //Displaying in order traversal of the tree.
  displayDeleteDeque();
  displayTree(root);

  drawLine();
  cout<<"Tree structure in memory after -Deleting 23,24,8"<<endl;
  //Deleting 23,24,8
  removeNode(root,23);
  removeNode(root,24);
  removeNode(root,8);

  //Displaying in order traversal of the tree.
  displayDeleteDeque();
  displayTree(root);

  drawLine();
  cout<<"Tree structure in memory after -Inserting 24,25"<<endl;
  //Inserting 23,24
  insertNode(root,24);
  insertNode(root,25);

  //Displaying in order traversal of the tree.
  displayDeleteDeque();
  displayTree(root);

    return 0;
  }

/*
 * Function : insertNode
 * ------------------------------
 * Wrapper function to insertAVL
 */

  void insertNode(BSTNode* &tree,const int &key){
    bool lazilyDeleted =false;
    BSTNode* node= NULL;
    deque<BSTNode*> newdeque;
    for(int i=0;i<deleteDeque.size();i++){
      if(deleteDeque[i]->key==key){
        //Condition is set true if the node is already in tree but just marked deleted.
        lazilyDeleted=true;
        node = deleteDeque[i];
      }else{
        newdeque.push_back(deleteDeque[i]);
      }
    }
    //If node already present in tree, but just marked deleted, change the isDeleted field.
    if(lazilyDeleted){
      node->isDeleted = false;
      //Replacing old deque by new deque with inserted element removed in case it was lazily deleted.
      deleteDeque = newdeque;
    }else{
      //Else insert into the tree.
      insertAVL(NULL,tree,key);
    }
  }

/*
 * Function : displayDeleteDeque
 * -------------------------------------------------------------
 * Displays the status of the elements that have been deleted.
 */

  void displayDeleteDeque(){
    cout<<"Elements marked deleted : ";
    for(int k=0;k<deleteDeque.size();k++)
      cout<<deleteDeque[k]->key<<" ";
    cout<<endl;
  }

/*
 * Function drawLine
 * -----------------------------------------------
 * Function that draws a line(and a blank space)
 */

  void drawLine(){
    cout<<"----------------------------------------------------------------------------"<<endl;
    cout<<endl;
  }


/*
 * Function : insertAVL
 * ---------------------------------------------------------------------
 * Inserts a new node into a tree while keeping the tree balanced.
 * Uses the AVL algorithm for balancing of trees. Returns the change
 * in depth of tree due to insertion, which aids during recursive calls.
 * Assumes unique keys. Does nothing if key same as a key in the tree.
 */

  int insertAVL(BSTNode* parent,BSTNode* &tree, const int &key){
    if(tree==NULL){
      BSTNode* node = new BSTNode;
      node->key = key;
      node->parent = parent;
      node->bf = 0;
      node->left = node->right= NULL;
      node->isDeleted = false;
      tree = node;
      return 1;
    }
    if(tree->key==key) return 0;
    if(key<tree->key){
      int delta = insertAVL(tree,tree->left,key);
      if(delta==0) return 0;
      switch(tree->bf){
        case 1: tree->bf = 0 ;return 0;
        case 0: tree->bf = -1;return 1;
        case -1: fixLeftImbalance(tree); return 0;
      }
    }else{
      int delta = insertAVL(tree,tree->right,key);
      if(delta==0) return 0;
      switch(tree->bf){
        case -1: tree->bf= 0;return 0;
        case 0: tree->bf = 1; return 1;
        case 1: fixRightImbalance(tree);return 0;
      }
    }
  }

/*
 * Functions : fixLeftImbalance,fixRightImbalance
 * -----------------------------------------------------------------------------
 * Fix the imbalances in the left/right subtree of the current tree so that the
 * balance factor is restored and the tree is balanced.
 */

  void fixLeftImbalance(BSTNode* &tree){
    BSTNode *child = tree->left;
    if(child->bf!=tree->bf){
      int oldBF = child->right->bf;
      rotateLeft(tree->left);
      rotateRight(tree);
      tree->bf = 0;
      switch(oldBF){
        case -1: tree->right->bf = 1;tree->left->bf=0;break;
        case 0 : tree->right->bf = 0;tree->left->bf=0;break;
        case 1 :tree->right->bf = 0;tree->left->bf=-1;break;
      }
    }else{
      rotateRight(tree);
      tree->right->bf = tree->bf = 0;
    }
  }

  void fixRightImbalance(BSTNode* &tree){
    BSTNode *child = tree->right;
    if(child->bf!=tree->bf){
      int oldBF = child->left->bf;
      rotateRight(tree->right);
      rotateLeft(tree);
      tree->bf = 0;
      switch(oldBF){
        case -1: tree->right->bf = 1;tree->left->bf=0;break;
        case 0 : tree->right->bf = 0;tree->left->bf=0;break;
        case 1 :tree->right->bf = 0;tree->left->bf=-1;break;
      }
    }else{
      rotateLeft(tree);
      tree->left->bf = tree->bf = 0;
    }
  }

/*
 * Function : rotateLeft,rotateRight
 * -----------------------------------------------------------------------------
 * Functions to perform single left or right rotations.They modify the left and
 * the right child of nodes involved in rotations as well as the parent
 * relationships.
 */

  void rotateLeft(BSTNode* &tree){
    //Recording the parent of the tree since we need a swap
    BSTNode* treeParent = tree->parent;
    bool isLeft = false;
    if(treeParent!=NULL){   
      if(treeParent->left==tree)
        isLeft=true;
    }

    BSTNode* child = tree->right;
    //Modifying the tree structs members.
    tree->right = child->left;
    if(tree->right!=NULL)
      tree->right->parent = tree;
    tree->parent = child;
    //Modifying the child structs members.
    child->left = tree;
    child->parent = treeParent;
    //Assigning the child as the new Root i.e tree.

    tree = child;
    if(treeParent!=NULL){
      if(isLeft)
        treeParent->left = child;
      else
        treeParent->right = child;
    }
  }

  void rotateRight(BSTNode* &tree){
    //Recording the parent of the tree since we need a swap
    BSTNode* treeParent = tree->parent;
    bool isLeft = false;
    if(treeParent!=NULL){
      if(treeParent->left==tree)
        isLeft=true;
    }

    BSTNode* child = tree->left;
    //Modifying the tree structs members.
    tree->left = child->right;
    if(tree->left!=NULL)
      tree->left->parent = tree;
    tree->parent = child;
    //Modifying the child structs members.
    child->right = tree;
    child->parent = treeParent;
    //Assigning the child as the new Root i.e tree.
    tree = child;
    if(treeParent!=NULL){
      if(isLeft)
        treeParent->left = child;
      else
        treeParent->right = child;
    }

  }

/*
 * Function : findNode
 * ------------------------------------------------------------------------
 * Finds the node with the specified key and returns a pointer to the same.
 */

  BSTNode *findNode(BSTNode* &tree, const int &key){
    if(tree==NULL)
      return NULL;
    if(tree->key==key && !tree->isDeleted)
      return tree;
    else
      if(key<tree->key)
        return findNode(tree->left,key);
      else
        return findNode(tree->right,key);
  }

/*
 * Function : isBST
 * ---------------------------------------------------------
 * Returns if the Binary Search property holds for the tree.
 */

  bool isBST(BSTNode* tree){
    if(tree==NULL)
      return true;
    else{
      int key = tree->key;
      int leftkey;
      int rightkey;
      if(tree->left==NULL && tree->right==NULL)
        return true;
      else if(tree->left==NULL && tree->right!=NULL){
        rightkey = tree->right->key;
        return key<rightkey && isBST(tree->right);
      }
      else if(tree->left!=NULL && tree->right==NULL){
        leftkey = tree->left->key;
        return key>leftkey && isBST(tree->left);
      }else{
        rightkey = tree->right->key;
        leftkey = tree->left->key;
        return key<rightkey && key>leftkey && isBST(tree->left) && isBST(tree->right);
      }
    }
  }

/*
 * Function : isBalanced
 * --------------------------------------------
 * Returns whether the tree is balanced or not
 */

  bool isBalanced(BSTNode *tree){
    if(tree==NULL)
      return true;
    else{
      if(isBalanced(tree->left) && isBalanced(tree->right)){
        int leftheight = height(tree->left);
        int rightheight =height(tree->right);
        int diff = abs(leftheight-rightheight);
        if(diff<=1)
          return true;
        else
          return false;
      }else
        return false;
    }
  }

/*
 * Function : height
 * --------------------------------
 * Determines the height of a tree
 */

  int height(BSTNode* tree){
    if(tree==NULL)
      return 0;
    else{
      if(tree->left==NULL && tree->right==NULL)
        return 1;
      else if(tree->left==NULL && tree->right!=NULL)
        return (1 + height(tree->right));
      else if(tree->left!=NULL && tree->right==NULL)
        return (1 + height(tree->left));
      else{
        int leftheight = height(tree->left);
        int rightheight = height(tree->right);
        int heightToConsider = leftheight>rightheight?leftheight:rightheight;
        return (1 + heightToConsider);
      }
    }
  }

/*
 * Function : displayTree
 * --------------------------------------------------------------------------------------------------------
 * Displays by inorder traversal. Displays the actual tree in memory, with elements marked by lazy delete
 */

  void displayTree(BSTNode* tree){
    if(tree==NULL)
      return;
    else{
      displayTree(tree->left);
      cout<<"Key : "<<tree->key<<"  ";
      if(tree->parent!=NULL)
        cout<<"Parent : "<<tree->parent->key<<"  ";
      else
        cout<<"Parent : NULL"<<"  ";
      if(tree->left!=NULL)
        cout<<"Left Child : "<<tree->left->key<<"  ";
      else
        cout<<"Left Child : NULL"<<"  ";
      if(tree->right!=NULL)
        cout<<"Right Child : "<<tree->right->key<<"  ";
      else
        cout<<"Right Child : NULL"<<"  ";
      bool isDeleted = tree->isDeleted;
      string status = isDeleted?"Deleted":"Not Deleted";
      cout<<"Status : "<<status<<endl;
      displayTree(tree->right);
    }
  }

/*
 * Function : removeNode
 * -----------------------------------------------------------------------------------------
 * Function that removes a node from an AVL tree while keeping it balanced. Wrapper function
 * to removeAVL function.
 */

  void removeNode(BSTNode* &tree,const int &key){
    BSTNode* nodeToDelete = findNode(tree,key);
    if(nodeToDelete!=NULL)
      removeAVLLazy(tree,nodeToDelete);
    else
      cout<<"Key not found!"<<endl;
  }

/*
 * Function : removeAVLLazy
 * ------------------------------------------------------------------------------------------------
 * Performs the lazy delete operation. Pushes a node to the delete queue, and performs the delete
 * operation on the BST if the delete queue has reached its capacity of 5 elements.
 */

  void removeAVLLazy(BSTNode* &tree,BSTNode* nodeToDelete){
    deque<BSTNode* > newdeque;
    if(deleteDeque.size()==LAZY_DEL_CAPACITY){
      //Deleting all the nodes listed in the delete Queue , and empty the queue, once the capacity has been reached.
      for(int i=0;i<LAZY_DEL_CAPACITY;i++){
        removeAVL(tree,deleteDeque[i]);
      }
      nodeToDelete->isDeleted =true;
      newdeque.push_back(nodeToDelete);
      deleteDeque = newdeque;
    }else{
      nodeToDelete->isDeleted =true;
      deleteDeque.push_back(nodeToDelete);
    }
  }

/*
 * Function : removeAVL
 * ------------------------------------------------------------------------------------------------
 * Removes a node from the AVL tree while keeping it balanced according to the following algorithm.
 */

  void removeAVL(BSTNode* &tree,BSTNode* nodeToDelete){
    //Case 1 : Deleting the node with no children. The leaf node.
    if(nodeToDelete->left==NULL && nodeToDelete->right==NULL){

      //Making amends to the parents members. Memory freeing done at the end.
      if(nodeToDelete->parent->left==nodeToDelete)
        nodeToDelete->parent->left=NULL;
      else
        nodeToDelete->parent->right=NULL;

      //Freeing the heap memory.
      delete nodeToDelete;

      //Balancing the tree after deletion
      fixImbalance(tree,nodeToDelete->parent);

    }else if((nodeToDelete->right!=NULL && nodeToDelete->left==NULL)||(nodeToDelete->right==NULL && nodeToDelete->left!=NULL)){

    //Case 2 : Deleting the node with one child.
      if(nodeToDelete->right!=NULL){
        copyNode(nodeToDelete,nodeToDelete->right);

        //Deleting the leaf
        delete nodeToDelete->right;
        //Balancing the tree after deletion
        fixImbalance(tree,nodeToDelete);

      }
      else{
        copyNode(nodeToDelete,nodeToDelete->left);
        //Deleting the leaf
        delete nodeToDelete->left;
        //Balancing the tree after deletion
        fixImbalance(tree,nodeToDelete);
      }

    }else{
    //Case 3 : Deleting the node with two children.
      BSTNode* successor = findSuccessorInLeftSubtree(nodeToDelete);
      nodeToDelete->key = successor->key;
      nodeToDelete->isDeleted = successor->isDeleted;
      if(successor->left!=NULL){
        //We use ->left here since findSuccessorInLeftSubtree finds the rightmost node in the left subtree.
        copyNode(successor,successor->left);

        //Deleting the left child.
        delete successor->left;

        //Balancing the tree after deletion
        fixImbalance(tree,successor);
      }else{
        if(successor->parent->left == successor)
          successor->parent->left= NULL;
        else
          successor->parent->right = NULL;

        //Delete the apt leaf node
        delete successor;

        //Balancing the tree after deletion
        fixImbalance(tree,successor->parent);

      }
    }
  }
/*
 * Function : fixImbalance
 * ----------------------------------------------------------------------------------------
 * Function used in removeAVL. Fixed imbalance starting at a node all the way upto the root
 */

  void fixImbalance(BSTNode* &tree,BSTNode* start){
    if(start==NULL) return;//Incase of one node tree.

    //Some node pointers we use in the algorithm to balance the tree.
    BSTNode* z = start;
    BSTNode* forTheTree = NULL;
    //Travels up until it reaches the root
    while(z!=NULL){
      int bf_z = height(z->right)-height(z->left);
      z->bf = bf_z;
      //Condition for a node being unbalanced
      if(abs(bf_z)>1){
        bool yl = height(z->left)>height(z->right);
        bool yr = yl?false:true;
        BSTNode* y = yl?z->left:z->right;
        bool xl = height(y->left)>height(y->right);
        bool xr = xl?false:true;
        BSTNode* x = xl?y->left:y->right;
        bool ylxl = yl && xl;
        bool ylxr = yl && xr;
        bool yrxl = yr && xl;
        bool yrxr = yr && xr;
        if(ylxl){
          rotateRight(z);
        }else if(ylxr){
          rotateLeft(y);
          z->left = y;
          rotateRight(z);
        }else if(yrxl){
          rotateRight(y);
          z->right = y;
          rotateLeft(z);
        }else{
          rotateLeft(z);
        }
      }

      //Update for the while loop
      forTheTree = z;
      z = z->parent;
    }//End of while loop
    if(forTheTree!=NULL)
      tree = forTheTree;
  }
/*
 * Function : findSuccessorInLeftSubtree
 * -----------------------------------------------------------------
 * Finds the right most node in the left subtree of the passed node.
 */

  BSTNode* findSuccessorInLeftSubtree(BSTNode* tree){
    BSTNode* leftRoot = tree->left;
    BSTNode* successor = leftRoot;
    while(successor->right!=NULL){
      successor = successor->right;
    }
    return successor;
  }

/*
 * Function : copyNode
 * ----------------------------------------------
 * Copies contents from one node to second node.
 */

  void copyNode(BSTNode* nodeToCopyInto,BSTNode* nodeToDelete){
    nodeToCopyInto->key = nodeToDelete->key;
    nodeToCopyInto->left = nodeToDelete->left;
    nodeToCopyInto->right = nodeToDelete->right;
    nodeToCopyInto->isDeleted = nodeToDelete->isDeleted;
  }

