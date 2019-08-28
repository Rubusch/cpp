// rcptr.hpp
/*******************************************************************************
 *                 Template Class RCPtr (from pp. 203, 206)                    *
 *******************************************************************************

annotations:

  implementation of a smart pointer for a customized class supporting reference
  counting

  template class for smart pointers-to-T objects;
  T must support the RCObject interface
*/


#ifndef RC_PTR
#define RC_PTR


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

  // smart pointer stuff
  T* operator->() const;
  T& operator*() const;

private:
  T *pointee;
  void init();
};


/************************************************************************************/


/*
  init funciton called by the ctor
//*/
template<class T>
void RCPtr<T>::init()
{
  if (pointee == 0) return;

  if (pointee->isShareable() == false) {
    pointee = new T(*pointee);
  }

  pointee->addReference();
}


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
  copy ctor
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
  if(pointee){
    pointee->removeReference();
  }
}


/*
  op= - this code was modified for the book's 10th
//*/
template<class T>
RCPtr<T>& RCPtr<T>::operator=(const RCPtr& rhs)
{
  if(pointee != rhs.pointee){
    T *oldPointee = pointee;

    // printing
    pointee = rhs.pointee;
    init();

    if(oldPointee){
      oldPointee->removeReference();
    }
  }

  return *this;
}


/*
  smart pointer
//*/
template<class T>
T* RCPtr<T>::operator->() const
{
  return pointee;
}


/*
  smart pointer
//*/
template<class T>
T& RCPtr<T>::operator*() const
{
  return *pointee;
}

#endif

