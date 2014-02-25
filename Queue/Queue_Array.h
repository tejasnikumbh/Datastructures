/*
 * File : Queue.h
 * ----------------------------------------------------------
 * Interface and implementation for the queue datastructure.
 */

#ifndef _Queue_Array_h
#define _Queue_Array_h

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

  /* Initial capacity of array holding queue */
  static const int INITIAL_CAPACITY = 10;
  
  /* Instance variables for a queue object*/
  valueType *array;
  int capacity;
  int head;
  int tail;
 
  /* Private methods */
  deepCopy(const Queue<valueType>& src);
  expandCapacity(); 
}

/*
 * Method : Constructor
 * ----------------------------------------------------------------------
 * Single parameter constructor that initializes all instance variables. 
 */

  template<typename valueType> 
  Queue<valueType>::Queue(){
    capacity = INITIAL_CAPACITY;
    head = 0;
    tail=0;
    array = new valueType[capacity];
  }

/* 
 * Method : Destructor
 * -------------------------------------------------------------------
 * Frees heap memory by deleting the array associated with the queue.
 */
  
  template<typename valueType>
  Queue<valueType>::~Queue(){
    delete[] array;
  }

/* 
 * Method : size
 * -----------------------------------------------------------------------------------
 * Returns the size by performing modular arithematic on the values of head and tail.
 */

  template<typename valueType>
  int Queue<valueType>::size() const{
    return ((capacity-head+tail)%capacity);
  }

/* 
 * Method : isEmpty
 * ----------------------------------------------------------------------------------------------
 * Returns true if head and tail are equal in value. [Which implies that the queue is empty].
 * Another way is to maintain a special boolean variable, which switches between true and false
 * depending upon whether the last operation was enqueue or dequeue, but it includes more opera
 * tions and is computationally expensive. One can also maintain a size variable, or use size()
 * but this is a good way too. We always keep one space between head and tail empty to make sure
 * that whenever the queue is not empty, head and tail values dont coincide in any case[even
 * when there is a circular fill.]
 */

  template<typename valueType>
  bool Queue<valueType>::isEmpty() const{
    return head==tail;
  }

/* 
 * Method : clear
 * ------------------------------------
 * Removes all elements from the queue 
 */
 
  template<typename valueType>
  void Queue<valueType>::clear(){
    head=0;
    tail=0;
  } 

/* 
 * Method : enqueue
 * ------------------------------------------------------------------------------------------------------
 * Enqueue's the element passed according to the circular buffer implementation,and increments the value
 * of the tail accordingly.
 */
 
  template<typename valueType>
  void Queue<valueType>::enqueue(valueType value){
    /* Checking whether the array for the queue is filled.One extra for the circular buffer implementation. */
    if(size()==(capacity-1)) expandCapacity();
    array[tail] = value;
    tail = (tail +1)%capacity;
  }

/* 
 * Method : dequeue
 * ---------------------------------------------------------------------------------------------------------
 * Dequeues the first element at the front end of the queue , and increments the value of head accordingly.
 */

  template<typename valueType>
  valueType Queue<valueType>::dequeue(){
    if(isEmpty()) throw "Error : Cannot dequeu from an empty queue.";
    valueType result = array[head];
    head = (head+1)%capacity;
    return result;
  }

/* 
 * Method : peek
 * ---------------------------------------------------------------------
 * Returns the value pointed to by the head, without affecting the head.
 */

  template<typename valueType>
  valueType Queue<valueType>::peek(){
    if(isEmpty()) throw "Error: Cannot peek at empty queue";
    return array[head]; 
  }

/* Methods : Copy constructor and assignment operator */

  template<typename valueType>
  Queue<valueType>::Queue(const Queue<valueType>& src){
    /* No need to free memory as this is the constructor , so there is no junk memory allocated */
    deepCopy(src);
  }

  template<typename valueType>
  Queue<valueType>& Queue<valueType>::operator=(const Queue<valueType>& src){
    if(this!=&src){
      /* Need to free heap memory associated with old array */
      delete[] array;
      deepCopy(src);
    }
    return *this;
  }

/* Implemenation of private methods */
  
/* 
 * Method : deepCopy
 * --------------------------------------------------
 * Creates a deep copy of the passed in queue object.
 */
 
  template<typename valueType>
  void Queue<valueType>::deepCopy(const Queue<valueType>& src){
    int count = src.size();
    capacity = count + INITIAL_CAPACITY;
    array = new valueType[capacity];
    for(int i=0;i<count;i++){
      array[i] = src[(src.head+i)%(src.capacity)];
    }    
    head = 0;
    tail = count;
  }

/* 
 * Method : expandCapacity
 * ------------------------------------------------------------
 * Expands the capacity, incase the old one has less capacity.
 */

  template<typename valueType>
  void Queue<valueType>::expandCapacity(){
    int count = size();
    capacity*=2;
    valueType *oldArray = array;
    array = new valueType[capacity];
    for(int i=0;i<count;i++){
      array[i] = oldArray[(head+i)%capacity];
    }
    head = 0;
    tail = count;
    delete[] oldArray;
  }
 
 
#endif

