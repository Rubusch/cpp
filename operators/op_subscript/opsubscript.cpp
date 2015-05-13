// opsubscript.cpp
/*
//*/

#include <iostream>
#include <cstdlib> // exit()


template<class T>
class FoobarContainer
{
private:
  const unsigned int SIZE;
  T* arr;

public:
  // ctor
  FoobarContainer(unsigned int size);

  // dtor
  ~FoobarContainer();
  
  // functions
  void init();

  // operators
  T& operator[](unsigned int idx);
};

template<class T>
FoobarContainer<T>::FoobarContainer(unsigned int size)
:SIZE(size), arr(NULL)
{
  std::cout << "ctor" << std::endl;
  /*
    if init() won't be called here - the code will compile, but the first usage of operator[] 
    will fail with signal 11
  //*/
  init();
}

template<class T>
FoobarContainer<T>::~FoobarContainer()
{
  std::cout << "dtor" << std::endl;
  delete [] arr;
}

template<class T>
void FoobarContainer<T>::init()
{
  try{
    if(NULL == (arr = new T[SIZE])) throw "memory allocation failed!"; 
  }catch(char* str){
    std::cerr << "ERROR: " << str << std::endl;
    delete arr;
    exit(-1);
  }

  for(unsigned int idx=0; idx<SIZE; ++idx){
    arr[idx] = idx;
  }
}




template<class T>
T& FoobarContainer<T>::operator[](unsigned int idx)
{
  try{
    if(idx >= SIZE) throw "index out of bounds!";    
  }catch(char* str){
    std::cerr << "ERROR: " << str << std::endl;
    exit(-2);
  }

  return arr[idx];
}




/*
  some main
//*/
int main()
{ 
  // alloc
  unsigned int containersize = 10;
  FoobarContainer<int> foo(containersize);

  // init - FIXME: doesn't work - Sig 11!
  foo[7] = 77;  

  // output
  std::cout << "the seventh element is: " << foo[7] << std::endl;

  std::cout << "READY.\n";
  return 0;
}
