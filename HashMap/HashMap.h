/* 
 * File : HashMap.h
 * ---------------------------------------------------------------------------------
 * This file exports an interface for a templatized version of the HashMap Class
 * This version of the implementation of the HashMap class works only for primitive 
 * key types.Only allows unique keys.
 */

#ifndef HashMap_h
#define HashMap_h

#include "hashfunctions.h"
#include "hashfunctions.cpp"
using namespace std;//This is important incase one of key/Val pairs is string.

template<typename keyType, typename valueType> class HashMap{

  /* The public interface for the HashMap class */

  public :  

  /* 
   * Constructors : HashMap
   * Usage        : HashMap<int,string> hashmap;
   * -------------------------------------------
   * Initialise an empty hashmap. 
   */
   
    HashMap();

   /* 
    * Destructor : ~HashMap
    * --------------------------------------------------
    * Frees any heap memory associated with the hashmap
    */
  
    ~HashMap();

   /* 
    * Method : size
    * Usage  : int sizeOfMap = hashmap.size();
    * ---------------------------------------------------
    * Returns the number of keyvalue pairs in the hashmap.
    */
  
    int size() const;

   /* 
    * Method : isEmpty 
    * Usage  : if(hashmap.isEmpty());
    * -------------------------------------  
    * Returns true if the hashmap is empty.
    */
     
    bool isEmpty() const;

   /*
    * Method : clear()
    * Usage  : hashmap.clear();
    * -------------------------------------------------
    * Deletes all the key value pairs from the hashmap.
    */ 

    void clear();

   /*
    * Method : get
    * Usage  : hashmap.get(keyValue);
    * ---------------------------------------------------------------------------
    * Returns the Value corresponding to the key passed in stored in the hashmap.
    */
  
    valueType get(const keyType& key) const;
 
   /* 
    * Method : put
    * Usage  : hashmap.put(key,value);
    * ------------------------------------------------------------------------------------------
    * Inserts the key value pair into the map.As keys are unique, any past data is overwritten.
    */  
  
    void put(const keyType& key,const valueType& value);

   /*
    * Method : remove
    * Usage  : hashmap.remove(key);
    * ---------------------------------------------------------------
    * Removes the key value pair corresponding to the key passed in. 
    */

    void remove(const keyType& key);

   /*   
    * Method : containsKey
    * Usage  : if(hashmap.containsKey(key));
    * ---------------------------------------------------------------------
    * Returns true if the hashmap contains the given key, false otherwise.
    */

    bool containsKey(const keyType& key) const;
   
  private : 

  /* 
   * Representational Notes : 
   * -----------------------------------------------------------------------------------------------
   * This version of a hashmap uses an array to keep track of buckets , which store pointers to the
   * start of linked lists of structures containing the key value pairs which are to be stored in 
   * the hashmap. This kind of strategy allows for get and put to operate in O(1) time, given there
   * are no collisions. In case of collisions, the time is O(N) in worst case, where all keys are 
   * hashed to the same bucket. The Implementation makes use of hash functions for all primitive 
   * types exported by the hashfunctions.h interface, as included in the beginning.The represent
   * -ation also allows for rehashing using dynamic array size expansion capabilties.Keep the 
   * nBuckets such that nBuckets is a prime number/ it has no factor in 1 to 20 in order to
   * help uniform distribution of hash codes.
   */
   
  static const int INITIAL_BUCKETS = 13;
  static const double REHASH_THRESHHOLD = 0.7;

  /* Structure to store key value pairs */
  struct Cell{
    keyType key;
    valueType value;
    Cell* link;  
  };

  /* Instance variables */
  Cell **buckets;
  int nBuckets;
  int cellCount;

  /* Private methods */  
  Cell *findCell(int bucket,const keyType& key) const;
  void expandAndRehash();

  /* Making copying illegal */
  HashMap(const Hashmap<keyType,valueType>& hashmap){};
  HashMap<keyType,valueType>& operator=(const Hashmap<keyType,valueType>& hashmap){return *this;};

};

/* 
 * Implementation Notes : Constructor and Destructor
 * -----------------------------------------------------------------------------------
 * Initialize an empty hashmap and free heap memory attached to hashmap respectively.
 */

template<typename keyType,typename valueType>
HashMap<keyType,valueType>::HashMap(){
  cellCount = 0;
  nBuckets = INITIAL_BUCKETS;
  buckets = new Cell*[nBuckets];
  for(int i=0;i<nBuckets;i++)
    buckets[i] = NULL;
  return;
}

template<typename keyType,typename valueType>
HashMap<keyType,valueType>::~HashMap(){
  clear();
}

/* 
 * Implementation Notes : clear
 * --------------------------------------------------------------------------------------------------
 * Freez the heap memory associated with the entire HashMap by looping through it and freeing memory 
 * associated with every linked list whose starting address is stored at every bucket. Runs in O(N)
 * time.
 */

