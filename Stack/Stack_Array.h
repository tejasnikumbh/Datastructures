/* 
 * File : Stack_Array.h
 * -----------------------------------------------------------------------------------
 * A template for the Stack Data structure class parametrized over any data type.
 * Refer the public section for the interface and the remaining code [private section]
 * and remaining code for implementational details.
 */

#ifndef _Stack_Array_h
#define _Stack_Array_h

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
   * This particular implementation of Stack Data Structure uses dynamic arrays for storage.
   * The allocated size of the array doubles everytime the push method exceeds the current
   * allocated size for the array. This ensures that the push method takes O(1) time.
   */

 
  static const int INITIAL_CAPACITY = 10; //Initial array capacity

  /* Instance variables */

  valueType *array;  //Array to store the elements in the stack.
  int count;         //Count of number of elements in the array.   
  int capacity;      //Current allocated size of array.

  /* Private method prototypes */

  void deepCopy(const Stack<valueType>& src);
  void expandCapacity(); 
 
};

/* Implementation of methods for Stack Template Class */

/* Method : Constructor
 * --------------------------------------------------------------------------------------------------
 * Creates a dynamic array for the stack with initial size equal to INITIAL CAPACITY and initialises 
 * other fields for the stack object.
 */

  template<typename valueType> 
  Stack<valueType>::Stack(){
    capacity = INITIAL_CAPACITY;
    count =0 ;
    array = new valueType[capacity];
  }

/* Methods : Destructor 
 * ------------------------------------------------------------------------------------------------------
 * Frees any heap memory associated with the stack object, which in this case is just the dynamic array 
 * of elements.
 */

  template<typename valueType> 
  Stack<valueType>::~Stack(){
    delete[] array;
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
 * --------------------------------------------------------
 * Removes all elements from the stack, rendering it empty.
 */

  template<typename valueType>
  void Stack<valueType>::clear(){
    count = 0;
  }

/* Method : push
 * -----------------------------------------------------------------------------------
 * This method expands the array if the capacity is full and adds an element on top.
 */
 
  template<typename valueType>
  void Stack<valueType>::push(valueType value){
    if(count==capacity) expandCapacity();
    array[count++] = value;
  }

/* Methods : pop and peek
 * -------------------------------------------------------------------------
 * Both methods do the following : If the stack is empty, throws an error.
 */

  template<typename valueType>
  valueType Stack<valueType>::pop(){
    if(count==0) throw "Error : Cannot pop from empty stack";
    return array[--count];
  }

  template<typename valueType>
  valueType Stack<valueType>::peek() const{
    if(count==0) throw "Error: Cannot peek at an empty stack";
    return array[count-1];
  }

/* Methods : Copy constructor and assignment operator
 * ----------------------------------------------------
 * Leave the work to the deepCopy method
 */

  template<typename valueType>
  Stack<valueType>::Stack(const Stack<valueType>& src){
    deepCopy(src);
  }
  
  template<typename valueType>
  Stack<valueType>& Stack<valueType>::operator=(const Stack<valueType>& src){
    if(this!=&src){
      delete[] array;
      deepCopy(src);
    }
    return *this;
  }

/* Method : deepCopy
 * -----------------------------------------------------------------------
 * Creates an independent deep copy of src object into the current object.
 * Capacity is set such that there is some room to expand. 
 */

  template<typename valueType>
  void Stack<valueType>::deepCopy(const Stack<valueType>& src){
    capacity = src.count + INITIAL_CAPACITY;
    array = new valueType[capacity];
    for(int i=0;i<count;i++){
      array[i] = src.array[i];
    } 
    count = src.count;
  }

/* Method : expandCapacity
 * ----------------------------------------------------------------------------------------------------
 * Craetes a new array with twice the allocated size of old array, copies contents from old array, and
 * deletes old array.
 */

  template<typename valueType>
  void Stack<valueType>::expandCapacity(){
    valueType *oldArray = array;
    capacity*=2;
    array = new valueType[capacity];
    for(int i=0;i<count;i++){
      array[i] = oldArray[i];
    }
    delete[] oldArray;
  }

#endif
