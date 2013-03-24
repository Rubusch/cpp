// rciptr.cpp
/******************************************************************************
 *                  Template Class RCIPtr (from pp. 209-210)                   *
 *                                                                             *
 * The code for RCIPtr has changed over the years in response to errors        *
 * both in the original source code as well as in the subsequent fixes.  You   *
 * can find a complete list of changes at the More Effective C++ errata page.  *
 * The code here is accurate as of the 13th printing of the book.              *
 *******************************************************************************

annotations:

  COW - copy on write, 
  working with the operator[] to be able to access the single elements
*/


#ifndef RCI_PTR
#define RCI_PTR


#include "rcobject.hpp"


template<class T>
class RCIPtr 
{
public:
  // ctor
  RCIPtr(T* realPtr = 0);

  // copy ctor
  RCIPtr(const RCIPtr& rhs);

  // dtor
  ~RCIPtr();

  // op=
  RCIPtr& operator=(const RCIPtr& rhs);

  // smart pointer stuff  
  T* operator->() const;
  T& operator*() const;
  
  RCObject& getRCObject()
  {
    // give clients access to isShared, etc. 
    return *counter;
  }                  
  
private:
  struct CountHolder: public RCObject 
  {
    ~CountHolder();
    T *pointee;
  };
  
  CountHolder *counter;
  void init();
};


/************************************************************************************/


/*
  init called by the ctor
//*/
template<class T>
void RCIPtr<T>::init()
{
  if (counter->isShareable() == false) {
    T *oldValue = counter->pointee;
    counter = new CountHolder;
    counter->pointee = oldValue ? new T(*oldValue) : 0;
  } 
  
  counter->addReference();
}


/*
  ctor
//*/
template<class T>
RCIPtr<T>::RCIPtr(T* realPtr)
  : counter(new CountHolder)
{ 
  counter->pointee = realPtr;
  init();
}


/*
  copy ctor
//*/ 
template<class T>
RCIPtr<T>::RCIPtr(const RCIPtr& rhs)
  : counter(rhs.counter)
{ 
  init(); 
}


/*
  dtor
//*/
template<class T>
RCIPtr<T>::~RCIPtr()
{ 
  counter->removeReference(); 
}


/*
  operator= - remember rule of big three (cpy ctor, operator= and dtor)!
//*/
template<class T>
RCIPtr<T>& RCIPtr<T>::operator=(const RCIPtr& rhs)
{
  if(counter != rhs.counter){         
    counter->removeReference();     
    counter = rhs.counter;
    init();
  }

  return *this;
}


/*
  op-> - smart pointer 
//*/
template<class T>
T* RCIPtr<T>::operator->() const
{ 
  return counter->pointee; 
}


/*
  op* - smart pointer
//*/
template<class T>
T& RCIPtr<T>::operator*() const
{ 
  return *(counter->pointee); 
}


/************************************************************************************/


/*
  inner class dtor
//*/
template<class T>
RCIPtr<T>::CountHolder::~CountHolder() 
{ 
  delete pointee; 
}


#endif
