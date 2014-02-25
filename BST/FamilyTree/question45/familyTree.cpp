/*
 * File : familyTree.cpp
 * -------------------------------------------------------------------------------
 * Implementation of the familyTree data structure using the class FamilyTreeNode
 */

/* Including standard libraries */
#include "familyTree.h"

/* Implementation of class FamilyTreeNode */

  /* 
   * Constructor : FamilyTreeNode
   * ----------------------------------------------------------
   * Constructs a new family tree node with the specified name
   * Assigns the passed name to the instance variable name.
   */

   FamilyTreeNode::FamilyTreeNode(const string &name){
     this->name = name;
     this->parent = NULL;
   }

  /*
   * Getter Methods : getName,getParent,getChildren
   * ------------------------------------------------------------------------------------------------------
   * Returns the specified information about the current node.
   * getName : Returns name.
   * getParent : Returns the pointer to the parent FamilyTreeNode
   * getChildren : Returns children[vector containing pointers to child nodes(which are FamilyTreeNodes)]
   */

   string FamilyTreeNode::getName() const{
     return name;
   }

   FamilyTreeNode* FamilyTreeNode::getParent() const{
     return parent;
   }

   vector<FamilyTreeNode *> FamilyTreeNode::getChildren() const{
     return children;
   }

  /*
   * Setter Method : addChild
   * --------------------------------------------------------------
   * Adds the passed element as a child to current FamilyTreeNode. 
   */   
  
   void FamilyTreeNode::addChild(FamilyTreeNode *child){
     children.push_back(child);
     setThisAsParent(child);
   }

  /* 
   * Private method : setThisAsParent
   * ------------------------------------------------------------------
   * Set the parent of the recently added child as the current element 
   */

   void FamilyTreeNode::setThisAsParent(FamilyTreeNode* child){
     child->parent = this;
   }

