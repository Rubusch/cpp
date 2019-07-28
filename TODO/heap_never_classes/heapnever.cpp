// heapnever.cpp
/*
  Demonstrates a class that only can be instantiated on the stack, but not on the heap.
  private operator new() and operator delete()
//*/

#include <iostream>
#include <string>


template<class T>
class HeapNever
{
public:
  HeapNever();
  ~HeapNever();
  // ...

private: // private declaration is sufficient!
  static void* operator new(size_t size);
  static void operator delete(void* ptr);
};

template<class T>
HeapNever<T>::HeapNever()
{
  std::cout << "HeapNever ctor" << std::endl;
}

template<class T>
HeapNever<T>::~HeapNever()
{
  std::cout << "HeapNever dtor" << std::endl;
}




int main()
{
  HeapNever<std::string> hn;

  // ERROR - operator new() is private!
  //  HeapNever<std::string> *pHn = new HeapNever<std::string>();


  std::cout << "READY.\n";
  return 0;
}


