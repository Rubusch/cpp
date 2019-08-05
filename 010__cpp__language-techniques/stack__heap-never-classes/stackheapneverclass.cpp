// heapnever.cpp
/*
  Demonstrates a class that only can be instantiated on the stack, but not on the heap.
  private operator new() and operator delete()
//*/

#include <iostream>
#include <string>

using namespace std;


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
  cout << "HeapNever ctor" << endl;
}

template<class T>
HeapNever<T>::~HeapNever()
{
  cout << "HeapNever dtor" << endl;
}


int main()
{
  HeapNever<string> hn;

  // ERROR - operator new() is private!
  //  HeapNever<string> *pHn = new HeapNever<string>();

  cout << "READY.\n";
  return 0;
}


