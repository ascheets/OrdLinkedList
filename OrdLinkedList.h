#pragma once
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include "OrdLinkedListExceptions.h"

using namespace std;

template <class T>
class OrdLinkedList
{
 public:
  OrdLinkedList();
  ~OrdLinkedList();

  void insert(const T& elem);
 
  bool find(const T& elem);

  bool remove(const T& elem);
 
  T at(int pos);
  T operator [] (int pos);

  bool first(T& elem);
  bool next(T& elem);
  bool last(T& elem);
  bool previous(T& elem);

  int size();
  bool isEmpty();

  void printAllFromHead();
  void printAllFromTail();

 private:

  //create node structure
  struct Node
  {
    T data;
    //pointer to previous node, closer to head
    Node* p_prev;
    //pointer to next node, closer to tail
    Node* p_next;
  };

  Node* p_head;
  Node* p_tail;
  Node* p_marker;
 
  Node* p_traversal;
  int p_traversalPos;

  int numElements;
  
};

//OrdLinkedList constructor
template <class T>
OrdLinkedList <T> :: OrdLinkedList()
{
  //what should happen when OrdLinkedList is initialized?
  //set head to zero
  p_head = 0;
  //set tail to zero
  p_tail = 0;
  //set current node to zero
  p_marker = 0;
  //since there are no elements in this list yet
  numElements = 0;
  //set p_traversal
  p_traversal = 0;
      
}

//OrdLinkedList destructor
template <class T>
OrdLinkedList <T> :: ~OrdLinkedList()
{
  //temp node helper pointer
  Node* p_temp;

  //while the list is not empty
  while(!isEmpty()){

    //set pointer to head node
    p_temp = p_head;

    //move the head one towards tail
    p_head = p_head->p_next;

    //delete the current p_head
    delete p_temp;

    //increment numElements
    numElements--;
  }
}

//insert
template <class T>
void OrdLinkedList <T> :: insert(const T& elem)
{
  //create new node on the heap
  Node* p_newNode = new Node;

  //initialize search node pointer
  Node* p_search = p_head;

  //set data for new node
  p_newNode->data = elem;

  //if the list is empty
  if(isEmpty()){

    //set newNode values
    p_newNode->p_next = 0;
    p_newNode->p_prev = 0;

    //update dll values
    p_head = p_newNode;
    p_tail = p_newNode;
    //p_marker = p_newNode; //for now don't touch p_marker here...

  }
  //if the list is not empty
  else{
    //quick check, does new elem belong at tail or head?
    //belongs at head
    if(p_newNode->data <= p_head->data){
      
      //update node data
      p_head->p_prev = p_newNode;

      p_newNode->p_next = p_head;
      p_newNode->p_prev = 0;
      
      //update list data
      p_head = p_newNode;

    }
    //belongs at tail
    else if(p_newNode->data > p_tail->data){

      //update node data
      p_tail->p_next = p_newNode;
      
      p_newNode->p_prev = p_tail;
      p_newNode->p_next = 0;

      //update list data
      p_tail = p_newNode;

    }
    //otherwise insert somewhere in middle
    else{
      
      //iterate through list, trying to find correct position for newNode
      while(p_search != 0){

	//p_marker is equal to p_head at this point

	//if the new element is less than or equal to p_search->data
	if(p_newNode->data <= p_search->data){

	  //what list kind of looks like:
	  //[i-1][i][i+1]
	  //[p_search->p_prev][p_search][p_search->p_next]

	  Node* beforeMarker = p_search->p_prev;

	  //insert newNode correctly, hopefully...
	  beforeMarker->p_next = p_newNode;

          p_newNode->p_prev = beforeMarker;
	  p_search->p_prev = p_newNode;
	  p_newNode->p_next = p_search;	    

	  break;
	}

	//increment p_search
	p_search = p_search->p_next;
      }
    }
  }

  //update numElements
  numElements++;

}

//find
template <class T>
bool OrdLinkedList <T> :: find(const T& elem)
{
 
  bool retVal = false;
  
  //temp node* search helper
  Node* p_search = p_head;

  while(p_search != 0){
    
    if(p_search->data == elem){
      retVal = true;
      break;      
    }
    
    //else increment p_search
    p_search = p_search->p_next;

  }

  return retVal;

}

