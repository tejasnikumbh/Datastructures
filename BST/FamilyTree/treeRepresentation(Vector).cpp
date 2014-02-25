/*
 * File : treeRepresentation.cpp
 * -------------------------------------------------------------------------------------
 * The following code reads input from a text file and constructs a tree representation.
 * The input data has to follow a specific format. The family tree uses vectors [STL]
 * in representing relationships amongst nodes.
 */

/* Including standard libraries */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

/* Useful data types and constants for programs */
struct FamilyTreeNode {
  string name;
  vector<FamilyTreeNode *> children;
};


/* Function prototypes */
string openFileFromUser(ifstream& file);
string getLine(const string& prompt);
FamilyTreeNode *readFamilyTree(ifstream& file);
void storeEntryInTree(const string& parent, const string& child,FamilyTreeNode *root);
void displayFamilyTree(FamilyTreeNode *root);
void displayFamilyTreeWithSpacing(FamilyTreeNode *root,string spacing);

/* Main program */
  int main(){

    /* Associating input file stream with a valid file */
    ifstream file;
    string fileName = openFileFromUser(file);
    
    /* Reading the family tree */
    FamilyTreeNode *root = readFamilyTree(file);

    /* Display the family tree */
    displayFamilyTree(root);
    return 0; 
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
 * Function : storeEntryInTree
 * -------------------------------------------------------------------------------------------------
 * Reads input from a file and stores it in a tree data structure, if input is in a specific format.
 * Note : See familytree.txt for the format.
 */

  void storeEntryInTree(const string& parent, const string& child,FamilyTreeNode *root){
    if(root->name == parent){
      FamilyTreeNode *tempChild = new FamilyTreeNode;
      tempChild->name = child;
      root->children.push_back(tempChild);
    }
  
    if(root->children.size() == 0)
      return;

    else{
      for(int i=0;i<root->children.size();i++){
        storeEntryInTree(parent,child,root->children[i]);
      }
    }
  }

/* 
 * Function : displayFamilyTree
 * -----------------------------------------------------------
 * Wrapper function to the function drawFamilyTreeWithSpacing.
 */

  void displayFamilyTree(FamilyTreeNode *root){
    string spacing = "";
    displayFamilyTreeWithSpacing(root,spacing);
  }

/* 
 * Function : displayFamilyTreeWithSpacing
 * -------------------------------------------------------------------
 * This function draws the family tree by traversing it "In Pre Order".
 */

  void displayFamilyTreeWithSpacing(FamilyTreeNode *root,string spacing){
    cout<<spacing<<root->name<<endl;
    if(root->children.size()==0)
      return;
    else{
      for(int i=0;i<root->children.size();i++){
        displayFamilyTreeWithSpacing(root->children[i],string(spacing+"  "));
      }
    }
  }
