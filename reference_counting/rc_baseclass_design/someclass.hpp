// someclass.hpp
/*
  Class to be used by application developers
//*/

#ifndef SOME_CLASS
#define SOME_CLASS

#include <iostream>
#include <cstdlib>
#include <cstring>

#include "rcbaseobject.hpp"
#include "rcptr.hpp"


/*
  forward declarations
//*/
class SomeClass;

std::ostream& operator<<(std::ostream& out, SomeClass& obj);

template<class T> class RCPtr;


/*
  class definition
//*/
class SomeClass
{
public: 
  // ctor
  SomeClass(const char *value = "");
  ~SomeClass();
  
  // copy on write - operator[]
  const char& operator[](int index) const;
  char& operator[](int index);

  // ouput accessibility
  friend
  std::ostream& operator<<(std::ostream& out, SomeClass& obj);

private:
  /*
    The following class represents the treated values

    This class is deduced from RCBaseObject, the here used abstract class 
    for reference counting.
  //*/
  struct SomeClassValue: public RCBaseObject 
  {
    char *data;

    // ref count ctor
    SomeClassValue(const char *initValue);

    // ref count copy ctor
    SomeClassValue(const SomeClassValue& rhs);

    // ref count dtor
    ~SomeClassValue();

    void init(const char *initValue);
  };

  /*
    reference count pointer here as smart pointer
  //*/
  RCPtr<SomeClassValue> value;
};

#endif