//remove
template <class T>
bool OrdLinkedList <T> :: remove(const T& elem)
{
  //assume the element is not in the list
  bool retVal = false;

  //temp Node* search helper
  Node* p_search = p_head;

  if(isEmpty()){
    //OrdLinkedListOutOfBoundsException error;
    //throw error;
    cout << "Trying to remove from an empty list...carry on" << endl;
  }

  //this code shouldn't be called unless list has something in it...
  while(p_search != 0){

    //if val is equal to remove elem
    if(p_search->data == elem){

      //premptively change numElements and switch retVal
      numElements--;

      retVal = true;

      //is it the last item in the list?
      if(numElements == 0){
	
	//basically as we started
	p_head = 0;
	p_tail = 0;

	//free up old node space
	delete p_search;
	
	//just for good measure, reset p_marker...
	p_search = 0;

      }
      //it is not the last item in the list...
      else{
	
	  //is item head?
	  if(p_search == p_head){

	    //adjust p_head
	    p_head = p_head->p_next;

	    //free up old item
	    delete p_head->p_prev;
	    p_head->p_prev = 0;

	  }

	  //is item tail?
	  else if(p_search == p_tail){

	    //adjust p_tail
	    p_tail = p_tail->p_prev;

	    //free up old item
	    delete p_tail->p_next;
	    p_tail->p_next = 0;

	  }

	  //is item normal?
	  else{

	    //adjust pointers so that p_search prev and next point to each other
	    p_search->p_next->p_prev = p_search->p_prev;
    	    p_search->p_prev->p_next = p_search->p_next;

	    //free up old item
	    delete p_search;
	  }
      }
      
      //we have removed an item, exit while loop
      break;    
    }
    
    //increment p_search
    p_search = p_search->p_next;
  }
  
  return retVal;

}

//at
template <class T>
T OrdLinkedList <T> :: at(int pos)
{
 
  //object to return eventually
  T retVal;

  //search helper node*
  Node* p_search;
  //position ints
  int headPos = 0;
  int tailPos = numElements;

  int count = 0;
  
  //if pos isn't a valid index
  if(pos >= size() ||
     pos < 0){
    OrdLinkedListOutOfBoundsException error;
    throw error;
  }
  //if pos is within used potion of array
  else{
      //if p_traversal hasn't been initialized yet
      if(p_traversal == 0){

	  //set position of traversal pointer
	  p_traversalPos = pos;

	  //check whether should go from head or tail
	  //from head
	  if(abs(p_traversalPos) < abs(p_traversalPos-tailPos)){
	      
	      //start search from head
	      p_search = p_head;

	      while(p_search != 0){
     	      
		  //if the count is equal to the position we are looking for...
		  if(count == pos){
		      retVal = p_search->data;
		      //set traversal pointer
		      p_traversal = p_search;
		      break;
		  }
      
		  //otherwise increment p_search
		  p_search = p_search->p_next;
	      }
	  }
	  //from tail
	  else{

	      //start search from tail
	      p_search = p_tail;

	      while(p_search != 0){
     	      
		  //if the count is equal to the position we are looking for...
		  if(count == pos){
		      retVal = p_search->data;
		      //set traversal pointer
		      p_traversal = p_search;
		      break;
		  }
      
		  //otherwise increment p_search
		  p_search = p_search->p_prev;
	      }
	  }	  
      }
      //if p_traversal has been initialized
      else{
	  
	  int fromHead = pos;
	  int fromTail = abs(tailPos - pos);
	  int fromTrav = abs(p_traversalPos - pos);

	  //at this point, p_traversal, p_traversalPos, headPos and tailPos should be set
	  //check which distance is smallest
	  if(fromHead < fromTail &&
	     fromHead < fromTrav){
	      //start search from head
	      p_search = p_head;

	      while(p_search != 0){
     	      
		  //if the count is equal to the position we are looking for...
		  if(count == pos){
		      retVal = p_search->data;
		      //set traversal pointer
		      p_traversal = p_search;
		      break;
		  }
      
		  //otherwise increment p_search
		  p_search = p_search->p_next;
	      }
	  }
	  else if(fromTail < fromHead &&
		  fromTail < fromTrav){
	      //start search from tail
	      p_search = p_tail;

	      while(p_search != 0){
     	      
		  //if the count is equal to the position we are looking for...
		  if(count == pos){
		      retVal = p_search->data;
		      //set traversal pointer
		      p_traversal = p_search;
		      break;
		  }
      
		  //otherwise increment p_search
		  p_search = p_search->p_prev;
	      }
	  }
	  else{
	      //start from traversal pointer
	      //check whether to go to left or right of traversal pointer
	      if(pos < p_traversalPos){
		  //go left
		  
		  //start from traversal pointer
		  p_search = p_traversal;

		  while(p_search != 0){
     	      
		      //if the count is equal to the position we are looking for...
		      if(count == pos){
			  retVal = p_search->data;
			  //set traversal pointer
			  p_traversal = p_search;
			  break;
		      }
      
		      //otherwise increment p_search towards left
		      p_search = p_search->p_prev;
		  }

	      }
	      else{
		  //go right

		  //start from traversal pointer
		  p_search = p_traversal;

		  while(p_search != 0){
     	      
		      //if the count is equal to the position we are looking for...
		      if(count == pos){
			  retVal = p_search->data;
			  //set traversal pointer
			  p_traversal = p_search;
			  break;
		      }
      
		      //otherwise increment p_search towards right
		      p_search = p_search->p_next;
		  }
	      }
	  }
      }
  }


  return retVal;

}

