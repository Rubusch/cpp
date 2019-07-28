// opassignment.cpp
/*
  demonstrates a overloaded copy assignment operator working in a derived class in conjunction with a
  overloaded assignment operator of a base class.
//*/

#include <iostream>
#include <string>
#include <cstdlib>

template<class T>
class Base;

template<class T>
class Derived;



/*
  base class
//*/
template<class T>
class Base
{
private:
  int baseValue;
  T* basePointer;

public:
  Base(int initVal, T initPtr);
  virtual ~Base();

  // copy assignment operator - base class
  virtual Base<T>& operator=(const Base<T>& deepcopy);

  int getBaseValue() const;
  T* getBasePointer() const;
  virtual void getAll();
};

template<class T>
Base<T>::Base(int initVal, T initPtr)
:baseValue(initVal), basePointer(NULL)
{
  try{
    basePointer = new T;
  }catch(...){
    std::cerr << "ERROR: allocation failed!\n";
    delete basePointer; basePointer = NULL;
    exit(-1);
  }

  *basePointer = initPtr;
}

template<class T>
Base<T>::~Base()
{
  delete basePointer; basePointer = NULL;
}

template<class T>
int Base<T>::getBaseValue() const
{
  return baseValue;
}

template<class T>
T* Base<T>::getBasePointer() const
{
  return basePointer;
}

template<class T>
void Base<T>::getAll()
{
  std::cout << "base class:\t" << baseValue << " \"" << *basePointer << "\"" << std::endl;
}

/*
  base class - copy assignemnt operator
//*/
template<class T>
Base<T>& Base<T>::operator=(const Base<T>& deepcopy)
{
  if(this == &deepcopy) return *this;

  baseValue = deepcopy.getBaseValue();

  if(NULL != deepcopy.getBasePointer()){
    // alloc new and init
    T *tmp = new T;
    *tmp = *(deepcopy.getBasePointer());

    // free old memory
    delete basePointer; basePointer = NULL;

    // reset
    basePointer = tmp;
  }

  return *this;
}





/*
  derived class
//*/
template<class T>
class Derived : public Base<T>
{
private:
  int derivedValue;
  T *derivedPointer;

public:
  Derived(int initVal, T initPtr, int initBaseVal, T initBasePtr);
  ~Derived(); // dtor because we use pointers

  // copy assignment operator
  Derived& operator=(const Derived& deepcopy);

  int getDerivedValue() const;
  T* getDerivedPointer() const;
  void getAll();
};

template<class T>
Derived<T>::Derived(int initBaseVal, T initBasePtr, int initVal, T initPtr)
  : Base<T>(initBaseVal, initBasePtr)
  , derivedValue(initVal)
  , derivedPointer(NULL)
{
  // alloc
  try{
    derivedPointer = new T;
  }catch(...){
    std::cerr << "ERROR: allocation failed!\n";
    delete derivedPointer; derivedPointer = NULL;
    exit(-1);
  }

  // init
  *derivedPointer = initPtr;
}

template<class T>
Derived<T>::~Derived()
{
  delete derivedPointer; derivedPointer = NULL;
}

template<class T>
int Derived<T>::getDerivedValue() const
{
  return derivedValue;
}

template<class T>
T* Derived<T>::getDerivedPointer() const
{
  return derivedPointer;
}

template<class T>
void Derived<T>::getAll()
{
  Base<T>::getAll();

  std::cout << "derived class:\t" << derivedValue << " \"" << *derivedPointer << "\"" << std::endl;
}

/*
  derived class - copy assignment operator
//*/
template<class T>
Derived<T>& Derived<T>::operator=(const Derived<T>& deepcopy)
{
  if(this == &deepcopy) return *this;

  // initializing a base class
  Base<T>::operator=(deepcopy);

  // ...or hack for old compilers
  //static_cast<Base<T>&>(*this) = deepcopy;

  // static pointer
  derivedValue = deepcopy.getDerivedValue();

  // dynamic pointer
  if(NULL != deepcopy.getDerivedPointer()){

    // alloc new memory
    T* tmp = new T;
    *tmp = *(deepcopy.getDerivedPointer());

    // discard old memory
    delete derivedPointer; derivedPointer = NULL;

    // set to new memory
    derivedPointer = tmp;
  }

  return *this;
}





/*
  main
//*/
int main()
{
  // init
  Derived<std::string> op1(12, "buckle my shoe", 34, "knock at the door");
  Derived<std::string> op2(0, "", 0, "");

  // output - before
  std::cout << "object 1:\n";
  op1.getAll();
  std::cout << std::endl;

  std::cout << "object 2:\n";
  op2.getAll();
  std::cout << std::endl;


  // usage: assignment operator
  std::cout << "object 2 = object 1\n\n";
  op2 = op1;


  // output - after
  std::cout << "object 1:\n";
  op1.getAll();
  std::cout << std::endl;

  std::cout << "object 2:\n";
  op2.getAll();
  std::cout << std::endl;

  std::cout << "READY.\n";
  return 0;
}
