/*
 * File : Vector.h
 * ----------------------------------------------------------------------------------
 * This file exports an interface for the templatized vector class, which is a safe, 
 * efficient,and convienient replacement for traditional arrays.
 */

#ifndef _Vector_h
#define _Vector_h

template<typename valueType> class Vector{

  /* Interface for the Vector class */

  public : 
  
   /* 
    * Constructors : Vector(), Vector(int size, valueType defaultVal = valueType) 
    * Usage        : Vector<int> vec;       -> Empty Vector.
    * Usage        : Vector<int> vec(3);    -> Vector with 3 elements, each defaults 0. 
    * Usage        : Vector<int> vec(3,20); -> Vector with 3 elements, each numbered 20.
    * -----------------------------------------------------------------------------------
    * They initialise the vector. The first form creates an empty vector.The second form 
    * creates a vector of size n, with default value as provided by user or, if not the
    * default value of the valuetype.
    */  
  
    Vector();
    Vector(int size, valueType defaultVal = valueType());

   /* 
    * Destructor : ~Vector()
    * Usage      : Implicit
    * --------------------------------------------------
    * Frees the heap memory associated with the Vector.
    */
   
    ~Vector();

   /*
    * Method : size 
    * Usage  : int size = vec.size();
    * ---------------------------------------------------------------
    * Returns the number of elements stored currently in the vector.
    */  
  
    int size() const;

   /*
    * Method : isEmpty
    * Usage  : if(vec.isEmpty()) 
    * ------------------------------------------------
    * Returns true if the vector contains no elements.
    */

    bool isEmpty() const;

   /*
    * Method : clear
    * Usage  : vec.clear();
    * -----------------------------------------------------------
    * Removes all elements from the vector and renders it empty.
    */ 

    void clear();

   /*
    * Method : get(index)
    * Usage  : valueType val = vec.get(0);
    * ------------------------------------------------------------------------------------------
    * Returns the element in the vector situated at provided index, throws an error if index is 
    * out of bounds.
    */

    valueType get(int index) const;

   /*
    * Method : set(index,value)
    * Usage  : vec.set(0,1);
    * ------------------------------------------------------------------------------------------
    * Sets the value at the given index to be equal to provided value, throws an error if index
    * is out of bounds.
    */

    void set(int index,valueType value);

   /* 
    * Method : insert(index,value)
    * Usage  : vec.insert(1,34);
    * ---------------------------------------------------------------------------------------------
    * Inserts the specified element before the specified index. All elements beyond this index are
    * shifted one place to the right.Accepts indices from 0 upto and including the length of the 
    * vector, throws an error otherwise.
    */

    void insert(int index,valueType value);

   /*
    * Method : remove(index)
    * Usage  : vec.remove(0);
    * -----------------------------------------------------------------------------------
    * Removes the element at specified index. Throws an error if index is out of bounds.
    */
     
    void remove(int index);
 
   /* 
    * Method : add(value)
    * Usage  : vec.add(69);
    * ------------------------------------------------------
    * Appends the specified value to the end of the vector. 
    */

    void add(valueType value);

   /* 
    * Operator : []
    * Usage    : vec[2] = 30;
    * ------------------------------------------------------------------------------------------------
    * Overloads the [] operator for the vector class.Returns the value at the specified index if used
    * as a rvalue. If used as a lvalue, overwrites the value at the given index. 
    */
    
    valueType& operator=(int index);
    

    /* Copy constructor and assignment operator */

    Vector(const Vector<valueTye> &vec);
    Vector<valueType>& operator=(const Vector<valueType> &Vec); 
       
  private :

  /* Implementation for the Vector class */
  
  /* Notes on representation 
   * --------------------------------------------------------------------------------------------
   * This implementation uses a dynamic array to store elements of the vector. When the capacity
   * of the vector is exhausted, the array capacity is doubled.
   */
 
  static const int INITIAL_CAPACITY = 10;
  
  /* Instance variables */
  Vector* array;
  int capacity;
  int count;

  /* Private methods */

  deepCopy(const Vector<valueType> &src);
  expandCapacity();
  
}

