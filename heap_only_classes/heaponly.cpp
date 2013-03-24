// heaponly.cpp
/*
  this class can only be constructed on the heap, because of the private declaration
  of its destructor.

  No instance on the stack will be possible as also no direct call to the destructor!
//*/


#include <iostream>
#include <string>



template<class T>
class HeapOnly
{
public:
  HeapOnly();
  // ...

  /*
    pseudo destructor - dtor is no more accessible!
  //*/
  void destroy() const;  

  /*
    private declaration of dtor
  //*/
private:
  ~HeapOnly();
};

template<class T>
HeapOnly<T>::HeapOnly()
{
  std::cout << "HeapOnly ctor" << std:: endl;
}

template<class T>
void HeapOnly<T>::destroy() const
{ 
  delete this; 
}

// if the dtor won't be implemented, it will lead to a linker error
template<class T>
HeapOnly<T>::~HeapOnly()
{}



int main()
{
  // ERROR - heap only, due to private dtor
  //  HeapOnly<std::string> ho; 
  
  HeapOnly<std::string> *pHo = new HeapOnly<std::string>();

  // ERROR - private dtor!
  //  delete pHo; 
  
  pHo->destroy();
  
  std::cout << "READY.\n" << std::endl;
  return 0;
}
