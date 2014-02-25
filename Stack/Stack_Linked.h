/* 
 * File : Stack.h
 * -----------------------------------------------------------------------------------
 * A template for the Stack Data structure class parametrized over any data type.
 * Refer the public section for the interface and the remaining code [private section]
 * and remaining code for implementational details.
 */

#ifndef _Stack_h
#define _Stack_h

template<typename valueType> class Stack{
  public:

  /* 

  /* 
   * Constructor : Stack
   * Usage : Stack<valueType> stack;
   * --------------------------------
   * Initialises a new stack.
   */

   Stack();

  /* Destructor : ~Stack 
   * -----------------------------------------------
   * Frees any heap memory associated with the stack.
   */

   ~Stack();

  /* Method : size
   * Usage  : int n = stack.size();
   * --------------------------------------------
   * Returns the number of elements in the stack.
   */

  int size() const;

  /* Method : isEmpty
   * Usage  : if(stack.isEmpty()) //do something
   * --------------------------------------------------------------------------
   * Predicate method that returns true if the stack is empty, false otherwise.
   */

  bool isEmpty() const;

  /* Method : clear
   * Usage  : stack.clear()
   * -------------------------------------------------------
   * Removes all elements from the stack and makes it empty.
   */
  
  void clear();

  /* Method : peek
   * Usage  : stack.peek();
   * ----------------------------------------------------------------------------------
   * Returns the value of the topmost element in the stack without affecting the stack.
   */
 
  valueType peek() const;

  /* Method : push
   * Usage  : stack.push(value);
   * --------------------------------------------
   * Pushes the specified value onto this stack. 
   */
  
  void push(valueType value);

  /* Method : pop
   * Usage  : stack.pop();
   * -----------------------------------------------------------------------------------------------
   * Removes the top element from a stack and returns it. Throws an error if called on empty stack.
   */
  
  valueType pop();

  /* Copy contructor and assignment operator
   * ----------------------------------------
   * Implements deep copying for the stack.
   */
  
  Stack(const Stack<valueType>& src);
  Stack<valueType>& operator=(const Stack<valueType>& src);
 
  private:
 
  /* Implementation Notes : 
   * ---------------------------------------------------------------------------------------
   * This particular implementation of Stack Data Structure uses linked lists of cells for 
   * storage. Each new entry is added to the front of the linked list, so that the entry at 
   * the top of the stack is accessible in O(1) time. Also, the implementatio keeps a track
   * of the number of elements in the stack so the size method returns in O(1) time.
   */

 
  

  /* Cell structure to store each unit of data */
  struct Cell{
    valueType data;
    Cell *link;
  };
  
  /* Instance variables */

  Cell *list; //Initial pointer in the list
  int count;  //Number of elements in the stack.
  
   
  /* Private method prototypes */

  void deepCopy(const Stack<valueType>& src);
 
 
};

/* Implementation of methods for Stack Template Class */

/* Method : Constructor
 * --------------------------------------------------------------------------------------------------
 * Initialises fields for the stack object.Initialises the list pointer to a NULL pointer and count
 * , the number of elements in the stack to 0.
 */

  template<typename valueType> 
  Stack<valueType>::Stack(){
    list = NULL;
    count = 0;
  }

/* Methods : Destructor 
 * ------------------------------------------------------------------------------------------------------
 * Frees any heap memory associated with the stack object, which in this case is memory associated with 
 * the entire linked list.
 */

  template<typename valueType> 
  Stack<valueType>::~Stack(){
    clear();
  }

/* Method : size
 * ---------------------------------------------------------
 * Returns the value of count ivar indicating size of stack.
 */

  template<typename valueType> 
  int Stack<valueType>::size() const{
    return count;
  }

/* Method : isEmpty
 * -------------------------------
 * Returns if count is equal to 0.
 */
 
  template<typename valueType>
  bool Stack<valueType>::isEmpty() const{
    return count==0;
  }

/* Method : clear
 * --------------------------------------------------------------------------
 * Removes all elements from the stack, rendering it empty. Makes use of pop.
 */

  template<typename valueType>
  void Stack<valueType>::clear(){
    while(count>0)
      pop();
  }

/* Method : push
 * -----------------------------------------------------------------------------------
 * Adds a cell element to the front of the linked list. This cell element contains the
 * value specified and a link to the element which was previously at the front of the 
 * list.
 */
 
  template<typename valueType>
  void Stack<valueType>::push(valueType value){
    Cell *current = new Cell;
    current->link = list;
    current->data = value;
    list = current;
    count++;
  }

/* Methods : pop and peek
 * -------------------------------------------------------------------------
 * Both methods do the following : If the stack is empty, throws an error.
 * Pop removes element on top of the stack and peek returns the value of the 
 * data in the cell unit at the top of stack, without affecting the stack.
 */

  template<typename valueType>
  valueType Stack<valueType>::pop(){
    if(isEmpty()) throw "Error: Cannot pop from empty stack.";
    Cell *current = list;
    list = current->link;
    valueType returnVal = current->data;
    delete current;
    count--;
    return returnVal;
  }

  template<typename valueType>
  valueType Stack<valueType>::peek() const{
    if(count==0) throw "Error: Cannot peek at an empty stack";
    return list->data;
  }

/* Methods : Copy constructor and assignment operator
 * ----------------------------------------------------
 * Leave the work to the deepCopy method.
 */

  template<typename valueType>
  Stack<valueType>::Stack(const Stack<valueType>& src){
    deepCopy(src);
  }
  
  template<typename valueType>
  Stack<valueType>& Stack<valueType>::operator=(const Stack<valueType>& src){
    if(this!=&src){
      clear();
      deepCopy(src);
    }
    return *this;
  }

/* Method : deepCopy
 * -----------------------------------------------------------------------
 * Creates an independent deep copy of src object into the current object.
 */

  template<typename valueType>
  void Stack<valueType>::deepCopy(const Stack<valueType>& src){
    count = src.count;
    Cell *tail = NULL;
    for(Cell *pointer = src.list;pointer!=NULL;pointer = pointer->link){
      Cell *currentCell = new Cell;
      currentCell->data = pointer->data;
      if(tail==NULL){
        list = currentCell;
      }else{
        tail->link = currentCell;
      }
      tail = currentCell;
    }
    if(tail!=NULL) tail->link = NULL;
  }


#endif