//operator []
template <class T>
T OrdLinkedList <T> :: operator [] (int pos)
{
  //call and return result of at() function
  return at(pos);
}

//first()
template <class T>
bool OrdLinkedList <T> :: first(T& elem)
{
  //if list is not empty this function places
  //current pointer at head of list

  //assume there is not a first item
  bool retVal = false;

  //if the list is not empty
  if(!isEmpty()){
    
    //indicate there is a first item
    retVal = true;

    //copy data into reference parameter
    elem = p_head->data;

    //store current node that is being processed
    p_marker = p_head;

  }

  return retVal;

}

//next()
template <class T>
bool OrdLinkedList <T> :: next(T& elem)
{
  //assume at tail of list
  bool retVal = false;

  //if we have not processed all the elements
  //moving tailwards
  if(p_marker->p_next != 0){
    
    //move the current pointer towards tail
    p_marker = p_marker->p_next;

    //indicate there is another p_next
    retVal = true;

    //copy the data into ref parameter
    elem = p_marker->data;
  }

  return retVal;

}

//last()
template <class T>
bool OrdLinkedList <T> :: last(T& elem)
{
  //if list is not empty this function places
  //current pointer to tail of list
  
  bool retVal = false;

  //if list is not empty
  if(!isEmpty()){

    //indicate there is a last item
    retVal = true;

    //copy data into ref parameter
    elem = p_tail->data;

    //set current node to last/tail
    p_marker = p_tail;

  }

  return retVal;

}

//previous
template <class T>
bool OrdLinkedList <T> :: previous(T& elem)
{
  //if list is not empty this function moves
  //current pointer towards head

  //assume we are at head
  bool retVal = false;

  //if we have not processed all the elements
  if(p_marker->p_prev != 0){

    //move current pointer towards head one
    p_marker = p_marker->p_prev;

    //indicate there is another item
    retVal = true;

    //copy data of item into ref param
    elem = p_marker->data;
     
  }

  return retVal;

}

//size()
template <class T>
int OrdLinkedList <T> :: size()
{
  return numElements;
}

//isEmpty()
template <class T>
bool OrdLinkedList <T> :: isEmpty()
{
  return (size() == 0);
}

/*

//printAllFromHead()
template <class T>
void OrdLinkedList <T> :: printAllFromHead()
{

}

//printAllFromTail()
template <class T>
void OrdLinkedList <T> :: printAllFromTail()
{

}

*/