/*
 * Implementation Notes : Constructor and Destructor
 * ------------------------------------------------------------------------------------------
 * The constructors allocate heap memory for the dynamic array and initialise other instance 
 * variables for the vector. The destructor frees this heap memory.
 */

  template<typename valueType>
  Vector<valueType>::Vector(){
    capacity = INITIAL_CAPACITY;
    array = new valueType[capacity];
    count=0;
  } 

  template<typename valueType>
  Vector<valueType>::Vector(int size, valueType defaultVal = valueType()){
    capacity = INITIAL_CAPACITY;
    array = new valueType[capacity];
    for(int i=0;i<count;i++){
      array[i] = defaultVal;
    }
    count=size;
  } 

  template<typename valueType>
  Vector<valueType>::~Vector(){
    delete[] array;
  }
  
/*
 * Implementation Notes : size,isEmpty,clear
 * -------------------------------------------------------------------
 * These methods only require count field and do not look at the data.
 */

  template<typename valueType>
  int Vector<valueType>::size() const{
    return count;
  }

  template<typename valueType>
  bool Vector<valueType>::isEmpty() const{
    return (count==0);
  }

  template<typename valueType>
  void Vector<valueType>::clear(){
    count = 0;
  }

/*
 * Implementation Notes : get,set
 * -----------------------------------------------------------------------------------------------
 * These methods first check whether the index is inside the bounds and return the val/modify it.
 */

  template<typename valueType>
  valueType Vector<valueType>::get(int index) const{
    if(index<0 || index>=count) throw "Error : Index out of bounds";
    return array[index];
  }

  template<typename valueType>
  valueType Vector<valueType>::set(int index,valueType value) const{
    if(index<0 || index>=count) throw "Error : Index out of bounds";
    array[index] = value;
  }

/*
 * Implementation Notes : operator []
 * ------------------------------------------------------------------------------------------------- 
 * Checks to see whether index is out of bounds. Throws an error if index is less than 0 or greater
 * than count[current number of elements]. Returns by reference to make sure that it can be used 
 * as a lvalue along with being used as a selection operator as a rvalue.
 */

  template<typename valueType>
  valueType& Vector<valueType>::operator=(int index){
    if(index<0 || index>=count) throw "Error : Index out of bounds";
    return array[index];
  }

/* 
 * Implementation Notes : insert,remove,add
 * -------------------------------------------------------------------------------
 * These methods involve shifting of elements to insert, remove and add elements.
 * Incase of insert and add, the vector's dynamic array expands to twice its 
 * capacity in case of a capacity crunch.
 */

  template<typename valueType>
  void Vector<valueType>::insert(int index, valueType value){
    if(index<0||index>count) throw "Error : Index out of bounds"; 
    if(capacity==count) expandCapacity();
    for(int i= count;i>=index;i--){
      array[i] = array[i-1];
    }
    array[index] = value;
    count++;
  } 
  
  template<typename valueType>
  void Vector<valueType>::remove(int index){
    if(index<0||index>=count) throw "Error : Index out of bounds"; 
    for(int i= index;i<count;i++){
      array[i] = array[i+1];
    }
    array[index] = value;
    count--;
  } 

  template<typename valueType>
  void Vector<valueType>::add(valueType value){
    if(capacity==count) expandCapacity();
    array[count] = value;
  }

/* 
 * Implementation Notes : copy constructor and assignment operator
 * ----------------------------------------------------------------
 * These work by making use of the deepCopy() method.
 */

  template<typename valueType>
  Vector<valueType>::Vector(const Vector<valueType> &src){
    deepCopy(src);
  }

  template<typename valueType>
  Vector<valueType>& Vector<valueType>::operator=(const Vector<valueType> &src){
    if(!(this==&src)){
      delete[] array;
      deepCopy(src);
    }
    return *this;
  }

/* 
 * Implementation Notes : deepCopy()
 * -------------------------------------------------------------------
 * Private method that produces a deep copy of the vector in context.
 */

  template<typename valueType>
  void Vector<valueType>::deepCopy(const Vector<valueType>& src){
    count = src.count;
    capacity = src.capacity + INITIAL_CAPACITY;
    array = new valueType[capacity];
    for(int i=0;i<count;i++){
      array[i] = src[i];
    }
  }

/*
 * Implementation Notes : expandCapacity()
 * ----------------------------------------
 * Doubles the capacity of the array.
 */

  template<typename valueType>
  void Vector<valueType>::expandCapacity(){
    Vector* oldArray = array;
    capacity *=2;
    Vector* newArray = new valueType[capacity];
    for(int i=0;i<count;i++){
      newArray[i] = array[i];
    }
    array = newArray;
    delete[] oldArray;
  }



#endif
