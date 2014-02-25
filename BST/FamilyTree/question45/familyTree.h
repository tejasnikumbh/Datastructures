/*
 * File : familyTree.h
 * ---------------------------------------------------------------------------------
 * An interface to a family tree data structure created using FamilyTreeNode class.
 */

#ifndef _familytree_h
#define _familytree_h

/* Including standard libraries */
#include <string>
#include <vector>
using namespace std;

/* 
 * Class : FamilyTreeNode
 * ---------------------------------------------
 * Representative of a node in the family tree.
 */

class FamilyTreeNode{

  public : 

  /* 
   * Constructor : FamilyTreeNode
   * ----------------------------------------------------------
   * Constructs a new family tree node with the specified name
   */

   FamilyTreeNode(const string &name);

  /*
   * Getter Methods : getName,getParent,getChildren
   * ---------------------------------------------------------
   * Returns the specified information about the current node.
   * getName : Returns the name(String)
   * getParent : Returns the pointer to the parent(FamilyTreeNode)
   * getChildren : Returns a vector of children(Vector of FamilyTreeNode pointers)
   */

   string getName() const;  
   FamilyTreeNode *getParent() const;
   vector<FamilyTreeNode *> getChildren() const;

  /*
   * Setter Method : addChild
   * --------------------------------------------------------------
   * Adds the passed element as a child to current FamilyTreeNode. 
   */   
  
   void addChild(FamilyTreeNode *child);

  private : 

  /* Private instance variables */
    string name;
    FamilyTreeNode* parent;
    vector<FamilyTreeNode *> children;

  /* Private methods */
    void setThisAsParent(FamilyTreeNode* child);
};

#endif
