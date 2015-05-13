// someclass.hpp
/*******************************************************************************
 *           Classes SomeClass and SomeClassValue (from pp. 204, 206-207)      *
 *******************************************************************************

annotations:

  class to be used by application developers
  COW = copy on write

  the names were changed from "String" to "SomeClass" since I found it a bit 
  confusing ;)
*/


#ifndef SOMECLASS
#define SOMECLASS


#include <iostream>
#include <cstring>


#include "rcobject.hpp"
#include "rcptr.hpp"


// forward declarations
class SomeClass;


std::ostream& operator<<(std::ostream& out, const SomeClass& sc);



class SomeClass 
{ 
public: 
  // ctor
  SomeClass(const char *value = "");

  // COW support
  char operator[](int index) const;       
  char& operator[](int index);
  
private:

  // class representing the data which can be shared
  struct SomeClassValue: public RCObject 
  {
    char *data;

    // ctor
    SomeClassValue(const char *initValue);
    
    // copy ctor
    SomeClassValue(const SomeClassValue& rhs);

    // dtor
    ~SomeClassValue();

    void init(const char *initValue);
  };

  // (smart) pointer to the value object
  RCPtr<SomeClassValue> value;                       
  
  // This function is not in the book, but it's convenient for testing the
  // class -- see below.
  friend 
  std::ostream& operator<<(std::ostream& out, const SomeClass& sc);
};

#endif


