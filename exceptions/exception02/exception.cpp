// exception.cpp
/*
  Demonstrates another example of usage of the exceptions
//*/


#include <iostream>
#include <cstdlib> // exit()


template<class T>
class SomeClass
{
private:
  T *ptr;

public:
  // ctor
  SomeClass(T t);

  // dtor - since we have a dynamic pointer!
  ~SomeClass();

  T getVal();
};

template<class T>
SomeClass<T>::SomeClass(T t)
  : ptr(NULL)
{
  std::cout << "\tSomeClass::SomeClass() - ctor\n";

  // allocate
  try{
    ptr = new T;
  }catch(...){ // ... catches every exception
    std::cerr << "ERROR: allocation failed" << std::endl;
    delete ptr;
    throw;

    exit(-1);
  }

  // init
  *ptr = t;
}

template<class T>
SomeClass<T>::~SomeClass()
{
  std::cout << "\tSomeClass::~SomeClass() - dtor\n";

  // free memory - avoid exceptions in the dtor
  delete ptr;
  ptr = NULL;
}

template<class T>
T SomeClass<T>::getVal()
{
  std::cout << "\tSomeClass::getVal()\n";

  try{
    if(NULL == ptr){
      throw "no delete necessary!";
    }
    return *ptr;
  }catch(char const* str){ // catches a thrown string exception
    std::cerr << "ERROR: " << str << std::endl;
  }
  return "empty";
}


/*
  some main
//*/
int main()
{
  using namespace std;

  cout << "instantiate a class\n";
  SomeClass< string > sc("Hello World!");
  cout << endl;

  cout << "get value()\n";
  cout << sc.getVal() << endl;
  cout << endl;

  cout << "READY.\n";
  return 0;
}
