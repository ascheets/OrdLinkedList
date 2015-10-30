#pragma once
#include <iostream>
#include <stdlib.h>
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
    p_marker = p_newNode;

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
      
      //helper T object
      T val;
      
      //iterate through list, trying to find correct position for newNode
      if(first(val)){

	//p_marker is equal to p_head at this point

	//each time this loop runs, val should be next item in list
	while(next(val)){

	  //p_marker is set to one towards tail by next(val)

	  //val is p_marker->data
	  //if the new element is less than or equal to current marker
	  //place it before current marker
	  if(p_newNode->data <= val){

	    //want to insert p_newNode just before p_marker 
	    //[p_marker->p_prev][p_marker][p_marker->p_next]
	    //create helper pointer
	    Node* beforeMarker = p_marker->p_prev;

	    //insert newNode correctly, hopefully...
	    beforeMarker->p_next = p_newNode;

	    p_newNode->p_prev = beforeMarker;

	    p_marker->p_prev = p_newNode;
	    p_newNode->p_next = p_marker;	    
	    
	    break;
	  }
	}
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

  //helper T object
  T val;

  if(first(val)){
    
    if(val == elem){
      retVal = true;
    }
    else{
      while(next(val)){
	if(retVal == true)
	  break;
	if(val == elem){
	  retVal = true;
	  break;
	}
      }
    }
  }
  return retVal;
}

//remove
template <class T>
bool OrdLinkedList <T> :: remove(const T& elem)
{
  //assume the element is not in the list
  bool retVal = false;

  //helper T object
  T val;

  //this code shouldn't be called unless list has something in it...
  if(first(val)){

    //if val is equal to remove elem
    if(val == elem){

      //premptively change numElements and switch retVal
      numElements--;

      retVal = true;

      //is it the last item in the list?
      if(numElements == 0){
	
	//basically as we started
	p_head = 0;
	p_tail = 0;

	//free up old node space
	delete p_marker;
	
	//just for good measure, reset p_marker...
	p_marker = 0;

      }
      //it is not the last item in the list...
      else{
	
	  //is item head?
	  if(p_marker == p_head){

	    //adjust p_head
	    p_head = p_head->p_next;

	    //free up old item
	    delete p_head->p_prev;
	    p_head->p_prev = 0;

	    //adjust p_marker
	    p_marker = p_head;

	  }

	  //is item tail?
	  else if(p_marker == p_tail){

	    //adjust p_tail
	    p_tail = p_tail->p_prev;

	    //free up old item
	    delete p_tail->p_next;
	    p_tail->p_next = 0;

	    //adjust p_marker
	    p_marker = p_head;

	  }

	  //is item normal?
	  else{

	    //adjust pointers so that p_marker prev and next point to each other
	    p_marker->p_next->p_prev = p_marker->p_prev;
    	    p_marker->p_prev->p_next = p_marker->p_next;

	    //free up old item using tempNode
	    Node* p_temp = p_marker;
	    
	    //adjust p_marker
	    p_marker = p_marker->p_next;

	    //delete item temp pointer points to
	    delete p_temp;
	    p_temp = 0;

	  }

	  //iterate through list
	  while(next(val)){
      
	    //if val is equal to remove elem
	    if(val == elem){
	
	      //preemptively change numElements and switch retVal
	      numElements--;

	      retVal = true;

	      //is it the last item in the list?
	      if(numElements == 0){
		
		//basically as we started
		p_head = 0;
		p_tail = 0;

		//free up old node space
		delete p_marker;

		//just for good measure, reset p_marker...
		p_marker = 0;

		//don't iterate again, we know the list is empty...
		break;
	      }
	      //not the last item in the list...
	      else{
		  //is item head?
		  if(p_marker == p_head){

		    //adjust p_head
		    p_head = p_head->p_next;

		    //free up old item
		    delete p_head->p_prev;
		    p_head->p_prev = 0;

		    //adjust p_marker
		    p_marker = p_head;

		  }
		  //is item tail?
		  else if(p_marker == p_tail){
		    
		    //adjust p_tail
		    p_tail = p_tail->p_prev;

		    //free up old item
		    delete p_tail->p_next;
		    p_tail->p_next = 0;

		    //adjust p_marker
		    p_marker = p_head;

		  }
		  //is item normal?
		  else{

		    //adjust pointers so that p_marker prev and next point to each other
		    p_marker->p_next->p_prev = p_marker->p_prev;
		    p_marker->p_prev->p_next = p_marker->p_next;

		    //free up old item using tempNode
		    Node* p_temp = p_marker;
	    
		    //adjust p_marker
		    p_marker = p_marker->p_next;

		    //delete item temp pointer points to
		    delete p_temp;
		    p_temp = 0;

		  }
	      }

	    }
	  }
      }
    
    }
  }
  else{
    //cout << "Tried to remove from an empty list" << endl;
  }

  return retVal;

}

//at
template <class T>
T OrdLinkedList <T> :: at(int pos)
{
 
  //object to return eventually
  T retVal;

  //helper T object
  T val;

  int myCount = 0;

  if(pos >= size()){
    OrdLinkedListOutOfBoundsException error;
    throw error;
  }
  else{
    if(first(val)){
      //right now val is at index 0
      if(myCount == pos){
	retVal = val;
      }
      else{
	while(next(val)){
	  myCount++;

	  if(myCount == pos){
	    retVal = val;
	    break;
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

/*//printAllFromHead()
template <class T>
void OrdLinkedList <T> :: printAllFromHead()
{
  //helper T object
  T val;

  if(isEmpty()){
    
    //if the list is empty
    cout << "Not printing because list is empty" << endl;

  }
  else{
    
    //if there is a last item (list is not empty)
    //store the element in val
    if(first(val)){

      cout << val << endl;

      //while we are not at the end, store each element in val
      while(next(val)){

	cout << val << endl;

      }
    }
  }
}

//printAllFromTail()
template <class T>
void OrdLinkedList <T> :: printAllFromTail()
{
  //helper T object
  T val;

  if(isEmpty()){
    
    //if the list is empty
    cout << "Not printing because list is empty" << endl;
  
  }
  else{
    
    //if there is a last item (list is not empty)
    //store the element in val
    if(last(val)){

      cout << val << endl;

      //while we are not at the end, store each element in val
      while(previous(val)){

	cout << val << endl;

      }

    }
  }    
}

*/
