// opstreams.cpp
/*
  If func() is operator>> or operator<<, func() has to be global. In case func()
needs access to private elements of SomeClass, func() has to be declared as
"friend"-Function of SomeClass.

  - virtual functions have to be element functions
  - operator>> and operator<< never are element functions
  - only global functions allow implicit typeconversion of the left argument
  - all other functions have to be element functions

  resource: Effective C++ / 19 / Meyers


  interesting:
  If the operator<<() is not implemented as reference and the SomeClass<T>
variable is passed by-value, another second destructor call happens. The problem
is, that a first call to the dtor is able to delete the pointer pData, but is
not able to set it to NULL. Hence a second call tries to delete this already
deleted pData pointer which is NOT NULL at that point! -> double free situation.
//*/


#include <cstdlib>
#include <iostream>
#include <string>


/*
  forward declaration
//*/
template < class T >
class SomeClass;

template < class T >
std::ostream &operator<<(std::ostream &output, SomeClass< T > &sc);

template < class T >
std::istream &operator>>(std::istream &input, SomeClass< T > &sc);


/*
  some class
//*/
template < class T >
class SomeClass
{
private:
  T *pData;

public:
  SomeClass(T t);
  SomeClass(SomeClass< T > const &shallowcopy);
  SomeClass< T > &operator=(const SomeClass< T > &deepcopy);

  ~SomeClass();

  // func
  void setData(T t);
  T getData() const;

  // friend - operators
  //* operator<<
  friend std::ostream &operator<<< T >(std::ostream &output,
                                       SomeClass< T > &sc);
  //*/

  //* operator>>
  friend std::istream &operator>>< T >(std::istream &input, SomeClass< T > &sc);
  //*/
};

template < class T >
SomeClass< T >::SomeClass(T t) : pData(NULL)
{
  std::cout << "ctor\n";

  // allocate memory
  try {
    pData = new T;
  } catch (...) {
    std::cerr << "ERROR: allocation failed!" << std::endl;
    delete pData;
    pData = NULL;
    exit(-1);
  }

  setData(t);
}

/*
  copy constructor - shallow copy
//*/
template < class T >
SomeClass< T >::SomeClass(SomeClass< T > const &shallowcopy) : pData(NULL)
{
  *pData = shallowcopy.getData();
}

/*
  operator= - deep copy
//*/
template < class T >
SomeClass< T > &SomeClass< T >::operator=(const SomeClass< T > &deepcopy)
{
  // check
  if (this == &deepcopy)
    return *this;

  // allocate new
  T *ptr = NULL;
  try {
    ptr = new T;
  } catch (...) {
    std::cerr << "ERROR: allocation failed!" << std::endl;
    delete pData;
    pData = NULL;
    exit(-1);
  }

  *ptr = deepcopy.getData();

  // free old
  delete pData;
  pData = NULL;

  // assign values
  pData = ptr;

  return *this;
}

template < class T >
SomeClass< T >::~SomeClass()
{
  std::cout << "dtor\n";

  delete pData;
  pData = NULL;
}

template < class T >
void SomeClass< T >::setData(T t)
{
  *pData = t;
}

template < class T >
T SomeClass< T >::getData() const
{
  return *pData;
}


/*
  writes from the specified class into the output stream
//*/
template < class T >
std::ostream &operator<<(std::ostream &output, SomeClass< T > &sc)
{
  return output << sc.getData();
}

/*
  reads from the specified class into the input stream
//*/
template < class T >
std::istream &operator>>(std::istream &input, SomeClass< T > &sc)
{
  // read the value out of sc into the istream object
  if (NULL == sc.pData) {
    try {
      sc.pData = new T;
    } catch (...) {
      std::cerr << "error allocation failed!\n";
      delete sc.pData;
      sc.pData = NULL;
      exit(-1);
    }
  }

  input >> *sc.pData;

  return input;
}


/*
  some main()
//*/
int main()
{
  // init
  SomeClass< std::string > sc = SomeClass< std::string >("");

  // operator>>
  std::cout << "operator>> - enter something to be read into the object:\n> ";
  std::cin >> sc;
  std::cout << std::endl;

  // operator<<
  std::cout << "operator<< - the entered text was:\n> ";
  std::cout << "\"" << sc << "\"" << std::endl;
  std::cout << "it only read in the first word!\n";

  std::cout << "READY.\n";
  return 0;
}
