/*
 * File : UnitTests.cpp
 * ----------------------------------------------------------------------------------------------------
 * Unit tests for the testing of the array and linked list implementations of the stack datastructure.
 */

/* Including standard libraries */
#include <iostream>
#include <sstream>
#include "Stack_Linked.h"
using namespace std;

/* Main program */

  int main(){

    cout<<"Program to test stack implementation"<<endl;
 
    /* Tests the constructor */
    Stack<int> myStack;
  
    /* Initialising array using push method */
    for(int i=0;i<30;i++)
      myStack.push(i);

    /* Testing the peek method. Should return 29. */
    cout<<myStack.peek()<<endl;

    /* Testing the popo method. Should return 29. */
    cout<<myStack.pop()<<endl;
  
    /* Testing push after pop. SHould return 28, now that 29 is out */
    cout<<myStack.peek()<<endl;

    /* Testing whether stack is empty.SHould return false */
    cout<<myStack.isEmpty()<<endl;

    /* Testing the size method. Should return 29. */
    cout<<myStack.size()<<endl;

    /* Testing copy constructor */
    Stack<int> otherStack(myStack);

    /* Testing the assignment operator */
    Stack<int> thirdStack = myStack;

    /* Testing the clear method */
    myStack.clear();    
    cout<<myStack.size()<<endl; //Should return 0.

    /* SHould return 29 if copy constructor runs properly */
    cout<<otherStack.size()<<endl;
  
    /* Should return 29, if the assignment operator worked properly */
    cout<<thirdStack.size()<<endl;

    return 0;
  }

