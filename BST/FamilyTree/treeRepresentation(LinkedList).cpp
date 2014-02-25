/*
 * File : treeRepresentation.cpp
 * -----------------------------------------------------------------------------------------
 * The following code reads input from a text file and constructs a tree representation.
 * The input data has to follow a specific format. The tree representation uses linked 
 * lists in its representation of relationship amongst nodes. 
 * 
 */

/* Inluding standard libraries */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;


/* Useful data types and constants for programs */

/* 
 * Struct : FamilyTreeNode
 * ----------------------------------------------------------------------------
 * Field name contains name of current element.
 * Other nodes contain a pointer to next sibling and a pointer to firstChild.
 */

  struct FamilyTreeNode{
    string name;
    FamilyTreeNode *nextSibling;
    FamilyTreeNode *firstChild;
  };

/* Function prototypes */
string openFileFromUser(ifstream& file);
string getLine(const string& prompt);
FamilyTreeNode *readFamilyTree(ifstream& file);
void displayFamilyTree(FamilyTreeNode *root,string spacing);
void storeEntryInTree(const string& parent, const string& child,FamilyTreeNode *root);

/* Main program */
  int main(){
    /* Associating input file stream with a valid file */
    ifstream file;
    string fileName = openFileFromUser(file);
    
    /* Reading the family tree */
    FamilyTreeNode *root = readFamilyTree(file);

    /* Display the family tree */
    displayFamilyTree(root,"");
    
    return 0;
  }

/*
 * Function : readFamilyTree
 * -----------------------------------------------------------------------------------------------
 * Reads in the family tree as stored in the specified file with the help of the storeEntryInTree
 * file.
 */

  FamilyTreeNode *readFamilyTree(ifstream& file){
    FamilyTreeNode *root = new FamilyTreeNode;
    string rootName;
    getline(file,rootName);
    root->name = rootName;
    root->nextSibling = NULL;
    root->firstChild = NULL;
    string currentRel;
    while(getline(file,currentRel)){
      int colonIndex = currentRel.find(":");
      string child = currentRel.substr(0,colonIndex);
      string parent = currentRel.substr(colonIndex+1);
      storeEntryInTree(parent,child,root);
    }
    return root;
  }

/* 
 * Function  : storeEntryInTree 
 * -------------------------------------------------------------------------------- 
 * Uses linked lists to create and store entries in underlying tree representation.
 * Uses Pre Order traversal. 
 */

  void storeEntryInTree(const string& parent, const string& child,FamilyTreeNode *root){
   FamilyTreeNode *traversalPointer1 = root->firstChild;
  
   if(parent==root->name){
     /* Creating the new Cell */
     FamilyTreeNode *tempCell = new FamilyTreeNode;
     tempCell->name = child;
     tempCell->firstChild = NULL;
     tempCell->nextSibling = NULL;
    
     /* Inserting the new Cell */
     if(traversalPointer1==NULL){
       cout<<"Stored Root Child!"<<endl;
       root->firstChild = tempCell;
     }else{
       while(traversalPointer1->nextSibling!=NULL){
         traversalPointer1 = traversalPointer1->nextSibling;   
       }
       cout<<"Stored Sibling !"<<child<<endl;
       traversalPointer1->nextSibling = tempCell;
     }
   }else{
     if(root->firstChild == NULL) return;
     for(FamilyTreeNode *childStart = root->firstChild;childStart !=NULL;childStart = childStart->nextSibling){
       storeEntryInTree(parent,child,childStart);
     }
   }
}
  

/* 
 * Function : displayFamilyTree
 * -------------------------------------------------------------------------
 * Recursive function to display the family tree. Uses Pre Order traversal.
 */

  void displayFamilyTree(FamilyTreeNode *root,string spacing){
    cout<<spacing<<root->name<<endl; 
    for(FamilyTreeNode *childStart = root->firstChild;childStart !=NULL;childStart = childStart->nextSibling){
      displayFamilyTree(childStart,spacing + "  ");
    } 
    return;
  }

/*
 * Function : openFileFromUser
 * ---------------------------------------------------------------------------------------
 * Opens the file as specified by user in cin and associates the passed input file stream
 * with it.
 */

  string openFileFromUser(ifstream& file){
    string fileName;
    while(true){
      fileName = getLine("Enter a file name : ");
      file.open(fileName.c_str());
      if(!file.fail())//streams predate c++, so c style strings are required.
        break;
      else{
        cout<<"Please enter a valid file name : "<<endl; 
        file.clear();
      }
    }
    return fileName;
  }

/* 
 * Function : getLine
 * ---------------------------------------------
 * Retrieves and returns a string from the user
 */

  string getLine(const string& prompt){
    string result;
    cout<<prompt<<endl;
    getline(cin,result);
    return result;
  }