template<typename keyType,typename valueType>
void HashMap<keyType,valueType>::clear(){
 for(int i=0;i<nBuckets;i++){
    Cell *cp = buckets[i];
    while(cp!=NULL){
      Cell *oldCell = cp;
      cp = cp->link;
      delete oldCell;
    }
    buckets[i] = cp;
  } 
  cellCount = 0;
}

/* 
 * Implementation Notes : size, isEmpty
 * -------------------------------------------------------------
 * Run in constant time and make use of the cellCount variable.
 */

template<typename keyType,typename valueType>
int HashMap<keyType,valueType>::size() const{
  return cellCount;
}

template<typename keyType,typename valueType>
bool HashMap<keyType,valueType>::isEmpty() const{
  return cellCount==0;
}

/* 
 * Implementation Notes : get.
 * ----------------------------------------------------------------------------------------
 * Uses the hash function for the keyType and generates a hash code. Sees to it if it can 
 * find value for corresponding key in linked list corresponding to bucket which the key is
 * hashed to.Get takes worst case O(N), max time for findcell.Usually expected time is much 
 * less due to loading factor. Expected time is O(1). 1 + REHASH_THRESHOLD/2.
 */

template<typename keyType,typename valueType>
valueType HashMap<keyType,valueType>::get(const keyType& key) const{
  int bucket = hashfunction(key)%nBuckets;
  Cell *cp = findCell(bucket,key);
  return cp==NULL?valueType():cp->value;
}

/* 
 * Implementation Notes : put
 * ------------------------------------------------------------------------------------------
 * Checks if REHASH THRESHOLD is reached. If yes, expands capacity by approximately doubling 
 * the array size, and updates the nBuckets variable. Rehashing is handles by the expandAndRehash
 * function. puts the the key value pair in apt bucket later.Note that any new element is added
 * to the start of the linked list so that addition operation takes constant time.So, in turn,
 * put takes worst case O(N)[max for find Cell] + O(1) time.Expected time is O(1). 
 */

template<typename keyType,typename valueType>
void HashMap<keyType,valueType>::put(const keyType& key,const valueType& value) {
  if(cellCount/nBuckets>=REHASH_THRESHHOLD) expandAndRehash();
  int bucket = hashfunction(key)%nBuckets;
  Cell *cp = findCell(bucket,key);
  if(cp==NULL){
    cp = new Cell;
    cp->key = key;
    cp->link = buckets[bucket];
    buckets[bucket] = cp;
  }
  cp->value = value;
  cellCount++;
}

/*
 * Implementation Notes : contains Key
 * ------------------------------------
 * Takes help of the findCell function.
 */

template<typename keyType,typename valueType>
bool HashMap<keyType,valueType>::containsKey(const keyType& key) const {
  int bucket = hashfunction(key)%nBuckets;
  return findCell(bucket,key)!=NULL;
}

/*
 * Implementation Notes : remove
 * -------------------------------------------------------------------------------------------
 * Removes a particular key by first finding it using findCell. Takes O(N) time in worst case.
 * Expected time is 1+REHASH_THRESHHOLD. O(1).
 */

template<typename keyType,typename valueType>
void HashMap<keyType,valueType>::remove(const keyType& key){
  int bucket = hashfunction(key)%nBuckets;
  Cell *cp = findCell(bucket,key);
  Cell *prevCell;
  for(prevCell = buckets[bucket];(prevCell->link)!=cp;prevCell = prevCell->link){}
  prevCell->link = cp->link;
  delete cp;
}

/* 
 * Implementation Notes : findCell
 * ------------------------------------------------------------------------------------------------
 * Loops to find the address of cell having key attribute equal to passed key in the given bucket.
 */

template<typename keyType,typename valueType>
Cell *HashMap<keyType,valueType>::findCell(int bucket,const keyType& key){
  Cell *start = buckets[bucket];
  while(start!=NULL){
    if((start->key)==key)
      break;
    start = start->link;
  }
  return start;    
}

/*
 * Implementation Notes : expandAndRehash
 * ------------------------------------------------------------------------------------------------
 * Expands the capacity of the dynamic array of buckets and rehsashes the table.Called in case the
 * REHASH_THRESHHOLD is exceeded. Takes O(N) time.
 */

template<typename keyType,typename valueType>
void HashMap<keyType,valueType>::expandAndRehash(){
  int oldnBuckets = nBuckets;
  int nBuckets *= 1.0/REHASH_THRESHHOLD;
  Cell **bucketsNew = new Cell*[nBuckets];
  for(int i=0;i<oldnBuckets;i++){
    Cell *start = buckets[i];
    while(start!=NULL){ 
      keyType key = start->key;

      int bucket = hashfunction(key)%nBuckets;

      Cell *cp = new Cell;
      cp->key = key;
      cp->link = bucketsNew[bucket];
      cp->value = value;
      bucketsNew[bucket] = cp;

      start = start->link;
    }    
  }
  Cell **oldBuckets = buckets;
  delete oldBuckets[];
  buckets = bucketsNew;
}


#endif

