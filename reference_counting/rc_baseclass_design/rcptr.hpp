// rcptr.hpp
/*
  Implementation of reference counting as smart pointer!

  Template class for smart poitners-to-T objects. T must
  support the RCObject interface, typically by inheriting 
  from RCObject
//*/

#ifndef RC_PTR
#define RC_PTR


#include "someclass.hpp"


template<class T> 
class RCPtr
{
public: 
  // ctor
  RCPtr(T* realPtr = 0);

  // copy ctor
  RCPtr(const RCPtr& rhs);

  // dtor
  ~RCPtr();

  // op=
  RCPtr& operator=(const RCPtr& rhs);

  // various operators for smart pointer functionality
  T* operator->() const;
  T& operator*() const;

private:
  T *pointee;
  void init();
};


/************************************************************************************

    Because of the template design - here everything in the .hpp file!

************************************************************************************/


template<class T>
void RCPtr<T>::init()
{
  if(pointee == 0) return;

  if(pointee->isShareable() == false){
    pointee = new T(*pointee);
  }

  pointee->addReference();
}


/************************************************************************************/


/*
  ctor
//*/
template<class T>
RCPtr<T>::RCPtr(T* realPtr)
  : pointee(realPtr)
{ 
  init(); 
}


/*
  copy constructor
//*/
template<class T>
RCPtr<T>::RCPtr(const RCPtr& rhs)
  : pointee(rhs.pointee)
{ 
  init(); 
}


/*
  dtor
//*/
template<class T>
RCPtr<T>::~RCPtr()
{ 
  std::cout << "RCPtr<T>::DTOR\n";

  if(pointee)pointee->removeReference();
}


/************************************************************************************/


/*
  operator=
//*/
template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
  if(pointee != rhs.pointee){
    if(pointee) pointee->removeReference();
    pointee = rhs.pointee;
    init();
  }
  return *this;
}


/*
  operator->
//*/
template<class T>
T* RCPtr<T>::operator->() const 
{ 
  return pointee; 
}


/*
  operator*
//*/
template<class T>
T& RCPtr<T>::operator*() const 
{ 
  return *pointee; 
}


#endif

