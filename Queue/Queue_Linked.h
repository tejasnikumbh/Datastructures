/*
 * File : Queue.h
 * ----------------------------------------------------------
 * Interface and implementation for the queue datastructure.
 */

#ifndef _Queue_Linked_h
#define _Queue_Linked_h

template<typename valueType> class Queue{

  /* Public interface for the queue class */
  public:

  /* 
   * Constructor : Queue
   * Usage       : Queue<valueType> queue;
   * --------------------------------------
   * Initializes an empty queue.
   */

   Queue();
  
  /*
   * Destructor : ~Queue
   * Usage      : Usually implicit. 
   * ------------------------------------------------
   * Frees the heap memory associated with the queue.
   */
   
   ~Queue();
 
  /* 
   * Method : size
   * Usage  : queue.size();
   * ------------------------------------------------------
   * Returns the number of elements currently in the queue.
   */
   
   int size() const;

  /*
   * Method : isEmpty
   * Usage  : if(queue.isEmpty()) //Some code
   * ---------------------------------------------------
   * Returns true if there are no elements in the queue
   */

   bool isEmpty() const;

  /* 
   * Method : clear
   * Usage  : queue.clear();
   * -----------------------------------
   * Removes all element from the queue 
   */

   void clear();

   /*
    * Method : enqueue
    * Usage  : queue.enqueue(value);
    * -------------------------------------------------------
    * Adds the specified value to the rear end of the queue.
    */
   
   void enqueue(valueType value);

   

   /*
    * Method : dequeue
    * Usage  : queue.dequeue();
    * -------------------------------------------------------
    * Removes the first value at the front end of the queue.
    */
   
   valueType dequeue();

   /* 
    * Method : peek
    * Usage  : queue.peek();
    * ---------------------------------------------------------------------------------------------------
    * Returns the value of the first element at the front end of the queue, without affecting the queue.
    */
   
   valueType peek() const;

   /* Copy constructor(single parameter constructor) and assignment operator */
   
   Queue(const Queue<valueType>& src);
   Queue<valueType>& operator=(const Queue<valueType>& src);


  /* Implementation part */
  private:
   
  /* Cell structure to hold one data value */
  struct Cell{
    Cell *link;
    valueType data;
  } 

  /* Instance variables */
  Cell *head;
  Cell *tail;
  int count;

  /* Private method prototype */
  void deepCopy(const Queue<valueType>& src);
}

/* 
 * Constructor : Queue
 * ---------------------------------------------------------------------------------------
 * Initialises all the instance variables of the queue object.Initialises an empty queue.
 */

  template<typename valueType> 
  Queue<valueType>::Queue(){
    head = tail = NULL;
    count = 0;
  }

/* 
 * Destructor : ~Queue
 * --------------------------------------------
 * Frees heap memory associated with the queue
 */
  
  template<typename valueType> 
  Queue<valueType>::~Queue(){
    clear();
  }

/* 
 * Method : size
 * -----------------------------------------
 * Returns the value of the variable count.
 */

  template<typename valueType> 
  int Queue<valueType>::size() const{
    return count;
  }

/* 
 * Method :  isEmpty
 * ----------------------------------
 * returns true if count is set to 0.
 */
 
  template<typename valueType> 
  bool Queue<valueType>::isEmpty() const{
    return count==0;
  }

/*
 * Method : clear
 * -------------------------------------
 * Removes all elements from the queue.
 */

  template<typename valueType> 
  void Queue<valueType>::clear(){
    while(count>0){
      dequeue();
    }
  }  

/* 
 * Method : enqueue
 * -------------------------------------------------------------------------------------------------------
 * Adds a new cell element to the linked list and increments the tail pointer tp point at the new element.
 * Cell element holds the value passed in the data field.
 */

  template<typename valueType> 
  void Queue<valueType>::enqueue(valueType value){
    Cell *newCell = new Cell;
    newCell->link = NULL;
    newCell->data = value;
    if(head==NULL){
      head = newCell;
    }else{
      tail->link = newCell;
    }
    tail = newCell;
    count++;
  }

/*
 * Method : dequeue
 * -----------------------------------------------------------------------------------------------------------
 * Removes the cell element from the linked list which is pointed to by the head pointer.Decrements count and
 * updates the head pointer.
 */

  template<typename valueType> 
  valueType Queue<valueType>::dequeue(){
    if(head==NULL) throw "Error: Cannot dequeue from empty queue";
    valueType data = tail->data;
    Cell *cp = head;
    if(cp->link==NULL){
      head = tail = NULL;
    }else{
      head = cp->link;
    }
    delete cp;
    count--;
    return data;
  }

/* 
 * Method : peek
 * ---------------------------------------------------------------
 * Returns teh value of the element at the front end of the queue.
 */

  template<typename valueType>
  valueType Queue<valueType>::peek() const{
    if(head==NULL) throw "Error: Cannot dequeue from empty queue";
    return head->data;
  }

/* Copy constructor and assignment operator */

  template<typename valueType>
  Queue<valueType>::Queue(const Queue<valueType>& src){
    /* No need to free heap memory since it is a constructor */
    deepCopy(src);
  }  

  template<typename valueType>
  Queue<valueType>& Queue<valueType>::operator=(const Queue<valueType>& src){
    /* Freeing the heap memory */
    if(&src!=head){
      clear();
      deepCopy(src);
    }
    return *this;
  }

/* 
 * Private Method : deepCopy
 * -------------------------------------------------------------------------
 * Creates a deep copy of the queue passed in into the current queue object.
 * Any heap memory associated with the previous queue must be freed before
 * making use of this method.
 */

  template<typename valueType>
  void Queue<valueType>::deepCopy(const Queue<valueType>& src){
    head = NULL;
    tail = NULL;
    count = 0;
    for(Cell *cp = src.head;cp!=NULL;cp = cp->link)
      enqueue(cp->data);
  }

 


  
